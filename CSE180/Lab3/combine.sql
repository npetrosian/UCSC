BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
UPDATE Showings S
SET movieID = MS.movieID
FROM ModifyShowings MS
WHERE S.theaterID = MS.theaterID
AND S.showingDate = MS.showingDate
AND S.startTime = MS.startTime;

INSERT INTO Showings(theaterID, showingDate, startTime, movieID, priceCode)
SELECT MS.theaterID, MS.showingDate, MS.startTime, MS.movieID, NULL
FROM ModifyShowings MS
WHERE (theaterID, showingDate, startTime) NOT IN (
	SELECT theaterID, showingDate, startTime 
	FROM Showings S
);
COMMIT;