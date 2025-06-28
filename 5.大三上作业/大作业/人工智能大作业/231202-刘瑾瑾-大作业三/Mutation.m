%变异函数 ，逆转变异
function a=Mutation(A)
%%
% % 互换变异
index1=0;
index2=0;
nnper=randperm(size(A,2));%返回矩阵的列数，并随机取N个1-N之间的数
index1=nnper(1);
index2=nnper(2);
temp=0;
temp=A(index1);
A(index1)=A(index2);
A(index2)=temp;
a=A;
%%
%逆转变异
% index1=0;
% index2=0;
% nnper=randperm(size(A,2));%返回矩阵的列数，并随机取N个1-N之间的数
% index1=nnper(1);
% index2=nnper(2);
% C=A;
% if index1>index2
%     [index1,index2]=exchange(index1,index2);
% end
% for k=1:(index2-index1+1)
%    A(index1)=C(index2);
%    index1=index1+1;
%    index2=index2-1;
% end
% a=A;
%%
%移动变异 随机选取一个基因，向右移动一个移动位数。
% long=length(A);
% index1=0;%随机移动的基因
% index2=0;%随机移动的位数
% nnper=randperm(size(A,2));%返回矩阵的列数，并随机取N个1-N之间的数
% index1=nnper(1);
% index2=nnper(2);
% temp=A(index1);%保存这个位点
% i=index1;
% j=index1+1; 
% for k=1:index2
%    if i>long
%        i=mod(i,long);
%    end
%    if j>long
%        j=mod(j,long);
%    end
%        A(i)=A(j);
%    i=i+1;
%    j=i+1;
% end
% index=index1+index2;
% if index1+index2>20
%     index=mod((index1+index2),long);
% end
% A(index)=temp;
% a=A;
end

