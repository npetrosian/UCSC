airport( atl, 'Atlanta         ', degmin(  33,39 ), degmin(  84,25 ) ).
airport( bos, 'Boston-Logan    ', degmin(  42,22 ), degmin(  71, 2 ) ).
airport( chi, 'Chicago         ', degmin(  42, 0 ), degmin(  87,53 ) ).
airport( den, 'Denver-Stapleton', degmin(  39,45 ), degmin( 104,52 ) ).
airport( dfw, 'Dallas-Ft.Worth ', degmin(  32,54 ), degmin(  97, 2 ) ).
airport( lax, 'Los Angeles     ', degmin(  33,57 ), degmin( 118,24 ) ).
airport( mia, 'Miami           ', degmin(  25,49 ), degmin(  80,17 ) ).
airport( nyc, 'New York City   ', degmin(  40,46 ), degmin(  73,59 ) ).
airport( sea, 'Seattle-Tacoma  ', degmin(  47,27 ), degmin( 122,17 ) ).
airport( sfo, 'San Francisco   ', degmin(  37,37 ), degmin( 122,23 ) ).
airport( sjc, 'San Jose        ', degmin(  37,22 ), degmin( 121,56 ) ).

flight( bos, nyc, time( 7,30 ) ).
flight( dfw, den, time( 8, 0 ) ).
flight( atl, lax, time( 8,30 ) ).
flight( chi, den, time( 8,45 ) ).
flight( mia, atl, time( 9, 0 ) ).
flight( sfo, lax, time( 9, 0 ) ).
flight( sea, den, time( 10, 0 ) ).
flight( nyc, chi, time( 11, 0 ) ).
flight( sea, lax, time( 11, 0 ) ).
flight( den, dfw, time( 11,15 ) ).
flight( sjc, lax, time( 11,15 ) ).
flight( atl, lax, time( 11,30 ) ).
flight( atl, mia, time( 11,30 ) ).
flight( chi, nyc, time( 12, 0 ) ).
flight( lax, atl, time( 12, 0 ) ).
flight( lax, sfo, time( 12, 0 ) ).
flight( lax, sjc, time( 12, 15 ) ).
flight( nyc, bos, time( 12,15 ) ).
flight( bos, nyc, time( 12,30 ) ).
flight( den, chi, time( 12,30 ) ).
flight( dfw, den, time( 12,30 ) ).
flight( mia, atl, time( 13, 0 ) ).
flight( sjc, lax, time( 13,15 ) ).
flight( lax, sea, time( 13,30 ) ).
flight( chi, den, time( 14, 0 ) ).
flight( lax, nyc, time( 14, 0 ) ).
flight( sfo, lax, time( 14, 0 ) ).
flight( atl, lax, time( 14,30 ) ).
flight( lax, atl, time( 15, 0 ) ).
flight( nyc, chi, time( 15, 0 ) ).
flight( nyc, lax, time( 15, 0 ) ).
flight( den, dfw, time( 15,15 ) ).
flight( lax, sjc, time( 15,30 ) ).
flight( chi, nyc, time( 18, 0 ) ).
flight( lax, atl, time( 18, 0 ) ).
flight( lax, sfo, time( 18, 0 ) ).
flight( nyc, bos, time( 18, 0 ) ).
flight( sfo, lax, time( 18, 0 ) ).
flight( sjc, lax, time( 18,15 ) ).
flight( atl, mia, time( 18,30 ) ).
flight( den, chi, time( 18,30 ) ).
flight( lax, sjc, time( 19,30 ) ).
flight( lax, sfo, time( 20, 0 ) ).
flight( lax, sea, time( 22,30 ) ).

minutes_to_hours(Minutes, Hours) :- Hours is Minutes / 60.

time_to_minutes(time(Hours, Minutes), Time) :-hours_to_minutes(X, Hours),  Time is  X + Minutes. 

minutes_to_time(time(Hours, Minutes), Time) :- Hours is floor(Time/60), Minutes is Time rem 60.
 

hours_to_minutes(Minutes, Hours) :- Minutes is Hours * 60.



haversine(Latitude1, Longitude1, Latitude2, Longitude2, Distance) :-
   Dlongitude is Longitude2 - Longitude1,
   Dlatitude is Latitude2 - Latitude1,
   A is sin(Dlatitude / 2) ** 2 + cos(Latitude1) * cos(Latitude2) * sin(Dlongitude / 2) ** 2,
   C is 2 * atan2(sqrt(A), sqrt(1-A)),
   Distance is 3956 * C.

convert_degree_radians(Degrees, Minutes, Radians) :- Radians is (Degrees + (Minutes/60)) * pi/180.

airport_distance(Airport1, Airport2, Distance) :- airport(Airport1, _, degmin(LatDeg1, LatMin1), degmin(LongDeg1, LongMin1)),
                                           airport(Airport2, _, degmin(LatDeg2, LatMin2), degmin(LongDeg2, LongMin2)),
                                           convert_degree_radians(LatDeg1, LatMin1, Lat1), convert_degree_radians(LongDeg1, LongMin1, Long1),
                                           convert_degree_radians(LatDeg2, LatMin2, Lat2), convert_degree_radians(LongDeg2, LongMin2, Long2),
                                           haversine(Lat1, Long1, Lat2, Long2, Distance). 
                                           
flight_time(Airport1, Airport2, FlightTime) :-
    airport_distance(Airport1, Airport2, Distance),
    FlightTime is Distance / 500.

fly(Departure,Arrival) :-
   findFlights(Departure, Arrival, 0, 0,X ),   
   printFlights(X).

print_trip( Action, Code, Name, time( Hour, Minute)) :-
   upcase_atom( Code, Upper_code),
   format( "~6s  ~3s  ~s~26|  ~`0t~d~30|:~`0t~d~33|",
           [Action, Upper_code, Name, Hour, Minute]),
   nl.

test :-
   print_trip( depart, nyc, 'New York City', time( 9, 3)),
   print_trip( arrive, lax, 'Los Angeles', time( 14, 22)).

doSomething(nyc,lax) :- test.

printFlights([]).
printFlights([[Source, Dest, DepartHour, DepartMin, ArrivalHour, ArrivalMin]|Flights]) :-  
airport( Source, SourceName, _, _), 
airport( Dest, DestName, _, _), 
print_trip(depart, Source, SourceName, time(DepartHour, DepartMin)),
print_trip(arrive, Dest, DestName, time(ArrivalHour, ArrivalMin)),
printFlights(Flights).

main :- read(A),read(B), fly(A, B).

findFlights(Destination, Destination, _, _, []) :- !.
findFlights(Source, Destination, CurHour, CurMin, [[Source, Stop, DepartHour, DepartMin, ArrivalHour, ArrivalMin]|Flights]) :- 
   % Checking that Source != Destination (Sanity Check)
   Source \= Destination,
   % Finding any flight that departs from Source at least 30 minutes after the current time
   flight(Source, Stop, time(DepartHour, DepartMin)),
   time_to_minutes(time(CurHour, CurMin), CurrentMin), 
   time_to_minutes(time(DepartHour, DepartMin), ProposedMin),
   BufferedTime is CurrentMin + 30,
   BufferedTime < ProposedMin,
   % Computing the duration of flight 
   flight_time(Source, Stop, FlightTime),
   % Converting to Minutes 
   hours_to_minutes(FlightDurationMinutes, FlightTime),
   FlooredFlightDuration is floor(FlightDurationMinutes),
   % Computing Arrival Time (Departure Time + Duration)
   ArrivalMinutes is ProposedMin + FlooredFlightDuration,
   % Convert Arrival Time to Minutes
   minutes_to_time(time(ArrivalHour, ArrivalMin), ArrivalMinutes),
   % Recursive Call
   % Cut is to only return the first flight path founds. If removed will return all possible paths.
   findFlights(Stop, Destination, ArrivalHour, ArrivalMin, Flights), !.
   % Need to print outside of exectution
  

