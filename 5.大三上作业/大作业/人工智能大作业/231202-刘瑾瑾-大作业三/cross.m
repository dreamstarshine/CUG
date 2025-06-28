function [A,B]=cross(A,B)
%二点交叉
L=length(A);
if L<10
    W=L;
elseif ((L/10)-floor(L/10))>=rand&&L>10%floor函数向负无穷大方向取整
    W=ceil(L/10)+8;%ceil朝正无穷大方向取整
else
    W=floor(L/10)+8;
end
%%W为需要交叉的位数
p=unidrnd(L-W+1);%随机产生一个交叉位置
%fprintf('p=%d ',p);%交叉位置
for i=1:W
    x=find(A==B(1,p+i-1));
    y=find(B==A(1,p+i-1));
    [A(1,p+i-1),B(1,p+i-1)]=exchange(A(1,p+i-1),B(1,p+i-1));
    [A(1,x),B(1,y)]=exchange(A(1,x),B(1,y));
end
end


