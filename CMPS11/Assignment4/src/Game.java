import java.util.Random;

public class Game {
	
	private Board board;
	private Player[] players = new Player[200];
	private int numOfPlayers = 0;
	private Player currentPlayer;
	private int currentPlayerIndex = 0;

	public static void main(String[] args) {
		Player[] players = new Player[3];
	    players [0] = new Player("abc");
	    players [1] = new Player("def");
	    players [2] = new Player("ghi");
	    Board myBoard = new Board(5);
	    myBoard.setCellToLadder(7, 17);
	    myBoard.setCellToLadder(5, 14);
	    myBoard.setCellToSnake(19, 8);
	    myBoard.setCellToSnake(16, 4);
	    Game game = new Game(myBoard, players);
	    Player p = new Player("jkl");
	    game.addPlayer(p);
	    boolean b = false;
	    Random random = new Random();
	    int n;
	    while (!b) {
	        n = random.nextInt(6) + 1;
	        b = game.play(n);
	     }
	     System.out.println(game.currentPlayer().getName());
	}
	
	
	public Game(Board board, Player[] players) {
		for(int i = 0; i < players.length; i++) {
			if(players[i] != null) {
				this.players[i] = players[i];
				numOfPlayers++;
			}
		}
		
		this.board = board;
	}
	
	public Game(Player[] players) {
		for(int i = 0; i < players.length; i++) {
			if(players[i] != null) {
				this.players[i] = players[i];
				numOfPlayers++;
			}
		}
		
		this.board = new Board(10);
	}
	
	public Player currentPlayer() {
		return currentPlayer;
	}
	
	public void addPlayer(Player p) {
		players[numOfPlayers] = p;
		numOfPlayers++;
	}
	
	public boolean winner() {
		if (currentPlayer.getPosition() == board.getCells().length-1) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public void movePlayer(int n) {
		
		//System.out.printf("%s rolled a %d \n", currentPlayer,n);
		board.getCells()[currentPlayer.getPosition()].setOccupied(false);

		currentPlayer.setPosition(currentPlayer.getPosition() + n);
		if (currentPlayer.getPosition() >= board.getCells().length) {
			//System.out.println("bounce");
			currentPlayer.setPosition(0);
		}
		else if (board.getCells()[currentPlayer.getPosition()].getLadder() != null){
			//System.out.println("ladder");
			Ladder l = board.getCells()[currentPlayer.getPosition()].getLadder();
			currentPlayer.setPosition(l.getTop());
		}
		else if (board.getCells()[currentPlayer.getPosition()].getSnake() != null) {
			//System.out.println("snake");
			Snake s = board.getCells()[currentPlayer.getPosition()].getSnake();
			currentPlayer.setPosition(s.getTail());
		}
		if (board.getCells()[currentPlayer.getPosition()].isOccupied()){
			//System.out.println("occupied");
			currentPlayer.setPosition(0);
		}
		
		board.getCells()[currentPlayer.getPosition()].setOccupied(true);
		
		//System.out.println(currentPlayer);
	}
	
	public boolean play(int moveCount) {
		currentPlayer = players[currentPlayerIndex];
		movePlayer(moveCount);
		
		Ladder l = board.getCells()[currentPlayer.getPosition()].getLadder();
		Snake  s = board.getCells()[currentPlayer.getPosition()].getSnake();	
		if (l != null) {
			movePlayer(0);
		}
		if (s != null) {
			movePlayer(0);
		}
		
		currentPlayerIndex++;
		if (currentPlayerIndex == numOfPlayers) {
			currentPlayerIndex = 0;
		}
		
		return winner();
	}
}

class Player{
	
	private String name;
	private int position;
	
	public Player(String name) {
		this.name = new String(name);
		position = 0;
	}
	
	public void setPosition(int position) {
		this.position = position;
	}
	
	public int getPosition() {
		return position;
	}
	
	public String getName() {
		return name;
	}
	
	public String toString() {
		return name + " @ " + position;
	}
}

class Cell{
	
	private int number;
	private boolean occupied = false;
	private Ladder ladder = null;
	private Snake snake = null;
	
	public Cell(int number) {
		this.number = number;
	}
	
	public void setOccupied(boolean occupied) {
		this.occupied = occupied;
	}
	
	public boolean isOccupied() {
		return occupied;
	}
	
	public Ladder getLadder() {
		return ladder;
	}
	
	public Snake getSnake() {
		return snake;
	}
	
	public void setLadder(Ladder ladder) {
		this.ladder = ladder;
	}
	
	public void setSnake(Snake snake) {
		this.snake = snake;
	}
	
	public int getNumber() {
		return number;
	}
}

class Board{
	
	private Cell[] cells;
	
	public Board(int n) {
		
		cells = new Cell[n*n];
		for(int i = 0; i < n*n; i++) {
			cells[i] = new Cell(i);
		}
	}
	
	public void setCellToLadder(int startPosition, int endPosition) {
		Ladder ladder = new Ladder(startPosition, endPosition);
		cells[startPosition].setLadder(ladder);
	}
	
	public void setCellToSnake(int headPosition, int tailPosition) {
		Snake snake = new Snake(headPosition, tailPosition);
		cells[headPosition].setSnake(snake);
	}
	
	public Cell[] getCells() {
		return cells;
	}
}

class Snake{
	
	private int headPosition;
	private int tailPosition;
	
	public Snake(int headPosition, int tailPosition) {
		this.headPosition = headPosition;
		this.tailPosition = tailPosition;
	}
	
	public int getTail() {
		return tailPosition;
	}
	
	public String toString() {
		return headPosition + " - " + tailPosition;
	}
}

class Ladder{
	
	private int startPosition;
	private int endPosition;
	
	public Ladder(int startPosition, int endPosition) {
		this.startPosition = startPosition;
		this.endPosition = endPosition;
	}
	
	public int getTop() {
		return endPosition;
	}
	
	public String toString() {
		return startPosition + " - " + endPosition;
	}
}