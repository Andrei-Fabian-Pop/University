package domain;

public class City {
    private final int id;
    private final String name;

    public City(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String toJSON() {
        return "{\"id\":" + id + ", \"name\":\"" + name + '\"' + '}';
    }

    @Override
    public String toString() {
        return "City {" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }
}
