package Model.ADT;

import Exceptions.MyException;

import java.util.Stack;

public interface IStack<T> extends Iterable<T> {
    void push(T val);

    T pop() throws MyException;

    T top() throws MyException;

    boolean isEmpty();

    Stack<T> getStack();
}
