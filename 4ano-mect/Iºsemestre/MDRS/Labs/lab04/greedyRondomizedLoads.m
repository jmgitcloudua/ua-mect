function [sol,load] = greedyRondomizedLoads(nFlows,nSP, nNodes, Links, T, sP, limit)
%Optimization algorithm based on greedy randomized strategy
aux = randperm(nFlows); % array in random order
sol= zeros(1,nFlows);
for i= aux
    xBest = 0;
    best = inf;
    n = min(limit, nSP(i));
    for x = 1:n
        sol(i)= x;
        Loads= calculateLinkLoads(nNodes,Links,T,sP,sol);
        load= max(max(Loads(:,3:4)));
        if load < best
            xBest = x;
            best = load;
        end
    end
    sol(i) = xBest;
end
load= best;