% -------------------------------------------------------------------------
% A*算法
% 出处：https://b23.tv/5mMqX1 - b站up主【小黎的Ally】
% 视频教程中讲解大部分内容，但closeList_path\openList_path没怎么说
% 为此，根据个人理解添加了 —— 2021/10/27  Poaoz 
% -------------------------------------------------------------------------

%   流程梳理 - A*算法
%   1）起点、终点、障碍物等参数的设定 & openlist、closelist的初始化
%   2）从起点出发，将起点作为父节点，记录起点到父节点的路径
%   3）对父节点周围的八个点进行障碍物判断，找出可前进的子节点
%   4）挨个计算上述子节点的代价，记录【起点到其父节点，再到该子节点的路径】，并将其放到openlist中
%   5）将父节点（包括起点到父节点的路径）移动到closelist中，然后从openlist中寻找一个代价最小的节点，作为下一步的父节点
%   6）对该新的父节点，重复上述“3-5”，直到发现 新的父节点就是目标节点
%   7）从closelist取出最后一行，其第一个元素为目标点坐标，第二个元素为【起点到目标点的最优路径--- 一串坐标值】

clc
clear
close all

%% 建立地图

% m行 n列的网格   5  7
m = 5;       
n = 7;
start_node = [2, 3];      % 起点
target_node = [6, 3];     % 终点 
obs = [4,2; 4,3; 4,4 ;5,4];    % 障碍物

% 画xy的网格直线
for i = 1:m
    plot([0,n], [i, i], 'k');
    hold on
end
    
for j = 1:n
     plot([j, j], [0, m], 'k');
end

axis equal
xlim([0, n]);
ylim([0, m]);   

% 使用fill命令，将起点、终点、障碍物 染色
% fill([x1,x2,x3,x4],[y1,y2,y3,y4],'k') 
% 按照顺序连接四点 x1,y1 x2,y2 ,,, x4,y4， 然后填充封闭图形
fill([start_node(1)-1, start_node(1), start_node(1), start_node(1)-1],...
    [start_node(2)-1, start_node(2)-1 , start_node(2), start_node(2)], 'g');

fill([target_node(1)-1, target_node(1), target_node(1), target_node(1)-1],...
    [target_node(2)-1, target_node(2)-1 , target_node(2), target_node(2)], 'r');

for i = 1:size(obs,1)     %  size求出obs的行数
    temp = obs(i,:);      %  obs的某一行
    fill([temp(1)-1, temp(1), temp(1), temp(1)-1],...
        [temp(2)-1, temp(2)-1 , temp(2), temp(2)], 'b');
end

%% openlist closelist的建立
%  close 储存最近点， open 储存已经计算过的点（去除close）
%  xxxxList_path 的格式 [[x1,y1],[x1,y1;x2,y2];[x2,y2],[x1,y1;x2,y2;...]...]
%  xxxxList_path{i,1} -某个节点坐标；_path{i,2} -从出发点到该节点的路径
%  关于path的内容，可运行一遍程序后，于【工作区】查看对应两个变量的具体内容

% closeList
closeList = start_node;
closeList_path = {start_node,start_node};
closeList_cost = 0;
child_nodes = child_nodes_cal(start_node,  m, n, obs, closeList);  % 计算下一步需要计算的子节点

% openList   节点、路径、代价
openList = child_nodes;   % 拷贝待计算的子节点 [x,y; xx,yy; xxx,yyy....]
for i = 1:size(openList,1)
    openList_path{i,1} = openList(i,:);                % 节点坐标
    openList_path{i,2} = [start_node;openList(i,:)];   % 从出发点到该节点
end
% 求取f=g+h g父节点到子节点 h子节点到目标
for i = 1:size(openList, 1)
    g = norm(start_node - openList(i,1:2)); % norm(v) 求欧几里德长度-向量模 1&根号二
    h = abs(target_node(1) - openList(i,1)) + abs(target_node(2) - openList(i,2));   % 求xxx距离
    f = g + h;    % 总代价
    openList_cost(i,:) = [g, h, f];   % 各子节点代价赋值储存
end

%% 
% 寻找openList中总代价f最小的节点，并将其作为下一个父节点
[~, min_idx] = min(openList_cost(:,3));
parent_node = openList(min_idx,:);


%% 循环搜索🔍
% 找到父节点，计算其周围的子节点并将其加入openlist；然后将父节点移动到closelist中，并寻找新的“父节点”
% 如此往复，直到新找到的父节点是目标点。
% 整个过程中，会记录 a-【从起点到父节点的路径】 b-【起点到父节点再到子节点的路径】
% 而每次寻找新的父节点时，会将a移动到close中，并从b中选一个作为下一次的“a” 

flag = 1;
while flag   
    
    % 寻找下一步的子节点
    child_nodes = child_nodes_cal(parent_node,  m, n, obs, closeList); 
    
    % 判断子节点是否在openList：在则更新其代价值，不在则加到openlist中
    for i = 1:size(child_nodes,1)
        child_node = child_nodes(i,:);
        % in_flag-是否在openlist中   openList_idx-在openlist的哪个位置
        [in_flag,openList_idx] = ismember(child_node, openList, 'rows');
        % g = 到父节点的距离g + 父节点到子节点距离
        g = openList_cost(min_idx, 1) + norm(parent_node - child_node);
        h = abs(child_node(1) - target_node(1)) + abs(child_node(2) - target_node(2));
        f = g+h;
        
        % path补充：openList_path{min_idx,2}即【出发点到当前父节点】的路径
        % 因为当前父节点是最短代价，故该路径算是目前的最短代价
        
        if in_flag   % 子节点在openlist中  （是否更优的路径）      
            if g < openList_cost(openList_idx,1)       % 如果现在的g值 小于 已经存在的该节点的g值
                openList_cost(openList_idx, 1) = g;    % 更新该节点的代价值
                openList_cost(openList_idx, 3) = f;
                openList_path{openList_idx,2} = [openList_path{min_idx,2}; child_node];
            end
        else         % 不在，将子节点加入openList末尾
            openList(end+1,:) = child_node;
            openList_cost(end+1, :) = [g, h, f];
            openList_path{end+1, 1} = child_node;    % path中加入节点
            openList_path{end, 2} = [openList_path{min_idx,2}; child_node]; % 更新该节点路径为【出发到该节点】
        end
    end
   
    % 将openList中上述父节点移动到 closeList中（非刚刚更新的openlist中代价最小的节点）
    closeList(end+1,: ) =  openList(min_idx,:);    
    closeList_cost(end+1,1) = openList_cost(min_idx,3);
    closeList_path(end+1,:) = openList_path(min_idx,:);
    openList(min_idx,:) = [];        % 从openlist清除该父节点
    openList_cost(min_idx,:) = [];
    openList_path(min_idx,:) = [];

    
    % 寻找openList中总代价最小的节点，并将其作为下一个父节点（刚更新的openlist）
    [~, min_idx] = min(openList_cost(:,3));
    parent_node = openList(min_idx,:);
    
    % 父节点为目标，停止搜索
    if parent_node == target_node    % 加入到closelist中
        closeList(end+1,: ) =  openList(min_idx,:);   
        closeList_cost(end+1,1) =   openList_cost(min_idx,1);
        closeList_path(end+1,:) = openList_path(min_idx,:);    % 将从起点到目标点的路径移动至close中
        flag = 0;     %  退出循环
    end
end
    

%% 画出路径
path_opt = closeList_path{end,2};    % 取数组中最后一行的第二个元素为路径
path_opt(:,1) = path_opt(:,1)-0.5;   % 散点为各个方块中心点，故需进行坐标偏移
path_opt(:,2) = path_opt(:,2)-0.5;
scatter(path_opt(:,1), path_opt(:,2), 'k');  % 画一系列散点
plot(path_opt(:,1), path_opt(:,2), 'k');     % 将散点们连线
  