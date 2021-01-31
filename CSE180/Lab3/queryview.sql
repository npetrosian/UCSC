SELECT M.rating, COUNT(*) AS misreportCount
FROM Movies M, earningsView E
WHERE M.movieID = E.movieID
AND M.year < 2019
AND M.totalEarned<>E.computedEarnings
GROUP BY M.rating;

--output before deletions

/*
rating | misreportcount 
--------+----------------
 G      |              1
 R      |              1
(2 rows)
*/

DELETE FROM tickets 
where theaterID = 111 
and seatNum = 2 
and showingDate = DATE'2009-06-23' 
and startTime = TIME '11:00:00';

DELETE FROM tickets 
where theaterID = 444 
and seatNum = 5 
and showingDate = DATE'2020-06-24' 
and startTime = TIME '15:00:00';

--output after deletions

/*
rating | misreportcount 
--------+----------------
 G      |              1
 R      |              1
(2 rows)
*/

SELECT M.rating, COUNT(*) AS misreportCount
FROM Movies M, earningsView E
WHERE M.movieID = E.movieID
AND M.year < 2019
AND M.totalEarned<>E.computedEarnings
GROUP BY M.rating;
