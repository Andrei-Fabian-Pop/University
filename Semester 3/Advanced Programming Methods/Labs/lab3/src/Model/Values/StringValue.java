package Model.Values;

import Model.Types.StringType;
import Model.Types.Type;

import java.util.concurrent.TimeUnit;

public class StringValue implements Values{
    private final String val;

    public StringValue(String val) {
        this.val = val;
    }

    public String getVal() {
        return val;
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public String toString() {
        return val;
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof StringValue cast)) {
            return false;
        }
        return val.equals(cast.val);
    }
}
