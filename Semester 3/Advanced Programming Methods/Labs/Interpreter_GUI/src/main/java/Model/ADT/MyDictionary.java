package Model.ADT;

import Exceptions.MyException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDictionary<K, V> implements IDictionary<K, V>{
    private final Map<K, V> dictionary;

    public MyDictionary() {
        this.dictionary = new HashMap<K, V>();
    }

    public MyDictionary(Map<K, V> dictionary) {
        this.dictionary = dictionary;
    }


    @Override
    public V get(K key) {
        synchronized (dictionary) {
            return this.dictionary.get(key);
        }
    }

    @Override
    public V put(K key, V value) {
        synchronized (dictionary) {
            return this.dictionary.put(key, value);
        }
    }

    @Override
    public void remove(K key) throws MyException {
        synchronized (dictionary) {
            if (!this.dictionary.containsKey(key))
                throw new MyException("ERROR: Dictionary does not contain key.");
            this.dictionary.remove(key);
        }
    }

    @Override
    public boolean containsKey(K key) {
        synchronized (dictionary) {
            return this.dictionary.containsKey(key);
        }
    }

    @Override
    public boolean containsValue(V value) {
        synchronized (dictionary) {
            return this.dictionary.containsValue(value);
        }
    }

    @Override
    public Collection<V> values() {
        synchronized (dictionary) {
            return this.dictionary.values();
        }
    }

    @Override
    public Set<K> keys() {
        synchronized (dictionary) {
            return this.dictionary.keySet();
        }
    }

    @Override
    public MyDictionary<K, V> copy() {
        MyDictionary<K, V> newDict = new MyDictionary<>();
        for (K key : this.keys()) {
            newDict.put(key, this.dictionary.get(key));
        }
        return newDict;
    }

    @Override
    public Iterable<Map.Entry<K, V>> getAll() {
        synchronized (dictionary) {
            return this.dictionary.entrySet();
        }
    }

    @Override
    public Map<K, V> getContent() {
        synchronized (dictionary) {
            return this.dictionary;
        }
    }

    @Override
    public int size() {
        synchronized (dictionary) {
            return this.dictionary.size();
        }
    }
}
