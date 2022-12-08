package Repository;

import Exceptions.MyException;
import Model.ADT.IList;
import Model.ProgramState;
import java.io.IOException;
import java.util.List;

public interface IRepository {
    void addPrg(ProgramState newPrg);

    void logProgramStateExecution(ProgramState programState) throws IOException;
    List<ProgramState> getProgramStates();
    void setProgramStates(List<ProgramState> prgStates);

    ProgramState getCurrentPrg();
}
