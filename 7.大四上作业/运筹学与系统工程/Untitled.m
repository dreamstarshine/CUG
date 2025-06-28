clc,clear
N = 50;%种群数量
L = 20;%二进制位串长度
pc =0.8;%交叉率
pm =0.1;%变异率
g =100;%最大遗传代数
xs =10;%上限
xx =0;%下限
f = round(rand(N,L));%随机初始化种群（二维数组）
%遗传算法循环
for k =1:g
    %将二进制解码为定义域范围内十进制
    for i = 1:N
        u =f (i,:);
        m = 0;
        for j =1:L
            m = u(j)*2^(j-1)+m;%求出该个体的二进制编码的十进制数
        end
        x(i) = xx + m*(xs-xx)/(2^L-1);%映射到所要求的自变量区间上
        fit(i) = func1(x(i));%调用适应度函数
    end
    maxfit = max(fit);%定义适应度中的最大值
    minfit = min(fit);%定义适应度中的最小值
    rr = find(fit==maxfit);
    fbest = f(rr(1,1),:);%得到第k代最优个体的染色体编码数组
    xbest = x(rr(1,1));%得到最优个体对应十进制映射数值
    fit = (fit-minfit)/(maxfit-minfit);%归一化适应度函数值
 
    %基于轮盘赌的复制操作
    sum_fit = sum(fit);%适应度函数的和
    fitvaule  = fit./sum_fit;%计算概率
    fitvaule = cumsum(fitvaule);%计算累加概率
    ms = sort(rand(N,1));%随机生成N行1列在[0，1]范围内的列向量并升序排列
    fiti = 1;%原种群当前被比较的个体序号
    newi = 1;%被选择进入下一代的个体序号
    while newi <= N
        if (ms(newi)) < fitvaule(fiti)
            nf(newi,:) = f(fiti,:);
            newi = newi +1;
        else
            fiti = fiti +1;
        end
    end
 
    %基于概率的交叉操作
    for i = 1:2:N   %选择两个优秀个体
        p = rand;%生成[0,1]的随机小数
        if p <pc%若p小于交叉概率
            q = round(rand(1,L));%生成一条（0，1）分布的二进制数串
            for j =1:L
                if q(j) == 1%如果第j位上的值为1，则进行第i组个体的第j位交叉操作
                    temp = nf(i+1,j);
                    nf(i+1,j) = nf(i,j);
                    nf(i,j) = temp;%完成第j位交叉互换
                end
            end
        end
    end
 
    %基于概率的变异操作
    i =1;
    while i <= round(N*pm)%四舍五入取整
        h = randi(N);%随机选取一条需要变异的染色体
        for j = 1:round(L*pm)%在需要变异的染色体上进行L*pm个记忆变异
            g = randi(L);%随机选择变异的基因序号
            nf(h,g) = ~nf(h,g);%取反完成变异
        end
        i = i+1;
    end
 
    f = nf;
    f(1,:) =fbest;
    value(k) = maxfit;
end
disp(['最终函数最大值点为',num2str(xbest)]) 
disp(['最终函数最大值为',num2str(func1(xbest))])
 
figure(1);
xy = 0:0.01:10;
y =  10*sin(5*xy)+7*cos(4*xy);
plot(xy,y)
xlabel('x')
ylabel('f(x)')
title('f(x)=10sin(5x)+7cos(4x)')
figure(2);
plot(value)
xlabel('x')
ylabel('F(x)')
title('适应度函数变化曲线')
axis([0 100 16.8 17.1])
function result = func1(x)
fit = 10*sin(5*x)+7*cos(4*x);
result = fit;
end