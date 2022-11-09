package Model.Types;

import Model.Values.IntValue;
import Model.Values.Values;

public class IntType implements Type {
    @Override
    public boolean equals(Type other) {
        return other instanceof IntType;
    }

    @Override
    public Values getDefault() {
        return new IntValue(0);
    }

    @Override
    public String toString() {
        return "Int";
    }
}
