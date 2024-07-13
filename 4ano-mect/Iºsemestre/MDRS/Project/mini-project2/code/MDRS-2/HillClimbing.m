function [bestSol, betterLoad] = HillClimbing(nNodes,Links,T,sP,nSP,currSol)
    
    % nNodes is the number of nodes
    % Links is the matrix containing all the links between nodes
    % T is the flow matrix 
    % sP contains the computed paths for each flow
    % nSP contains the number of paths for each flow in sP
    % currSol is the starting solution

    % returns an optimized solution (optimizing the worst link load) and the worst link load of said
    % solution

    % compute the worst link load of the current solution
    currLoads = calculateLinkLoads(nNodes,Links,T,sP,currSol);
    betterLoad = max(max(currLoads(:,3:4)));

    nFLows = size(T, 1);
    bestSol = currSol;

    improved = true;

    % keep going while we improve
    while improved
       improved = false;

       m = inf;
       mSol = inf;

       % try to improve by changing a single path
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

       % determine if we improved
       if m < betterLoad
           betterLoad = m;
           bestSol = mSol;
           improved = true;
       end

    end
end