-- Query 2
-- Find the name and year of all movies for which a customer named Donald Duck bought a ticket. 
-- No duplicates should appear in your answer.

SELECT DISTINCT M.name, M.year
FROM Movies M, Tickets T, Showings S, Customers C
WHERE T.theaterID = S.theaterID
AND T.showingDate = S.showingDate
AND T.startTime = S.startTime
AND S.movieID = M.movieID 
AND C.name = 'Donald Duck'
AND C.customerID = T.customerID;

