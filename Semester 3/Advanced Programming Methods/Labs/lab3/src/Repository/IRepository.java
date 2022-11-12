package Repository;

import Exceptions.MyException;
import Model.ADT.IList;
import Model.ProgramState;
import java.io.IOException;

public interface IRepository {
    void addPrg(ProgramState newPrg);

    void logProgramStateExecution(ProgramState programState) throws IOException;
    IList<ProgramState> getProgramStates();
    void setProgramStates(IList<ProgramState> prgStates);

    ProgramState getCurrentPrg();
}
