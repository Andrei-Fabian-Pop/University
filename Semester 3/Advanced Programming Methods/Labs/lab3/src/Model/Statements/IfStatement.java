package Model.Statements;

import Exceptions.MyException;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Values;

public class IfStatement implements IStatement {
    private final Expression expression;
    private final IStatement first;
    private final IStatement second;

    public IfStatement(Expression expression, IStatement first, IStatement second) {
        this.expression = expression;
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Values value = expression.eval(state.getSymTable());
        if (value.getType().equals(new BoolType())) {
            BoolValue condition = (BoolValue) value;
            if (condition.getValue()) {
                state.getExecStack().push(first);
            } else {
                state.getExecStack().push(second);
            }
        }
        return null;
    }

    @Override
    public String toString() {
        return String.format("if(%s){\n\t%s\n}else{\n\t%s\n}", expression.toString(), first.toString(), second.toString());
    }
}
