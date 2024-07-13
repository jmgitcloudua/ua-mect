package sharedRegions;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import entities.MasterThief;
import entities.MasterThiefStates;
import entities.OrdinaryThief;
import entities.OrdinaryThiefStates;
import main.SimulPar;

public class AssaultParty {

    /**
     * Explicit mutual exclusion access lock
     */
    private final Lock mutex;

    /**
     * Condition that gets signalled to awake an ordinary thief's crawling movement
     */
    private final Condition startCrawling;

    /**
     * Condition that gets signalled when the last Ordinary Thief arrives at the target room
     */
    private final Condition atTheRoom;

    /**
     * Reference to the General Information Repository
     */
    private final GeneralRepos generalRepos;

    /**
     * Holds the Ids of the ordinary thieves in this assault party
     */
    private final int[] thieves;

    /**
     * Holds the current position of the ordinary thieves
     */
    private final int[] thievesPositions;

    /**
     * The room this assault party is robbing
     */
    private int roomId;

    /**
     * The distance from the concentration site to the target room
     */
    private int roomDistance;

    /**
     * The thief that is currently crawling
     */
    private int crawlingThief;

    /**
     * The number of thieves that have arrived at the target room
     */
    private int thievesAtTheRoom;

    /**
     * Keeps track whether a thief has a canvas
     */
    private final boolean[] thiefHasCanvas;

    public AssaultParty(GeneralRepos generalRepos) {
        mutex = new ReentrantLock();
        startCrawling = mutex.newCondition();
        atTheRoom = mutex.newCondition();
        this.generalRepos = generalRepos;

        thieves = new int[SimulPar.ASSAULT_PARTY_SIZE];
        thievesPositions = new int[SimulPar.ASSAULT_PARTY_SIZE];
        thievesAtTheRoom = 0;
        thiefHasCanvas = new boolean[SimulPar.ASSAULT_PARTY_SIZE];
        clear();
    }

    /**
     * Clears the Assault Party internal structure. Used to clear previous data
     */
    public void clear() {
        mutex.lock();
        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            thieves[t] = -1;
            thievesPositions[t] = 0;
            thiefHasCanvas[t] = false;
        }
        thievesAtTheRoom = 0;

        roomId = -1;
        roomDistance = -1;
        crawlingThief = -1;
        mutex.unlock();
    }

    /**
     * Called by the Ordinary Thieves to join an Assault Party
     * @param thiefId the id of an Ordinary Thief
     */
    public void join(int thiefId) {
        mutex.lock();
        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thieves[t] == -1) {
                thieves[t] = thiefId;
                mutex.unlock();
                return;
            }
        }

        System.err.println("Too many thieves in Assault Party");
        System.exit(1);
        mutex.unlock();
    }

    /**
     * Called by the Master Thief after all the Ordinary Thieves have joined the Assault Party
     * Changes state from Assembling a group to Deciding what to do
     * Wakes up the first thief to start crawling
     */
    public void sendAssaultParty() {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof MasterThief);
        MasterThief masterThief = (MasterThief)callingThread;

        crawlingThief = 0;
        startCrawling.signalAll();

        masterThief.setMasterThiefState(MasterThiefStates.DECIDING_WHAT_TO_DO);
        generalRepos.setMasterThiefState(MasterThiefStates.DECIDING_WHAT_TO_DO);
        mutex.unlock();
    }

    /**
     * Called by all the Ordinary Thieves in this Assault Party while moving towards the room
     *
     * @return Whether the thief is at the target room
     */
    public boolean crawlIn() {
        boolean arrived;
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        while(crawlingThief != getInternalThiefIdFromThiefId(thief.getOrdinaryThiefId())) {
            try {
                startCrawling.await();
            } catch (InterruptedException ignored) {}
        }

        boolean iCanGo = true;
        do
        {
            char situation = whereAmIIn(crawlingThief);
            switch(situation)
            {
                case 'F':
                {
                    int thiefBehind = getThiefBehind(crawlingThief);
                    int distanceBetween = Math.abs(thievesPositions[crawlingThief] - thievesPositions[thiefBehind]);
                    int idealMovementTarget = SimulPar.MAX_ASSAULT_PARTY_SEPARATION - distanceBetween;
                    if(idealMovementTarget == 0) {
                        // we can't move at all because of the max separation restriction
                        iCanGo = false;
                    }
                    else {
                        int movementTarget = Math.min(thief.getOrdinaryThiefAgility(), idealMovementTarget);
                        if(thievesPositions[crawlingThief] + movementTarget >= roomDistance) {
                            // we have arrived
                            thievesPositions[crawlingThief] = roomDistance;
                            iCanGo = false;
                        }
                        else {
                            thievesPositions[crawlingThief] += movementTarget;

                            // if our movement was limited by the max separation and not agility we can't go any further for now
                            if(movementTarget == idealMovementTarget) iCanGo = false;
                        }
                    }

                    break;
                }
                case 'M':
                {
                    int thiefBehind = getThiefBehind(crawlingThief);
                    int thiefInFront = getThiefAhead(crawlingThief);

                    int distanceBetween = Math.abs(thievesPositions[crawlingThief] - thievesPositions[thiefBehind]);
                    int idealMovementTarget = SimulPar.MAX_ASSAULT_PARTY_SEPARATION - distanceBetween;

                    if(idealMovementTarget == 0) {
                        // we can't move at all because of the max separation restriction
                        iCanGo = false;
                    }
                    else
                    {
                        int movementTarget = Math.min(thief.getOrdinaryThiefAgility(), idealMovementTarget);

                        if(thievesPositions[crawlingThief] + movementTarget >= roomDistance) {
                            thievesPositions[crawlingThief] = roomDistance;
                            iCanGo = false;
                        }
                        else if(thievesPositions[crawlingThief] + movementTarget == thievesPositions[thiefInFront]) {
                            // we can't overlap with another thief
                            thievesPositions[crawlingThief] = thievesPositions[thiefInFront] - 1;
                            iCanGo = false;
                        }
                        else {
                            thievesPositions[crawlingThief] += movementTarget;

                            // if our movement was limited by the max separation and not agility we can't go any further for now
                            if(movementTarget == idealMovementTarget) iCanGo = false;
                        }
                    }

                    break;
                }
                case 'B':
                {
                    int frontMostPosition = thievesPositions[getThiefInFront()] + SimulPar.MAX_ASSAULT_PARTY_SEPARATION;
                    int targetPosition = Math.min(thievesPositions[crawlingThief] + thief.getOrdinaryThiefAgility(), roomDistance);
                    targetPosition = Math.min(targetPosition, frontMostPosition);
                    boolean found = false;

                    while(!found && targetPosition > thievesPositions[crawlingThief]) {
                        boolean conflict = false;
                        for(int p = 0; p < SimulPar.ASSAULT_PARTY_SIZE; p++) {
                            if(p == crawlingThief) continue;
                            if(thievesPositions[p] == roomDistance) continue;

                            if(targetPosition == thievesPositions[p]) {
                                conflict = true;
                                break;
                            }
                        }
                        if(!conflict)
                        {
                            found = true;
                            continue;
                        }
                        targetPosition--;
                    }

                    // if we can't move, or we're in the room we can't go any further for now
                    if(targetPosition == thievesPositions[crawlingThief] || targetPosition == roomDistance) iCanGo = false;
                    // if our movement was limited by the max separation and not agility we can't go any further for now
                    if(targetPosition == frontMostPosition) iCanGo = false;
                    thievesPositions[crawlingThief] = targetPosition;

                    break;
                }
            }
            generalRepos.setOrdinaryThiefPosition(thief.getOrdinaryThiefId(), thievesPositions[crawlingThief]);
        }while(iCanGo);

        arrived = roomDistance == thievesPositions[crawlingThief];
        if(arrived) {
            thief.setOrdinaryThiefState(OrdinaryThiefStates.AT_A_ROOM);
            generalRepos.setOrdinaryThiefState(thief.getOrdinaryThiefId(), OrdinaryThiefStates.AT_A_ROOM);
        }

        crawlingThief = getNextThiefWakeUpIn();
        startCrawling.signalAll();

        mutex.unlock();
        return !arrived;
    }

    /**
     * Called by all the Ordinary Thieves after they attempt to collect a canvas. Last thief to call this function
     * awakes the first one to start crawling out
     */
    public void reverseDirection() {
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        if(++thievesAtTheRoom == SimulPar.ASSAULT_PARTY_SIZE) {
            crawlingThief = 0;
            atTheRoom.signalAll();
        } else {
            while(thievesAtTheRoom < SimulPar.ASSAULT_PARTY_SIZE) {
                try {
                    atTheRoom.await();
                } catch (InterruptedException ignored) {}
            }
        }

        thief.setOrdinaryThiefState(OrdinaryThiefStates.CRAWLING_OUTWARDS);
        generalRepos.setOrdinaryThiefState(thief.getOrdinaryThiefId(), OrdinaryThiefStates.CRAWLING_OUTWARDS);

        mutex.unlock();
    }

    /**
     * Called by all the Ordinary Thieves in this Assault Party while moving from a room towards the control site
     *
     * @return Whether the thief has arrived at the control site
     */
    public boolean crawlOut() {
        boolean arrived;
        mutex.lock();

        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        while(crawlingThief != getInternalThiefIdFromThiefId(thief.getOrdinaryThiefId())) {
            try {
                startCrawling.await();
            } catch (InterruptedException ignored) {}
        }

        boolean iCanGo = true;
        do
        {
            char situation = whereAmIOut(crawlingThief);
            switch(situation)
            {
                case 'F':
                {
                    int thiefBehind = getThiefAhead(crawlingThief);
                    int distanceBetween = Math.abs(thievesPositions[crawlingThief] - thievesPositions[thiefBehind]);
                    int idealMovementTarget = SimulPar.MAX_ASSAULT_PARTY_SEPARATION - distanceBetween;
                    if(idealMovementTarget == 0) {
                        iCanGo = false;
                    }
                    else {
                        int movementTarget = Math.min(thief.getOrdinaryThiefAgility(), idealMovementTarget);
                        if(thievesPositions[crawlingThief] - movementTarget <= 0) {
                            thievesPositions[crawlingThief] = 0;
                            iCanGo = false;
                        }
                        else {
                            thievesPositions[crawlingThief] -= movementTarget;

                            if(movementTarget == idealMovementTarget) iCanGo = false;
                        }
                    }

                    break;
                }
                case 'M':
                {
                    int thiefBehind = getThiefAhead(crawlingThief);
                    int thiefInFront = getThiefBehind(crawlingThief);

                    int distanceBetween = Math.abs(thievesPositions[crawlingThief] - thievesPositions[thiefBehind]);
                    int idealMovementTarget = SimulPar.MAX_ASSAULT_PARTY_SEPARATION - distanceBetween;

                    if(idealMovementTarget == 0) {
                        iCanGo = false;
                    }
                    else
                    {
                        int movementTarget = Math.min(thief.getOrdinaryThiefAgility(), idealMovementTarget);

                        if(thievesPositions[crawlingThief] - movementTarget <= 0) {
                            thievesPositions[crawlingThief] = 0;
                            iCanGo = false;
                        }
                        else if(thievesPositions[crawlingThief] - movementTarget == thievesPositions[thiefInFront]) {
                            thievesPositions[crawlingThief] = thievesPositions[thiefInFront] + 1;
                            iCanGo = false;
                        }
                        else {
                            thievesPositions[crawlingThief] -= movementTarget;

                            if(movementTarget == idealMovementTarget) iCanGo = false;
                        }
                    }

                    break;
                }
                case 'B':
                {
                    int frontMostPosition = thievesPositions[getThiefAtBack()] - SimulPar.MAX_ASSAULT_PARTY_SEPARATION;
                    int targetPosition = Math.max(thievesPositions[crawlingThief] - thief.getOrdinaryThiefAgility(), 0);
                    targetPosition = Math.max(targetPosition, frontMostPosition);
                    boolean found = false;

                    while(!found && targetPosition < thievesPositions[crawlingThief]) {
                        boolean conflict = false;
                        for(int p = 0; p < SimulPar.ASSAULT_PARTY_SIZE ; p++) {
                            if(p == crawlingThief) continue;
                            if(thievesPositions[p] == 0) continue;

                            if(targetPosition == thievesPositions[p]) {
                                conflict = true;
                                break;
                            }
                        }
                        if(!conflict)
                        {
                            found = true;
                            continue;
                        }
                        targetPosition++;
                    }

                    if(targetPosition == thievesPositions[crawlingThief] || targetPosition == 0) iCanGo = false;
                    if(targetPosition == frontMostPosition) iCanGo = false;
                    thievesPositions[crawlingThief] = targetPosition;

                    break;
                }
            }
            generalRepos.setOrdinaryThiefPosition(thief.getOrdinaryThiefId(), thievesPositions[crawlingThief]);
        }while(iCanGo);

        arrived = 0 == thievesPositions[crawlingThief];
        if(arrived) {
            thief.setOrdinaryThiefState(OrdinaryThiefStates.COLLECTION_SITE);
            generalRepos.setOrdinaryThiefState(thief.getOrdinaryThiefId(), OrdinaryThiefStates.COLLECTION_SITE);
        }

        crawlingThief = getNextThiefWakeUpOut();
        startCrawling.signalAll();
        mutex.unlock();
        return !arrived;
    }

    /**
     * @return The id of the room this Assault Party is assigned to
     */
    public int getRoomId() {
        int result;
        mutex.lock();
        result = roomId;
        mutex.unlock();
        return result;
    }

    /**
     * Sets the room an assault party is assigned to
     * @param roomId the id of a museum room
     */
    public void setRoomId(int roomId) {
        mutex.lock();
        this.roomId = roomId;
        mutex.unlock();
    }

    /**
     * Sets whether an Ordinary Thief is carrying a canvas
     * @param thiefId the id of an Ordinary Thief
     * @param hasCanvas whether the thief has a canvas
     */
    public void setHasCanvas(int thiefId, boolean hasCanvas) {
        mutex.lock();
        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thieves[t] == thiefId) {
                thiefHasCanvas[t] = hasCanvas;
                mutex.unlock();
                return;
            }
        }

        System.err.printf("Thief %d is not a member of this assault party\n", thiefId);
        System.exit(1);
        mutex.unlock();
    }

    /**
     * Gets whether an Ordinary Thief is carrying a canvas
     * @param thiefId the id of an Ordinary Thief
     * @return whether an Ordinary Thief is carrying a canvas
     */
    public boolean hasCanvas(int thiefId) {
        mutex.lock();
        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thieves[t] == thiefId) {
                mutex.unlock();
                return thiefHasCanvas[t];
            }
        }

        System.err.printf("Thief %d is not a member of this assault party\n", thiefId);
        System.exit(1);
        mutex.unlock();
        return false;
    }

    /**
     * Sets the distance to the target room
     * @param roomDistance the distance to the target room
     */
    public void setRoomDistance(int roomDistance) {
        mutex.lock();
        this.roomDistance = roomDistance;
        mutex.unlock();
    }

    /**
     * Converts an Ordinary Thief id to an internal id
     * @param thiefId An Ordinary Thief id that's a member of this assault party
     * @return the internal id of said thief
     */
    public int getInternalThiefIdFromThiefId(int thiefId) {
        int internalThiefId = Integer.MIN_VALUE;
        mutex.lock();
        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thieves[t] == thiefId) {
                internalThiefId = t;
            }
        }
        mutex.unlock();
        return internalThiefId;
    }

    /**
     * Returns the situation of a thief during outwards crawling movement
     * @param internalThief the internal thief id of the thief
     * @return Front ('F'), Back ('B'), Middle ('M')
     */
    private char whereAmIIn(int internalThief) {
        int max = -1;
        int min = Integer.MAX_VALUE;

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thievesPositions[t] == roomDistance) continue;

            if(thievesPositions[t] > max) {
                max = thievesPositions[t];
            }
            if(thievesPositions[t] < min) {
                min = thievesPositions[t];
            }
        }

        if(thievesPositions[internalThief] == max) {
            return 'F';
        }

        if(thievesPositions[internalThief] == min) {
            return 'B';
        }

        /*
         * This handles a special case where a thief in the middle can behave as if he's behind.
         * Suppose there's 3 thieves. Thief_0 at position 3, Thief_1 at position 2 and Thief_2 at position 0.
         * Thief_2 when moving does not need to worry about breaking the max separation between thieves with the thief that's
         * directly behind him.
         * Current:
         * |2| |1|0| | | |
         * Next move (assuming inf agility):
         * |2| | |0| | |1|
         */
        int thiefBehind = getThiefBehind(crawlingThief);
        int thiefInFront = getThiefAhead(crawlingThief);
        if(Math.abs(thievesPositions[thiefInFront] - thievesPositions[thiefBehind]) <= SimulPar.MAX_ASSAULT_PARTY_SEPARATION) return 'B';

        return 'M';
    }

    /**
     * Returns the situation of a thief during inwards crawling movement
     * @param internalThief the internal thief id of the thief
     * @return Front ('F'), Back ('B'), Middle ('M')
     */
    private char whereAmIOut(int internalThief) {
        int max = -1;
        int min = Integer.MAX_VALUE;

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thievesPositions[t] == 0) continue;

            if(thievesPositions[t] > max) {
                max = thievesPositions[t];
            }
            if(thievesPositions[t] < min) {
                min = thievesPositions[t];
            }
        }

        if(thievesPositions[internalThief] == min) {
            return 'F';
        }

        if(thievesPositions[internalThief] == max) {
            return 'B';
        }

        int thiefBehind = getThiefAhead(crawlingThief);
        int thiefInFront = getThiefBehind(crawlingThief);
        if(Math.abs(thievesPositions[thiefInFront] - thievesPositions[thiefBehind]) <= SimulPar.MAX_ASSAULT_PARTY_SEPARATION) return 'B';

        return 'M';
    }

    /**
     * Returns the internal id of the thief directly behind another
     * @param internalThiefId the internal thief id of the thief
     * @return internal id of the thief directly behind
     */
    private int getThiefBehind(int internalThiefId) {
        int pos = thievesPositions[internalThiefId];

        int behindPos = -1;
        int behindId = internalThiefId;

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thievesPositions[t] > behindPos && thievesPositions[t] < pos) {
                behindPos = thievesPositions[t];
                behindId = t;
            }
        }

        return behindId;
    }

    /**
     * Returns the internal id of the thief directly ahead of another
     * @param internalThiefId the internal thief id of the thief
     * @return internal id of the thief directly ahead
     */
    private int getThiefAhead(int internalThiefId) {
        int pos = thievesPositions[internalThiefId];

        int forwardPos = Integer.MAX_VALUE;
        int forwardId = internalThiefId;

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thievesPositions[t] < forwardPos && thievesPositions[t] > pos) {
                forwardPos = thievesPositions[t];
                forwardId = t;
            }
        }

        return forwardId;
    }

    /**
     * Gets the next thief to be wakened up during the inwards crawling movement.
     * @return the internal thief id of the next thief to be awakened
     */
    private int getNextThiefWakeUpIn() {
        int result = getThiefBehind(crawlingThief);
        if(result != crawlingThief) return result;          // if there is someone else behind awake them

        return getThiefInFront();                           // otherwise awake the one at the front
    }

    /**
     * Gets the next thief to be wakened up during the outwards crawling movement.
     * @return the internal thief id of the next thief to be awakened
     */
    private int getNextThiefWakeUpOut() {
        int result = getThiefAhead(crawlingThief);
        if(result != crawlingThief) return result;          // if there is someone else behind awake them

        return getThiefAtBack();                           // otherwise awake the one at the front
    }

    /**
     * Gets the assault party thief id
     * that's in front. When all thieves are at the initial position (0)
     * this returns their own ids for all of them
     * @return The thief that's the furthest ahead
     */
    private int getThiefInFront() {
        int max = -1;

        int forwardId = 0;

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thievesPositions[t] == roomDistance) continue;      // if thief is at the initial or final position we don't consider him

            if(thievesPositions[t] > max) {
                max = thievesPositions[t];
                forwardId = t;
            }
        }

        return forwardId;
    }

    /**
     * Internal Function used for crawling movement
     * Gets the internal thief id of the thief
     * that's at the back.
     * @return The thief that's the furthest behind
     */
    private int getThiefAtBack() {
        int min = Integer.MAX_VALUE;

        int backId = 0;

        for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
            if(thievesPositions[t] == 0) continue;      // if thief is at the initial or final position we don't consider him

            if(thievesPositions[t] < min) {
                min = thievesPositions[t];
                backId = t;
            }
        }

        return backId;
    }
}
