package Model.ADT;

import Exceptions.MyException;

import java.util.Iterator;
import java.util.Stack;
import java.util.function.Consumer;

public class MyStack<T> implements IStack<T>{
    private final Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<T>();
    }

    public MyStack(Stack<T> stack) {
        this.stack = stack;
    }

    @Override
    public void push(T val) {
        this.stack.push(val);
    }

    @Override
    public T pop() throws MyException {
        if (this.stack.isEmpty())
            throw new MyException("ERROR: Stack is empty.");
        return this.stack.pop();
    }

    @Override
    public T top() throws MyException {
        if (this.stack.isEmpty())
            throw new MyException("ERROR: Stack is empty.");
        return this.stack.peek();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public Stack<T> getStack() {
        return this.stack;
    }

    @Override
    public Iterator<T> iterator() {
        return this.stack.iterator();
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        IStack.super.forEach(action);
    }
}
