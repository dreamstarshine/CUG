clc
clear
close all
%% ����ʼ��ͼ
% load map.mat
map=zeros(22,20);
%�ϰ������꣬���У�����Ϊy����Ϊx
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
MAX=rot90(map,3); %%%����0,1�ڷŵ�ͼ�����������鲻һ��
MAX_X=size(MAX,1); %%% ?��ȡ��������x�᳤��
MAX_Y=size(MAX,2); %%% ?��ȡ��������y�᳤��
axis([1 MAX_X+1, 1 MAX_Y+1]) %%% ?����x��y��������
set(gca,'xtick',1:1:MAX_X+1,'ytick',1:1:MAX_Y+1,'GridLineStyle','-',...
    'xGrid','on','yGrid','on')
grid on;  %%% ?�ڻ�ͼ��ʱ�����������
hold on; %%% ?��ǰ�ἰͼ�񱣳ֶ�����ˢ�£�׼�����ܴ˺󽫻��Ƶ�ͼ�Σ���ͼ����
n=0;%Number of Obstacles ? ? ? ? ? ? ? ? ? %%% ?�ϰ�������
for j=1:MAX_Y
    for i=1:MAX_X
        if (MAX(i,j)==1)
            %%plot(i+.5,j+.5,'ks','MarkerFaceColor','b'); ԭ���Ǻ��Բ��ʾ
            fill([i,i+1,i+1,i],[j,j,j+1,j+1],'k'); %%%�ĳ� �úڷ�������ʾ�ϰ���
        end
    end
end
io=1;
Q=[2;2];
MAX(Q(1,end),Q(2,end))=1;
plot(Q(1,:)+.5,Q(2,:)+.5,'ob')
hold on
pause(0.01)
io1=0;io2=0;io3=0;io4=0;%1��2��3��4��Ӧ�ж��Ƿ����ҡ��ϡ������ߣ���ʱ��
while io==1
    io=0;
    if MAX(Q(1,end)+1,Q(2,end))==0&&io1==0&&io2==0&&io3==0&&io4==0%�Գ�ʼ�㵥��Ѱ��һ������
        Qa=[Q(1,end)+1,Q(2,end)];
        MAX(Q(1,end)+1,Q(2,end))=1;%���߹��ĵ������ϰ������ͬ��
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
    %io1�����ң������������ҵĹ����������¾����£�Ȼ�����Ҳ����������ߣ�������Һ����϶������˾�����ֻ������
   %io2~io4ͬ��
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
disp('�������')