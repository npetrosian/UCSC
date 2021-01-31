import java.sql.*;
import java.io.*;
import java.util.*;

/**
 * A class that connects to PostgreSQL and disconnects.
 * You will need to change your credentials below, to match the usename and password of your account
 * in the PostgreSQL server.
 * The name of your database in the server is the same as your username.
 * You are asked to include code that tests the methods of the MovieTheaterApplication class
 * in a similar manner to the sample RunFilmsApplication.java program.
*/


public class RunMovieTheaterApplication
{
    public static void main(String[] args) {
    	
    	Connection connection = null;
    	try {
    	    //Register the driver
    		Class.forName("org.postgresql.Driver"); 
    	    // Make the connection.
            // You will need to fill in your real username (twice) and password for your
            // Postgres account in the arguments of the getConnection method below.
            connection = DriverManager.getConnection(
                                                     "jdbc:postgresql://cse180-db.lt.ucsc.edu/npetrosi",
                                                     "npetrosi",
                                                     "");
            
            if (connection != null)
                System.out.println("Connected to the database!");

            /* Include your code below to test the methods of the MovieTheaterApplication class.
             * The sample code in RunFilmsApplication.java should be useful.
             * That code tests other methods for a different database schema.
             * Your code below: */
            

            MovieTheaterApplication app = new MovieTheaterApplication(connection);
            int rowCount = app.getShowingsCount("B");
            System.out.println("/*");
            System.out.println("* Output of getShowingsCount");
            System.out.println("* when the paramter thePriceCode is 'B'.");
            System.out.println(rowCount);
            System.out.println("*/");

            /*
            * Output of getShowingsCount
            * when the parameter thePriceCode is 'B'.
            * 8
            */

            int nameResult = app.updateMovieName(101, "Avatar 1");
            System.out.println("/*");
            System.out.println("* Output of updateMovieName when theMovieID is 101");
            System.out.println("* and newMovieName is 'Avatar 1'");
            System.out.println(nameResult);
            System.out.println("*/");


            /*
            * Output of updateMovieName when theMovieID is 101
            * and newMovieName is 'Avatar 1'
            * 
            * 1
            */

            int nameResult2 = app.updateMovieName(888, "Star Wars: A New Hope");
            System.out.println("/*");
            System.out.println("* Output of updateMovieName when theMovieID is 888");
            System.out.println("* and newMovieName is 'Star Wars: A New Hope'.");
            System.out.println(nameResult2);
            System.out.println("*/");

            /*
            * Output of updateMovieName when theMovieID is 888
            * and newMovieName is 'Star Wars: A New Hope'
            * 
            * 0
            */
            
            /*******************


            


            * Your code ends here */
            int reduceSomeTicketPricesresult1 = app.reduceSomeTicketPrices(15);
            System.out.println("/*");
            System.out.println("* Output of reduceSomeTicketPrices when maxTicketCount is 15");
            System.out.println(reduceSomeTicketPricesresult1);
            System.out.println("*/");

            /*
            * Output of reduceSomeTicketPrices when maxTicketCount is 15
            * 43
            */

            int reduceSomeTicketPricesresult2 = app.reduceSomeTicketPrices(99);
            System.out.println("/*");
            System.out.println("* Output of reduceSomeTicketPrices when maxTicketCount is 99");
            System.out.println(reduceSomeTicketPricesresult2);
            System.out.println("*/");

            /*
            * Output of reduceSomeTicketPrices when maxTicketCount is 888
            * 76
            */
            
    	}
    	catch (SQLException | ClassNotFoundException e) {
    		System.out.println("Error while connecting to database: " + e);
    		e.printStackTrace();
    	}
    	finally {
    		if (connection != null) {
    			// Closing Connection
    			try {
					connection.close();
				} catch (SQLException e) {
					System.out.println("Failed to close connection: " + e);
					e.printStackTrace();
				}
    		}
    	}
    }
}
