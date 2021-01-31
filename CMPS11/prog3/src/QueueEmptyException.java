// Name: Natalie Petrosian
// Class: 12B
// CruzID: npetrosi
// File name: QueueEmptyException.java
// The purpose of this file is to satisfy the QueueEmptyExceptions
// in QueueInterface.java.

// package prog3;

public class QueueEmptyException extends RuntimeException{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public QueueEmptyException(String s) {
		super(s);
	}

}
