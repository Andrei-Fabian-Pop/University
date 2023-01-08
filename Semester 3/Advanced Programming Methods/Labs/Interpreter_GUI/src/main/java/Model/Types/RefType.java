package Model.Types;

import Model.Values.RefValue;
import Model.Values.Values;

public class RefType implements Type {
    private final Type inner;

    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return inner;
    }

    @Override
    public boolean equals(Type other) {
        if (other instanceof RefType) {
            return inner.equals(((RefType)other).getInner());
        }
        return false;
    }

    @Override
    public Values getDefault() {
        return new RefValue("0", inner);
    }

    @Override
    public String toString() {
        return "Reference(" + inner.toString() + ")";
    }
}
