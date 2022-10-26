package view;

import controller.Controller;
import model.Apple;
import model.Book;
import model.Cake;
import model.Entity;

import java.util.List;

public class View {

    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void execute() {
        Entity apple = new Apple("green");
        apple.setWeight(50);
        controller.add(apple);

        Entity book = new Book(50, "harry porter");
        book.setWeight(100);
        controller.add(book);

        Entity cake = new Cake("cioco");
        cake.setWeight(500);
        controller.add(cake);

        Entity book2 = new Book(100, "book2");
        book2.setWeight(300);
        controller.add(book2);

        List<Entity> entities = controller.getAllWithWeightGreaterThan();

        for (Entity entity : entities) {
            System.out.println(entity);
        }
    }
}
