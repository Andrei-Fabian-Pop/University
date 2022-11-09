package Model.ADT;

import Exceptions.MyException;

import java.util.List;

public interface IList<T> extends Iterable<T> {
    void add(T val);

    void remove(T val) throws MyException;

    void remove(int index) throws MyException;

    T get(int index);

    boolean isEmpty();

    List<T> getList();

    String toString();
}
