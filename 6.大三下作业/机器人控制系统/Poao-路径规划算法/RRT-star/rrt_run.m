% -------------------------------------------------------------------------
% RRT* 算法
% 出处：GitHub-https://github.com/wntun/RRT-star
% 参考提供源代码作者提供的资料，依照个人理解，添加了大量中文注释
%               —— 2021/10/29  Poaoz 
% -------------------------------------------------------------------------

%   流程梳理 - RRT算法
%   1) 进行起点、终点、障碍物、前进步长、迭代次数等参数的设定，rrt树的初始化
%   2) 在地图上随机采样一个点a，并找出现有节点中与其最近的节点b
%   3）沿最近的节点b到采样点a方向，根据机器人步长，求得新的节点c
%   4）对新的节点c进行障碍物判断 & 找到c的父节点 （最近点 or 可到达的点-eighbors）
%   5）如果新节点符合要求，将其插入到rrt树中（携带四个rrt参数）  并进行节点重连的路径优化计算
%   6）判断该新节点c是否“到达目标点”（按条件修改rrt的第四个参数），并持续重复上述“2-6”
%   7）迭代次数达到设定值后，根据得到的rrt树，找出最佳路径
function []=rrt_run

    % 画矩形块：[x,y,a,b]起始点(x,y),宽a，长b
    function[] = rect(x,y,l,b)
      hold on
      rectangle('Position',[x,y,l,b],'FaceColor','k')
    end

    % 画圆的函数
    function circle(x,y,r)
        ang=0:0.01:2*pi; 
        xp=r*cos(ang);
        yp=r*sin(ang);
        plot(x+xp,y+yp, '.r');
    end

    % 画图，及一些输入参数的设置
figure;
axis([0,200,0,200])
set(gca, 'XTick', 0:10:200)
set(gca, 'YTick', 10:10:200)
grid ON
hold on
%边框
rect(0,0,3,200);    
rect(0,0,200,3);    
rect(197,0,3,200);   
rect(0,197,200,3);  
% 画矩形块充当障碍物
rect(20,170,10,30);    
rect(80,180,60,10);    
rect(160,170,30,10);      
rect(60,110,20,30);    
rect(130,90,10,70);    
rect(30,60,10,50);     
rect(130,40,30,10);    

p_start = [30;160];    % 起点，目标点设定
p_goal = [180;120];

rob.x = 30;      % 机器人所在起点坐标
rob.y = 160;

% 初始化参数
param.obstacles =[20,170,10,30; 80,180,60,10;160,170,30,10;
    60,110,20,30;130,90,10,70;30,60,10,50;130,40,30,10;
    0,0,3,200;0,0,200,3;197,0,3,200;10,197,200,3];   % 对应矩形块
% param.obstacles =[0,0,3,200;0,0,200,3;197,0,3,200;10,197,200,3];   % 对应矩形块
param.threshold = 2;
param.maxNodes = 800;
param.step_size = 5;       % 机器人每次行进步数
param.neighbourhood = 5;   % 寻找子节点的距离
param.random_seed = 40;

% plot(rob.x,rob.y,'.r') 
plot(rob.x,rob.y,'go','MarkerFaceColor','g');
hold on;
plot(p_goal(1)+.5,p_goal(2)+.5,'ro','MarkerFaceColor','r');
hold on;
text(rob.x+.5,rob.y+.5,'起点');
text(p_goal(1)+.5,p_goal(2)+.5,'终点');

% 进行搜图并出结果
result = PlanPathRRTstar(param, p_start, p_goal)   
plot(rob.x+.5,rob.y+.5,'go','MarkerFaceColor','g');
end