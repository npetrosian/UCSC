-- Query 4
-- Find the ID and name of each customer whose name has the letter ‘a’ or ‘A’ anywhere in it, 
-- and who bought tickets to at least 2 different movies. Careful; a customer who bought 2 or more 
-- tickets to the same movie doesn't qualify. 
-- No duplicates should appear in your answer
SELECT C.customerID, C.name
FROM Customers C
WHERE (C.name LIKE '%a%' OR C.name LIKE '%A%')
AND C.customerID IN (
			SELECT C.customerID from Customers C, Tickets T, Showings S
			WHERE C.customerID = T.customerID
			AND T.theaterID = S.theaterID
			AND T.showingDate = S.showingDate
			AND T.startTime = S.startTime
			GROUP BY C.customerID
			HAVING COUNT(C.customerID) >= 2

);


