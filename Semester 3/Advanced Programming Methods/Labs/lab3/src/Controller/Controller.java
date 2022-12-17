package Controller;

import Exceptions.MyException;
import Model.ADT.*;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.Type;
import Model.Values.RefValue;
import Model.Values.Values;
import Repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private final IRepository repository;
    private ExecutorService executor;
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

    public List<ProgramState> getProgramState() {
        return repository.getProgramStates();
    }

    private String displayCurrentProgrammeState(ProgramState programState) {
        if (this.displayFlag) {
            return programState.toString();
        }
        return null;
    }

    List<ProgramState> removeCompletedPrograms(List<ProgramState> programStateList) {
        return programStateList.stream().filter(p -> !p.isCompleted()).collect(Collectors.toList());
    }

    Map<String, Values> safeGarbageCollector(Set<String> symTableAddr, Map<String, Values> heap) {
        return heap.entrySet().stream()
                .filter(e -> symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    Set<String> getAddrFromSymTable(List<Collection<Values>> symTableValues, Map<String, Values> heap) {
        Set<String> res = new TreeSet<>();
        symTableValues.forEach(symTable -> symTable.stream()
                .filter(v -> v instanceof RefValue)
                .forEach(v -> {
                    while (v instanceof RefValue) {
                        res.add(((RefValue) v).getAddress());
                        v = heap.get(((RefValue) v).getAddress());
                    }
                })
        );

        return res;
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

    public void oneStepForEachPrg(List<ProgramState> programStateList) throws MyException {
        programStateList.forEach(prg -> {
            try {
                repository.logProgramStateExecution(prg);
            } catch (IOException e) {
                System.out.println(e.getMessage());
                System.exit(1);
            }
        });

        List<Callable<ProgramState>> callableList = programStateList.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::oneStep))
                .collect(Collectors.toList());
        List<Pair<ProgramState, MyException>> newProgramStateList = null;
        try {
            newProgramStateList = executor.invokeAll(callableList).stream()
                    .map(future -> {
                        try {
                            return new Pair<ProgramState, MyException>(future.get(), null);
                        } catch (ExecutionException | InterruptedException e) {
                            if (e.getCause() instanceof MyException) {
                                return new Pair<ProgramState, MyException>(null, (MyException) e.getCause());
                            }
                            System.out.println(e.getMessage());
                            System.exit(1);
                            return null;
                        }
                    }).filter(pair -> pair.first != null || pair.second != null)
                    .collect(Collectors.toList());
        } catch (InterruptedException e) {
            e.printStackTrace();
            System.exit(1);
        }

        for (Pair<ProgramState, MyException> error : newProgramStateList) {
            if (error.second != null) {
                throw error.second;
            }
        }

        programStateList.addAll(newProgramStateList.stream().map(pair -> pair.first).toList());
        repository.setProgramStates(programStateList);
    }

    public void typeChecker() throws MyException {
        for (ProgramState state: repository.getProgramStates()) {
            IDictionary<String, Type> typeTable = new MyDictionary<>();
            state.getExecStack().top().typeCheck(typeTable);
        }
    }

    public IList<String> allStep() throws MyException {
        if (!repository.getCurrentPrg().getOut().isEmpty()) {
            return repository.getCurrentPrg().getOut();
        }
        typeChecker();
        executor = Executors.newFixedThreadPool(2);
        List<ProgramState> programStatesList = removeCompletedPrograms(repository.getProgramStates());
        IList<String> out = programStatesList.get(0).getOut();
        while (!programStatesList.isEmpty()) {
            ProgramState state = programStatesList.get(0);
            state.getHeap().setContent(
                    safeGarbageCollector(
                            getAddrFromSymTable(
                                    programStatesList.stream().map(programState -> programState.getSymTable().getCon tent().values()).collect(Collectors.toList()),
                                    state.getHeap().getContent()
                            ),
                            state.getHeap().getContent()
                    )
            );

            oneStepForEachPrg(programStatesList);
            programStatesList = removeCompletedPrograms(repository.getProgramStates());
        }

        executor.shutdownNow();
//        repository.setProgramStates(programStatesList);
        return out;
    }
}
