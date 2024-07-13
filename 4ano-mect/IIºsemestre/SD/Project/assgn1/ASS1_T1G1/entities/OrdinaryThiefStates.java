package entities;

/**
 *    Definition of the internal states of an ordinary thief during his life cycle.
 */
public final class OrdinaryThiefStates {

    /**
     *   The ordinary thief is at the concentration site waiting to be assigned to an assault party or to leave
     */
    public static final int CONCENTRATION_SITE = 0;
    /**
     *   The ordinary thief is crawling towards a museum room
     */
    public static final int CRAWLING_INWARDS = 1;
    /**
     *   The ordinary thief is at a room attempting to collect a canvas
     */
    public static final int AT_A_ROOM = 2;
    /**
     *   The ordinary thief is crawling from a museum room towards the collection site
     */
    public static final int CRAWLING_OUTWARDS = 3;
    /**
     *   The ordinary thief is at tbe collection site waiting for the Master Thief to attend him
     */
    public static final int COLLECTION_SITE = 4;

    /**
     *   Can not be instantiated.
     */
    private OrdinaryThiefStates() {}
}
