-- A SQL query to list the names of all people who have directed a movie that
-- received a rating of at least 9.0.

-- Select names
SELECT name FROM people
WHERE id IN
(
    -- Select person IDs from directors
    SELECT person_id FROM directors
    WHERE movie_id IN
    (
        -- Who have a movie with a rating greater than or equal to 9.0
        SELECT movie_id FROM ratings
        WHERE rating >= 9.0
    )
);
