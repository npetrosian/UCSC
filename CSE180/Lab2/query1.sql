-- Query 1
-- Find the ID and address for all the theaters that have a broken seat. 
-- No duplicates should appear in your answer.

SELECT DISTINCT T.theaterID, address
FROM Theaters T, TheaterSeats TS
WHERE TS.brokenSeat = TRUE
AND T.theaterID = TS.theaterID;