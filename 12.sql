-- Titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
SELECT title
FROM movies
JOIN stars AS sc ON movies.id = sc.movie_id
JOIN people AS pc ON sc.person_id = pc.id
JOIN stars AS sl ON movies.id = sl.movie_id
JOIN people AS pl ON sl.person_id = pl.id
WHERE (pc.name = 'Bradley Cooper' AND sl.movie_id = sc.movie_id AND pl.name = 'Jennifer Lawrence')
ORDER BY title;
