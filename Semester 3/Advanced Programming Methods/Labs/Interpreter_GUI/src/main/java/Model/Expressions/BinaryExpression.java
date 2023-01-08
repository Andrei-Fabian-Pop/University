package Model.Expressions;

public abstract class BinaryExpression implements Expression {
    protected final OPERATOR operator;
    protected final Expression left, right;

    protected BinaryExpression(OPERATOR operator, Expression left, Expression right) {
        this.operator = operator;
        this.left = left;
        this.right = right;
    }

    public enum OPERATOR {
        ADD,
        SUBSTR,
        MULT,
        DIV,
        AND,
        OR,
        LESS,
        LESS_EQUAL,
        MORE,
        MORE_EQUAL,
        EQUAL,
        NOT_EQUAL
    }

    public String toString() {
        return String.format("BinaryExpression{%s %s %s}", left.toString(), operator, right.toString());
    }
}
