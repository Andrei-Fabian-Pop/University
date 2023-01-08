package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Types.Type;
import Model.Values.Values;

public class ValueExpression implements Expression {
    private final Values value;

    public ValueExpression(Values value) {
        this.value = value;
    }

    @Override
    public Values eval(IDictionary<String, Values> symTable, IHeap heap) throws MyException {
        return value;
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        return value.getType();
    }

    @Override
    public String toString() {
        return String.format("ValueExpression{%s}", value.toString());
    }
}
