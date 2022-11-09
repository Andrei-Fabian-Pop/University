package Model.ADT;

import Exceptions.MyException;

import java.util.Collection;
import java.util.Map;
import java.util.Set;

public interface IDictionary<K, V> {
    V get(K key);
    V put(K key, V value);
    void remove(K key) throws MyException;

    boolean containsKey(K key);
    boolean containsValue(V value);

    Collection<V> values();
    Set<K> keys();

    MyDictionary<K, V> cloneDict();
    Iterable<Map.Entry<K, V>> getAll();

    int size();
    String toString();
}
