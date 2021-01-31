DROP SCHEMA "Lab1" CASCADE;
CREATE SCHEMA "Lab1";

CREATE TABLE Movies (
	movieID INTEGER,
	name VARCHAR(30),
	year INTEGER,
	rating CHAR(1),
	length INTEGER,
	totalEarned NUMERIC(7,2),
	PRIMARY KEY(movieID)
);

CREATE TABLE Theaters (
	theaterID INTEGER,
	address VARCHAR(40),
	numSeats INTEGER,
	PRIMARY KEY(theaterID)
);

CREATE TABLE TheaterSeats (
	theaterID INTEGER,
	seatNum INTEGER,
	brokenSeat BOOLEAN,
	PRIMARY KEY(theaterID, seatNum),
	FOREIGN KEY(theaterID) REFERENCES Theaters
);

CREATE TABLE Showings (
	theaterID INTEGER,
	showingDate DATE,
	startTime TIME,
	movieID INTEGER,
	priceCode CHAR(1),
	PRIMARY KEY(theaterID, showingDate, startTime),
	FOREIGN KEY(theaterID) REFERENCES Theaters,
	FOREIGN KEY(movieID) REFERENCES Movies

);

CREATE TABLE Customers (
	customerID INTEGER,
	name VARCHAR(30),
	address VARCHAR(40),
	joinDate DATE,
	status CHAR(1),
	PRIMARY KEY(customerID)
);

CREATE TABLE Tickets (
	theaterID INTEGER,
	seatNum INTEGER,
	showingDate DATE,
	startTime TIME,
	customerID INTEGER,
	ticketPrice NUMERIC(4,2),
	PRIMARY KEY(theaterID, seatNum, showingDate, startTime),
	FOREIGN KEY(theaterID,showingDate,startTime) REFERENCES Showings,
	FOREIGN KEY(theaterID,seatNum) REFERENCES TheaterSeats,
	FOREIGN KEY(customerID) REFERENCES Customers
);