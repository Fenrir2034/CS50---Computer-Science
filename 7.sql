-- Movies released in 2010 and their ratings, in descending order by rating.
SELECT title, rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010 AND rating IS NOT NULL
ORDER BY rating DESC, title;
