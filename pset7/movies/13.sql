-- A SQL query to list the names of all people who starred in a movie in which
-- Kevin Bacon also starred.

SELECT name FROM people
WHERE id IN
(
    -- Find star ids associated with Kevin Bacon movie ids
    SELECT person_id FROM stars
    WHERE movie_id IN
    (
        -- Find movie ids with Kevin Bacon (born in 1958) in them
        SELECT movie_id FROM stars
        JOIN people ON people.id = stars.person_id
        WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
    )
)
-- Exclude Kevin Bacon in results
AND name != 'Kevin Bacon';



