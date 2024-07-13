function [CurrentObjective,GlobalBest, GlobalBestSolution,CurrentSolution2] = HillClimbingGreedyRandomized(nNodes,Links,T,sP, nSP, currentSolution)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

nFlows = size(currentSolution);
GlobalBest = Inf;
for iter=1:nFlows
     CurrentSolution2 = GreedyRandomized(nNodes,Links,T,sP,currentSolution);
     CurrentObjective = ObjectiveFunction(nNodes,Links,T,sP,CurrentSolution2);
     repeat = true;
     while repeat
         NeighbourBest = Inf;
         for i=1:size(currentSolution,1)
             NeighbourSolution = BuildNeighbours(Links, nNodes, T, bestSol, sP, nSP, currentSolution,i);
             NeighbourObjective = ObjectiveFunction(nNodes,Links,T,sP,NeighbourSolution);
             if NeighbourObjective < NeighbourBest
                 NeighbourBest = NeighbourObjetive;
                 NeighbourBestSolution = NeighbourSolution;
             end
         end
         if NeighbourBest < CurrentObjective
             CurrentObjective = NeighbourBest;
             CurrentSolution = NeighbourBestSolution;
         else
            repeat = false;
         end
     end
     if CurrentObjective < GlobalBest
         GlobalBestSolution = CurrentSolution; 
         GlobalBest= CurrentObjective;
     end
end
end