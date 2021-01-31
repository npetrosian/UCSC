ALTER TABLE Tickets
ADD CONSTRAINT fk_theaterID_showingDate_startTime
FOREIGN KEY (theaterID, showingDate, startTime) REFERENCES Showings(theaterID, showingDate, startTime);

ALTER TABLE Tickets
ADD CONSTRAINT fk_customerID
FOREIGN KEY (customerID) REFERENCES Customers(customerID)
ON DELETE SET NULL
ON UPDATE CASCADE;

ALTER TABLE Tickets
ADD CONSTRAINT fk_theaterID_seatNum
FOREIGN KEY (theaterID, seatNum) REFERENCES TheaterSeats(theaterID, seatNum)
ON DELETE CASCADE
ON UPDATE CASCADE;
