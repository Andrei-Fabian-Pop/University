package Repository;


import Model.Vehicles;

import java.util.Objects;

public class Repository {
    private final Vehicles[] vehicles;
    private int index;

    public Repository() {
        this.vehicles = new Vehicles[100];
        this.index = 0;
    }

    public void add(Vehicles vehicle) {
        if (index >= 100) {
            throw new ArrayIndexOutOfBoundsException("length exceeds 100");
        }
        this.vehicles[index++] = vehicle;
    }

    public void remove(Vehicles vehicle) {
        boolean past = false;
        for (int i = 0; i < this.index; ++i) {
            if (Objects.equals(vehicles[i].getName(), vehicle.getName())) {
                past = true;
            } else if (past) {
                vehicles[i-1] = vehicles[i];
            }
        }
        if (past) {
            --this.index;
        }
    }

    public Vehicles get(int i) {
        if (i < 0 || i > 100) {
            throw new ArrayIndexOutOfBoundsException("invalid index");
        }
        return this.vehicles[i];
    }

    public int getLen() {
        return this.index;
    }

    public Vehicles[] getAll() {
        return this.vehicles;
    }
}
