package Model.Values;

import Model.Types.BoolType;
import Model.Types.Type;

public class BoolValue implements Values{
    private boolean value;

    public BoolValue(boolean value_) {
        this.value = value_;
    }

    public boolean getValue() {
        return value;
    }

    public void setValue(boolean value) {
        this.value = value;
    }

    @Override
    public String toString() {
        return this.value ? "true" : "false";
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof BoolValue newObj)) {
            return false;
        }
        return this.value == newObj.value;
    }
}
