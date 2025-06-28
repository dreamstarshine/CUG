clear,clc,close;
L1=Link('theta',0,'a',0,'alpha',0,'offset',0,'qlim',[0
160],'modified');
L2=Link('d',0,'a',127.5,'alpha',0,'offset',0,'qlim',[-90
90]*pi/180,'modified');
L3=Link('d',0,'a',160,'alpha',0,'offset',0,'qlim',[-120
120]*pi/180,'modified');
L4=Link('d',0,'a',160,'alpha',0,'offset',0,'qlim',[-180
180]*pi/180,'modified');
robot = SerialLink([L1 L2 L3 L4],'name','SCARA');
% Q=[20 30 30 30];
Q=[45 45 45 45];
forward_Q=[Q(1) 0 0 0]+[0 Q(2) Q(3) Q(4)]/180*pi;
forward=robot.fkine(forward_Q)
rpy=tr2rpy(forward, 'xyz')*180/pi;
W=[-1200 +1200 -1200 +1200 -1200 +1200];
mask_vector = [1,1,1,1,0,0];
axi_val = robot.ikine(forward,'mask',mask_vector,'pinv');
Q=[axi_val(1) 0 0 0]+[0 axi_val(2) axi_val(3) axi_val(4)]*180/pi
view(3);
robot.plot(forward_Q,'workspace',W);
robot.teach(forward_Q,'rpy');