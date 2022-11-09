package Model.Expressions;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Types.Type;
import Model.Values.Values;


public interface Expression {
    Values eval(IDictionary<String, Values> symTable) throws MyException;
    Type typeCheck(IDictionary<String, Type> typeTable) throws MyException;
}
