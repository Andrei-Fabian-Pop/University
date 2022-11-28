package Model.Statements;

import Exceptions.MyException;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Values;

public class WhileStatement implements IStatement {
    private final Expression expression;
    private final IStatement statement;

    public WhileStatement(Expression expression, IStatement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Values value = expression.eval(state.getSymTable());
        if (!value.getType().equals(new BoolType())) {
            throw new MyException(String.format("ERROR: %s is not bool type", value));
        }

        BoolValue boolValue = (BoolValue) value;
        if (boolValue.getValue()) {
            state.getExecStack().push(this);
            state.getExecStack().push(statement);
        }
        return null;
    }

    @Override
    public String toString() {
        return String.format("While (%s) {\n\t%s\n}", expression, statement);
    }
}
