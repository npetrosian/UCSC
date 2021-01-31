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

