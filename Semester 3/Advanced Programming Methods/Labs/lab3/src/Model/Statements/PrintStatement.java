package Model.Statements;

import Exceptions.MyException;
import Model.Expressions.Expression;
import Model.ProgramState;

public class PrintStatement implements IStatement {
    private final Expression expression;

    public PrintStatement(Expression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        state.getOut().add(this.expression.eval(state.getSymTable(), state.getHeap()).toString());
        return null;
    }

    @Override
    public String toString() {
        return String.format("Print{%s}", expression.toString());
    }
}
