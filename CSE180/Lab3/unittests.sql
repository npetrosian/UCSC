INSERT INTO Tickets VALUES (555, 1, DATE '2017-06-23', TIME '12:00:00', 1, 8.50); 
INSERT INTO Tickets VALUES (111, 5, DATE '2009-06-23', TIME '11:00:00', 17, 8.50); 
INSERT INTO Tickets VALUES (222, 3, DATE '2019-06-24', TIME '10:00:00', 12, 5.00);

UPDATE Tickets
SET ticketPrice = 5.00
WHERE theaterID = 333;

UPDATE Tickets
SET ticketPrice = -5.00
WHERE theaterID = 333;

UPDATE Customers
SET joinDate = DATE '2015-12-01'
WHERE customerID = 1;

UPDATE Customers
SET joinDate = DATE '2014-11-27'
WHERE customerID = 1;

UPDATE Showings
SET movieID = NULL
WHERE priceCode = 'A';

UPDATE Showings
SET priceCode = NULL
WHERE movieID = 22358;