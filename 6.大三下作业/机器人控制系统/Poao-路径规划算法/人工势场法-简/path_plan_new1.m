% 算法梳理
% 1）起点、终点、障碍物、迭代次数、取点半径等的设定
% 2）以起点为中心，作半径为r的圆，均匀从圆上取八个点
% 3）分别计算八个点的前进“代价” 即 终点对其的引力+所有障碍物对其的斥力 
% 4）取“代价”最小的点的坐标，结合现有起点，计算得到新的起点，然后重复上述内容
% 5）当发现 一个点距离终点很近 or 迭代的次数计算完了 程序停止。

% 该程序中，computP 负责代价计算，为核心计算函数。 可对其进行修改，以实现其他优化功能。


% 参数：起点 终点 障碍物 的坐标
% 返回值： point储存的一系列起点信息
function [ point ] = path_plan_new1(begin,over,obstacle)

iters=1;      % 迭代次数
curr=begin;   % 起点坐标
testR=0.4;    % 测试8点的圆的半径为0.5

while (norm(curr-over)>0.2) &&  (iters<=2000)    % 未到终点&迭代次数不足
   
%     attr=attractive(curr,over);
%     repu=repulsion(curr,obstacle);
    %curoutput=computP(curr,over,obstacle);
    %计算当前点附近半径为0.2的8个点的势能，然后让当前点的势能减去8个点的势能取差值最大的，确定这个
    %方向，就是下一步迭代的点
    
    point(:,iters)=curr;    % point为函数返回值，储存每次遍历得到的新起点 curr
    
    %先求这八个点的坐标
    for i=1:8   % 求 以curr为起点，testR为半径的圆上的八个均匀分布的点
        testPoint(:,i)=[testR*sin((i-1)*pi/4)+curr(1);testR*cos((i-1)*pi/4)+curr(2)];
        testOut(:,i)=computP(testPoint(:,i),over,obstacle);   % 计算上述各个点的所受合力
    end
    [temp num]=min(testOut); % 找出这八个点中，代价最小的点 
    %迭代的距离为0.1
    curr=(curr+testPoint(:,num))/2;  % 将上述求得点，迭代到curr上。 （求取的 curr与testPoint 的中点）
    plot(curr(1),curr(2),'*g');      % 绘制得到的 新的起点curr
    pause(0.01);            % 程序暂停一会再继续运行 -- 体现出路径搜索的过程
    iters=iters+1;          % 迭代次数+1
end
end


 % 计算周围几个点的势能（代价）
 % 参数：当前起点  终点  障碍物   的坐标
 function [ output ] = computP( curr,over,obstacle)

att = 45;%引力增益系数
req = 10;%斥力增益系数
p0 = 3;%障碍物产生影响的最大距离，当障碍与移动目标之间距离大于Po时，斥力为0。
n=length(obstacle(1,:));%障碍物个数

    %% 引力计算
    V_att = (over-curr)';%路径点到目标点的向量
    r_att = sqrt(V_att(1)^2 + V_att(2)^2);%路径点到目标点的欧氏距离
    P_att = 0.5*att * (r_att)^2;%引力
    
    %% 斥力计算
    %改进的人工势场法，将斥力分散一部分到引力方向。通过添加随机扰动r_att^n实现，r_att为路径点到目标点的欧氏距离，本文n取2。
    V_req = zeros(n,2);
    r_req=zeros(n,1);
    for j =1:n
        V_req(j,:) = [obstacle(1,j) - curr(1,:), obstacle(2,j) - curr(2,:)];%路径点到各个障碍物的向量
        r_req(j,:) = sqrt(V_req(j,1)* V_req(j,1) + V_req(j,2)* V_req(j,2));%路径点到各个障碍物的欧氏距离
    end   
    P_req = 0;
    for k = 1:n
        if r_req(k,:) <= p0
            P_req1 = req * (1 / r_req(k,:) - 1 / p0) * r_att^2 / r_req(k,:)^2;%斥力分量1：障碍物指向路径点的斥力
            P_req2 = req * (1 / r_req(k,:) - 1 / p0)^2 * r_att;%斥力分量2：路径点指向目标点的分引力
%             P_reqk = P_req1 / r_req(k,:) * V_req(k,:) + P_req2 / r_att * V_att;%合力分散到x,y方向
             P_reqk = P_req1 / r_req(k,:) * V_req(k,:) + P_req2 / r_att * V_att;
            P_req = P_req + norm(P_reqk);%斥力
        end     
    end
    %% 合力计算
    output = P_att + P_req;
 end
