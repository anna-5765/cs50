import csv

books = []

# Add books to shelf by reading from books.csv (doesn't exist atm)
with open("books.csv") as file:
    reader = csv.DictReader(file) # need keys in top row
    for row in reader:
        books.append(row)
    # text = file.read()
    # print(text)
