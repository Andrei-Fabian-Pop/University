package View.CLI.Commands;

import Controller.Controller;
import Exceptions.MyException;
import Model.ADT.IList;

public class RunExample extends Command {
    private final Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {

            System.out.println(controller.allStep().toString());
        } catch (MyException e) {
            System.out.println(e.toString());
        }
    }
}
