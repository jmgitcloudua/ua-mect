%{
function [sol,load] = GreedyRandomized(nFlows,nSP, nNodes, Links, T, sP)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
ax2 = randperm(nFlows); % array numa ordem aleatória
sol= zeros(1,nFlows);
for i= ax2
    k_best = 0;
    best = inf;
 
    for k= 1:nSP(i)
        sol(i)= k;
        Loads= calculateLinkLoads(nNodes,Links,T,sP,sol);
        load= max(max(Loads(:,3:4)));
        if load < best
            k_best = k;
            best = load;
        end
    end
    sol(i) = k_best;
end
load= best;
end
%}

function [load, sol, bestSol, bestLoad, bestLoads] = GreedyRandomized(nFlows, nSP, nNodes,Links,T,sP,bestLoad)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

bestSol = zeros(1,nFlows);
sol = zeros(1,nFlows);
randFlows = randperm(nFlows);

    for flow= randFlows           
        m = inf;
        mi = inf;
        for i=1:nSP(flow)
            sol(flow) = i;
    
            Loads = calculateLinkLoads(nNodes,Links,T,sP,sol);
            load= max(max(Loads(:,3:4)));
    
            if load < m
                m =load;
                mi = i;
            end
        end
    
        sol(flow) = mi;
        load= m;
    end
    if load < bestLoad
        bestSol= sol;
        bestLoad= load;
       
    end
bestLoads = calculateLinkLoads(nNodes,Links,T,sP,bestSol);
end
