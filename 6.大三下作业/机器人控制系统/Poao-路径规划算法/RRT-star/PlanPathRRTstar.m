function result = PlanPathRRTstar(param, p_start, p_goal)

% RRT* 
% credit : Anytime Motion Planning using the RRT*, S. Karaman, et. al.
% calculates the path using RRT* algorithm 
% param : parameters for the problem 
%   1) threshold : stopping criteria (distance between goal and current
%   node)  
%   2) maxNodes : maximum nodes for rrt tree   
%   3) neighborhood : distance limit used in finding neighbors  
%   4) obstacle : must be rectangle-shaped #limitation
%   5) step_size : the maximum distance that a robot can move at a time
%   (must be equal to neighborhood size) #limitation    
%   6) random_seed : to control the random number generation   
% p_start : [x;y] coordinates    
% p_goal : [x;y] coordinates   
% variable naming : when it comes to describe node, if the name is with
% 'node', it means the coordinates of that node or it is just an index of
% rrt tree 
% rrt struct : 1) p : coordinate, 2) iPrev : parent index, 3) cost :
% distance    
% obstacle can only be detected at the end points but not along the line
% between the points  障碍物只能在端点处检测到，而不能沿着端点之间的直线检测到
% for cost, Euclidean distance is considered.   代价计算--欧几里得距离
% output : cost, rrt, time_taken 
% whether goal is reached or not, depends on the minimum distance between
% any node and goal 

%  GitHub作者：GitHub-https://github.com/wntun/RRT-star

%   中文简述如下，给关系程序理解的大部分程序段都添加了注释。
%   部分细节可能存在偏差，望海涵。
%            --  by Poaoz  2021/10/29
%   知乎：https://www.zhihu.com/people/panda-13-16


%   初始化参数简述 param 
%   1) threshold : 停止搜索的距离阈值--当前节点于目标点的距离
%   2) maxNodes :  RRT树的最大节点数
%   3) neighborhood :  父节点到下一个节点的步长
%   4) obstacle : 该程序的障碍物只能是矩形的，可通过修改函数【isObstacleFree(node_free)】替换其他的障碍物
%   5) step_size : 机器人一次可前进的步长，此处需与neighborhood相等
%   6) random_seed :   控制随机数生成的种子
%   代价计算说明： 采用norm计算两个坐标点之间的距离-欧几里得距离

%   rrt 树参数结构简述
%   1) p : 节点坐标 pose
%   2) iPrev : 该节点的父节点索引 （rrt树中的索引）  联系了该节点与父节点
%   3) cost : 累计代价  = 父节点代价 + 父节点到该子节点的距离代价 【欧几里得距离】
%   4) goalReached : 是否到达目标点标志 （与设定的threshold有关）

%   while循环进行的内容
%   1)地图上随机采样一个点
%   2）找出现有节点中，与该采样点最近的节点
%   3）沿最近的节点到采样点方向，根据机器人步长，求得新的节点
%   4）新节点的障碍物判断 & 找到新节点的父节点 （最近点 or 可到达的点neighbors_ind）
%   5）将新节点插入到rrt树中（非障碍物 & 四个rrt参数）  这里有 节点重连的路径优化 
%   6）判断该节点是否满足阈值条件 “达到目标点”-threshold （第四个rrt参数）

%   while循环结束后：根据得到到rrt树，计算出最终路径并绘制
%   最短路径寻找简述：
%   1）找出rrt中 goalReached=1 的节点
%   2）找出上述节点中，cost最小的节点（选一个就可）
%   3）根据该节点的rrt中第二个参数iPrev，找到其父节点
%   4）重新上述“3）”直到发现父节点为开始节点，便可得到一条cost最小的路径

% rrt树的四个参数
field1 = 'p';
field2 = 'iPrev';  %  借助该参数，可将整个路径搜索出来。
field3 = 'cost';
field4 = 'goalReached';

rng(param.random_seed);   % 用指定的 randomseed 初始化随机数生成器
tic;       % tic开始计时，常与toc配合使用，toc停止计时  （算法运行的时间计时）
start();   % 执行路径规划功能函数

    function start()      
        % s = struct(field1,value1,...,fieldN,valueN) 创建一个包含多个字段的结构体数组
        rrt(1) = struct(field1, p_start, field2, 0, field3, 0, field4, 0);  
        N = param.maxNodes; % 迭代次数 iterations
        j = 1;

%         while endcondition>param.threshold %&& j<=N    
%       每走一次循环，j++，一共循环N次
        while j<=N   
            % 1）随机采样一个点
            sample_node = getSample();  
%             plot(sample_node(1), sample_node(2), '.g');
%             text(sample_node(1), sample_node(2), strcat('random',num2str(j)))
            % 2）找到现有节点中，距离该采样点最近的点
            nearest_node_ind = findNearest(rrt, sample_node);  
%             plot(rrt(nearest_node_ind).p(1), rrt(nearest_node_ind).p(2), '.g');
%             text(rrt(nearest_node_ind).p(1), rrt(nearest_node_ind).p(2), strcat('nearest', num2str(j)));
            % 3）沿最近点到采样点方向，按照步长前进，得到新的节点
            new_node = steering(rrt(nearest_node_ind).p, sample_node);
            if (isObstacleFree(new_node)==1)        % 4.1） 新节点的障碍物检测
%                 plot(new_node(1), new_node(2), '.g');
%                 text(new_node(1), new_node(2)+3, strcat('steered: new node', num2str(j)))
                % 获取新节点附近可到达的节点索引  neighbourhood
                neighbors_ind = getNeighbors(rrt, new_node);
                if(~isempty(neighbors_ind))        % 4.2） 判断附近可达到的节点 存在与否 （找该新节点的父节点）
                    % 存在— 从根节点为新子节点选择成本最低的父节点  【难理解1】
                    parent_node_ind = chooseParent(rrt, neighbors_ind, nearest_node_ind,new_node);
%                     plot(rrt(parent_node_ind).p(1), rrt(parent_node_ind).p(2), '.g');
%                     text(rrt(parent_node_ind).p(1), rrt(parent_node_ind).p(2)+3, strcat('parent', num2str(j)));
                else   
                    % 不存在— 选取距离该采样点最近的点为父节点
                    parent_node_ind = nearest_node_ind;
                end
                % 5）将新节点插入到 rrt搜索树中
                rrt = insertNode(rrt, parent_node_ind, new_node);
                if (~isempty(neighbors_ind))    % 存在可到达节点时，进行重连操作  优化路径  【难理解2】
                    rrt = reWire(rrt, neighbors_ind, parent_node_ind, length(rrt));
                end
                % 满足距离阈值条件，记该节点为到达目标 （但依旧会持续嵌套搜索）
                if norm(new_node-p_goal) == param.threshold
                    rrt = setReachGoal(rrt);
                end
            end
            j = j + 1;
        end
        setPath(rrt);   % 上述while结束后，绘制寻找的路径
%         text1 = strcat('Total number of generated nodes:', num2str(j-1))
%         text1 = strcat('Total number of nodes in tree:', length(rrt))
    end

%% 一系列功能函数（start中调用）

    % 在rrt树中标记该节点为“到达目标点”（第四个参数）  ok
    function rrt=setReachGoal(rrt)
        rrt(end).goalReached = 1;
    end
    
    % 绘制出 rrt中各个节点的关系，并标识出最终得到的路径  ok
    function setPath(rrt)    
        % 1）绘制rrt树 ：各个父节点与子节点之间的连线  【父节点→子节点】
        for i = 1: length(rrt)-1
            p1 = rrt(i).p;   % 遍历rrt中各个节点
            rob.x = p1(1); rob.y=p1(2);
            plot(rob.x+.5,rob.y+.5,'.b')  % 绘制各个节点
            child_ind = find([rrt.iPrev]==i);  % 寻找rrt中父节点索引为i的一堆子节点
            for j = 1: length(child_ind)       % 遍历上述一堆子节点
                p2 = rrt(child_ind(j)).p;      % 找到并绘制 上述父节点到子节点 的连线
                pause(0.01);            % 程序暂停一会再继续运行 -- 体现出路径搜索的过程
                plot([p1(1),p2(1)], [p1(2),p2(2)], 'b', 'LineWidth', 1);
            end
        end 
        % 2）找到最短路径，并绘制
        [cost,i] = getFinalResult(rrt);
        result.cost = cost;
        result.rrt = [rrt.p];  % result输出的节点坐标
        % 绘制最终得到的最短路径
        while i ~= 0
            p11 = rrt(i).p;
            plot(p11(1)+.5,p11(2)+.5,'go','MarkerFaceColor','y');
            i = rrt(i).iPrev;
            if i ~= 0
                p22 = rrt(i).p;  % 依次画出该节点，其父节点，其父节点的父节点（从终点画到起点）     
                plot(p22(1)+.5,p22(2)+.5,'go','MarkerFaceColor','y');
                pause(0.02);            % 程序暂停一会再继续运行 -- 体现出路径搜索的过程
%                 plot([p11(1),p22(1)],[p11(2),p22(2)], 'b', 'LineWidth', 3);
            end 
        end  
        result.time_taken = toc;     % 返回程序总的运行时间
    end


    % 找最终路径 （在setPath中调用）           ok
    % 参    数：rrt树
    % 返 回 值：代价cost 最接近终点的最优节点索引
    % 寻找方法：寻找“到达目标点”的节点中，代价最小的节点
    % 由该代价最小的节点，rrt树中的第二个参数iPrev，可再找到其父节点，由此可得到一条代价最小的路径
    function [value,min_node_ind] = getFinalResult(rrt)
        % 找到所有“到目标点”的节点索引   rrt第四个参数
        goal_ind = find([rrt.goalReached]==1);
        if ~(isempty(goal_ind))   % 判断是否达到目标点（goal是否存在）
            disp('Goal has been reached!');
            rrt_goal = rrt(goal_ind);  % 储存“到目标点”节点
            value = min([rrt_goal.cost]);  % 取得上述节点中 cost最小值
            min_node_ind = find([rrt.cost]==value);  % 找到 cost最小值节点的索引
            if length(min_node_ind)>1    % 如果cost最小值对应的索引有多个，取第一个即可
                min_node_ind = min_node_ind(1);
            end
        else   % goal_ind不存在
            disp('Goal has not been reached!');
            % 计算rrt中各个节点到目标点的距离，求出最小的一个节点，充当“终点” 
            for i =1:length(rrt)
                norm_rrt(i) = norm(p_goal-rrt(i).p);
            end
            [value,min_node_ind]= min(norm_rrt);   % 求取其中距离目标点最近的节点
            value = rrt(min_node_ind).cost;        % 以求得的该点信息作为返回值
        end
    end
    

    % 新节点的障碍物判断函数 （针对此程序的矩形障碍物判断）   ok
    % 参    数：新节点的坐标信息
    % 返 回 值： 0-有障碍物   1-无障碍物
    % 判断方法：节点坐标是否在矩形障碍物四个端点的约束内（可更改该函数，实现障碍物的不同变换）
    % param.obstacles =[130,70,20,60; 70,135,60,20;]; 
    function free=isObstacleFree(node_free)
        free = 1;
        for i = 1: length(param.obstacles(:,1))
            obstacle = param.obstacles(i,:);    % 取一个矩形障碍物的信息
            op1 = [obstacle(1), obstacle(2)];   % 根据信息求得矩形的四个端点坐标
            op2 = [op1(1)+obstacle(3), op1(2)];
            op3 = [op2(1), op1(2) + obstacle(4)];
            op4 = [op1(1), op3(2)];
            
            nx = node_free(1);     % 取得待判断节点的xy坐标
            ny = node_free(2);
            
            % 判断节点是否在障碍物范围内
            if ((nx>=op1(1) && nx<=op2(1)) && (ny>=op1(2) && ny<=op4(2)))
                free = 0;
            end
        end 
    end
    
    % 【step_size】    ok
    % 沿最近点到采样点方向，按照机器人步长前进，得到新的节点
    % 参    数： 离采样点最近的节点  采样点
    % 返 回 值： 新节点的坐标
    function new_node=steering(nearest_node, random_node)
       dist = norm(random_node-nearest_node);   % 两点距离
       ratio_distance = param.step_size/dist;   
       % 计算新节点的xy坐标  （这里也可使用其他方式进行计算）
       x = (1-ratio_distance).* nearest_node(1)+ratio_distance .* random_node(1);
       y = (1-ratio_distance).* nearest_node(2)+ratio_distance .* random_node(2);
       
       new_node = [x;y];
    end
    
    % 范围内的可到达的节点重新连接，以得到更优的路径 
    % 参    数： rrt树   临近节点索引   父节点索引   新节点的索引--rrt节点总数（前面传入）
    % 返 回 值： 更新 新节点附近的临近节点的 父节点 【建立了更短的路径联系】
    function rrt = reWire(rrt, neighbors, parent, new)
        for i=1:length(neighbors)      % 遍历每个可达到的临近节点
            cost = rrt(new).cost + norm(rrt(neighbors(i)).p - rrt(new).p);   % 求以新节点作为父节点时，临近节点的代价
            
            if (cost<rrt(neighbors(i)).cost)  % 如果 上述新代价 小于 临近节点现有代价
%                 if norm(rrt(new).p-rrt(neighbors(i)).p)<param.step_size
% %                     plot(rrt(neighbors(i)).p(1), rrt(neighbors(i)).p(2), '.b');
%                     rrt(neighbors(i)).p = steering(rrt(new).p, rrt(neighbors(i)).p);
%                 end
%                 plot(rrt(neighbors(i)).p(1), rrt(neighbors(i)).p(2), '.m');
                rrt(neighbors(i)).iPrev = new;    % 将 新节点作为 该临近节点的 父节点
                rrt(neighbors(i)).cost = cost;
            end
        end
    end
    
    % 将新的节点插入rrt树末尾      ok
    % 参    数： rrt  父节点索引  新节点坐标
    % 返 回 值： 更新rrt
    % 其中第三个参数 cost = 父节点代价+新节点到父节点的代价
    function rrt = insertNode(rrt, parent, new_node)
        rrt(end+1) = struct(field1, new_node, field2, parent, field3, rrt(parent).cost + norm(rrt(parent).p-new_node), field4, 0);
    end
    
    % 从根节点为新子节点选择成本最低的父节点    ok  父节点？
    % 参    数： rrt  临近的节点  最近的节点  新节点
    % 返 回 值： 父节点索引
    function parent = chooseParent(rrt, neighbors, nearest, new_node)
        min_cost = getCostFromRoot(rrt, nearest, new_node);   % 求以最近的节点为父节点时，新节点的代价
        parent = nearest;            %  暂取最近的节点，作为父节点
        for i=1:length(neighbors)    % neighbors - 下一步可到达的节点
            cost = getCostFromRoot(rrt, neighbors(i), new_node);   % 求以可到达的节点为父节点时，新节点的代价
            if (cost<min_cost)    % 最终取代价最小的那个节点，作为父节点
               min_cost = cost;
               parent = neighbors(i);
            end
        end
    end
    
    % 父节点的cost + 子节点到父节点的距离代价    ok
    % 参    数： rrt  父节点索引  子节点
    % 返 回 值： 子节点的代价
    function cost = getCostFromRoot(rrt, parent, child_node)       
       cost =  rrt(parent).cost + norm(child_node - rrt(parent).p);
    end

    % 【neighbourhood】         ok
    % 获取指定节点周围可以到达的节点索引
    % 参    数： rrt  node -new_node（上面调用时传的参数）
    % 返 回 值： 保存可到达节点的索引的neighbors
    function neighbors = getNeighbors(rrt, node)
        neighbors = [];
        for i = 1:length(rrt)    % 遍历rrt树中所有的节点
            dist = norm(rrt(i).p-node);      % 计算rrt中各个节点到node的距离代价
            if (dist<=param.neighbourhood)   % 找到 距离代价＜单次行进步长的节点索引
               neighbors = [neighbors i];    % 使用 neighbors 将节点索引保存
            end
        end        
    end
    
    % 在坐标图上生成随机的采样点       ok
    function node = getSample()
        x = 0;
        y = 0;
        a = 0;
        b = 200;
        node = [x;y];
        node(1) = (b-a) * rand(1) + a;
        node(2) = (b-a) * rand(1) + a;  
    end
    
    % 寻找rrt树中距离采样点最近的节点   ok
    function indx = findNearest(rrt, n)
        mindist = norm(rrt(1).p - n);
        indx = 1;
        for i = 2:length(rrt)
            dist = norm(rrt(i).p - n);
            if (dist<mindist)
               mindist = dist;
               indx = i;
            end
        end
    end 
    
end