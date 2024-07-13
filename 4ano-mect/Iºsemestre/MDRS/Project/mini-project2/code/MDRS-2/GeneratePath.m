function [T, sP, nSP] = GeneratePath(L, T_any, T_uni, anycastNodes, k)
    
    % L contains the lenghts of the links between nodes
    % T_any contains the anycast flows (no destination yet, only src, up and down)
    % T_uni contains the unicast flows

    
    % add a column with destination to T_any 
    T_any = [T_any(:, 1) zeros(length(T_any(:, 1)), 1) T_any(:, 2) T_any(:, 3)];

    nUniFlows = size(T_uni,1);
    nAnyFlows = size(T_any,1);
    
    uni_sP= cell(1,nUniFlows);
    uni_nSP= zeros(1,nUniFlows);
    
    % determine k shortest paths for unicast flows
    for f=1:nUniFlows
        [shortestPath, totalCost] = kShortestPath(L,T_uni(f,1),T_uni(f,2),k);
        uni_sP{f}= shortestPath;
        uni_nSP(f) = length(totalCost);
    end

    nAnyNodes = length(anycastNodes);
    any_sP= cell(1,nAnyFlows);
    any_nSP= ones(1,nAnyFlows);

    % determine best destination node for the anycast flow
    cnt = 1;
    for n=T_any(:,1)'
        best = inf;
        for a=1:nAnyNodes

            % if the source node is an anycast node. the shortest path
            % will be the node itself
            if(n == anycastNodes(a)) 
                any_sP{cnt}= {n};
                T_any(cnt, 2) = n;
                break;
            end
    
            [shortestPath, totalCost] = kShortestPath(L, n, anycastNodes(a), 1);
            if totalCost < best
                any_sP{cnt}= shortestPath;
                best = totalCost;
                T_any(cnt, 2) = anycastNodes(a);
            end
        end
        cnt = cnt + 1;
    end
    
    % concat Ts and sPs
    T = [T_uni; T_any];
    sP = [uni_sP(:)' any_sP(:)' ];
    nSP = [uni_nSP any_nSP];
end

