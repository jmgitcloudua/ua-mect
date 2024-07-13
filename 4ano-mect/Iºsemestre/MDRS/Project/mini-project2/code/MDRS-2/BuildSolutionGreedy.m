function [sol] = BuildSolutionGreedy(nNodes,Links,T,sP,nSP)
    % nNodes is the number of nodes
    % Links is the matrix containing all the links between nodes
    % T is the matrix containing all the flows and their ip and down bandwidth
    % sP is a cell array containing paths for each flow
    % nSP is a array containing the number of paths for each flow in sP 

    % returns a solution built with Greedy Randomized strategy minimizing
    % the worst link load

    nFlows = size(T, 1);
    sol = zeros(1,nFlows);
    randFlows = randperm(nFlows); % randomly permutate the flows

    for flow= randFlows % go through each permutated flow
        m = inf;
        mi = inf;

        % find the path for this flow that leads to the smallest worst link load
        for i=1:nSP(flow)
            sol(flow) = i;
    
            Loads = calculateLinkLoads(nNodes,Links,T,sP,sol);
            load = max(max(Loads(:,3:4)));
    
            if load<m
                m=load;
                mi = i;
            end
        end
    
        sol(flow) = mi;
    end
end