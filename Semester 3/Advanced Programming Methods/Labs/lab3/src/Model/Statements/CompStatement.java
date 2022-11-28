package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IStack;
import Model.ProgramState;

public class CompStatement implements IStatement {
    private final IStatement first;
    private final IStatement second;

    public CompStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> stack = state.getExecStack();
        stack.push(second);
        stack.push(first);
        return null;
    }

    @Override
    public String toString() {
        return String.format("%s;\n%s\n", first.toString(), second.toString());
    }
}
