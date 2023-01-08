package View.ToyLangaugeGui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader1 = new FXMLLoader(Main.class.getResource("program_state_window.fxml"));
        Scene programStateScene = new Scene(fxmlLoader1.load(), 1200, 900);
        stage.setScene(programStateScene);
        stage.setTitle("Program States");
        ProgramStateController programStateController = fxmlLoader1.getController();

        FXMLLoader fxmlLoader2 = new FXMLLoader(Main.class.getResource("main_window.fxml"));
        Scene mainScene = new Scene(fxmlLoader2.load(), 1200, 900);
        Stage stage2 = new Stage();
        stage2.setScene(mainScene);
        stage2.setTitle("Main App");
        MainController mainController = fxmlLoader2.getController();
        programStateController.setMainController(mainController);

        stage2.show();
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}