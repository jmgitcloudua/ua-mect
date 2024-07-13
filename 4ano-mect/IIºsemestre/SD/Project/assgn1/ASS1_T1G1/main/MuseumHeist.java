package main;

import entities.MasterThief;
import entities.OrdinaryThief;
import sharedRegions.*;

public class MuseumHeist {
    public static void main(String[] args) {
        int[] museumRoomNumCanvas = new int[SimulPar.NUMBER_OF_ROOMS];
        int[] museumRoomDistances = new int[SimulPar.NUMBER_OF_ROOMS];
        int[] ordinaryThievesAgility = new int[SimulPar.NUMBER_OF_THIEVES-1];

        for (int r = 0; r < SimulPar.NUMBER_OF_ROOMS; r++) {
            museumRoomNumCanvas[r] = (int) (
                    (Math.random() *
                            (SimulPar.MAXIMUM_NUMBER_OF_PAINTINGS - SimulPar.MINIMUM_NUMBER_OF_PAINTINGS))
                            + SimulPar.MINIMUM_NUMBER_OF_PAINTINGS);

            museumRoomDistances[r] = (int) (
                    (Math.random() *
                            (SimulPar.MAX_ROOM_SITE_DISTANCE - SimulPar.MIN_ROOM_SITE_DISTANCE))
                            + SimulPar.MIN_ROOM_SITE_DISTANCE);
        }

        for(int i = 0; i < SimulPar.NUMBER_OF_THIEVES-1; i++) {
            ordinaryThievesAgility[i] = (int) (
                    (Math.random() *
                            (SimulPar.MAX_THIEF_AGILITY - SimulPar.MIN_THIEF_AGILITY))
                            + SimulPar.MIN_THIEF_AGILITY);
        }

        GeneralRepos generalRepos = new GeneralRepos(java.time.LocalDateTime.now()+".log", museumRoomNumCanvas,
                museumRoomDistances, ordinaryThievesAgility);

        AssaultParty[] assaultParties = new AssaultParty[SimulPar.NUM_ASS_PARTIES];
        for(int a = 0; a < SimulPar.NUM_ASS_PARTIES; a++) {
            assaultParties[a] = new AssaultParty(generalRepos);
        }

        Museum museum = new Museum(generalRepos, museumRoomNumCanvas, museumRoomDistances, assaultParties);
        ConcentrationSite concentrationSite = new ConcentrationSite(generalRepos, assaultParties, museum);
        ControlSite controlSite = new ControlSite(generalRepos, assaultParties);

        MasterThief masterThief = new MasterThief(concentrationSite, controlSite, assaultParties);

        OrdinaryThief[] ordinaryThieves = new OrdinaryThief[SimulPar.NUMBER_OF_THIEVES - 1];
        for(int t = 0; t < SimulPar.NUMBER_OF_THIEVES-1; t++) {
            ordinaryThieves[t] = new OrdinaryThief(t, ordinaryThievesAgility[t], concentrationSite, controlSite,
                    assaultParties, museum);
        }

        System.out.println("Starting Master Thief thread");
        masterThief.start();

        for(int i = 0; i < ordinaryThieves.length; i++) {
            System.out.printf("Starting Ordinary Thief %d Thread\n", i + 1);
            ordinaryThieves[i].start();
        }

        try {
            masterThief.join();
            System.out.println("Master Thief thread exited successfully");
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        for(int i = 0; i < ordinaryThieves.length; i++) {
            try {
                ordinaryThieves[i].join();
                System.out.printf("Ordinary Thief %d thread exited successfully\n", i + 1);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
