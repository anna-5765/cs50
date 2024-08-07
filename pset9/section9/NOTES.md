Flask
- listen for requests to a certain route
- execute python code depending on route requested
- render html files depending on route requested

Flask functions
render_template: flask takes html file, rendors it, adds data, and shows data back to us

@ is decorator to add to function with something you specify (@app.route)

Request Methods:
GET: client asks for information (get something from server)
POST: client can send data to server and server can do something with it (post something to server)

HTML:
add ability to interact with user info into html tags
action="/" route to request
method="post" method to access route
use request.form.get("<name from html form>") to get html form element in python

Python and SQL:
defined db as SQL database file .db
can use db.execute("<insert SQL code here>") to run sql in python once connection to SQL and database defined
cs50 sql library based on sqlalchemy
long queries may use this syntax with the triple quotes for better readability:
db.execute("""
    INSERT INTO birthdays (name, month, day)
    VALUES(?,?,?), name, month, day)
    """)
make sure to handle possible user info that is not expected, like missing values, numbers outside of possible months, etc.
to render info in index.html, use Flask's render_template function. specify what should be rendered in html then what it is equal to in python.
ex. return render_template("index.html", birthdays=rows) where birthdays is in the jinja for loop in python and rows is equal to db.execute("SELECT * FROM birthdays")

Jinja templating syntax:
special kind of for loop {% for birthday in birthdays %}{{ birthdays.name }}{ % endfor %}
this goes in html like <tbody>, and probably also <tr> and <td>

Create purchases table for finance.db SQL queries:
CREATE TABLE purchases (purchase_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER NOT NULL, symbol TEXT NOT NULL, shares NUMERIC NOT NULL, share_price NUMERIC NOT NULL, time DATETIME, FOREIGN KEY (user_id) REFERENCES users(id));

INSERT INTO users (username, hash) VALUES (?, ?)


