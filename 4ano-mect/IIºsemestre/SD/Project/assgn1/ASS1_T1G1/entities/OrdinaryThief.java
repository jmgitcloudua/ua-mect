package entities;

import sharedRegions.AssaultParty;
import sharedRegions.ConcentrationSite;
import sharedRegions.ControlSite;
import sharedRegions.Museum;

/**
 *   Ordinary Thief thread.
 * <p>
 *   It simulates the Ordinary Thief life cycle.
 *   Static solution.
 */
public class OrdinaryThief extends Thread {
    /**
     *  Ordinary Thief state
     */
    private int ordinaryThiefState;

    /**
     *  Ordinary Thief agility
     */
    private int ordinaryThiefAgility;

    /**
     *  Ordinary Thief id
     */
    private int ordinaryThiefId;

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
     * A reference to the museum
     */
    private final Museum museum;

    public OrdinaryThief(int ordinaryThiefId, int ordinaryThiefAgility, ConcentrationSite concentrationSite,
                         ControlSite controlSite, AssaultParty[] assaultParties, Museum museum) {
        super("Thief_" + ordinaryThiefId);
        this.ordinaryThiefId = ordinaryThiefId;
        ordinaryThiefState = OrdinaryThiefStates.CONCENTRATION_SITE;
        this.ordinaryThiefAgility = ordinaryThiefAgility;
        this.concentrationSite = concentrationSite;
        this.controlSite = controlSite;
        this.assaultParties = assaultParties;
        this.museum = museum;
    }

    /**
     * Get Ordinary Thief state.
     *
     * @return Ordinary Thief state
     */
    public int getOrdinaryThiefState() {
        return ordinaryThiefState;
    }

    /**
     *   Set Ordinary Thief state
     *
     *   @param ordinaryThiefState the new Ordinary Thief state
     */
    public void setOrdinaryThiefState(int ordinaryThiefState) {
        this.ordinaryThiefState = ordinaryThiefState;
    }

    /**
     * Get Ordinary Thief agility.
     *
     * @return Ordinary Thief agility
     */
    public int getOrdinaryThiefAgility() {
        return ordinaryThiefAgility;
    }

    /**
     *   Set Ordinary Thief agility
     *
     *   @param ordinaryThiefAgility the new Ordinary Thief agility
     */
    public void setOrdinaryThiefAgility(int ordinaryThiefAgility) {
        this.ordinaryThiefAgility = ordinaryThiefAgility;
    }

    /**
     * Get Ordinary Thief id.
     *
     * @return Ordinary Thief id
     */
    public int getOrdinaryThiefId() {
        return ordinaryThiefId;
    }

    /**
     *   Set Ordinary Thief state
     *
     *   @param ordinaryThiefId the new Ordinary Thief state
     */
    public void setOrdinaryThiefId(int ordinaryThiefId) {
        this.ordinaryThiefId = ordinaryThiefId;
    }

    /**
     *   Life cycle of an Ordinary Thief.
     */
    @Override
    public void run () {
        while(concentrationSite.amINeeded() != 'E') {
            int assaultPartyId = concentrationSite.prepareExcursion();
            AssaultParty assaultParty = assaultParties[assaultPartyId];

            while(assaultParty.crawlIn());
            museum.rollACanvas(assaultPartyId);
            assaultParty.reverseDirection();
            while(assaultParty.crawlOut());
            controlSite.handACanvas(assaultPartyId);
        }
    }
}
