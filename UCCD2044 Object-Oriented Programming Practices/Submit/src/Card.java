import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javafx.scene.image.Image;

public class Card {

	// Card's Suit
		public enum Suit {
			DIAMONDS(1, "Diamonds"), CLUBS(2, "Clubs"), 
			HEARTS(3, "Hearts"), SPADES(4, "Spades");
			
			private final int suitVal;
			private final String suitText;
			
			// Constructors
			private Suit(int suitVal, String suitText) {
				this.suitVal = suitVal;
				this.suitText = suitText;
			}
			
			// Public method
			public String printSuit() {
				return suitText;
			}
			
			public int getSuitVal() {
				return suitVal;
			}
	    }
		
		// Card's Rank
		public enum Rank {

			TWO(2, "2"), THREE(3, "3"), FOUR(4, "4"),
			FIVE(5, "5"), SIX(6, "6"), SEVEN(7, "7"), EIGHT(8, "8"),
			NINE(9, "9"), TEN(10, "10"), JACK(11, "Jack"),
			QUEEN(12, "Queen"), KING(13, "King"),ACE(14, "Ace");
			
			private final int rankVal;
			private final String rankText;
			
			// Constructors
			private Rank(int rankVal, String rankText) {
				this.rankVal = rankVal;
				this.rankText = rankText;
			}
			
			// Public method
			public String printRank() {
				return rankText;
			}
			
			public int getRankVal() {
				return rankVal;
			}
		}

		private Card() {
			
		}
		
		private Suit cardSuit;
		private Rank cardRank;
		private int cardIndex;
		private Image image;
		
		public Suit getCardSuit() {
			return cardSuit;
		}
		public void setCardSuit(Suit cardSuit) {
			this.cardSuit = cardSuit;
		}
		public Rank getCardRank() {
			return cardRank;
		}
		public void setCardRank(Rank cardRank) {
			this.cardRank = cardRank;
		}
		public int getCardIndex() {
			return cardIndex;
		}
		public void setCardIndex(int cardIndex) {
			this.cardIndex = cardIndex;
		}
		public Image getImage() {
			return image;
		}
		public void setImage(Image image) {
			this.image = image;
		}
		
		// Populate cards
		public static List<Card>populate() {
			List<Card>deck = new ArrayList<Card>();
			int index = 1;
			for(Suit suit: Suit.values()) {
				for(Rank rank: Rank.values()) {
					Card card = new Card();
					card.cardSuit = suit;
					card.cardRank = rank;
					card.cardIndex = index;
					card.image = new Image("Poker-Cards/" + index + ".png");
					deck.add(card);
					index++;
				}
			}
			return deck;
		}
		
		// Shuffle all card
		public static void shuffleCards(List<Card>cards) {
			Collections.shuffle(cards);
		}
		
		// Compare 2 card
		public boolean isBiggerThan(Card c) {
			if(this.getCardRank().getRankVal() < c.getCardRank().getRankVal()) return false;
			if(this.getCardRank().getRankVal() == c.getCardRank().getRankVal())
				if(this.getCardSuit().getSuitVal() < c.getCardSuit().getSuitVal()) return false;
			return true;
		}
		
		@Override
		public String toString() {
			return "Card: " + cardRank.printRank() + " of " + cardSuit.printSuit();

		}
}
