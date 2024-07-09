-- A SQL query to list all movies released in 2010 and their ratings, in descending order by rating.
-- For movies with the same rating, order them alphabetically by title.

-- Join movies and ratings table where release year is 2010 & show title with rating
SELECT title, rating FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE year = 2010
-- Two levels of sorting, first by rating, then by title
ORDER BY rating DESC, title ASC;
