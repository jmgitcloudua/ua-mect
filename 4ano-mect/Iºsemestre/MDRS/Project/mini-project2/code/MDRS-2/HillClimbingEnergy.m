function [bestSol, bestEnergy] = HillClimbingEnergy(nNodes, Links, T, L, sP, nSP, currSol, C)

    % nNodes is the number of nodes
    % Links is the matrix containing all the links between nodes
    % T is the flow matrix 
    % sP contains the computed paths for each flow
    % nSP contains the number of paths for each flow in sP
    % currSol is the starting solution
    % C is the link capacity

    % returns an optimized solution (optimizing the energy consumption) energy comsumption of said
    % solution

    nFLows = size(T, 1);
    nLinks = size(Links, 1);
    bestSol = currSol; % init bestSol as our starting solution

    % compute loads and energy comsumption for current solution;
    Loads = calculateLinkLoads(nNodes, Links, T, sP, currSol);
    bestEnergy = ComputeSolEnergy(nNodes, nLinks, sP, T, L, currSol, Loads, C);

    improved = true; 
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

                Loads = calculateLinkLoads(nNodes, Links, T, sP, sol);
                energy = ComputeSolEnergy(nNodes, nLinks, sP, T, L, sol, Loads, C);
    
                if energy < m
                    m = energy;
                    mSol = sol;
                end
            end
       end

       if m < bestEnergy % if we improve we continue. Else we stop
           bestEnergy = m;
           bestSol = mSol;
           improved = true;
       end

    end
end