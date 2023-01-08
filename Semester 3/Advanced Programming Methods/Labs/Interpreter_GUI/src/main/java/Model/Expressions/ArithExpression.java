package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Values;
import Model.Expressions.BinaryExpression;

public class ArithExpression extends BinaryExpression {
    public ArithExpression(OPERATOR operator, Expression left, Expression right) {
        super(operator, left, right);
    }

    private IntValue getValue(Expression expression, IDictionary<String, Values> symTable, IHeap heap) throws MyException {
        Values values = expression.eval(symTable, heap);
        if (values instanceof IntValue) {
            return (IntValue) values;
        } else {
            throw new MyException(String.format("ERROR: %s is not of type IntType", values.toString()));
        }
    }

    @Override
    public Values eval(IDictionary<String, Values> symTable, IHeap heap) throws MyException {
        IntValue leftValue = getValue(left, symTable, heap);
        IntValue rightValue = getValue(right, symTable, heap);
        switch (operator) {
            case ADD -> { return new IntValue(leftValue.getValue() + rightValue.getValue()); }
            case SUBSTR -> { return new IntValue(leftValue.getValue() - rightValue.getValue()); }
            case MULT -> { return new IntValue(leftValue.getValue() * rightValue.getValue()); }
            case DIV -> {
                if (rightValue.getValue() == 0) {
                    throw new MyException("ERROR: Division by 0 is forbidden");
                } else {
                    return new IntValue(leftValue.getValue() / rightValue.getValue());
                }
            }
            default -> {throw new MyException(String.format("ERROR: Invalid operator %s between %s and %s", operator, left.toString(), right.toString()));}
        }
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        Type type1, type2;
        type1 = left.typeCheck(typeTable);
        type2 = right.typeCheck(typeTable);
        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
            } else {
                throw new MyException("ERROR: The second operand is not an integer");
            }
        } else {
            throw new MyException("ERROR: The second operand is not an integer");
        }
    }
}
