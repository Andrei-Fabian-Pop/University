package Model.Statements;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Values;

public class DeclarationStatement implements IStatement{
    private final String name;
    private final Type type;

    public DeclarationStatement(String name, Type type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Values> symTable = state.getSymTable();
        if (symTable.containsKey(name)) {
            throw new MyException(String.format("ERROR: %s is already declared.", name));
        }
        symTable.put(name, type.getDefault());
        return null;
    }

    public String toString() {
        return String.format("Declaration{%s: %s}", name, type.toString());
    }
}
