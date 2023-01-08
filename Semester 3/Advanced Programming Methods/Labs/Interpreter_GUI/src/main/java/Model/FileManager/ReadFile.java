package Model.FileManager;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Values;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStatement {
    private final Expression expression;
    private final String varName;

    public ReadFile(Expression expression, String varName) {
        this.expression = expression;
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IDictionary<String, Values> symTable = state.getSymTable();
        IDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if (!symTable.containsKey(varName))
            throw new MyException(String.format("ERROR: %s is not present in the symTable", varName));
        Values value = symTable.get(varName);

        if (!value.getType().equals(new IntType()))
            throw new MyException(String.format("ERROR: %s is not of type IntType", value));
        value = expression.eval(symTable, state.getHeap());

        if (!value.getType().equals(new StringType()))
            throw new MyException(String.format("ERROR: %s does not evaluate to StringType", value));
        StringValue castValue = (StringValue) value;

        if (!fileTable.containsKey(castValue.getVal()))
            throw new MyException(String.format("ERROR: the fileTable does not contain %s", castValue));

        BufferedReader bufferedReader = fileTable.get(castValue.getVal());
        try {
            String line = bufferedReader.readLine();
            if (line == null)
                line = "0";
            symTable.put(varName, new IntValue(Integer.parseInt(line)));
        } catch (IOException e) {
            throw new MyException(String.format("ERROR: could not read from file %s", castValue));
        }

        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        if (!expression.typeCheck(typeTable).equals(new StringType())) {
            throw new MyException("ERROR: ReadFile requires a string as expression parameter");
        }
        if (!typeTable.get(varName).equals(new IntType())) {
            throw new MyException("ERROR: ReadFile requires an int as variable parameter");
        }
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("ReadFile {%s: %s}", expression, varName);
    }
}
