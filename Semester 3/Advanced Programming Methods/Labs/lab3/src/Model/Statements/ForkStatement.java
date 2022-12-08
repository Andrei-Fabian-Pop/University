package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IStack;
import Model.ADT.MyStack;
import Model.ProgramState;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> newExeStack = new MyStack<>();
        newExeStack.push(statement);

        return new ProgramState(newExeStack, state.getSymTable().cloneDict(), state.getOut(), state.getFileTable(), state.getHeap());
    }

    @Override
    public String toString() {
        return String.format("Fork{\n%s\n}", statement);
    }
}
