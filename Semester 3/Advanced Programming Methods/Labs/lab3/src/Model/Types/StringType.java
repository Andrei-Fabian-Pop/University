package Model.Types;

import Model.Values.StringValue;
import Model.Values.Values;

public class StringType implements Type {

    @Override
    public boolean equals(Type other) {
        return other instanceof StringType;
    }

    @Override
    public Values getDefault() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "string";
    }
}
