function [load, loads, sol, bestSol, bestLoad, nTraffic] = ObjectiveFunction(nNodes, Links, T, sP, currentSolution)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

bestLoad= inf;
nFlows = size(currentSolution);
loads = calculateLinkLoads(nNodes, Links, T, sP, currentSolution);
bestSol = zeros(1,nFlows);
sol = zeros(1,nFlows);
nTraffic = size(T,1);
    for i=1:nFlows
        for  j=1:nTraffic
            sol(i) = j;
            load = max(max(loads(:,3:4)));
            if load < bestLoad
                bestSol = sol;
                bestLoad = load;
            end
        end
    end
end