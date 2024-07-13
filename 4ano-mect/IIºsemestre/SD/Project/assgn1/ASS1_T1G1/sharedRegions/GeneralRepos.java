package sharedRegions;

import entities.MasterThiefStates;
import entities.OrdinaryThiefStates;
import main.SimulPar;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

/**
 *  General Repository.
 * <p>
 *    It is responsible to keep the visible internal state of the problem and to provide means for it
 *    to be printed in the logging file.
 *    It is implemented as an implicit monitor.
 *    All public methods are executed in mutual exclusion.
 *    There are no internal synchronization points.
 */
public class GeneralRepos {

    /**
     *  The name of the file the log will be written to
     */
    private final String logFileName;

    /**
     *  State of the Master Thief
     */
    private int masterThiefState;

    /**
     *  States of the Ordinary Thieves
     */
    private final int[] ordinaryThiefState;

    /**
     *  Situation of Ordinary Thieves
     */
    private final char[] ordinaryThiefSituation;

    /**
     *  Agility of Ordinary Thieves
     */
    private final int[] ordinaryThievesAgility;

    /**
     *  Assault Party each Ordinary Thief is in
     */
    private final int[][] assaultPartyThieves;

    /**
     *  Museum room each assault party is assigned to
     */
    private final int[] assaultPartyRooms;

    /**
     *  Whether each Ordinary Thief is carrying a canvas
     */
    private final boolean[] ordinaryThiefCarrying;

    /**
     *  The position of every ordinary thief
     */
    private final int[] ordinaryThiefPosition;


    /**
     *  The number of canvases currently in each museum room
     */
    private final int[] museumRoomCanvases;

    /**
     *  The distance from each museum room to the concentration site
     */
    private final int[] museumRoomDistance;

    /**
     *  A logWriter instance used to write to the log file
     */
    private PrintWriter logWriter;

    /**
     *   Instantiation of a general repository object.
     *
     *   @param logFileName name of the logging file
     */
    public GeneralRepos(String logFileName, int[] museumRoomCanvases,
                        int[] museumRoomDistance, int[] ordinaryThievesAgility) {
        this.logFileName = logFileName;

        masterThiefState = MasterThiefStates.PLANNING_THE_HEIST;

        ordinaryThiefState = new int[SimulPar.NUMBER_OF_THIEVES - 1];
        for(int t = 0; t < SimulPar.NUMBER_OF_THIEVES - 1; t++) {
            ordinaryThiefState[t] = OrdinaryThiefStates.CONCENTRATION_SITE;
        }

        ordinaryThiefSituation = new char[SimulPar.NUMBER_OF_THIEVES - 1];
        for(int t = 0; t < SimulPar.NUMBER_OF_THIEVES - 1; t++) {
            ordinaryThiefSituation[t] = 'W';
        }

        this.ordinaryThievesAgility = ordinaryThievesAgility;

        assaultPartyThieves = new int[SimulPar.NUM_ASS_PARTIES][SimulPar.ASSAULT_PARTY_SIZE];
        for(int a = 0; a < SimulPar.NUM_ASS_PARTIES; a++) {
            for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
                assaultPartyThieves[a][t] = -1;
            }
        }

        assaultPartyRooms = new int[SimulPar.NUM_ASS_PARTIES];
        for(int a = 0; a < SimulPar.NUM_ASS_PARTIES; a++) {
            assaultPartyRooms[a] = -1;
        }

        ordinaryThiefCarrying = new boolean[SimulPar.NUMBER_OF_THIEVES - 1];
        ordinaryThiefPosition = new int[SimulPar.NUMBER_OF_THIEVES - 1];

        this.museumRoomCanvases = museumRoomCanvases;
        this.museumRoomDistance = museumRoomDistance;

        FileWriter fileWriter = null;

        try
        {
            fileWriter = new FileWriter(logFileName);
            logWriter = new PrintWriter(fileWriter);
        }
        catch (IOException e)
        {
            System.err.println("The operation of creating the log file: " + logFileName + " failed!");
            System.exit(1);
        }

        reportInitialStatus();
    }

    /**
     * Sets the Master Thief state
     * @param state The new Master Thief state
     */
    public synchronized void setMasterThiefState(int state) {
        masterThiefState = state;
        reportStatus();
    }

    /**
     * Sets the state of an Ordinary Thief
     * @param thiefId the id of an Ordinary Thief
     * @param state the new state
     */
    public synchronized void setOrdinaryThiefState(int thiefId, int state) {
        ordinaryThiefState[thiefId] = state;
        reportStatus();
    }

    /**
     * @param assaultPartyId id of an Assault Party
     * @param roomId room id where the Assault Party is assigned to
     */
    public synchronized void setAssaultPartyRoom(int assaultPartyId, int roomId) {
        assaultPartyRooms[assaultPartyId] = roomId;
        reportStatus();
    }

    /**
     * @param roomId room id
     * @param numCanvases the number of canvases in the room
     * @param thiefId the id of an Ordinary Thief
     * @param carrying whether the thief is carrying a canvas
     */
    public synchronized void collectACanvas(int roomId, int numCanvases, int thiefId, boolean carrying) {
        museumRoomCanvases[roomId] = numCanvases;
        ordinaryThiefCarrying[thiefId] = carrying;
        reportStatus();
    }

    /**
     * @param thiefId the id of an Ordinary Thief
     * @param thiefInternalId the internal id (from the assault party) of an Ordinary Thief
     * @param thiefState the new state of the thief
     * @param thiefAssPartyId the assault party id of the thief
     * @param thiefPosition the position of the thief
     * @param thiefCarrying whether the thief is carrying a canvas or not
     * @param thiefSituation the situation
     */
    public synchronized void setOrdinaryThiefStateAndAssPartyIdAndPosAndCvAndSit(
            int thiefId, int thiefInternalId, int thiefState, int thiefAssPartyId,
            int thiefPosition, boolean thiefCarrying, char thiefSituation) {
        ordinaryThiefState[thiefId] = thiefState;
        if(thiefSituation == 'W') assaultPartyThieves[thiefAssPartyId][thiefInternalId] = -1;
        else assaultPartyThieves[thiefAssPartyId][thiefInternalId] = thiefId;
        ordinaryThiefPosition[thiefId] = thiefPosition;
        ordinaryThiefCarrying[thiefId] = thiefCarrying;
        ordinaryThiefSituation[thiefId] = thiefSituation;
        reportStatus();
    }

    /**
     * @param thiefId the id of an Ordinary Thief
     * @param thiefPosition the position of the thief
     */
    public synchronized void setOrdinaryThiefPosition(int thiefId, int thiefPosition) {
        ordinaryThiefPosition[thiefId] = thiefPosition;
        reportStatus();
    }


    /**
     * @param numCollectedCanvas the total number of canvases collected in the heist
     */
    public synchronized void sumUpResults(int numCollectedCanvas) {
        logWriter.printf("My friends, tonight's effort produced %2d priceless paintings!\n", numCollectedCanvas);
        logWriter.flush();
    }

    /**
     *  Write a state line at the end of the logging file.
     * <p>
     *
     *  Internal operation.
     */
    private void reportInitialStatus () {
        logWriter.println("                             Heist to the Museum - Description of the internal state\n");
        logWriter.println("MstT   Thief 1      Thief 2      Thief 3      Thief 4      Thief 5      Thief 6");
        logWriter.println("Stat  Stat S MD    Stat S MD    Stat S MD    Stat S MD    Stat S MD    Stat S MD");
        logWriter.println("                   Assault party 1                       Assault party 2                       Museum");
        logWriter.println("           Elem 1     Elem 2     Elem 3          Elem 1     Elem 2     Elem 3   Room 1  Room 2  Room 3  Room 4  Room 5");
        logWriter.println("    RId  Id Pos Cv  Id Pos Cv  Id Pos Cv  RId  Id Pos Cv  Id Pos Cv  Id Pos Cv   NP DT   NP DT   NP DT   NP DT   NP DT");
        logWriter.flush();

        reportStatus();
    }

    /**
     *  Write a state line at the end of the logging file.
     * <p>
     *
     *  Internal operation.
     */
    private void reportStatus() {
        logWriter.printf("%s  ", masterThiefStateToStr(masterThiefState));
        for(int t = 0; t < SimulPar.NUMBER_OF_THIEVES - 1; t++) {
            logWriter.printf("%s ", ordinaryThiefStateToStr(ordinaryThiefState[t]));
            logWriter.printf("%c ", ordinaryThiefSituation[t]);
            logWriter.printf("%d     ", ordinaryThievesAgility[t]);
        }
        logWriter.println();

        for(int p = 0; p < SimulPar.NUM_ASS_PARTIES; p++) {
            int assaultPartyRoom = assaultPartyRooms[p];
            if(p == 0) {
                if(assaultPartyRoom > -1) logWriter.printf("     %d ", assaultPartyRoom+1);
                else logWriter.print("     - ");
            }
            else {
                if(assaultPartyRoom > -1) logWriter.printf("   %d ", assaultPartyRoom+1);
                else logWriter.print("   - ");
            }

            for(int t = 0; t < SimulPar.ASSAULT_PARTY_SIZE; t++) {
                int thiefId = assaultPartyThieves[p][t];

                if(thiefId == -1) logWriter.print("   -   -  -");
                else logWriter.printf("   %d  %2d  %d", thiefId+1, ordinaryThiefPosition[thiefId], ordinaryThiefCarrying[thiefId] ? 1 : 0);
            }
        }
        logWriter.print("   ");
        for(int r = 0; r < SimulPar.NUMBER_OF_ROOMS; r++) {
            logWriter.printf("%2d %2d   ", museumRoomCanvases[r], museumRoomDistance[r]);
        }
        logWriter.println();
        logWriter.flush();
    }

    /**
     * Converts a master thief state to a 4 character string
     * @param masterThiefState the master thief state
     * @return 4 character string representation of the state
     */
    private String masterThiefStateToStr(int masterThiefState) {
        switch (masterThiefState) {
            case MasterThiefStates.PLANNING_THE_HEIST: return "PTH ";
            case MasterThiefStates.DECIDING_WHAT_TO_DO: return "DWTD";
            case MasterThiefStates.ASSEMBLING_A_GROUP: return "AAG ";
            case MasterThiefStates.WAITING_FOR_GROUP_ARRIVAL: return "WFGA";
            case MasterThiefStates.PRESENTING_THE_REPORT: return "PTR ";
        }
        return "    ";
    }

    /**
     * Converts an ordinary thief state to a 4 character string
     * @param ordinaryThiefState the ordinary thief state
     * @return 4 character string representation of the state
     */
    private String ordinaryThiefStateToStr(int ordinaryThiefState) {
        switch (ordinaryThiefState) {
            case OrdinaryThiefStates.CONCENTRATION_SITE: return "CONC";
            case OrdinaryThiefStates.CRAWLING_INWARDS: return "CIN ";
            case OrdinaryThiefStates.AT_A_ROOM: return "AAR ";
            case OrdinaryThiefStates.CRAWLING_OUTWARDS: return "COUT";
            case OrdinaryThiefStates.COLLECTION_SITE: return "COLL";
        }
        return "    ";
    }
}
