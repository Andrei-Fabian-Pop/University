package Controller;

import Model.Vehicles;
import Repository.Repository;

public class Controller {
    Repository repo;

    public Controller(Repository repository) {
        this.repo = repository;
    }

    public void add(Vehicles vehicle) {
        this.repo.add(vehicle);
    }

    public void remove(Vehicles vehicle) {
        this.repo.remove(vehicle);
    }

    public Vehicles get(int i) {
        return this.repo.get(i);
    }

    public Vehicles[] getAll() {
        return this.repo.getAll();
    }

    public int getLen() {
        return this.repo.getLen();
    }
}
