package Model.Values;

import Model.Types.IntType;
import Model.Types.Type;

public class IntValue implements Values {
    private int value;

    public IntValue(int value_) {
        this.value = value_;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public Type getType() {
        return new IntType();
    }

    @Override
    public String toString() {
        return String.format("%d", this.value);
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof IntValue)) {
            return false;
        }
        return this.value == ((IntValue) obj).value;
    }
}
