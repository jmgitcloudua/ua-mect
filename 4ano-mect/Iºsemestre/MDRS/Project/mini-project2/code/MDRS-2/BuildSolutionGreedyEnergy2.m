function sol = BuildSolutionGreedyEnergy2(nNodes, Links, T, L, sP, nSP)
    % nNodes is the total number of nodes
    % Links is the provided Links matrix which contains the links
    % connecting nodes
    % T is the flow matrix 
    % L contains the lenghts of the links between nodes
    % sP contains the computed paths for each flow
    % nSP contains the number of paths for each flow in sP

    % returns a solution and a capacity solution built with Greedy Randomized strategy minimizing
    % the energy comsuntion of a solution while adjusting the link
    % capacities for the avalilable values in C

    nFlows = size(T, 1);
    nLinks = size(Links, 1);
    
    valid = false;

    % keep going until we generate a valid solution 
    while ~valid
        valid = true;
        sol = zeros(1,nFlows);
        randFlows = randperm(nFlows);

        % find the path for this flow that leads to the lowest energy consumption 
        for flow= randFlows           
            m = inf;
            mi = inf;
            for i=1:nSP(flow)
                sol(flow) = i;
        
                Loads = calculateLinkLoads(nNodes, Links, T, sP, sol);
                energy = ComputeSolEnergy2(nNodes,nLinks, sP, T, L, sol, Loads);
        
                if energy<m
                    m=energy;
                    mi = i;
                end
            end

            % if mi is inf, all paths for this flow exceeded the link
            % capacity so the solution is invalid. try again
            if mi == inf 
                valid = false;
                break;
            end
        
            sol(flow) = mi;
        end
    end

end
