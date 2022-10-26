package View;

import Controller.Controller;
import Model.Bicicleta;
import Model.Car;
import Model.Motorcycle;
import Model.Vehicles;

import java.util.Objects;

public class View {
    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void execute() {
        Vehicles vehicle1 = new Motorcycle("red", "motorcycle1");
        Vehicles vehicle2 = new Bicicleta("blue", "bi1");
        Vehicles vehicle3 = new Car("red", "car1");
        Vehicles vehicle4 = new Motorcycle("green", "motorcycle2");

        controller.add(vehicle1);
        controller.add(vehicle2);
        controller.add(vehicle3);
        controller.add(vehicle4);

        Vehicles[] veh = controller.getAll();

        try {
            for (int i = 0; i < controller.getLen(); ++i) {
                if (Objects.equals(veh[i].getColor(), "red")) {
                    System.out.println(veh[i].getName());
                }
            }
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
    }
}
