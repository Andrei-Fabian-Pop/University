package Model.Types;

import Model.Values.BoolValue;
import Model.Values.Values;

public class BoolType implements Type {

    @Override
    public boolean equals(Type other) {
        return other instanceof BoolType;
    }

    @Override
    public Values getDefault() {
        return new BoolValue(false);
    }

    @Override
    public String toString() {
        return "Bool";
    }
}
