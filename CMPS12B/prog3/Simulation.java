//-----------------------------------------------------------------------------
// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// File name: Simulation.java
// This file supplies the main functionality of this programming assignment
// by moving jobs around the queues and processing them from start to finish
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Simulation {
	
	// No fields
	
	// This method logs the banner with the processor count into the trace file
	public static void logProcessorBanner(int pNum, Writer w) throws IOException{
		// System.out.println("*****************************");
		w.write("*****************************\n");
		if (pNum == 1) {
			//System.out.println(pNum + " processor:");
			w.write(pNum + " processor:\n");
		} 
		else {
			//System.out.println(pNum + " processors:");
			w.write(pNum + " processors:\n");
		}		
		//System.out.println("*****************************");	
		w.write("*****************************\n");
	}
	
	// This method logs the header information into the trace file
	public static void logTraceHeaderInfo(Queue q, String firstLine, Writer w) throws IOException{	
		//System.out.println(firstLine);
		//System.out.println(q.length() + " Jobs:");
		//System.out.println(q);
		//System.out.println();
		
		w.write(firstLine + "\n");
		w.write(q.length() + " Jobs:" + "\n");
		w.write(q.toString() + "\n\n");
		
	}
	
	// This method logs the header info into the report file
	public static void logReportHeaderInfo(Queue q, String firstLine, Writer w) throws IOException{	
		w.write(firstLine + "\n");
		w.write(q.length() + " Jobs:" + "\n");
		w.write(q.toString() + "\n");
		w.write("\n");
		w.write("***********************************************************\n");
	}
	
	// This method logs the summary of the total wait time, max wait time and 
	// average wait time into the report file, as it dequeues nodes from the
	// finished queue
	public static void dequeueAndlogReportSummary(Queue f, int pNum, Writer w) throws IOException{	
		
		int maxWait=0;
		int totalWait=0;
		int numOfJobs = f.length();
		double avgWait=0.0;
		while (!f.isEmpty()) {
           Job j = (Job)f.dequeue();
           if (j.getWaitTime() > maxWait) {
               maxWait = j.getWaitTime();
           }
           totalWait +=  j.getWaitTime();
		}
		
		// need the casts to force a decimal point division
		avgWait = (double)totalWait/(double)numOfJobs;
		
		if (pNum==1) {
			w.write(pNum + " processor: ");
		} 
		else {
			w.write(pNum + " processors: ");
		}
		
		// Got the String.format trick from Google search
		w.write("totalWait=" + totalWait + ", maxWait=" + maxWait + ", averageWait=" + String.format("%.2f", avgWait));
		w.write("\n");
		
		
	}
	
	
	// This method logs the information that goes into the trace file
	public static void logTraceInfo(int pNum,int time, Queue notYetArrivedQ, Queue[] procQueues, Queue finishedQ, Writer w) throws IOException {
		
		//System.out.println("time=" + time);
		w.write("time=" + time + "\n");
		if (!notYetArrivedQ.isEmpty()) {
		       //System.out.println("0: " + notYetArrivedQ  + " " + finishedQ);
		       // w.write("0: " + notYetArrivedQ.toString()  + "-" + finishedQ.toString() + "\n");
		       w.write("0: " + notYetArrivedQ.toString() + finishedQ.toString() + "\n");
		} 
		else {
			   //System.out.println("0: " + finishedQ);
			   w.write("0: " + finishedQ.toString() + "\n");
		}
		for (int i = 0; i < pNum; i++) {
			//System.out.println(i+1 + ": " + procQueues[i]);
			w.write(i+1 + ": " + procQueues[i].toString() + "\n");
		}
		//System.out.println();
		w.write("\n");
		
	}
	
	// Copy Queue1 into Queue2 used to create the backup Queue
	public static void copyQueues(Queue q1, Queue q2) {
		Job o = null;
		while (!q1.isEmpty()) {
			o = (Job)q1.dequeue();
			// Can't just enqueue o from q1 and put it in q 2 for the 
			// next run because the wait time has been calculated
			// and we don't have a method to set it back to -1.
			// But if we create a NEW Job with the original arrival
			// and duration, the wait time will be -1 and we will be
			// good to start fresh run with again
			q2.enqueue(new Job(o.getArrival(), o.getDuration()));
		}
		
	}
	
	// Compute the finish time of all jobs who have moved to the front of the 
	// queues in the processor queues array
	public static void calculateFinishedTimeForAll(Queue[] qa, int time) {
		Job j = null;
		for (int i = 0; i < qa.length; i++) {
			if (!qa[i].isEmpty()) {
				j = (Job)qa[i].peek();
				if (j.getFinish() == -1) {
					j.computeFinishTime(time);
				}		
			}
		}	
	}
		
	// Move any job in the processing queue  whose finish time has arrived to the 
	// finishedQ
	public static void moveCompletedJobs(Queue[] qa, Queue finishedQ, int time) {
		Job j = null;
		Object o = null;
		for (int i = 0; i < qa.length; i++) {
			if (!qa[i].isEmpty()) {
				j = (Job)qa[i].peek();
				if (j.getFinish() == time) {
					o = qa[i].dequeue();
					finishedQ.enqueue(o);
				}		
			}
		}	
	}
	
	// Check to see if there are ANY jobs in front of all processing queues
	// that have reached their finish time
	public static boolean checkCompletedJobs(Queue[] qa, int time) {
		Job j = null;
		// check front jobs in processor queues
		for (int i = 0; i < qa.length; i++) {
			if (!qa[i].isEmpty()) {
				// peek the front queue
				j = (Job)qa[i].peek();
				// as soon as you find one that is ready
				// return true
				if (j.getFinish() == time) {
					return true;
				}		
			}
		}	
		// if we are still here we didn't find any jobs that
		// have finished
		return false;
	}
	   
    // Find the shortest queue in the array of processing Queues and
	// return its index
	public static int findShortestQueueIndex (Queue[] qa) {
		int minLength = 1000;
		int minIndex = 0;
		for (int i = 0; i < qa.length; i++) {
			if (qa[i].length() < minLength) {
				minLength = qa[i].length();
				minIndex = i;
;			}
		}
        return minIndex;	
	}
	
	// This function checks the arrival time of the job at the front 
	// of the queue
	public static boolean checkArrivalTime(Queue q, int timer) {
		if (!q.isEmpty()) {
			Job j = (Job)q.peek();
			if (j.getArrival() == timer) {
				return true;
			}
		}
		// if we're still here return false
		return false;
	}
	
	// This function was provided by Professor MacDowell. It creates
    // a Job object and it's called as the input file is being read in
	public static Job getJob(Scanner in) {
	    String[] s = in.nextLine().split(" ");
	    int a = Integer.parseInt(s[0]);
	    int d = Integer.parseInt(s[1]);
	    return new Job(a, d);
	 }
	   
	 // throws IOException was suggested by Eclipse
      public static void main (String[] args) throws IOException {
    	  
    	      // Open the file that was passed in as an 
    	      // argument and set it up for Scanner
    	      File in = new File(args[0]);
    	      Scanner sc = new Scanner(in);
    	      
    	      // Construct filename for the trace file and 
    	      // prepare it for writing
    	      // String traceFileName = args[0] + ".trc";
    	      String traceFileName = in.getName() + ".trc";
    	      Writer wTrace = new FileWriter(traceFileName);
    	      
    	      // Construct filename for the report file and 
    	      // prepare it for writing
    	      // String reportFileName = args[0] + ".rpt";
    	      String reportFileName = in.getName() + ".rpt";
    	      Writer wReport = new FileWriter(reportFileName);
    	      
    	      // The first integer in the file states how
    	      // many jobs are coming up in the file. This will 
    	      // help us set the number of processors too
    	      // int m = sc.nextInt();
    	      int m = Integer.parseInt(sc.nextLine());
    	      int numProcs = m - 1;
    	      
    	      // System.out.println(m + " " + numProcs);
    	      
    	      // Create all the queues except the array of processor queues
    	      Queue notYetArrivedQ = new Queue();
    	      Queue backupAllQ     = new Queue();
    	      Queue finishedQ      = new Queue();
    	      
    	      // call getJob to for as many lines that remain in the input file.
    	      // getJob will return a Job object which it creates per each line
    	      // of input. That job then gets placed in notYetArrivedQ and backupAllQ 
    	      // queues
    	      Job j = null;
    	      for (int i=0; i < m; i++) {
    	    	  
    	    	         j = getJob(sc);
    	    	         // System.out.println(j);
    	   
    	    	         // put job j in both the notYetArrivedQ and backupAllQ
    	    	         notYetArrivedQ.enqueue(j);
    	    	         backupAllQ.enqueue(j);   	
    	      }
    	      
    	      // System.out.println(notYetArrivedQ);
    	      // System.out.println(backupAllQ);
    	      
    	      
    	      logTraceHeaderInfo(notYetArrivedQ, "Trace file: " + traceFileName, wTrace);
    	      logReportHeaderInfo(notYetArrivedQ, "Report file: " + reportFileName, wReport);
    	      
    	      // This is a for loop that will run the simulation with 1 to numProc number
    	      // of processors
    	      for (int pNum = 1;  pNum <= numProcs; pNum++)  {
    	    	  
    	    	          logProcessorBanner(pNum, wTrace);
    	    	  
    	    	          // Create an array which will hold pNum references to Queues
        	          // these will be our processing Arrays
        	          Queue[] procQueues = new Queue[pNum];
        	          for (int i=0; i< pNum; i++) {
        	        	        procQueues[i] = new Queue();
        	          }
    	    	  
    	    	          // initialize the timer to 0
    	    	          int     time = 0;
    	    	          // initialize the stateChange boolean to false
    	    	          // this boolean is used to detect state changes
    	    	          // which will trigger whether we log new information
    	    	          // to the log files or not
    	    	          boolean stateChange = false;
    	    	          // While there are still jobs to process
    	    	          while (finishedQ.length() != m) {
    	    	        	      
    	    	        	       stateChange = false;
    	    	        	  
    	    	        	      // If any jobs at front of processing queues 
    	    	        	      // have finished
    	    	        	      if (checkCompletedJobs(procQueues, time)) {    	    	        	    	  
        	    	        	      moveCompletedJobs(procQueues, finishedQ, time);
        	    	        	      stateChange = true;
    	    	        	      }
    	    	        	  
    	    	        	      // See if the job in the front of the notYetArrivedQ has an
    	    	        	      // an arrival time that matches timer
    	    	        	      if (checkArrivalTime(notYetArrivedQ, time)) {
    	    	        	    	  
    	    	        	    	        // find the shortest queue in the array of 
    	    	        	    	        // processing queues
    	    	        	    	        int qIndex = findShortestQueueIndex(procQueues);
    	    	        	    	        
    	    	        	    	        // Get and dequeue the Object in from of the notArrivedYetQ
    	    	        	    	        Object o = notYetArrivedQ.dequeue();
    	    	        	    	         	        	    	        
    	    	        	    	        // Put the object o in the shortest Queue index of the
    	    	        	    	        // array of processing queues. 
    	    	        	    	        procQueues[qIndex].enqueue(o);
    	    	        	    	        
    	    	        	    	        stateChange = true;
    	    	        	    	        	    	        	      
    	    	        	      }
    	    	        	      
    	    	        	      
    	    	        	      // Every job in front of the queues in the processing queues array
    	    	        	      // should have its finished time calculated. If not calculate it.
    	    	        	      calculateFinishedTimeForAll(procQueues, time);
    	    	        	      	      
    	    	        	      if (stateChange || time==0) {
    	    	        	          logTraceInfo(pNum,time, notYetArrivedQ, procQueues, finishedQ, wTrace);
    	    	        	          // System.out.println(time);
    	    	        	          // System.out.println("notYesArrivedQ: " + notYetArrivedQ);
    	    	        	          // System.out.println("finishedQ:      " + finishedQ);
    	    	        	      }
    	    	        	      
    	    	        	      // increment time
    	    	        	      time++;
    	    	        	      
    	    	        	      // reset statChange for the next iteration
    	    	        	      stateChange = false;
    	    	        	       
    	    	          } // while
    	    	  
    	    	          // Completed an iterations of the while loop and almost done with an 
    	    	          // iteration of the for loop of processors at this point.
    	    	          // We need to do the following:
    	    	          // 1. Write the summary entry in the report file and empty the finishedQ
    	    	          // the following routine accomplishes both
    	    	          dequeueAndlogReportSummary(finishedQ,  pNum, wReport);
    	    	          
    	    	          // 2. Copy the contents of the backup queue back into the
    	    	          // notYetArrivedQ before doing this again with more processors
    	    	          copyQueues(backupAllQ, notYetArrivedQ);
    	    	          
    	    	          // Note 1: The array of processor Queues will all be recreated 
    	    	          // at the top of the for loop and garbage collected when done so no need to clear those.
    	    	          // Note 2: copyQueues clears the backUpAllQ during the copy so attempting
    	    	          // to clear that one will throw an exception.
    	    	          
    	    	    
    	      } // for
    	   
    	  wTrace.close();  
    	  wReport.close();  
      } // main
	
} // class
