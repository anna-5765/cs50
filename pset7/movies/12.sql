-- A SQL query to list the titles of all movies in which both Bradley Cooper
-- and Jennifer Lawrence starred.

SELECT title FROM movies
WHERE id IN
(
    -- Get movies starring Bradley Cooper
    SELECT movie_id FROM stars
    WHERE person_id =
    (
        SELECT id FROM people
        WHERE name = 'Bradley Cooper'
    )
)
AND id IN
(
    -- Get movies starring Jennifer Lawrence
    SELECT movie_id FROM stars
    WHERE person_id =
    (
        SELECT id FROM people
        WHERE name = 'Jennifer Lawrence'
    )
);
