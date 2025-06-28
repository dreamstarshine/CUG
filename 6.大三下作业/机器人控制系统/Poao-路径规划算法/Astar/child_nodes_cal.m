%% 判断父节点周围的八个点是否为需进行计算的子节点
function child_nodes = child_nodes_cal(parent_node, m, n, obs, closeList)

child_nodes = [];
field = [1,1; n,1; n,m; 1,m];    % 矩形地图区域的四个点

% 左上 ↖️
child_node = [parent_node(1)-1, parent_node(2)+1];    % 子节点坐标
% inpolygon(xq,yq,xv,yv)命令，查询xq,yq是否在xv,yv定义的多边形区域内 (:,i)列向量
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))   
    % 判断 child_nodes 是否与 obs 有相同的行。
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];  % 该点不在obs中，将其加入子节点
    end
end

% 上 ⬆️
child_node = [parent_node(1), parent_node(2)+1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% 右上 ↗️
child_node = [parent_node(1)+1, parent_node(2)+1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% 左 ⬅️
child_node = [parent_node(1)-1, parent_node(2)];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% 右 ➡️
child_node = [parent_node(1)+1, parent_node(2)];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% 左下 ↙️
child_node = [parent_node(1)-1, parent_node(2)-1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% 下 ⬇️
child_node = [parent_node(1), parent_node(2)-1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% 右下 ↘️
child_node = [parent_node(1)+1, parent_node(2)-1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

%% 删除已经在closeList中的子节点
delete_idx = [];
for i = 1:size(child_nodes, 1)
    if ismember(child_nodes(i,:), closeList , 'rows')
        delete_idx(end+1,:) = i;
    end
end
child_nodes(delete_idx, :) = [];