-- A SQL query to list the names of all people who starred in a movie
-- released in 2004, ordered by birth year.

-- Select names
SELECT DISTINCT name FROM people
-- Join people with what movies they've starred in
JOIN stars ON stars.person_id = people.id
-- Filter by movies released in 2004
WHERE stars.movie_id IN (
    SELECT id FROM movies WHERE year = 2004)
-- Order names by birth year
ORDER BY people.birth;

-- -- Use nested queries
-- SELECT DISTINCT name FROM people
-- WHERE id IN (
--     SELECT person_id FROM stars
--     WHERE movie_id IN (
--         SELECT id FROM movies
--         WHERE year = 2004
--         )
--     )
-- ORDER BY birth;

