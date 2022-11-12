package Repository;

import Exceptions.MyException;
import Model.ADT.IList;
import Model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Repository implements IRepository {
    private IList<ProgramState> programStates;
    private String logFilePath;

    public Repository(IList<ProgramState> programStates, String logFilePath) {
        this.programStates = programStates;
        this.logFilePath = logFilePath;
    }

    @Override
    public void addPrg(ProgramState newPrg) {
        this.programStates.add(newPrg);
    }

    @Override
    public void logProgramStateExecution(ProgramState programState) throws IOException {
        PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
        logFile.println(programState);
        logFile.close();
    }

    @Override
    public IList<ProgramState> getProgramStates() {
        return this.programStates;
    }

    @Override
    public void setProgramStates(IList<ProgramState> prgStates) {
        this.programStates = prgStates;
    }

    @Override
    public ProgramState getCurrentPrg() {
        return programStates.get(0);
    }
}
