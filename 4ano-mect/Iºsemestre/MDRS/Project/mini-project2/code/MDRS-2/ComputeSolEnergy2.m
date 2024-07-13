function [energy] = ComputeSolEnergy2(nNodes, nLinks, sP, T, L, sol, Loads)

    % nNodes is the total number of nodes
    % nLinks is the number of links
    % sP contains the computed paths for each flow
    % T is the flow matrix 
    % L contains the lenghts of the links between nodes
    % sol is the solution for which the energy comsumption will be calculated
    % Loads contains the link loads of sol

    % returns the energy comsumption for sol. returns inf if the link capcity is
    % exceeded

    nodesLoads = zeros(nNodes, 1);
    nFlows = size(T, 1);
    
    % compute node load
    for f=1:nFlows
        if sol(f) > 0
           path = sP{f}{sol(f)};
            flow = T(f, :);
        
            for n=1:length(path)
                nodesLoads(path(n)) = nodesLoads(path(n)) + flow(3) + flow(4);
            end 
        end
    end
    
    % compute nodes energy consumption
    energy = sum(10 + 90 * (nodesLoads/500).^2);
    
    % compute link energy consumption
    for i= 1:nLinks
        if Loads(i,3) > 100 || Loads(i,4) > 100
            energy = inf;
            return;
        elseif (Loads(i,3) ~= 0 || Loads(i,4) ~= 0)
            if Loads(i,3) <= 50 && Loads(i,4) <= 50
                energy = energy + 6 + 0.2 * L(Loads(i,1), Loads(i,2));
            else
                energy = energy + 8 + 0.3 * L(Loads(i,1), Loads(i,2));
            end
        else
            energy = energy + 2;
        end
    end

end

