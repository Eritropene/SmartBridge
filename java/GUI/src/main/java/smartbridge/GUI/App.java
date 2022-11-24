package smartbridge.GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import smartbridge.model.*;

import java.io.IOException;

/**
 * JavaFX App
 */
public class App extends Application {

    private static Scene scene;

    @Override
    public void start(Stage stage) throws IOException {
    	
    	MainController controller = new MainController();
    	
        scene = new Scene(loadFXML("main", controller), 900, 550);
        scene.getStylesheets().add(ClassLoader.getSystemResource("smartbridge/css/stylesheet.css").toExternalForm());
        
        try {
        	Communicator comm = new SerialCommunicator(Launcher.PORT, controller);
			comm.listen();
		} catch (Exception e) {
			System.out.println("Error: PORT not found or busy");
			terminate(-1);
		}
        
        stage.setScene(scene);
        stage.setResizable(false);
        stage.setOnCloseRequest(e -> this.terminate(0));
        stage.show();
    }

    private static Parent loadFXML(String fxml, MainController controller) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(fxml + ".fxml"));
        fxmlLoader.setController(controller);
        return fxmlLoader.load();
    }

    public void terminate(int n) {
    	System.exit(n);
    }
}