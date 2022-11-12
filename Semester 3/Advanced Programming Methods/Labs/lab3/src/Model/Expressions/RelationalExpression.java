package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Values;

public class RelationalExpression extends BinaryExpression {
    public RelationalExpression(OPERATOR operator, Expression left, Expression right) {
        super(operator, left, right);
    }

    @Override
    public Values eval(IDictionary<String, Values> symTable) throws MyException {
        IntValue left = getValue(this.left, symTable),
                right = getValue(this.right, symTable);
        return switch (this.operator) {
            case LESS -> new BoolValue(left.getValue() < right.getValue());
            case LESS_EQUAL -> new BoolValue(left.getValue() <= right.getValue());
            case MORE -> new BoolValue(left.getValue() > right.getValue());
            case MORE_EQUAL -> new BoolValue(left.getValue() >= right.getValue());
            case EQUAL -> new BoolValue(left.getValue() == right.getValue());
            case NOT_EQUAL -> new BoolValue(left.getValue() != right.getValue());
            default -> throw new MyException("Unexpected value: " + this.operator);
        };
    }

    @Override
    public Type typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        Type type1 = left.typeCheck(typeTable), type2 = right.typeCheck(typeTable);
        if (type1.equals(new IntType())) {
            if (type1.equals(new IntType())) {
                return new BoolType();
            } else {
                throw new MyException("ERROR: The second operand is not an integer");
            }
        } else {
            throw new MyException("ERROR: The first operand is not an integer");
        }
    }

    private IntValue getValue(Expression expression, IDictionary<String, Values> symTable) throws MyException {
        Values value = expression.eval(symTable);
        if (value instanceof IntValue) {
            return (IntValue) value;
        } else {
            throw new MyException(String.format("ERROR: %s is not of type IntType", value.toString()));
        }
    }
}
