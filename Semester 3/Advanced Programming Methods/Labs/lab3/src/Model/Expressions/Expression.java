package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ADT.IHeap;
import Model.Types.Type;
import Model.Values.Values;


public interface Expression {
    Values eval(IDictionary<String, Values> symTable, IHeap heap) throws MyException;
    Type typeCheck(IDictionary<String, Type> typeTable) throws MyException;
}
