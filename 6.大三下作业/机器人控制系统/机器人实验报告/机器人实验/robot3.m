clear,clc,close;
L1=Link('theta',0,'a',0,'alpha',0,'offset',0,'qlim',[0
160],'modified');
L2=Link('d',0,'a',127.5,'alpha',0,'offset',0,'qlim',[-90
90]*pi/180,'modified');
L3=Link('d',0,'a',160,'alpha',0,'offset',0,'qlim',[-120
120]*pi/180,'modified');
L4=Link('d',0,'a',160,'alpha',0,'offset',0,'qlim',[-160
160]*pi/180,'modified');
robot = SerialLink([L1 L2 L3 L4],'name','SCARA');
[Q_theta,State]=ScaraIkineMDH(447.5,0,0,0,0,0);
Q=Q_theta(1,:);
W=[-1200 +1200 -1200 +1200 -1200 +1200];
robot.plot(Q,'workspace',W);
robot.teach(Q,'rpy');