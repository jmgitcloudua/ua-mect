package entities;

/**
 *    Definition of the internal states of the Master Thief during her life cycle.
 */
public final class MasterThiefStates {

    /**
     *   The Master Thief initial state
     */
    public static final int PLANNING_THE_HEIST = 0;
    /**
     *   The Master Thief is deciding whether to rest, send an assault party or leave
     */
    public static final int DECIDING_WHAT_TO_DO = 1;
    /**
     *   The Master Thief is assembling an assault party
     */
    public static final int ASSEMBLING_A_GROUP = 2;
    /**
     *   The Master Thief is waiting to collect canvases
     */
    public static final int WAITING_FOR_GROUP_ARRIVAL = 3;
    /**
     *   The Master Thief final state where she delivers the looting results to the ordinary thieves
     */
    public static final int PRESENTING_THE_REPORT = 4;


    private MasterThiefStates() {}
}
