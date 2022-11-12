package View;

import Controller.Controller;
import Exceptions.MyException;
import Model.ADT.IList;
import Model.ADT.MyList;
import Model.Expressions.ArithExpression;
import Model.Expressions.BinaryExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.FileManager.CloseFile;
import Model.FileManager.OpenFile;
import Model.FileManager.ReadFile;
import Model.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.Repository;

import java.io.IOException;

public class ExamplesView implements View {
    public static IStatement buildExample(IStatement... statements) {
        if (statements.length == 0) {
            return new NopStatement();
        } else if (statements.length == 1) {
            return statements[0];
        }
        IStatement finalStatement = new CompStatement(statements[0], statements[1]);
        for (int i = 2; i < statements.length; ++i) {
            finalStatement = new CompStatement(finalStatement, statements[i]);
        }
        finalStatement = new CompStatement(finalStatement, new NopStatement());
        return finalStatement;
    }

    protected static IStatement example0() {
        return buildExample(
                new DeclarationStatement("v", new IntType()),
                new AssStatement("v", new ValueExpression(new IntValue(2))),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new VariableExpression("v"))
        );
    }

    protected static IStatement example1() {
        return buildExample(
                new DeclarationStatement("a", new IntType()),
                new DeclarationStatement("b", new IntType()),
                new AssStatement("a",
                        new ArithExpression(BinaryExpression.OPERATOR.ADD,
                                new ValueExpression(new IntValue(2)),
                                new ArithExpression(BinaryExpression.OPERATOR.MULT,
                                        new ValueExpression(new IntValue(3)),
                                        new ValueExpression(new IntValue(5))
                                )
                        )
                ),
                new AssStatement("b",
                        new ArithExpression(BinaryExpression.OPERATOR.ADD,
                                new VariableExpression("a"),
                                new ValueExpression(new IntValue(1))
                        )
                ),
                new PrintStatement(new VariableExpression("b"))
        );
    }

    protected static IStatement example2() {
        return buildExample(
                new DeclarationStatement("a", new BoolType()),
                new DeclarationStatement("v", new IntType()),
                new AssStatement("a", new ValueExpression(new BoolValue(true))),
                new IfStatement(
                        new VariableExpression("a"),
                            new AssStatement("v", new ValueExpression(new IntValue(2))),
                            new AssStatement("v", new ValueExpression(new IntValue(3)))
                ),
                new PrintStatement(new VariableExpression("v"))
        );
    }

    protected static IStatement example3() {
        return buildExample(
                new DeclarationStatement("varF", new StringType()),
                new AssStatement("varF", new ValueExpression(new StringValue("test.in"))),
                new OpenFile(new VariableExpression("varF")),
                new DeclarationStatement("x", new IntType()),
                new ReadFile(new VariableExpression("varF"), "x"),
                new PrintStatement(new VariableExpression("x")),
                new ReadFile(new VariableExpression("varF"), "x"),
                new PrintStatement(new VariableExpression("x")),
                new CloseFile(new VariableExpression("varF"))
        );
    }

    public static IStatement[] exampleList() {
        return new IStatement[]{example0(), example1(), example2(), example3()};
    }

    @Override
    public void execute() {
        ProgramState programState = new ProgramState();
        IList<ProgramState> programStates = new MyList<>();
        programStates.add(programState);

        try {
            Repository repository = new Repository(programStates, "/home/andrew/uni_github/University/Semester 3/Advanced Programming Methods/Labs/lab3/src/Repository/logFile.txt");
            Controller controller = new Controller(repository);
            IStatement statement = example3();
            try {
                statement.execute(programState);
                controller.displayOn();
                controller.allStep();
                System.out.print("Programme output:\n" + programState.outToString());
            } catch (MyException e) {
                System.out.println(e.toString());
            }
        } catch (IOException e) {
            System.out.println(e.toString());
        }


    }
}
