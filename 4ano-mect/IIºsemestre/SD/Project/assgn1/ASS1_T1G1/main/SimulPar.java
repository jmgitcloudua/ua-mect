package main;

public final class SimulPar {
    /**
     *   Maximum number of paintings in a museum room
     */
    public static final int MINIMUM_NUMBER_OF_PAINTINGS = 8;
    /**
     *   Minimum number of paintings in a museum room
     */
    public static final int MAXIMUM_NUMBER_OF_PAINTINGS = 16;
    /**
     *   Number of Ordinary Thieves in an assault party
     */
    public static final int ASSAULT_PARTY_SIZE = 3;
    /**
     *   Maximum distance between assault party members while crawling in/out
     */
    public static final int MAX_ASSAULT_PARTY_SEPARATION = 3;
    /**
     *   Minimum distance between a museum room and the concentration site
     */
    public static final int MIN_ROOM_SITE_DISTANCE = 15;
    /**
     *   Maximum distance between a museum room and the concentration site
     */
    public static final int MAX_ROOM_SITE_DISTANCE = 30;
    /**
     *   Number of thieves in total. Master + Ordinary Thieves
     */
    public static final int NUMBER_OF_THIEVES = 7;
    /**
     *   Minimum agility of an Ordinary Thief
     */
    public static final int MIN_THIEF_AGILITY = 2;
    /**
     *   Maximum agility of an Ordinary Thief
     */
    public static final int MAX_THIEF_AGILITY = 6;
    /**
     *   Number of rooms in the museum
     */
    public static final int NUMBER_OF_ROOMS = 5;

    /**
     *   Number of Assault Parties
     */
    public static final int NUM_ASS_PARTIES = (NUMBER_OF_THIEVES - 1) / ASSAULT_PARTY_SIZE;
}
