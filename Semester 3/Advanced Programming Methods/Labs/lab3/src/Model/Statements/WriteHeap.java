package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Values.RefValue;
import Model.Values.Values;

public class WriteHeap implements IStatement {
    private final String varName;
    private final Expression expression;

    public WriteHeap(String varName, Expression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Values> symTable = state.getSymTable();
        IHeap heap = state.getHeap();
        if (!symTable.containsKey(varName)) {
            throw new MyException(String.format("ERROR: %s not present in the symTable", varName));
        }

        Values varValue = symTable.get(varName);
        if (!(varValue instanceof RefValue refValue)) {
            throw new MyException(String.format("ERROR: %s not RefType", varValue));
        }
        Values evaluated = expression.eval(symTable, heap);
        if (!evaluated.getType().equals(refValue.getLocationType())) {
            throw new MyException(String.format("ERROR: %s not %s", evaluated, refValue.getLocationType()));
        }

        heap.update(refValue.getAddress(), evaluated);
        return null;
    }

    @Override
    public String toString() {
        return String.format("WriteHeap{%s: %s}", varName, expression);
    }
}
