function [bestSol, betterLoad] = HillClimbing(nNodes,Links,T,sP,nSP,currSol)
    currLoads = calculateLinkLoads(nNodes,Links,T,sP,currSol);
    betterLoad = max(max(currLoads(:,3:4)));

    nFLows = size(T, 1);
    bestSol = currSol;

    improved = true;
    while improved
       improved = false;

       m = inf;
       mSol = inf;

       for f=1:nFLows
            sol = bestSol;
            for p=1:nSP(f)
                if(p == sol(f)) 
                    continue;
                end

                sol(f) = p;
                Loads = calculateLinkLoads(nNodes,Links,T,sP,sol);
                load = max(max(Loads(:,3:4)));

                if load < m
                    m = load;
                    mSol = sol;
                end
            end
       end

       if m < betterLoad
           betterLoad = m;
           bestSol = mSol;
           improved = true;
       end

    end
end