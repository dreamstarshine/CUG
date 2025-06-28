% -------------------------------------------------------------------------
% 人工势场算法
% 出处：GitHub-https://github.com/zzuwz/Artificial-Potential-Field
% 参考提供源代码作者提供的资料，依照个人理解，添加了大量中文注释
%               —— 2021/10/29  Poaoz 
% -------------------------------------------------------------------------

% 流程梳理 - 人工势场法
% 1）起点、终点、障碍物、迭代次数、取点半径等参数的设定
% 2）以起点为中心，作半径为r的圆，从圆上取八个均布的点
% 3）分别计算八个点的前进“代价”—— 终点对其的引力+所有障碍物对其的斥力 
% 4）取“代价”最小的点的坐标，结合现有起点，计算得到新的起点，然后重复上述内容
% 5）当发现 一个点距离终点很近 or 迭代的次数计算完 程序停止。

%%
clc
clear
close all

figure(1);
axis([0 20 0 20]);   % 地图 20x20
begin=[2;2];         % 起点
over=[18;18];        % 终点
obstacle=[4 10 11 13 14 6 8 8;8 9 6 13 18 8 6 4];  % 障碍物x;y坐标
% obstacle=[ 10 12 6 8;12 10 8 6];

% 绘制起点、终点、障碍物
hold on;
plot(begin(1),begin(2),'go','MarkerFaceColor','g');
plot(over(1),over(2),'ro','MarkerFaceColor','r');
text(begin(1),begin(2),'起点');
text(over(1),over(2),'终点');
plot(obstacle(1,:),obstacle(2,:),'ob');
title('传统人工势场法生成避障路径')
 for i=1:size(obstacle,2)      % 在个障碍物点处，绘制椭圆。  'Curvature' 矩形的曲率
    rectangle('Position',[obstacle(1,i)-0.5,obstacle(2,i)-0.5,1,1],'Curvature',[1,1],'FaceColor','r');
 end
scatter(obstacle(1,:),obstacle(2,:),'r')
% point= path_plan(begin,over,obstacle);  % 计算并绘制出路径
title('改进的人工势场法生成避障路径')
point=path_plan_new1(begin,over,obstacle);