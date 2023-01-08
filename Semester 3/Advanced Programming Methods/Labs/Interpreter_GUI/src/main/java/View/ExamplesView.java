package View;

import Controller.Controller;
import Exceptions.MyException;
import Model.ADT.IList;
import Model.ADT.MyList;
import Model.Expressions.*;
import Model.FileManager.CloseFile;
import Model.FileManager.OpenFile;
import Model.FileManager.ReadFile;
import Model.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.RefType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.Repository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

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

    protected static IStatement example4() {
        return buildExample(
                new DeclarationStatement("v", new RefType(new IntType())),
                new New("v", new ValueExpression(new IntValue(20))),
                new PrintStatement(new ReadHeap(new VariableExpression("v"))),
                new WriteHeap("v", new ValueExpression(new IntValue(30))),
                new PrintStatement(new ArithExpression(BinaryExpression.OPERATOR.ADD, new ReadHeap(new VariableExpression("v")), new ValueExpression(new IntValue(5))))
        );
    }

    protected static IStatement example5() {
        return buildExample(
                new DeclarationStatement("v", new RefType(new IntType())),
                new New("v", new ValueExpression(new IntValue(20))),
                new DeclarationStatement("a", new RefType(new RefType(new IntType()))),
                new New("a", new VariableExpression("v")),
                new WriteHeap("v", new ValueExpression(new IntValue(30))),
                new PrintStatement(new ReadHeap(new ReadHeap(new VariableExpression("a"))))
        );
    }

    protected static IStatement example6() {
        return buildExample(
                new DeclarationStatement("v", new IntType()),
                new AssStatement("v", new ValueExpression(new IntValue(4))),
                new WhileStatement(
                        new RelationalExpression(
                                BinaryExpression.OPERATOR.MORE,
                                new VariableExpression("v"),
                                new ValueExpression(new IntValue(0))
                        ),
                        buildExample(
                                new PrintStatement(new VariableExpression("v")),
                                new AssStatement("v",
                                        new ArithExpression(
                                                BinaryExpression.OPERATOR.SUBSTR,
                                                new VariableExpression("v"),
                                                new ValueExpression(new IntValue(1))
                                        )
                                )
                        )
                ),
                new PrintStatement(new VariableExpression("v"))
        );
    }

    protected static IStatement example7() {
        IStatement frk = buildExample(
                new WriteHeap("a", new ValueExpression(new IntValue(30))),
                new AssStatement("v", new ValueExpression(new IntValue(32))),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new ReadHeap(new VariableExpression("a")))
        );
        return buildExample(
                new DeclarationStatement("v", new IntType()),
                new DeclarationStatement("a", new RefType(new IntType())),
                new AssStatement("v", new ValueExpression(new IntValue(10))),
                new New("a", new ValueExpression(new IntValue(22))),
                new ForkStatement(frk),
                new PrintStatement(new VariableExpression("v")),
                new PrintStatement(new ReadHeap(new VariableExpression("a")))
        );
    }

    public static IStatement[] exampleList() {
        return new IStatement[]{example0(), example1(), example2(), example3(), example4(), example5(), example6(), example7()};
    }

    @Override
    public void execute() {
        ProgramState programState = new ProgramState();
        List<ProgramState> programStates = new ArrayList<>();
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
