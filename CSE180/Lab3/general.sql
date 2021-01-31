ALTER TABLE Tickets ADD CONSTRAINT positive_ticketPrice CHECK (ticketPrice > 0);

ALTER TABLE Customers ADD CHECK (joinDate >= DATE '2015-11-27');

ALTER TABLE Showings ADD CHECK (
	CASE 
		WHEN movieID IS NOT NULL THEN priceCode IS NOT NULL
	END);