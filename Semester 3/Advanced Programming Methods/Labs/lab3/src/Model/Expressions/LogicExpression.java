package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Values;

public class LogicExpression extends BinaryExpression {
    protected LogicExpression(OPERATOR operator, Expression left, Expression right) {
        super(operator, left, right);
    }

    private BoolValue getValue(Expression expression, IDictionary<String, Values> symTable, IHeap heap) throws MyException {
        Values value = expression.eval(symTable, heap);
        if (value instanceof BoolValue)
            return (BoolValue) value;
        throw new MyException(String.format("ERROR: %s is not of type BoolType", value.toString()));
    }
    
    @Override
    public Values eval(IDictionary<String, Values> symTable, IHeap heap) throws MyException {
        BoolValue leftValue = getValue(left, symTable, heap);
        BoolValue rightValue = getValue(right, symTable, heap);
        return switch (operator) {
            case AND -> new BoolValue(leftValue.getValue() && rightValue.getValue());
            case OR -> new BoolValue(leftValue.getValue() || rightValue.getValue());
            default -> throw new MyException(String.format("ERROR: Invalid operator %s between %s and %s", operator, left.toString(), right.toString()));
        };
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        Type type1, type2;
        type1 = left.typeCheck(typeTable);
        type2 = left.typeCheck(typeTable);
        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType()))
                return new BoolType();
            else
                throw new MyException("ERROR: The second operand is not a bool");
        } else {
            throw new MyException("ERROR: The first operand is not a bool");
        }
    }
}
