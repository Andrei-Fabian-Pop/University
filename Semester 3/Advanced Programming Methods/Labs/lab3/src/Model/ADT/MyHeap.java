package Model.ADT;

import Exceptions.MyException;
import Model.Values.Values;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class MyHeap implements IHeap {
    private final Map<String, Values> map;
    private String freeValue;

    public String newValue() {
        Random random = new Random();
        this.freeValue = Integer.toHexString(random.nextInt());
        while (freeValue.equals("0") || map.containsKey(freeValue)) {
            freeValue = Integer.toHexString(random.nextInt());
        }
        return freeValue;
    }

    public MyHeap(Map<String, Values> map) {
        this.map = map;
        this.freeValue = newValue();
    }

    public MyHeap() {
        this.map = new HashMap<>();
        this.freeValue = newValue();
    }

    @Override
    public String getFreeValue() {
        synchronized (this) {
            return freeValue;
        }
    }

    @Override
    public Map<String, Values> getContent() {
        synchronized (this) {
            return map;
        }
    }

    @Override
    public void setContent(Map<String, Values> newMap) {
        synchronized (this) {
            map.clear();
            for (String i : newMap.keySet()) {
                map.put(i, newMap.get(i));
            }
        }
    }

    @Override
    public String add(Values value) {
        synchronized (this) {
            map.put(this.freeValue, value);
            String res = this.freeValue;
            this.freeValue = this.newValue();

            return res;
        }
    }

    @Override
    public void update(String position, Values value) throws MyException {
        synchronized (this) {
            if (!map.containsKey(position)) {
                throw new MyException(String.format("ERROR: %s is not present in the heap", position));
            }
            map.put(position, value);
        }
    }

    @Override
    public Values get(String position) throws MyException {
        synchronized (this) {
            if (!map.containsKey(position)) {
                throw new MyException(String.format("ERROR: %s is not present in the heap", position));
            }

            return map.get(position);
        }
    }
}
