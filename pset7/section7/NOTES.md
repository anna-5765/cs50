SQL & Databases
Why Databases?
    - scale
    - frequency
    - speed
- A Database Management System is software via which you can interact with a database (DMS)
    - MySQL
    - Oracle
    - PostgreSQL
    - SQLite
- SQL is a language via wihich you can create, read, update and delete data in a database
    - note storage of dates is in a certain format
    - try and have tables that store only one thing
        - books & author table so we werent duplicating names of authors
        - now need relationship between tables to relate book with author, this is a primary key, or used in another table, a foreign key
        - created a third table, authored, with the author_id and book_id to associate book to author
- Design principles
    - create one table for each entity in your dataset
    - all tables should have a primary key
    - the information in the table should depend on the primary key only

sqlite> CREATE TABLE table_name (
    ...> column0 INTEGER,
    ...> column1 TEXT,
    ...> column2 NUMERIC, (flexible, includes dates)
    ...> column3 REAL
    ...> PRIMARY KEY(column0)
    ...> );

use .shcema table_name to check
use ctrl + l to clear terminal

you can create a primary key of the combination of two primary keys like in the authored table
    - PRIMARY KEY(author_id, book_id)
      FOREIGN KEY(author_id) REFERENCES authors(id),
      FOREIGN KEY(book_id) REFERENCES books(id)

use .tables to check tables made

Inserting and Deleting
sqlite> INSERT INTO table (column0, column1)
   ...> VALUES(value0, value1);

sqlite> DELETE FROM table
   ...> WHERE condition;

   ex. DELETE FROM books WHERE title = 'Flights';

***NEVER*** DELETE FROM table; ***UNLESS*** you actually want to delete the entire table ***VERY DESTRUCTIVE***

use .quit to leave sqlite

Pset7 Songs
Helpful hints:
SELECT * FROM songs; see everything
.schema songs to get create info
SELECT name FROM songs LIMIT 5;
you can have two terminals open, one for sql, one for regular
.read 1.sql in sqlite terminal will execute command
.tables to see tables involved
code 1.sql to add code
SELECT, WHERE, LIKE, ORDER BY
all sql satements begin with SELECT
2
SELECT name, tempo FROM songs ORDER BY tempo;
3
SELECT name, duration_ms, FROM songs, ORDER BY duration_ms DESC, LIMIT 5; (could enter in place of commas, don't do commas)
4
SELECT name, danceability, energy, valence
FROM songs
LIMIT 1;
SELECT name
FROM songs
WHERE danceability > 0.75
AND energy > 0.75
AND valence > 0.75;
5
SELECT energy FROM songs;
use aggregate functions to calculate from multiple lines of data
SELECT AVG(), SELECT MIN(), SELECT COUNT(), etc.
SELECT AVG(energy)
From songs
SELECT ROUND(AVG(energy), 2) FROM songs; (round to two decimals)
6
Combining tables using subqueries and joins
SELECT name
FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE name = 'Post Malone'
    );
7
see multiple information from different tables using JOIN
SELECT songs.name, energy, artists.name
FROM songs
JOIN artists ON artists.id = songs.artist_id
WHERE artists.name = 'Drake';
SELECT AVG(energy) ...
8
SELECT name
FROM songs
WHERE name LIKE '%feat.%' (percent on both ends means anywhere in word)

find mode
SELECT artists.name, COUNT(artists.name)
FROM songs
JOIN artists ON artists.id = songs.artists_id
GROUP BY artists.name;






