package sharedRegions;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

import commInfra.MemException;
import commInfra.MemFIFO;
import entities.MasterThief;
import entities.MasterThiefStates;
import entities.OrdinaryThief;
import entities.OrdinaryThiefStates;
import main.SimulPar;

public class ControlSite {
    /**
     * Explicit mutual exclusion access lock
     */
    private final Lock mutex;

    /**
     * Condition that gets signalled when an ordinary thief enters the delivery queue
     */
    private final Condition deliveryQueueEmpty;

    /**
     * Condition that gets signalled when the master thief collects a canvas to awake the thief delivering
     */
    private final Condition deliveryComplete;

    /**
     * Condition that gets signalled when the delivering thief has been awakened
     */
    private final Condition thiefLeft;

    /**
     * Reference to the General Information Repository
     */
    private final GeneralRepos generalRepos;

    /**
     * Array of references to the various Assault Parties
     */
    private final AssaultParty[] assaultParties;

    /**
     * Delivery Queue used by the Master Thief to attend to canvas deliveries by the ordinary thieves
     */
    private MemFIFO<Delivery> deliveryQueue;

    /**
     * Contains how many Ordinary Thieves are currently in the delivery queue
     */
    private int deliveryQueueCount;

    /**
     * Holds the number of Ordinaru Thives that haven't arrived here yet for every Assault Party
     */
    private final int[] numPartyMembersInside;

    /**
     * Used to keep track of which rooms are empty
     */
    private final boolean[] emptyRooms;

    /**
     * Used to keep track of how many canvases have been collected
     */
    private int numCollectedCanvas;

    /**
     * The id of the Ordinary Thief currently being attended to by the Master Thief
     */
    private int deliveringThiefId;

    /**
     * Whether the Ordinary Thief currently being attended to by the Master Thief is carrying a canvas
     */
    private boolean deliveringThiefHasCanvas;

    /**
     * The Assault Party id of the Ordinary Thief currently being attended to by the Master Thief
     */
    private int deliveringThiefAssParty;

    /**
     * The room id where the Ordinary Thief currently being attended to by the Master Thief came from
     */
    private int deliveringThiefRoomId;

    /**
     * Holds the id of the next assault party to be sent after appraiseSituation
     */
    private int assaultPartyId;

    /**
     * Holds the id of the room the next assault party will be sent to rob
     */
    private int roomId;

    public ControlSite(GeneralRepos generalRepos, AssaultParty[] assaultParties) {
        mutex = new ReentrantLock();
        deliveryQueueEmpty = mutex.newCondition();
        deliveryComplete = mutex.newCondition();
        thiefLeft = mutex.newCondition();

        this.generalRepos = generalRepos;
        this.assaultParties = assaultParties;

        try {
            deliveryQueue = new MemFIFO<>(new Delivery[SimulPar.NUMBER_OF_THIEVES-1]);
        }catch (MemException e) {
            System.err.println("Instantiation of waiting FIFO failed: " + e.getMessage ());
            System.exit(1);
        }
        deliveryQueueCount = 0;

        numPartyMembersInside = new int[SimulPar.NUM_ASS_PARTIES];
        emptyRooms = new boolean[SimulPar.NUMBER_OF_ROOMS];
        numCollectedCanvas = 0;
        deliveringThiefId = -1;
        deliveringThiefHasCanvas = false;
        deliveringThiefAssParty = -1;
        deliveringThiefRoomId = -1;
        assaultPartyId = -1;
        roomId = -1;
    }

    /**
     * Called by the Master Thief once at startup to set up operations
     */
    public void startOperations() {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof MasterThief);
        MasterThief masterThief = (MasterThief)callingThread;

        masterThief.setMasterThiefState(MasterThiefStates.DECIDING_WHAT_TO_DO);
        generalRepos.setMasterThiefState(MasterThiefStates.DECIDING_WHAT_TO_DO);

        mutex.unlock();
    }

    /**
     * Called by the Master Thief to decide what the next operation should be
     * @return a character representing the next operation. E if the heist is complete. P if a new Assault Party should be sent out. R to rest and wait for a canvas
     */
    public char appraiseSituation() {
        mutex.lock();

        // how many assault parties are in operation currently
        int numPartiesInOperation = 0;
        for(int a = 0; a < SimulPar.NUM_ASS_PARTIES; a++) {
            if(numPartyMembersInside[a] != 0) {
                numPartiesInOperation++;
            }
        }

        // how many rooms we know are empty
        int numEmptyRooms = 0;
        for(int r = 0; r < SimulPar.NUMBER_OF_ROOMS; r++) {
            if(emptyRooms[r]) {
                numEmptyRooms++;
            }
        }

        // clear the next assault party variables
        assaultPartyId = -1;
        roomId = -1;

        char result;
        if(numEmptyRooms == SimulPar.NUMBER_OF_ROOMS && numPartiesInOperation == 0) {   // If all rooms are empty and there is no assault party in operation we are done
            result = 'E';
        }
        else
        {
            result = 'R';   // set takeARest as next operation

            // try and find an assault party to send
            int candidateAssaultPartyId = -1;
            for(int a = 0; a < SimulPar.NUM_ASS_PARTIES; a++) {
                if(numPartyMembersInside[a] == 0) {
                    candidateAssaultPartyId = a;
                    break;
                }
            }

            // if we have one. try to find a room that's not empty and not currently being robbed by another assault party
            if(candidateAssaultPartyId >= 0) {
                int candidateRoomId = -1;

                for(int r = 0; r < SimulPar.NUMBER_OF_ROOMS && candidateRoomId == -1; r++) {
                    if(!emptyRooms[r]) {
                        boolean beingRobbed = false;
                        for(int a = 0; a < SimulPar.NUM_ASS_PARTIES; a++) {
                            if(numPartyMembersInside[a] > 0 && assaultParties[a].getRoomId() == r) {
                                beingRobbed = true;
                                break;
                            }
                        }

                        if(!beingRobbed) candidateRoomId = r;
                    }
                }

                // if we find a room, set the next operation to sendAssaultParty and update internal state
                if(candidateRoomId >= 0) {
                    assaultPartyId = candidateAssaultPartyId;
                    numPartyMembersInside[assaultPartyId] = SimulPar.ASSAULT_PARTY_SIZE;
                    roomId = candidateRoomId;
                    result = 'P';
                }
            }
        }

        mutex.unlock();
        return result;
    }

    /**
     * Called by the Master Thief to await a canvas delivery
     */
    public void takeARest() {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof MasterThief);
        MasterThief masterThief = (MasterThief)callingThread;

        masterThief.setMasterThiefState(MasterThiefStates.WAITING_FOR_GROUP_ARRIVAL);
        generalRepos.setMasterThiefState(MasterThiefStates.WAITING_FOR_GROUP_ARRIVAL);

        while(deliveryQueueCount == 0) {    // wait until there's someone in the delivery queue
            try {
                deliveryQueueEmpty.await();
            } catch (InterruptedException ignored) {}
        }

        Delivery delivery = null;
        try {
            delivery = deliveryQueue.read();
            deliveryQueueCount--;
        } catch (MemException e) {
            System.err.println("Delivery FIFO read failed: " + e.getMessage ());
            System.exit(1);
        }

        // update current delivery data
        deliveringThiefId = delivery.getThiefId();
        deliveringThiefAssParty = delivery.getAssaultPartyId();
        deliveringThiefHasCanvas = delivery.hasCanvas();
        deliveringThiefRoomId = assaultParties[deliveringThiefAssParty].getRoomId();

        mutex.unlock();
    }

    /**
     * Called by the Master Thief after being awakened in takeARest() by an Ordinary Thief
     */
    public void collectACanvas() {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof MasterThief);
        MasterThief masterThief = (MasterThief)callingThread;

        numPartyMembersInside[deliveringThiefAssParty]--;
        if(numPartyMembersInside[deliveringThiefAssParty] == 0) {   // if all members of this assault party have arrived it is now free
            assaultParties[deliveringThiefAssParty].clear();
            generalRepos.setAssaultPartyRoom(deliveringThiefAssParty, -1);
        }

        if(!deliveringThiefHasCanvas) { // if a thief arrived without a canvas, the room is empty
            emptyRooms[deliveringThiefRoomId] = true;
        }
        else {
            numCollectedCanvas++;
        }
        deliveryComplete.signalAll(); // signal thieves a delivery as been completed

        try {
            thiefLeft.await();  // wait until thief that was delivering has left
        } catch (InterruptedException ignored) {}

        masterThief.setMasterThiefState(MasterThiefStates.DECIDING_WHAT_TO_DO);
        generalRepos.setMasterThiefState(MasterThiefStates.DECIDING_WHAT_TO_DO);

        mutex.unlock();
    }

    /**
     * Called by an Ordinary Thief to deliver a canvas
     * @param assaultPartyId The Assault Party id of the delivering thief
     */
    public void handACanvas(int assaultPartyId) {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        AssaultParty assaultParty = assaultParties[assaultPartyId];
        int internalAssaultPartyId = assaultParty.getInternalThiefIdFromThiefId(thief.getOrdinaryThiefId());
        try {
            deliveryQueue.write(new Delivery(thief.getOrdinaryThiefId(), assaultPartyId,    // enter the delivery queue
                    assaultParty.hasCanvas(thief.getOrdinaryThiefId())));
        } catch (MemException e) {
            System.err.println("Delivery FIFO write failed: " + e.getMessage ());
            System.exit(1);
        }
        deliveryQueueCount++;
        deliveryQueueEmpty.signal();    // signal delivery queue not empty

        while(deliveringThiefId != thief.getOrdinaryThiefId()) {    // wait until I'm the one being attended
            try {
                deliveryComplete.await();
            } catch (InterruptedException ignored) {}
        }
        deliveringThiefId = -1;
        deliveringThiefAssParty = -1;
        deliveringThiefHasCanvas = false;
        deliveringThiefRoomId = -1;

        generalRepos.setOrdinaryThiefStateAndAssPartyIdAndPosAndCvAndSit(thief.getOrdinaryThiefId(),
                internalAssaultPartyId, OrdinaryThiefStates.COLLECTION_SITE,
                assaultPartyId, 0, false, 'W');
        thiefLeft.signal(); // signal I'm leaving

        mutex.unlock();
    }

    /**
     * @return The Assault Party id of the next Assault Party to be sent out
     */
    public int getAssaultId() {
        mutex.lock();
        int result = assaultPartyId;
        mutex.unlock();
        return result;
    }

    /**
     * @return The Museum Room id that the next Assault Party will be sent to
     */
    public int getRoomId() {
        mutex.lock();
        int result = roomId;
        mutex.unlock();
        return result;
    }

    /**
     * @return The number of canvases collected
     */
    public int getNumCollectedCanvases() {
        mutex.lock();
        int result = numCollectedCanvas;
        mutex.unlock();
        return result;
    }

    /**
     * Internal class containing the information required by the Master Thief to process a canvas delivery
     */
    private static class Delivery {
        /**
         * The id of the thief
         */
        private final int thiefId;
        /**
         * Whether he is carrying a canvas
         */
        private final boolean hasCanvas;
        /**
         * The id of the Assault Party he's in
         */
        private final int assaultPartyId;

        public Delivery(int thiefId, int assaultPartyId, boolean hasCanvas) {
            this.thiefId = thiefId;
            this.assaultPartyId = assaultPartyId;
            this.hasCanvas = hasCanvas;
        }

        /**
         * @return The id of the thief
         */
        public int getThiefId() {
            return thiefId;
        }

        /**
         * @return Whether he is carrying a canvas
         */
        public boolean hasCanvas() {
            return hasCanvas;
        }

        /**
         * @return The id of the Assault Party he's in
         */
        public int getAssaultPartyId() {
            return assaultPartyId;
        }
    }
}