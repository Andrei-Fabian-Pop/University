package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Types.Type;
import Model.Values.Values;

public class VariableExpression implements Expression {
    private final String key;

    public VariableExpression(String key) {
        this.key = key;
    }

    @Override
    public Values eval(IDictionary<String, Values> symTable, IHeap heap) throws MyException {
        return symTable.get(key);
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        return typeTable.get(key);
    }

    @Override
    public String toString() {
        return String.format("VariableExpression{%s}", key);
    }
}
