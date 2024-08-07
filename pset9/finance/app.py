import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""

    # User reached route via POST (Add Cash)
    if request.method == "POST":

        # Get cash amount to add
        try:
            add_cash = int(request.form.get("amount"))
            if add_cash < 0:
                return apology("must enter positive integer", 400)
        except ValueError:
            return apology("must enter a valid number", 400)

        # Get current cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # Add amount requested
        new_balance = cash[0]["cash"] + add_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        flash("Cash Added!", "success")
        return redirect("/")

    # User reached route via GET
    else:

        # Add rows of purchases
        rows = db.execute("SELECT symbol, SUM(shares) AS total_shares, share_price FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        get_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = get_cash[0]["cash"]

        if not rows:
            return render_template("index.html", cash=cash, total=cash)

        # Show cash totals
        get_total = db.execute("SELECT SUM(CAST(shares AS NUMERIC) * CAST(share_price AS NUMERIC)) AS total FROM transactions WHERE user_id = ?", session["user_id"])
        total = get_cash[0]["cash"] + get_total[0]["total"]

        return render_template("index.html", rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST
    if request.method == "POST":

        # Get stock symbol
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("must enter stock symbol", 400)
        else:

            # Lookup price
            stock_info = lookup(symbol)
            if not stock_info:
                return apology("invalid stock symbol", 400)
            price = stock_info["price"]

        # Get number of shares
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("shares must be positive", 400)
        except ValueError:
            return apology("must enter a valid number", 400)

        # Purchase shares
        get_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = get_cash[0]["cash"]
        purchase_value = stock_info["price"] * shares
        if purchase_value > cash:
            return apology("must have sufficient cash", 400)
        else:

            # Add purchases to table
            db.execute("""
                       INSERT INTO transactions (user_id, symbol, shares, share_price, time)
                       VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)""",
                       session["user_id"], symbol, shares, price)

            # Update user cash amount
            new_balance = cash - purchase_value
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

            flash("Bought!", "success")
            return redirect("/")

    # User reached route via GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT symbol, shares, share_price, time FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST
    if request.method == "POST":

        # Get stock symbol
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("must enter stock symbol", 400)
        else:

            # Lookup price
            stock_info = lookup(symbol)
            if not stock_info:
                return apology("invalid stock symbol", 400)
            price = stock_info["price"]

            return render_template("quoted.html", symbol=symbol, amount=usd(price))

    # User reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST
    if request.method == "POST":

        # Get new username and password data from form
        new_username = request.form.get("username")
        new_password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        # Check that password is not blank and matches confirmation
        if not new_password:
            return apology("must enter a password", 400)
        if new_password != confirm_password:
            return apology("passwords do not match", 400)

        # Hash password
        hash_password = generate_password_hash(new_password)

        # Check that username is not blank or duplicate
        if not new_username:
            return apology("must enter a username", 400)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", new_username, hash_password)
        except ValueError:
            return apology("username already exists", 400)

       # Log user in
        get_id = db.execute("SELECT id FROM users WHERE username = ?", new_username)
        session["user_id"] = get_id[0]["id"]

        flash("Registered!", "success")
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST
    if request.method == "POST":

        # Get stock selected to sell
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must select a stock", 400)

        # Get amount of shares to sell
        owned_shares = db.execute("SELECT SUM(shares) AS total_shares FROM transactions WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])

        try:
            sell_shares = int(request.form.get("shares"))
            if sell_shares > owned_shares[0]["total_shares"]:
                return apology("cannot sell more shares than owned", 400)
            elif sell_shares < 0:
                return apology("must select positive integer", 400)
        except ValueError:
            return apology("must select amount to sell", 400)

        # Get value of sell
        stock_info = lookup(symbol)
        sell_value = sell_shares * stock_info["price"]

        # Add sell to table
        db.execute("""
                    INSERT INTO transactions (user_id, symbol, shares, share_price, time)
                    VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)""",
                    session["user_id"], symbol, -1 * sell_shares, stock_info["price"])

        # Update user cash amount
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        new_balance = cash[0]["cash"] + sell_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        flash("Sold!", "success")
        return redirect("/")

    else:

        # Lookup user stocks owned
        stocks = db.execute("SELECT DISTINCT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", session["user_id"])

        return render_template("sell.html", stocks=stocks)
