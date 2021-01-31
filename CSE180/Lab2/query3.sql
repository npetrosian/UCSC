-- Query 3
-- Find the ID, name, year and length for every movie which was longer than the 2011 movie Avengers. 
-- In your result, movies with the largest year should appear first; 
-- within each year, movies should be in alphabetized by name. 
-- No duplicates should appear in your answer.

SELECT M1.movieID, M1.name, M1.year, M1.length
FROM Movies M1, Movies M2
WHERE M2.name = 'Avengers'
	AND M2.year = 2011
	AND M1.length > M2.length
ORDER BY M1.year DESC, M1.name;