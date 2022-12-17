package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.Type;
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
        Values value = expression.eval(state.getSymTable(), state.getHeap());
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
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        if (!expression.typeCheck(typeTable).equals(new BoolType())) {
            throw new MyException("The condition of while does not have the type bool");
        }
        statement.typeCheck(typeTable.copy());
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("While (%s) {\n\t%s\n}", expression, statement);
    }
}
