package entities;

import sharedRegions.AssaultParty;
import sharedRegions.ConcentrationSite;
import sharedRegions.ControlSite;

/**
 *   Master Thief thread.
 * <p>
 *   It simulates the Master Thief life cycle.
 *   Static solution.
 */
public class MasterThief extends Thread {
    /**
     *  Master Thief state
     */
    private int masterThiefState;

    /**
     * A reference to the Concentration Site
     */
    private final ConcentrationSite concentrationSite;

    /**
     * A reference to the Control Site
     */
    private final ControlSite controlSite;

    /**
     * An array of references to the Assault Parties
     */
    private final AssaultParty[] assaultParties;

    /**
     *   Instantiation of the Master Thief thread.
     */
    public MasterThief(ConcentrationSite concentrationSite, ControlSite controlSite, AssaultParty[] assaultParties) {
        super("MasterThief");
        masterThiefState = MasterThiefStates.PLANNING_THE_HEIST;
        this.concentrationSite = concentrationSite;
        this.controlSite = controlSite;
        this.assaultParties = assaultParties;
    }

    /**
     *   Get Master Thief state.
     *
     *   @return Master Thief state
     */
    public int getMasterThiefState() {
        return masterThiefState;
    }

    /**
     *   Set Master Thief state
     *
     *   @param masterThiefState the new Master Thief state
     */
    public void setMasterThiefState(int masterThiefState) {
        this.masterThiefState = masterThiefState;
    }

    /**
     *   Life cycle of the Master Thief.
     */
    @Override
    public void run () {
        controlSite.startOperations();

        char op;
        while((op = controlSite.appraiseSituation()) != 'E') {
            switch (op) {
                case 'P':
                {
                    int assGroupId = controlSite.getAssaultId();
                    concentrationSite.prepareAssaultParty(assGroupId, controlSite.getRoomId());
                    assaultParties[assGroupId].sendAssaultParty();

                    break;
                }
                case 'R':
                {
                    controlSite.takeARest();
                    controlSite.collectACanvas();

                    break;
                }
            }
        }

        concentrationSite.sumUpResults(controlSite.getNumCollectedCanvases());
    }
}
