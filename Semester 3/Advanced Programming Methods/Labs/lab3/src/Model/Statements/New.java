package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Types.RefType;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Values;

public class New implements IStatement {
    private final String varName;
    private final Expression expression;

    public New(String varName, Expression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Values> symTable = state.getSymTable();

        IHeap heap = state.getHeap();
        if (!symTable.containsKey(varName))
            throw new MyException(String.format("ERROR: %s not in symTable", varName));

        Values varValue = symTable.get(varName);
        if (!(varValue.getType() instanceof RefType))
            throw new MyException(String.format("ERROR: %s not of ReferenceType", varName));

        Values evaluated = expression.eval(symTable, heap);
        Type locationType = ((RefValue) varValue).getLocationType();
        if (!locationType.equals(evaluated.getType()))
            throw new MyException(String.format("ERROR: %s not of %s", varName, evaluated.getType()));

        String newPosition = heap.add(evaluated);
        symTable.put(varName, new RefValue(newPosition, locationType));
        return null;
    }

    @Override
    public String toString() {
        return String.format("New{%s: %s}", varName, expression);
    }
}
