package Model.FileManager;

import Exceptions.MyException;
import Model.ADT.IDictionary;
import Model.Expressions.Expression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Values;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenFile implements IStatement {
    private final Expression expression;

    public OpenFile(Expression expression) {
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
        if (fileTable.containsKey(fileName.getVal())) {
            throw new MyException(String.format("ERROR: %s is already opened", fileName));
        }

        BufferedReader bufferedReader;
        try {
            bufferedReader = new BufferedReader(new FileReader(fileName.getVal()));
        } catch (IOException e) {
            throw new MyException(String.format("ERROR: %s could not be opened", fileName));
        }
        fileTable.put(fileName.getVal(), bufferedReader);
        return null;
    }

    @Override
    public String toString() {
        return String.format("Open(r) file {%s}", expression);
    }
}
