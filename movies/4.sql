SELECT COUNT(TITLE)
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE rating = 10.0;