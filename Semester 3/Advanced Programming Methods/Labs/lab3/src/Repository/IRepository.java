package Repository;

import Model.ADT.IList;
import Model.ProgramState;
import java.io.IOException;

public interface IRepository {
    void addPrg(ProgramState newPrg);
    IList<ProgramState> getProgramStates();
    void setProgramStates(IList<ProgramState> prgStates);

    ProgramState getCurrentPrg();
}
