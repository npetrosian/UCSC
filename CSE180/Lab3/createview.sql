CREATE VIEW earningsView AS 
SELECT M.movieID, SUM(T.ticketPrice) AS computedEarnings
FROM Movies M, Tickets T, Showings S
WHERE S.theaterID = T.theaterID
AND S.showingDate = T.showingDate
AND S.startTime = T.startTime
AND M.movieID = S.movieID
GROUP BY M.movieID;

CREATE VIEW temp AS 
SELECT DISTINCT movieID FROM Showings
WHERE movieID NOT IN (SELECT movieID FROM earningsView);

SELECT * FROM earningsView
UNION
SELECT temp.movieID, 0 as computedEarnings FROM temp, Showings S
WHERE temp.movieID = S.movieID
AND (S.theaterID, S.showingDate, S.startTime) NOT IN (SELECT T.theaterID, T.showingDate, T.startTime FROM Tickets T);
