package Model.ADT;

import Exceptions.MyException;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.function.Consumer;

public class MyList<T> implements IList<T>{
    private final ArrayList<T> list;

    public MyList() {
        this.list = new ArrayList<>();
    }

    public MyList(ArrayList<T> list) {
        this.list = list;
    }

    @Override
    public void add(T val) {
        synchronized (list) {
            this.list.add(val);
        }
    }

    @Override
    public void remove(T val) throws MyException {
        synchronized (list) {
            if (!this.list.remove(val))
                throw new MyException("ERROR: No such element in list.");
        }
    }

    @Override
    public void remove(int index) throws MyException {
        synchronized (list) {
            if (index < 0 || index >= this.list.size())
                throw new MyException("ERROR: No such element in list.");
            this.list.remove(index);
        }
    }

    @Override
    public T get(int index)
    {
        synchronized (list) {
            return this.list.get(index);
        }
    }

    @Override
    public boolean isEmpty() {
        synchronized (list) {
            return this.list.isEmpty();
        }
    }

    @Override
    public java.util.List<T> getList() {
        synchronized (list) {
            return this.list;
        }
    }

    @Override
    public Iterator<T> iterator() {
        synchronized (list) {
            return this.list.listIterator();
        }
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        synchronized (list) {
            IList.super.forEach(action);
        }
    }

    @Override
    public String toString() {
        synchronized (list) {
            return this.list.toString();
        }
    }
}
