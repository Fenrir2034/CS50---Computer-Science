-- Titles of the five highest-rated movies that Chadwick Boseman starred in.
SELECT title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN ratings ON movies.id = ratings.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;
