import java.util.Random;

public class Bingo {

	Player[] players;
	public Bingo(Player[] players) {
		this.players = new Player[players.length];
		for(int i = 0; i < players.length; i++) {
			this.players[i] = players[i];
		}
	}
	public String play(int number) {
		String retVal = "";
		for(int i = 0; i < players.length; i++) {
			players[i].markNumber(number);
			if(players[i].isWinner()) {
				if(retVal.length() > 0) {
					retVal = retVal + " " + players[i].getName();
				}
				else {
					retVal = retVal + players[i].getName();
				}
			}
		}
		return retVal;
	}	
	public static void main(String[] args) {		
		int[][] numbers1 = {{10, 30, 45, 66, 82}, {3, 25, 11, 63, 78},
				{22, 4, 13, 46, 90}, {5, 23, 12, 6, 85}, {1, 88, 67, 2, 44}};
				Card[] cards1 = new Card[1];
				cards1[0] = new Card(numbers1);
		int[][] numbers2 = {{11, 31, 46, 67, 83}, {4, 26, 12, 64, 79},
				{23, 5, 14, 47, 90}, {6, 24, 13, 7, 86}, {2, 89, 68, 3, 45}};
				Card[] cards2 = new Card[1];
				cards2[0] = new Card(numbers2);
				Player[] players = new Player[2];
				players[0] = new Player("Player1", cards1);
				players[1] = new Player("Player2", cards2);
				Bingo bingo = new Bingo(players);
				Random random = new Random();
				String winners = "";
				while(winners.equals("")) {
					int number = random.nextInt(90) + 1;
					winners = bingo.play(number);
				}
				System.out.println(winners);
	}
}

class Card {
	int[][] numbers;
	public Card (int[][] cardNumbers) {
		int rows = cardNumbers.length;
		int columns = cardNumbers[0].length;
		numbers = new int[rows][columns];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				numbers[i][j] = cardNumbers[i][j];
			}
		}
	}
	public int getNumber(int Row, int Column) {
		return numbers[Row][Column];
	}
	public boolean isMarked(int row, int column) {
		if (numbers[row][column] == 100) {
			return true;
		}
		else {
			return false;
		}
	}
	public void markNumber(int number) {
		int rows = numbers.length;
		int columns = numbers[0].length;
		for (int i = 0; i < rows; i++) {
			for(int j = 0; j < columns; j++) {
				if(numbers[i][j] == number) {
					numbers[i][j] = 100;
				}
			}
		}
	}
}
class Player {
	String name;
	Card[] cards;
	public Player (String name, Card[] cards) {
		this.name = new String(name);
		this.cards = new Card[cards.length];
		for(int i = 0; i < cards.length; i++) {
			this.cards[i] = cards[i];
		}
	}
	public String getName() {
		return name;
	}
	public Card[] getCards() {
		return cards;
	}
	public boolean isWinner() {
		Card currentCard;
		for(int cardCount = 0; cardCount < cards.length; cardCount++) {
			currentCard = cards[cardCount];
			for(int rows = 0; rows < currentCard.numbers.length; rows++) {
				boolean flag = true;
				for(int columns = 0; columns < currentCard.numbers[0].length; columns++) {
					if(currentCard.numbers[rows][columns] != 100) {
						flag = false;
					}
				}
				if(flag == true) {
					return true;
				}
			}
		}
		return false;
	}
	public void markNumber(int number) {
		Card currentCard;
		for(int cardCount = 0; cardCount < cards.length; cardCount++) {
			currentCard = cards[cardCount];
			for(int rows = 0; rows < currentCard.numbers.length; rows++) {
				for(int columns = 0; columns < currentCard.numbers[0].length; columns++) {
					if(currentCard.numbers[rows][columns] == number) {
						currentCard.numbers[rows][columns] = 100;
					}
				}
			}
		}
	}
}
