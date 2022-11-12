import View.CLI.CLIView;
import View.ExamplesView;
import View.View;

public class Main {
    public static void main(String[] args) {
        View view = new CLIView();
        view.execute();
    }
}