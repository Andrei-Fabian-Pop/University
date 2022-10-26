package Model;

public class Bicicleta implements Vehicles {
    private String color;
    private String name;

    public Bicicleta(String color, String name) {
        this.color = color;
        this.name = name;
    }

    @Override
    public String getColor() {
        return this.color;
    }

    @Override
    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }
}
