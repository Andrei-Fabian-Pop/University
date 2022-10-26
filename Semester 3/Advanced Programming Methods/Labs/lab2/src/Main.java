//1. In a parking lot there are cars, motorcycles
//and bicycles. To display all vehicles
//red color.

import Controller.Controller;
import Repository.Repository;
import View.View;

public class Main {
    public static void main(String[] args) {
        Repository repository = new Repository();
        Controller controller = new Controller(repository);
        View view = new View(controller);
        view.execute();
    }
}