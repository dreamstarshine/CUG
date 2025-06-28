%main
tic%计算程序运行时间
% close;
% clear;
% clc;
%%%%%%%%%%%%%%%输入参数%%%%%%%%
N=20;               %%快递站的个数
M=100;               %%种群的个数
C=2000;             %%迭代次数
m=2;                %%适应值淘汰加速指数
Pc=0.85;               %%交叉概率
Pmutation=0.15;     %%变异概率
%%生成城市的坐标
% load citys.mat
% pos = citys
%%固定城市坐标
pos=[2.1893   -0.1602;
    0.9362    1.1615;
    0.5290    2.3257;
    0.1618   -0.0956;
    0.3285    0.4135;
    0.2682    0.1005;
    0.4068   -0.1376;
    0.1594   -1.2238;
    0.2043    0.2530;
   -0.6908    0.3889;
    0.2555   -0.4658;
   -0.6643    0.6551;
    0.2791    1.1504;
   -0.1534   -0.2348;
   -0.5919    0.5875;
   -0.0739   -0.2483;
    0.3788    0.5261;
   -1.4055    0.6267;
   -2.1593   -1.5176;
   -0.7890    0.5819];
%%生成快递站之间距离矩阵
D=zeros(N,N);
for i=1:N
    for j=i+1:N
        dis=(pos(i,1)-pos(j,1)).^2+(pos(i,2)-pos(j,2)).^2;
        D(i,j)=dis^(0.5);%快递站i到j的距离
        D(j,i)=D(i,j);%快递站j到i的距离与i到j的距离相同
    end
end

%%生成初始群体

popm=zeros(M,N);%M*N的矩阵
popm_sel=zeros(M,N);
for i=1:M
    popm(i,:)=randperm(N);%随机排列N个1-N之间的随机数
end
%%随机选择一个种群
R=popm(1,:);
figure(1);
scatter(pos(:,1),pos(:,2),'rx');%画出所有城市坐标
axis([-3 3 -3 3]);
figure(2);
plot_route(pos,R);      %%画出初始种群对应各城市之间的连线
axis([-3 3 -3 3]);
%%初始化种群及其适应函数
fitness=zeros(M,1);%适应度
len=zeros(M,1);

for i=1:M%计算每个染色体对应的总长度
    len(i,1)=myLength(D,popm(i,:));
end
maxlen=max(len);%最大回路
minlen=min(len);%最小回路

fitness=fit(len,m,maxlen,minlen);
rr=find(len==minlen);%找到最小值的下标，赋值为rr
R=popm(rr(1,1),:);%提取该染色体，赋值为R
for i=1:N
    fprintf('%d ',R(i));%把R顺序打印出来
end
fprintf('\n');

fitness=fitness/sum(fitness);
distance_min=zeros(C+1,1);  %%各次迭代的最小的种群的路径总长
nn=M;
iter=0;
while iter<C
    fprintf('迭代第%d次\n',iter);
    %%选择操作（适应度比例法）
    p=fitness./sum(fitness);
    q=cumsum(p);%累加
    for i=1:M
        len(i,1)=myLength(D,popm(i,:));
        r=rand;
        tmp=find(r<=q);
        popm_sel(i,:)=popm(tmp(1),:);
    end 
    %%锦标赛选择
%     for i=1:M
%         n=0.05*M;
%         ran=randperm(M);
%         for j=1:n %选出n个个体，进行竞争
%             fitness_insert(j,1)=fitness(ran(j),1);
%             popm_insert(j,:)=popm(ran(j),:);
%         end
%         [fimax,indexi]=max(fitness_insert);
%         popm_sel(i,:)=popm_insert(indexi,:);
%     end

    %%线性排序法
%     Fit=[fitness,popm];
%     Fit=sortrows(Fit,1);
%     Fit(:,1)=[];
%     pmax=max(fitness)/sum(fitness);
%     pmin=min(fitness)/sum(fitness);
%     
%     for i=1:M
%         p(i,1)=pmin+(pmax-pmin)*(i-1)/(M-1);
%     end
%     p=p/sum(p);
%     q=cumsum(p);%累加
%     for i=1:M
%         r=rand;
%         tmp=find(r<=q);
%         popm_sel(i,:)=Fit(tmp(1),:);
%     end 

    %%非线性排序法选择
%     Fit=[fitness,popm];
%     Fit=sortrows(Fit,-1);
%     Fit(:,1)=[];
%     Fitmax=max(fitness)/sum(fitness);
%     for i=1:M
%         p(i,1)=Fitmax*(1-Fitmax).^(i-1);
%     end
%     p(M,1)=(1-Fitmax).^(M-1);
%     p=p/sum(p);
%     q=cumsum(p);%累加
%     for i=1:M
%         r=rand;
%         tmp=find(r<=q);
%         popm_sel(i,:)=Fit(tmp(1),:);
%     end 

    %%交叉操作
    nnper=randperm(M);%返回M个1-M的随机数
    for i=1:2:M
        p=rand;
         while p==0
             p=rand;
        end
        if Pc>=p
        A=popm_sel(nnper(i),:);
        B=popm_sel(nnper(i+1),:);
        [A,B]=cross(A,B);
         popm_sel(nnper(i),:)=A;
         popm_sel(nnper(i+1),:)=B;
        end
    end
    %%变异操作
    for i=1:M
        pick=rand;
        while pick==0
             pick=rand;
        end
        if pick<=Pmutation
           popm_sel(i,:)=Mutation(popm_sel(i,:));
        end
    end
    [fmax,indmax]=max(fitness);%求当代最佳个体
    popm_sel(1,:)=popm(indmax,:);%保存当代最佳个体，以保证不丢失最优个体
    %%求适应度函数
    NN=size(popm_sel,1);
    len=zeros(NN,1);
    for i=1:NN
        len(i,1)=myLength(D,popm_sel(i,:));
    end

    maxlen=max(len);
    minlen=min(len);
    distance_min(iter+1,1)=minlen;
    fitness=fit(len,m,maxlen,minlen);
    final_fit=fitness;
    rr=find(len==minlen);
    fprintf('minlen=%d\n',minlen);
    R=popm_sel(rr(1,1),:);
    for i=1:N
        fprintf('%d ',R(i));
    end
    fprintf('\n');
    popm=[];
    popm=popm_sel;
    iter=iter+1;
    %pause(1);

end
%end of while
disp("最大适应度为：")
maxfit=max(final_fit)
disp("最小适应度为：")
minfit=min(final_fit)
disp("平均适应度为：")
avgfit=mean(final_fit)
figure(3)
plot_route(pos,R);
axis([-3 3 -3 3]);
figure(4)
plot(distance_min);
toc%计算运行时间
disp("平均迭代次数")
t=toc/C*1000

