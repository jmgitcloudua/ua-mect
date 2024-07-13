function [load, sol, bestSol, bestLoad, bestLoads] = RandomStrategy(nFlows,nSP, nNodes, Links, T, sP)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
bestLoad= inf;
sol= zeros(1,nFlows);
 for f= 1:nFlows
        sol(f)= randi(nSP(f));
 end
    Loads= calculateLinkLoads(nNodes,Links,T,sP,sol);
    load= max(max(Loads(:,3:4)));
    if load<bestLoad
        bestSol= sol;
        bestLoad= load;
        bestLoads= Loads;
    end
  
end