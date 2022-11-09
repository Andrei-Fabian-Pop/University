package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Values;

public class AssStatement implements IStatement{ // assign :)
    private final String key;
    private final Expression expression;

    public AssStatement(String key, Expression expression) {
        this.key = key;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Values> symTable = state.getSymTable();
        Type type = symTable.get(key).getType();
        Values value = expression.eval(symTable);
        if (!value.getType().equals(type)) {
            throw new MyException(String.format("Error: %s is not compatible with %s", value.toString(), type.toString()));
        }
        if (!symTable.containsKey(key)) {
            throw new MyException(String.format("ERROR: %s does not exist in the symTable", key));
        }
        symTable.put(key, value);
        return null;
    }

    @Override
    public String toString() {
        return String.format("Assignment{%s = %s}", key, expression.toString());
    }
}
