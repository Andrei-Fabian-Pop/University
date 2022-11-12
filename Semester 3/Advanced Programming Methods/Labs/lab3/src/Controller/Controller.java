package Controller;

import Exceptions.MyException;
import Model.ADT.IList;
import Model.ADT.IStack;
import Model.ProgramState;
import Model.Statements.IStatement;
import Repository.IRepository;

import java.io.IOException;

public class Controller {
    private final IRepository repository;
    private boolean displayFlag;

    public Controller(IRepository repository) {
        this.repository = repository;
        this.displayFlag = false;
    }

    public void displayOn() { this.displayFlag = true; }
    public void displayOff() { this.displayFlag = false; }

    public void addPrg(ProgramState programState) {
        repository.addPrg(programState);
    }

    public IList<ProgramState> getProgramState() {
        return repository.getProgramStates();
    }

    private void displayCurrentProgrammeState(ProgramState programState) {
        if (this.displayFlag) {
            System.out.println(programState.toString());
        }
    }

    public ProgramState oneStep(ProgramState programState) throws MyException {
        IStack<IStatement> stack = programState.getExecStack();
        if (stack.isEmpty()) {
            throw new MyException("PrgState stack is empty");
        }
        IStatement crtStatement = stack.pop();

        this.displayCurrentProgrammeState(programState);

        return crtStatement.execute(programState);
    }

    public void allStep() throws MyException {
        try {
            ProgramState programState = repository.getCurrentPrg();

            repository.logProgramStateExecution(programState);
            while (!programState.getExecStack().isEmpty()) {
                this.oneStep(programState);
                repository.logProgramStateExecution(programState);
            }
        } catch (IOException e) {
            System.out.println(e.toString());
        }
    }
}
