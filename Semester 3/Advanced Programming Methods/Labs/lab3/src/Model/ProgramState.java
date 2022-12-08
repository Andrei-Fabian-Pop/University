package Model;

import Exceptions.MyException;
import Model.ADT.*;
import Model.Statements.IStatement;
import Model.Values.Values;

import java.io.BufferedReader;
import java.util.Map;
import java.util.Random;
import java.util.TreeSet;

public class ProgramState {
    private final IStack<IStatement> execStack;
    private final IDictionary<String, Values> symTable;
    private final IList<String> out;
    private final IDictionary<String, BufferedReader> fileTable;
    private final IHeap heap;
    private static final TreeSet<Integer> ids = new TreeSet<>();
    public final Integer id;

    public ProgramState(IStatement originalProgram) {
        execStack = new MyStack<>();
        symTable = new MyDictionary<>();
        out = new MyList<>();
        fileTable = new MyDictionary<>();
        execStack.push(originalProgram);
        heap = new MyHeap();
        id = newId();
    }

    public ProgramState() {
        execStack = new MyStack<>();
        symTable = new MyDictionary<>();
        out = new MyList<>();
        fileTable = new MyDictionary<>();
        heap = new MyHeap();
        id = newId();
    }

    public ProgramState(IStack<IStatement> execStack, IDictionary<String, Values> symTable, IList<String> out, IDictionary<String, BufferedReader> fileTable, IHeap heap) {
        this.execStack = execStack;
        this.fileTable = fileTable;
        this.symTable = symTable;
        this.out = out;
        this.heap = heap;
        id = newId();
    }

    public IDictionary<String, Values> getSymTable() {
        return symTable;
    }

    public IList<String> getOut() {
        return out;
    }

    public IStack<IStatement> getExecStack() {
        return this.execStack;
    }

    public IDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public IHeap getHeap() {
        return heap;
    }

    public boolean isCompleted() {
        return this.execStack.isEmpty();
    }

    public ProgramState oneStep() throws MyException {
        if (execStack.isEmpty()) {
            throw new MyException("Exec stack is empty.");
        }

        IStatement statement = execStack.pop();
        return statement.execute(this);
    }

    private static Integer newId() {
        Random random = new Random();
        int _id;
        synchronized (ids) {
            do {
                _id = 1000 + (random.nextInt() % 9000); // to look like a pid :))
            } while (ids.contains(_id));
            ids.add(_id);
        }

        return _id;
    }

    public String execToString() {
        StringBuilder builder = new StringBuilder();
        for (IStatement statement: execStack) {
            builder.append(statement.toString());
            builder.append("\n");
        }
        return builder.toString();
    }

    public String symToString() {
        StringBuilder builder = new StringBuilder();
        for (String key: symTable.keys()) {
            builder.append(String.format("%s: %s\n", key, symTable.get(key)));
        }
        return builder.toString();
    }

    public String outToString() {
        StringBuilder builder = new StringBuilder();
        for (String o: out) {
            builder.append(o).append("\n");
        }

        return builder.toString();
    }

    public String fileToString() {
        StringBuilder builder = new StringBuilder();
        for (String o: fileTable.keys()) {
            builder.append(o).append("\n");
        }

        return builder.toString();
    }

    public String heapToString() {
        StringBuilder builder = new StringBuilder();
        Map<String, Values> map = heap.getContent();
        for (String key : map.keySet()) {
            builder.append(key).append(" in ").append(map.get(key)).append("\n");
        }

        return builder.toString();
    }

    @Override
    public String toString() {
        return String.format("ID: %d\nExecution stack:\n%s\nSymbol Table:\n%s\nOut:\n%s\nFile Table:\n%s\nHeap:\n%s",
                this.id,
                execToString(),
                symToString(),
                outToString(),
                fileToString(),
                heapToString()
        );
    }
}
