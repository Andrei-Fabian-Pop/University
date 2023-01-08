package Model.Types;

import Model.Values.Values;

public interface Type {
    boolean equals(Type other);
    Values getDefault();
    String toString();
}
