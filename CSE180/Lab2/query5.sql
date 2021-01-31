-- Query 5
-- For each ticket for which all of the following are true:
-- 		a) the ticket was bought by a customer whose name starts with ‘D’ (capital D),
-- 		b) the ticket is for a showing whose price code isn't NULL, and
-- 		c) the ticket is on a date between June 1, 2019 and June 30, 2019 (including those dates), and
--		d) the ticket is for a theater that has more than 5 seats,
-- Output the ID, name and address of the customer, the address and number of seats of the theater, 
-- and the price code for the showing. The 6 attributes in your result should appear as custID, 
-- custName, custAddress, theaterAddress, theaterSeats and priceCode
-- No duplicates should appear in your result.

SELECT DISTINCT C.customerID AS custID, C.name AS custName, C.address AS custAddress, Th.address AS theaterAddress, Th.numSeats AS theaterSeats, S.priceCode AS priceCode
FROM Customers C, Tickets T, Theaters Th, Showings S
WHERE C.customerID = T.customerID
AND T.theaterID = S.theaterID
AND T.showingDate = S.showingDate
AND T.startTime = S.startTime
AND T.theaterID = Th.theaterID
AND C.name LIKE 'D%'
AND S.priceCode IS NOT NULL
AND S.showingDate BETWEEN DATE '2019-06-01' AND DATE '2019-06-30'
AND Th.numSeats > 5;
