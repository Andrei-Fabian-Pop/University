package Model.FileManager;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Values;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseFile implements IStatement {
    private final Expression expression;

    public CloseFile(Expression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Values value = expression.eval(state.getSymTable(), state.getHeap());
        if (!value.getType().equals(new StringType())) {
            throw new MyException(String.format("ERROR: %s does not evaluate to StringValue", expression));
        }
        StringValue fileName = (StringValue) value;

        IDictionary<String, BufferedReader> fileTable = state.getFileTable();
        if (!fileTable.containsKey(fileName.getVal())) {
            throw new MyException(String.format("ERROR: %s is not present in the symTable", value));
        }

        BufferedReader bufferedReader = fileTable.get(fileName.getVal());
        try {
            bufferedReader.close();
        } catch (IOException e) {
            throw new MyException(String.format("ERROR: Unexpected error in closing %s", value));
        }

        fileTable.remove(fileName.getVal());
        return null;
    }

    @Override
    public IDictionary<String, Type> typeCheck(IDictionary<String, Type> typeTable) throws MyException {
        if (!expression.typeCheck(typeTable).equals(new StringType()))
            throw new MyException("ERROR: CloseFile requires a string expression");
        return typeTable;
    }

    @Override
    public String toString() {
        return String.format("Close(r) file {%s}", expression);
    }
}
