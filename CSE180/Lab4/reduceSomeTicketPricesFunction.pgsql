CREATE OR REPLACE FUNCTION reduceSomeTicketPricesFunction (maxTicketCount INTEGER)
RETURNS INTEGER AS $$

DECLARE
	priceReductionTotal INTEGER := 0;
	iterator INTEGER := 0;
	tID INTEGER;
	sD DATE;
	sT TIME;
	pC CHAR(1);
	tP NUMERIC(4,2);

DECLARE priceCodeA CURSOR FOR
	SELECT T.theaterID, T.showingDate, T.startTime, S.priceCode
	FROM Tickets T, Showings S
	WHERE T.theaterID = S.theaterID
	AND T.showingDate = S.showingDate
	AND T.startTime = S.startTime
	AND S.priceCode IS NOT NULL
	AND T.ticketPrice IS NOT NULL
	AND S.priceCode = 'A'
	ORDER BY T.customerID;

DECLARE priceCodeB CURSOR FOR
	SELECT T.theaterID, T.showingDate, T.startTime, S.priceCode
	FROM Tickets T, Showings S
	WHERE T.theaterID = S.theaterID
	AND T.showingDate = S.showingDate
	AND T.startTime = S.startTime
	AND S.priceCode IS NOT NULL
	AND T.ticketPrice IS NOT NULL
	AND S.priceCode = 'B'
	ORDER BY T.customerID;

DECLARE priceCodeC CURSOR FOR
	SELECT T.theaterID, T.showingDate, T.startTime, S.priceCode
	FROM Tickets T, Showings S
	WHERE T.theaterID = S.theaterID
	AND T.showingDate = S.showingDate
	AND T.startTime = S.startTime
	AND S.priceCode IS NOT NULL
	AND T.ticketPrice IS NOT NULL
	AND S.priceCode = 'C'
	ORDER BY T.customerID;

BEGIN

	OPEN priceCodeA;
	LOOP
		FETCH priceCodeA INTO tID, sD, sT, pC, tP;
		EXIT WHEN NOT FOUND OR iterator = maxTicketCount;
		UPDATE Tickets
		SET ticketPrice = ticketPrice - 3
		WHERE theaterID = tID
		AND showingDate = sD
		AND startTime = sT;

		iterator := iterator + 1;
		priceReductionTotal := priceReductionTotal + 3;
	END LOOP;
	CLOSE priceCodeA;

	OPEN priceCodeB;
	LOOP
		FETCH priceCodeB INTO tID, sD, sT, pC, tP;
		EXIT WHEN NOT FOUND OR iterator = maxTicketCount;
		UPDATE Tickets
		SET ticketPrice = ticketPrice - 2
		WHERE theaterID = tID
		AND showingDate = sD
		AND startTime = sT;

		iterator := iterator + 1;
		priceReductionTotal := priceReductionTotal + 2;
	END LOOP;
	CLOSE priceCodeB;

	OPEN priceCodeC;
	LOOP
		FETCH priceCodeC INTO tID, sD, sT, pC, tP;
		EXIT WHEN NOT FOUND OR iterator = maxTicketCount;
		UPDATE Tickets
		SET ticketPrice = ticketPrice - 1
		WHERE theaterID = tID
		AND showingDate = sD
		AND startTime = sT;

		iterator := iterator + 1;
		priceReductionTotal := priceReductionTotal + 1;
	END LOOP;
	CLOSE priceCodeC;
		
	RETURN priceReductionTotal;

END;
$$ 
LANGUAGE plpgsql

