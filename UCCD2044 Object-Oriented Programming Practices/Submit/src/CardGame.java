import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;

public class CardGame {
	
	private List<Card> deck;
	private List<Player> Players = new ArrayList<Player>();
	private Map<Player,List<Card>>playerCardsMap = new HashMap<Player,List<Card>>();
	private Image cover = new Image("Poker-Cards/0.png");
	
	private int numOfPlayer;
	private int cardLimit;
	private int curPlayerIndex;
	private boolean hasWinner;
	private Player winningPlayer;
	private Card largestCard;
	private Player curPlayer;
	private Card curCard;
	
	Font font = Font.font("Times New Roman", FontWeight.BOLD, 36);
	
	public CardGame() {
		// Default value
		this.numOfPlayer = 4;
		this.cardLimit = 7;
		this.curPlayerIndex = 0;
		this.hasWinner = false;
		this.winningPlayer = null;
		this.largestCard = null;
		this.curPlayer = null;
		this.curCard = null;
	}
	
	// Getter and Setter
	public List<Player> getPlayers() {
		return Players;
	}

	public void setNumOfPlayer(int numOfPlayer) {
		this.numOfPlayer = numOfPlayer;
	}

	public void setCardLimit(int cardLimit) {
		this.cardLimit = cardLimit;
	}

	// Create players
	private void createMultiplepPlayer(int numOfPlayer) {
		playerCardsMap.clear();
		
		if(Players.size() != 0)
			Players.clear();
		if(playerCardsMap.size() != 0)
			playerCardsMap.clear();
		
		for(int i = 1; i <= numOfPlayer; i++) {
			Player p = new Player(i);
			p.setName("Player " + i);
			p.setPoint(0);
			Players.add(p);
		}
		distributeCards(Players);
	}

	// Distribute cards to all players
	public void distributeCards(List<Player> Players) {
		this.Players = Players;
		Card.shuffleCards(deck);
		
		for(Player p: Players) {
			List<Card>c = new ArrayList<Card>();
			for(int i = 0; i < cardLimit; i++) {
				c.add(deck.get(0));
				deck.remove(0);
			}
			playerCardsMap.put(p, c);
		}
	}
	
	// Get to next player
	private Player getNextPlayer() {
		Player p = null;
		if(curPlayerIndex == Players.size()) {
			curPlayerIndex = 1;
			p = Players.get(0);
		}
		else {
			p = Players.get(curPlayerIndex);
			curPlayerIndex++;
		}
		return p;
	}
	
	// Game main menu
	public void mainMenu(BorderPane pane) {
		pane.getChildren().clear();
		
		Label text = new Label("Welcome to Card Game");
		text.setFont(font);
		
		Button bStart = new Button("Start Game");
		bStart.setPrefSize(100, 50);
		
		bStart.setOnAction(e->{
			deck = Card.populate();
			insertNumOfPlayer(pane);
			curPlayerIndex = 0;
			hasWinner = false;
			winningPlayer = null;
			largestCard = null;
			curPlayer = null;
			curCard = null;
		});
		Button bExit = new Button("Exit Game");
		bExit.setMaxSize(100, 200);
		bExit.setOnAction(e->System.exit(0));
		
		VBox box = new VBox(20);
		box.setAlignment(Pos.CENTER);
		box.getChildren().addAll(text,bStart,bExit);
		pane.setCenter(box);
	}
	
	// Get player number
	private void insertNumOfPlayer(BorderPane pane) {
		pane.getChildren().clear();
		
		Label text = new Label("Select number of Player");
		text.setFont(font);
		
		Button p2 = new Button("2 Players");
		p2.setPrefSize(100, 50);
		p2.setOnAction(e->{
			setNumOfPlayer(2);
			createMultiplepPlayer(2);
			gameStart(pane);
    	});
		Button p3 = new Button("3 Players");
		p3.setPrefSize(100, 50);
		p3.setOnAction(e->{
			setNumOfPlayer(3);
			createMultiplepPlayer(3);
			gameStart(pane);
    	});
		Button p4 = new Button("4 Players");
		p4.setPrefSize(100, 50);
		p4.setOnAction(e->{
			setNumOfPlayer(4);
			createMultiplepPlayer(4);
			gameStart(pane);
    	});
		VBox box = new VBox(20);
		box.setAlignment(Pos.CENTER);
		box.getChildren().addAll(text,p2,p3,p4);
		pane.setCenter(box);
	}
	
	// Game start
	private void gameStart(BorderPane pane) {
		pane.getChildren().clear();
		
		curPlayer = getNextPlayer();
		int cards = playerCardsMap.get(curPlayer).size();
		
		if(cards == 0) {
			displayWinner(pane);
		}
		else {
			Label playerName = new Label(curPlayer.getName());
			playerName.setFont(font);
			
			HBox boxForCards = new HBox(20);
			boxForCards.setAlignment(Pos.CENTER);
			Button[] btns = new Button[cards];
			for (int i=1; i<=cards; i++) {
				
				Button btn = new Button();
				ImageView view = new ImageView(cover);
				view.setFitHeight(200);
				view.setPreserveRatio(true);
				btn.setGraphic(view);
				btns[i-1] = btn;
			}
			for (int i=0; i<cards; i++) {
				final int index = i;

				boxForCards.getChildren().add(btns[i]);
				btns[i].setOnAction(e->{
					curCard = playerCardsMap.get(curPlayer).get(index);
					playerCardsMap.get(curPlayer).remove(index);
					if(largestCard == null) {
	            		largestCard = curCard;
	            		winningPlayer = curPlayer;
	            	}
	            	else {
	            		if(curCard.isBiggerThan(largestCard)) {
	            			largestCard = curCard;
	            			winningPlayer = curPlayer;
	            		}
	            	}
					
					playerSelection(pane);
				});
			}
			Label player = new Label(Players.toString());
			player.setFont(font);
			VBox box = new VBox(20);
			box.setAlignment(Pos.CENTER);
			box.getChildren().addAll(playerName,boxForCards,player);
			pane.setCenter(box);
		}
	}
	
	// Player selection (Continue or stop game)
	private void playerSelection(BorderPane pane) {
		pane.getChildren().clear();
		
		Label playerName = new Label(curPlayer.getName());
		playerName.setFont(font);
		ImageView view = new ImageView(curCard.getImage());
		view.setFitHeight(200);
		view.setPreserveRatio(true);
		
		Label playerCard = new Label(curCard.toString());
		playerCard.setFont(font);

		HBox boxForSelection = new HBox(20);
		boxForSelection.setAlignment(Pos.CENTER);
		
		if(curPlayerIndex == numOfPlayer) {
			Button bCont = new Button("Continue");
			bCont.setOnAction(e->{
				roundEnd(pane);
			});
			boxForSelection.getChildren().add(bCont);
		}
		else {
			Button bCont = new Button("Continue");
			bCont.setOnAction(e->{
				gameStart(pane);
			});
			boxForSelection.getChildren().add(bCont);
		}
		
		Button bStop = new Button("Stop");
		bStop.setOnAction(e->{
			displayWinner(pane);
		});
		boxForSelection.getChildren().add(bStop);
		
		VBox box = new VBox(20);
		box.setAlignment(Pos.CENTER);
		box.getChildren().addAll(playerName,view,playerCard,boxForSelection);
		pane.setCenter(box);
		
	}
	
	// Round end
	private void roundEnd(BorderPane pane) {
		pane.getChildren().clear();
		
		winningPlayer.setPoint(winningPlayer.getPoint() + 1);
		
		Label text = new Label("Player won this round:");
		text.setFont(font);
		Label player = new Label(winningPlayer.toString());
		player.setFont(font);
		
		VBox box = new VBox(20);
		
		HBox boxForSelection = new HBox(20);
		boxForSelection.setAlignment(Pos.CENTER);
		Button bCont = new Button("Continue");
		bCont.setOnAction(e->{
			gameStart(pane);
		});
		Button bStop = new Button("Stop");
		bStop.setOnAction(e->{
			displayWinner(pane);
		});
		boxForSelection.getChildren().addAll(bCont,bStop);
		
		box.setAlignment(Pos.CENTER);
		box.getChildren().addAll(text,player,boxForSelection);
		pane.setCenter(box);
		
		hasWinner = true;
		largestCard = null;
		winningPlayer = null;
	}
	
	// Game end
	private void displayWinner(BorderPane pane) {
		pane.getChildren().clear();

		VBox box = new VBox(20);
		box.setAlignment(Pos.CENTER);
		
		List<Player> winner = new ArrayList<Player>();
		Player largest = Players.get(0);
		for(Player p: Players) {
			if(hasWinner) {
				if(p.compareScore(largest) == 0) {
					winner.add(p);
				}
				else if(p.compareScore(largest) > 0) {
					winner.clear();
					winner.add(p);
					largest = p;
				}
			}
		}
		if (winner.size() == 0) {
			Label text = new Label("There are no winner among the players.");
			text.setFont(font);
			box.getChildren().add(text);
		}
		else if (winner.size()>1) {
			Label text = new Label("Its a draw among the following players:");
			text.setFont(font);
			box.getChildren().add(text);

			Label winners = new Label(winner.toString());
			winners.setFont(font);
			box.getChildren().add(winners);
		}
		else {
			Label text = new Label("The winner is:");
			text.setFont(font);
			Label winners = new Label(winner.get(0).toString());
			winners.setFont(font);
			
			box.getChildren().add(text);
			box.getChildren().add(winners);
		}
		Button btn = new Button("Return to main menu");
		btn.setAlignment(Pos.CENTER);
		box.getChildren().add(btn);
		btn.setOnAction(e->{
			mainMenu(pane);
		});
		
		pane.setCenter(box);
	}
}
