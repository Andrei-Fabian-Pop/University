package Controller;

import Exceptions.MyException;
import Model.ADT.IList;
import Model.ADT.IStack;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Values.RefValue;
import Model.Values.Values;
import Repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

public class Controller {
    private final IRepository repository;
    private boolean displayFlag;

    public Controller(IRepository repository) {
        this.repository = repository;
        this.displayFlag = false;
    }

    public void displayOn() {
        this.displayFlag = true;
    }

    public void displayOff() {
        this.displayFlag = false;
    }

    public void addPrg(ProgramState programState) {
        repository.addPrg(programState);
    }

    public IList<ProgramState> getProgramState() {
        return repository.getProgramStates();
    }

    private String displayCurrentProgrammeState(ProgramState programState) {
        if (this.displayFlag) {
            return programState.toString();
        }
        return null;
    }

    Map<String, Values> unsafeGarbageCollector(Set<String> symTableAddr, Map<String, Values> heap) {
        return heap.entrySet().stream()
                .filter(e -> symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    Set<String> getAddrFromSymTable(Collection<Values> symTableValues, Map<String, Values> heap) {
        return symTableValues.stream().filter(v -> v instanceof RefValue).map(v -> {
            RefValue v1 = (RefValue) v;
            return v1.getAddress();
        }).collect(Collectors.toSet());
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

    public IList<String> allStep() throws MyException {
        try {
            ProgramState programState = repository.getCurrentPrg();

            repository.logProgramStateExecution(programState);
            while (!programState.getExecStack().isEmpty()) {
                this.oneStep(programState);
                repository.logProgramStateExecution(programState);
                programState.getHeap().setContent(unsafeGarbageCollector(
                        getAddrFromSymTable(programState.getSymTable().values(), programState.getHeap().getContent()),
                        programState.getHeap().getContent()
                ));
            }
        } catch (IOException e) {
            System.out.println(e.toString());
        }

        return repository.getCurrentPrg().getOut();
    }
}
