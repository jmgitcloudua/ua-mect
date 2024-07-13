package sharedRegions;

import commInfra.MemException;
import commInfra.MemFIFO;
import entities.MasterThief;
import entities.MasterThiefStates;
import entities.OrdinaryThief;
import entities.OrdinaryThiefStates;
import main.SimulPar;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ConcentrationSite {
    /**
     * Explicit mutual exclusion access lock
     */
    private final Lock mutex;

    /**
     * Condition that gets signalled when an ordinary thief joins the queue
     */
    private final Condition thiefQueueEmpty;

    /**
     * Ordinary Thieves wait on this condition until needed by the Master Thief
     * to join an Assault Party. The Master Thief signals this condition when a thief is needed
     */
    private final Condition thiefNeeded;

    /**
     * The Master Thief awaits on this condition after waking up an Ordinary Thief
     * to join an Assault Party. After successfully joining, the Ordinary Thief signals this condition
     */
    private final Condition thiefJoined;

    /**
     * The id of the Ordinary Thief that's being awakened
     */
    private int neededThief;

    /**
     * Reference to the General Information Repository
     */
    private final GeneralRepos generalRepos;

    /**
     * Array of references to the various Assault Parties
     */
    private final AssaultParty[] assaultParties;

    /**
     * A reference to the museum
     */
    private final Museum museum;

    /**
     * A reference to a queue representing the Ordinary Thief queue
     */
    private MemFIFO<Integer> thiefQueue;

    /**
     * The number of thieves currently in the queue
     */
    private int thievesInQueue;

    /**
     * Whether the heist to the museum is done
     */
    private boolean endAssault;

    /**
     * The id of the Assault Party being formed
     */
    private int formingAssPartyId;

    public ConcentrationSite(GeneralRepos generalRepos, AssaultParty[] assaultParties, Museum museum) {
        mutex = new ReentrantLock();
        thiefQueueEmpty = mutex.newCondition();
        thiefNeeded = mutex.newCondition();
        thiefJoined = mutex.newCondition();
        neededThief = -1;

        this.generalRepos = generalRepos;
        this.assaultParties = assaultParties;
        this.museum = museum;

        try {
            thiefQueue = new MemFIFO<>(new Integer[SimulPar.NUMBER_OF_THIEVES-1]);
        }catch (MemException e) {
            System.err.println("Instantiation of thief FIFO failed: " + e.getMessage ());
            System.exit(1);
        }
        thievesInQueue = 0;
        endAssault = false;
        formingAssPartyId = -1;
    }

    /**
     * Called by the Master Thief when the heist is done
     * @param numCollectedCanvas The number of total canvases collected
     */
    public void sumUpResults(int numCollectedCanvas) {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof MasterThief);
        MasterThief masterThief = (MasterThief)callingThread;

        masterThief.setMasterThiefState(MasterThiefStates.PRESENTING_THE_REPORT);
        generalRepos.setMasterThiefState(MasterThiefStates.PRESENTING_THE_REPORT);

        while(!thiefQueue.full()) {
            try {
                thiefQueueEmpty.await();
            } catch (InterruptedException ignored) {}
        }
        generalRepos.sumUpResults(numCollectedCanvas);
        endAssault = true;

        thiefNeeded.signalAll();
        mutex.unlock();
    }

    /**
     * Called by the Master Thief to form an Assault Party
     * @param assGroupId The id of the forming Assault Party
     * @param roomId The id the Assault Party is assigned to
     */
    public void prepareAssaultParty(int assGroupId, int roomId) {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof MasterThief);
        MasterThief masterThief = (MasterThief)callingThread;

        masterThief.setMasterThiefState(MasterThiefStates.ASSEMBLING_A_GROUP);
        generalRepos.setMasterThiefState(MasterThiefStates.ASSEMBLING_A_GROUP);

        while(thievesInQueue < SimulPar.ASSAULT_PARTY_SIZE) {
            try {
                thiefQueueEmpty.await();
            } catch (InterruptedException ignored) {}
        }

        formingAssPartyId = assGroupId;
        AssaultParty assaultParty = assaultParties[assGroupId];
        assaultParty.setRoomId(roomId);
        assaultParty.setRoomDistance(museum.getRoomDistance(roomId));
        generalRepos.setAssaultPartyRoom(assGroupId, roomId);

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            try {
                neededThief = thiefQueue.read();
                thievesInQueue--;
                thiefNeeded.signalAll();
                try {
                    thiefJoined.await();
                } catch (InterruptedException ignored) {}
            } catch (MemException e) {
                System.err.println("Thief FIFO read failed: " + e.getMessage ());
                System.exit(1);
            }
        }

        mutex.unlock();
    }

    /**
     * Called by Ordinary Thieves waiting to form an Assault Party
     * @return 'Y' if they're needed, 'E' if the heist has ended
     */
    public char amINeeded() {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        char result = 'Y';
        if(thief.getOrdinaryThiefState() == OrdinaryThiefStates.COLLECTION_SITE) {
            thief.setOrdinaryThiefState(OrdinaryThiefStates.CONCENTRATION_SITE);
            generalRepos.setOrdinaryThiefState(thief.getOrdinaryThiefId(), OrdinaryThiefStates.CONCENTRATION_SITE);
        }

        try {
            thiefQueue.write(thief.getOrdinaryThiefId());
            thievesInQueue++;
        } catch (MemException e) {
            System.err.println("Thief FIFO write failed: " + e.getMessage ());
            System.exit(1);
        }
        thiefQueueEmpty.signal();

        while(neededThief != thief.getOrdinaryThiefId() && !endAssault) {
            try {
                thiefNeeded.await();
            } catch (InterruptedException ignored) {}
        }
        if(endAssault) {
            result = 'E';
        }
        neededThief = -1;

        mutex.unlock();
        return result;
    }

    /**
     * Called by the Ordinary Thieves to join the Assault Party they're assigned to
     * @return The id of the Assault Party joined
     */
    public int prepareExcursion() {
        mutex.lock();
        int result = formingAssPartyId;

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        AssaultParty assaultParty = assaultParties[formingAssPartyId];
        assaultParty.join(thief.getOrdinaryThiefId());

        thief.setOrdinaryThiefState(OrdinaryThiefStates.CRAWLING_INWARDS);
        generalRepos.setOrdinaryThiefStateAndAssPartyIdAndPosAndCvAndSit(
                thief.getOrdinaryThiefId(), assaultParty.getInternalThiefIdFromThiefId(thief.getOrdinaryThiefId()),
                OrdinaryThiefStates.CRAWLING_INWARDS, formingAssPartyId, 0, false, 'P');

        thiefJoined.signal();
        mutex.unlock();
        return result;
    }
}
