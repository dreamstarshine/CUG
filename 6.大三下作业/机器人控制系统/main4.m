clc
clear
close all
%% 画初始地图
% load map.mat
map=zeros(22,20);
%障碍物坐标，两行，上面为y下面为x
a{1}=[ones(1,size(11:20,2))*30,ones(1,size(11:20,2))*31;11:20,11:20];
a{2}=[ones(1,size(10:12,2))*19,ones(1,size(10:12,2))*20;10:12,10:12];
a{3}=[ones(1,size(21:25,2))*21,ones(1,size(21:25,2))*26;21:25,21:25];
a{4}=[22:26;ones(1,size(22:26,2))*25];
a{5}=[9,10,11,12,13,14,15;29,29,29,29,29,29,29];
a{6}=[15,15,15;13,14,15];

for i=1:size(a,2)
    Aa=a{i};
    for j=1:size(Aa,2)
        map(Aa(1,j),Aa(2,j))=1;
    end
end
map(1:10,:)=[];
map(:,1:8)=[];
map(1,:)=ones(1,length(map(1,:)))*1;
map(end,:)=ones(end,length(map(end,:)))*1;
map(:,1)=ones(length(map(:,1)),1)*1;
map(:,end)=ones(length(map(:,end)),1)*1;
q_start=[2,2];
MAX=rot90(map,3); %%%设置0,1摆放的图像与存入的数组不一样
MAX_X=size(MAX,1); %%% ?获取列数，即x轴长度
MAX_Y=size(MAX,2); %%% ?获取行数，即y轴长度
axis([1 MAX_X+1, 1 MAX_Y+1]) %%% ?设置x，y轴上下限
set(gca,'xtick',1:1:MAX_X+1,'ytick',1:1:MAX_Y+1,'GridLineStyle','-',...
    'xGrid','on','yGrid','on')
grid on;  %%% ?在画图的时候添加网格线
hold on; %%% ?当前轴及图像保持而不被刷新，准备接受此后将绘制的图形，多图共存
n=0;%Number of Obstacles ? ? ? ? ? ? ? ? ? %%% ?障碍的数量
for j=1:MAX_Y
    for i=1:MAX_X
        if (MAX(i,j)==1)
            %%plot(i+.5,j+.5,'ks','MarkerFaceColor','b'); 原来是红点圆表示
            fill([i,i+1,i+1,i],[j,j,j+1,j+1],'k'); %%%改成 用黑方块来表示障碍物
        end
    end
end
io=1;
Q=[2;2];
MAX(Q(1,end),Q(2,end))=1;
plot(Q(1,:)+.5,Q(2,:)+.5,'ob')
hold on
pause(0.01)
io1=0;io2=0;io3=0;io4=0;%1、2、3、4对应判断是否能右、上、左、下走，逆时针
while io==1
    io=0;
    if MAX(Q(1,end)+1,Q(2,end))==0&&io1==0&&io2==0&&io3==0&&io4==0%对初始点单独寻找一个方向
        Qa=[Q(1,end)+1,Q(2,end)];
        MAX(Q(1,end)+1,Q(2,end))=1;%将走过的点填充成障碍物，以下同理
        Q=[Q,Qa'];
        plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
        hold on
        plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
        hold on
        pause(0.01)
        io=1;
        io1=1;
    elseif MAX(Q(1,end),Q(2,end)+1)==0&&io1==0&&io2==0&&io3==0&&io4==0
        Qa=[Q(1,end),Q(2,end)+1];
        MAX(Q(1,end),Q(2,end)+1)=1;
        Q=[Q,Qa'];
        plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
        hold on
        plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
        hold on
        pause(0.01)
        io=1;
        io2=1;
    elseif MAX(Q(1,end)-1,Q(2,end))==0&&io1==0&&io2==0&&io3==0&&io4==0
        Qa=[Q(1,end)-1,Q(2,end)];
        MAX(Q(1,end)-1,Q(2,end))=1;
        Q=[Q,Qa'];
        plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
        hold on
        plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
        hold on
        pause(0.01)
        io=1;
        io3=1;
    elseif MAX(Q(1,end),Q(2,end)-1)==0&&io1==0&&io2==0&&io3==0&&io4==0
        Qa=[Q(1,end),Q(2,end)-1];
        MAX(Q(1,end),Q(2,end)-1)=1;
        Q=[Q,Qa'];
        plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
        hold on
        plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
        hold on
        pause(0.01)
        io=1;
        io4=1;
    end
    %io1是向右，具体是在向右的过程中能向下就向下，然后向右不了了往上走；如果向右和向上都不行了就跳出只能向左
   %io2~io4同理
    while io1==1
        io1=0;
        if MAX(Q(1,end),Q(2,end)-1)==0
            io4=1;
            io=1;
            break
        else
            if MAX(Q(1,end)+1,Q(2,end))==0
                Qa=[Q(1,end)+1,Q(2,end)];
                MAX(Q(1,end)+1,Q(2,end))=1;
                Q=[Q,Qa'];
                plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                hold on
                plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                hold on
                pause(0.01)
                io1=1;
                io=1;
            else
                if MAX(Q(1,end),Q(2,end)+1)==0
                    Qa=[Q(1,end),Q(2,end)+1];
                    MAX(Q(1,end),Q(2,end)+1)=1;
                    Q=[Q,Qa'];
                    plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                    hold on
                    plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                    hold on
                    pause(0.01)
                    io1=1;
                    io=1;
                end
            end
        end
    end
    
    while io2==1
        io2=0;
        if MAX(Q(1,end)+1,Q(2,end))==0
            io1=1;
            io=1;
            break
        else
            if MAX(Q(1,end),Q(2,end)+1)==0
                Qa=[Q(1,end),Q(2,end)+1];
                MAX(Q(1,end),Q(2,end)+1)=1;
                Q=[Q,Qa'];
                plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                hold on
                plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                hold on
                pause(0.01)
                io2=1;
                io=1;
            else
                if MAX(Q(1,end)-1,Q(2,end))==0
                    Qa=[Q(1,end)-1,Q(2,end)];
                    MAX(Q(1,end)-1,Q(2,end))=1;
                    Q=[Q,Qa'];
                    plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                    hold on
                    plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                    hold on
                    pause(0.01)
                    io2=1;
                    io=1;
                end
            end
        end
    end
    
    while io3==1
        io3=0;
        if MAX(Q(1,end),Q(2,end)+1)==0
            io2=1;
            io=1;
            break
        else
            if MAX(Q(1,end)-1,Q(2,end))==0
                Qa=[Q(1,end)-1,Q(2,end)];
                MAX(Q(1,end)-1,Q(2,end))=1;
                Q=[Q,Qa'];
                plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                hold on
                plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                hold on
                pause(0.01)
                io3=1;
                io=1;
            else
                if MAX(Q(1,end),Q(2,end)-1)==0
                    Qa=[Q(1,end),Q(2,end)-1];
                    MAX(Q(1,end),Q(2,end)-1)=1;
                    Q=[Q,Qa'];
                    plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                    hold on
                    plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                    hold on
                    pause(0.01)
                    io3=1;
                    io=1;
                end
            end
        end
    end
    
    while io4==1
        io4=0;
        if MAX(Q(1,end)-1,Q(2,end))==0
            io3=1;
            io=1;
            break
        else
            if MAX(Q(1,end),Q(2,end)-1)==0
                Qa=[Q(1,end),Q(2,end)-1];
                MAX(Q(1,end),Q(2,end)-1)=1;
                Q=[Q,Qa'];
                plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                hold on
                plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                hold on
                pause(0.01)
                io4=1;
                io=1;
            else
                if MAX(Q(1,end)+1,Q(2,end))==0
                    Qa=[Q(1,end)+1,Q(2,end)];
                    MAX(Q(1,end)+1,Q(2,end))=1;
                    Q=[Q,Qa'];
                    plot(Q(1,end)+.5,Q(2,end)+.5,'ob')
                    hold on
                    plot([Q(1,size(Q,2))+.5,Q(1,size(Q,2)-1)+.5],[Q(2,size(Q,2))+.5,Q(2,size(Q,2)-1)+.5],'-b')
                    hold on
                    pause(0.01)
                    io4=1;
                    io=1;
                end
            end
        end
    end
end
disp('搜索完成')