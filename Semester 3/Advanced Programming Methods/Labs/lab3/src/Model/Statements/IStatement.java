package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ProgramState;
import Model.Types.Type;

public interface IStatement {
    ProgramState execute(ProgramState state) throws MyException;
}
