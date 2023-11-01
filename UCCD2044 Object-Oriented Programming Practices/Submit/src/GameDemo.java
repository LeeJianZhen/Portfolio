import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class GameDemo extends Application {
	
	private Stage window;
	private Scene scene;
	private BorderPane pane;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) {
		// TODO Auto-generated method stub
		window = primaryStage;
		pane = new BorderPane();
		pane.setStyle("-fx-background-image: url(bg.png);-fx-background-size: cover, auto;");
		// Start game
		CardGame game = new CardGame();
		game.mainMenu(pane);
		
		// Show scene
		scene = new Scene(pane, 1440, 900);
		
		window.setScene(scene);
		window.setTitle("Card Game");
		window.show();
	}
}
