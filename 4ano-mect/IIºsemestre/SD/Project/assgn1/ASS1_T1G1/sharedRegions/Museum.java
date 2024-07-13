package sharedRegions;

import entities.OrdinaryThief;

public class Museum {

    /**
     * An array containing the number of canvases in every museum room
     */
    private final int[] numCanvasPerRoom;

    /**
     * An array containing the distance to every museum room
     */
    private final int[] roomDistances;

    /**
     * A reference to the General Repository
     */
    private final GeneralRepos genRep;


    /**
     * An array of references to the several Assault Parties
     */
    private final AssaultParty[] assaultParties;

    public Museum(GeneralRepos genRep, int[] numCanvasPerRoom, int[] roomDistances, AssaultParty[] assaultParties) {
        this.numCanvasPerRoom = numCanvasPerRoom;
        this.roomDistances = roomDistances;
        this.genRep = genRep;
        this.assaultParties = assaultParties;
    }

    /**
     * Called by an ordinary thief at a room to try to collect a canvas
     * @param assPartyId the id of the assault party the thief is a member of
     */
    public synchronized void rollACanvas(int assPartyId) {
        Thread callingThread = Thread.currentThread();
        assert(callingThread instanceof OrdinaryThief);
        OrdinaryThief thief = (OrdinaryThief)callingThread;

        AssaultParty assParty = assaultParties[assPartyId];
        if(numCanvasPerRoom[assParty.getRoomId()] > 0) {
            numCanvasPerRoom[assParty.getRoomId()]--;

            assParty.setHasCanvas(thief.getOrdinaryThiefId(), true);
            genRep.collectACanvas(assParty.getRoomId(), numCanvasPerRoom[assParty.getRoomId()],
                    thief.getOrdinaryThiefId(), true);
        }
        else {
            assParty.setHasCanvas(thief.getOrdinaryThiefId(), false);
            genRep.collectACanvas(assParty.getRoomId(), numCanvasPerRoom[assParty.getRoomId()],
                    thief.getOrdinaryThiefId(), false);
        }
    }

    /**
     * Gets the distance from the collection/concentration site to a room
     * @param roomId the id of a room
     * @return the distance to the room
     */
    public synchronized int getRoomDistance(int roomId) {
        return roomDistances[roomId];
    }
}

