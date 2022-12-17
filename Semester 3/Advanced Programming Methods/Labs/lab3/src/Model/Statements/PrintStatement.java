package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.Type;

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
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        expression.typeCheck(typeTable);
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("Print{%s}", expression.toString());
    }
}
