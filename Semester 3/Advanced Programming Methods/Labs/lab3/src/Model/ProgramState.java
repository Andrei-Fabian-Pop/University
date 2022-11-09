package Model;

import Exceptions.MyException;
import Model.ADT.*;
import Model.Statements.IStatement;
import Model.Values.Values;

public class ProgramState {
    private final IStack<IStatement> execStack;
    private final IDictionary<String, Values> symTable;
    private final IList<String> out;

    public ProgramState() {
        execStack = new MyStack<>();
        symTable = new MyDictionary<>();
        out = new MyList<>();
    }

    public ProgramState(IStack<IStatement> execStack, IDictionary<String, Values> symTable, IList<String> out) {
        this.execStack = execStack;
        this.symTable = symTable;
        this.out = out;
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

    public boolean isCompleted() {
        return this.execStack.isEmpty();
    }

    public ProgramState thisStep() throws MyException {
        if (execStack.isEmpty()) {
            throw new MyException("Exec stack is empty.");
        }

        IStatement statement = execStack.pop();
        return statement.execute(this);
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
            builder.append(o.toString()).append("\n");
        }

        return builder.toString();
    }

    @Override
    public String toString() {
        return String.format("Execution stack:\n%s\nSymbol Table:\n%s\nOut:\n%s",
                execToString(),
                symToString(),
                outToString());
    }
}
