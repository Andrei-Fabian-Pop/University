package Model.ADT;

import Exceptions.MyException;
import Model.Values.Values;

import java.util.Map;

public interface IHeap {
    String getFreeValue();
    Map<String, Values> getContent();
    void setContent(Map<String, Values> newMap);
    String add(Values value);
    void update(String position, Values value) throws MyException;
    Values get(String position) throws MyException;
}
