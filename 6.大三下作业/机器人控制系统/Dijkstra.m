clc,clear all
n=7;%输入结点个数
a=zeros(7);
a(1,2)=1;a(1,3)=2;a(1,4)=3;%设置矩阵中非零非无穷的值          
a(2,1)=1;a(2,6)=6;
a(3,1)=2;a(3,5)=5;a(3,6)=4;
a(4,1)=3;a(4,5)=4;
a(5,3)=5;a(5,4)=4;a(5,7)=7;
a(6,2)=6;a(6,3)=4;a(6,7)=8;
a(7,5)=7;a(7,6)=8;
for i=1:n
    for j=1:n
       if(a(i,j)==0)
           a(i,j)=inf;%将矩阵中a=0的点换成无穷大
       end
    end
end
for i=1:n
    a(i,i)=0;%当前顶点到自身的距离为零
end
%................生成邻接矩阵
pb(1:length(a))=0;pb(1)=1;  %当一个点已经求出到原点的最短距离时，其下标i对应的pb(i)赋1
index1=1; %存放存入S集合的顺序
index2=ones(1,length(a)); %存放始点到第i点最短通路中第i顶点前一顶点的序号
d(1:length(a))=inf;d(1)=0;  %存放由始点到第i点最短通路的值
temp=1;  %temp表示c1,算c1到其它点的最短路。
while sum(pb)<length(a)  %看是否所有的点都标记为P标号
tb=find(pb==0); %找到标号为0的所有点,即找到还没有存入S的点
d(tb)=min(d(tb),d(temp)+a(temp,tb));%计算标号为0的点的最短路，或者是从原点直接到这个点，又或者是原点经过r1,间接到达这个点
tmpb=find(d(tb)==min(d(tb)));  %求d[tb]序列最小值的下标
temp=tb(tmpb(1));%可能有多条路径同时到达最小值，却其中一个，temp也从原点变为下一个点
pb(temp)=1;%找到最小路径的表对应的pb(i)=1
index1=[index1,temp];  %存放存入S集合的顺序
temp2=find(d(index1)==d(temp)-a(temp,index1));
index2(temp)=index1(temp2(1)); %记录标号索引
end
a, d, index1, index2