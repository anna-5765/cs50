-- A SQL query to list the names of all people who starred in Toy Story.

-- Select names
SELECT name FROM people
-- Link names to what movies they've starred in
JOIN stars ON stars.person_id = people.id
-- Find stars in Toy Story
WHERE stars.movie_id = (
    SELECT id FROM movies WHERE title = 'Toy Story'
    );
