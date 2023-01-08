package View.ToyLangaugeGui;

import Controller.Controller;
import Exceptions.MyException;
import Model.ProgramState;
import Model.Statements.IStatement;
import Repository.IRepository;
import Repository.Repository;
import View.ExamplesView;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.layout.Region;

import static View.ExamplesView.exampleList;

public class ProgramStateController {
    private MainController mainController;

    public void setMainController(MainController mainController) {
        this.mainController = mainController;
    }
    @FXML
    public Label welcomeTextLabel;
    @FXML
    public ListView<String> PrgStateList;

    public void initialize() {
        for (IStatement statement: exampleList()) {
            this.PrgStateList.getItems().add(statement.toString());
        }
    }
    @FXML
    protected void startProgram() {
        int index = this.PrgStateList.getSelectionModel().getSelectedIndex();
        if (index < 0)
            return;
        ProgramState programState = new ProgramState(ExamplesView.exampleList()[index]);
        IRepository repository = new Repository("execution_log.txt");
        Controller controller = new Controller(repository);
        controller.addPrg(programState);
        try {
            controller.typeChecker();
            this.mainController.setController(controller);
        } catch (MyException myException) {
            Alert alert = new Alert(Alert.AlertType.ERROR, myException.getMessage(), ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
        }
    }
}