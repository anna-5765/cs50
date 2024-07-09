-- A SQL query to list the titles of the five highest rated movies (in order)
-- that Chadwick Boseman starred in, starting with the highest rated.

-- Show title of movie
SELECT title FROM movies
-- Join movie titles and their ratings
JOIN ratings ON ratings.movie_id = movies.id
WHERE movies.id IN
(
    -- Find movies that star Chadwick Boseman
    SELECT movie_id FROM stars
    WHERE stars.person_id =
    (
        SELECT id FROM people
        WHERE name = 'Chadwick Boseman'
    )
)
-- Order top 5 by highest to lowest rating
ORDER BY rating DESC
LIMIT 5;
