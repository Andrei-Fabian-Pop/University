package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IStack;
import Model.ADT.MyStack;
import Model.ProgramState;
import Model.Types.Type;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IStack<IStatement> newExeStack = new MyStack<>();
        newExeStack.push(statement);

        return new ProgramState(newExeStack, state.getSymTable().copy(), state.getOut(), state.getFileTable(), state.getHeap());
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        statement.typeCheck(typeTable.copy());
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("Fork{\n%s\n}", statement);
    }
}
