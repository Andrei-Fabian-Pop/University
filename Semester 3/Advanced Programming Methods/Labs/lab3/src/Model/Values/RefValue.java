package Model.Values;

import Model.Types.RefType;
import Model.Types.Type;

public class RefValue implements Values {
    private final String address;
    private final Type locationType;

    public RefValue(String address_, Type locationType_) {
        address = address_;
        locationType = locationType_;
    }

    public String getAddress() {
        return address;
    }

    public Type getLocationType() {
        return locationType;
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public String toString() {
        return String.format("ReferenceValue{%s in %s}", address, locationType);
    }
}
