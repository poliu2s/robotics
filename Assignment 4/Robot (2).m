function Jaco=Robot(a1,a2,dx,a4,a5,a6) 
function T = DH(q)
   
    L1=1;L2=1;L3=0.5;L6=0.2;
    
		tw0 = [pi/2+q(1) L6+L3 L1 0];  
	t01 = [q(2), 0, L2, 0];
	t12 = [-pi/2, -L3+q(3), 0, -pi/2];
    t23 = [-pi/2+q(4), 0, 0, -pi/2];
	t34 = [-pi/2+q(5), 0, 0, pi/2];
	t45 = [-pi/2+q(6), -L6, 0, 0];	
	
	T = [tw0;t01;t12;t23;t34;t45];
end

function output = TRANS(input,i)

output =	[cos(input(i,1)) -sin(input(i,1))*cos(input(i,4)) sin(input(i,1))*sin(input(i,4)) (input(i,3))*cos(input(i,1));
          sin(input(i,1)) cos(input(i,1))*cos(input(i,4)) -cos(input(i,1))*sin(input(i,4)) (input(i,3))*sin(input(i,1));
			 0					sin(input(i,4))       			 cos(input(i,4))            input(i,2)				 	 ;
			 0          0               		   0                     1           ];
         
end
in=

T01=TRANS(DH(a1,a2,dx,a4,a5,a6),1);
T12=TRANS(DH(a1,a2,dx,a4,a5,a6),2);
T23=TRANS(DH(a1,a2,dx,a4,a5,a6),3);
T34=TRANS(DH(a1,a2,dx,a4,a5,a6),4);
T45=TRANS(DH(a1,a2,dx,a4,a5,a6),5);
T56=TRANS(DH(a1,a2,dx,a4,a5,a6),6);

T02=T01*T12;
T03=T01*T12*T23;
T04=T01*T12*T23*T34;
T05=T01*T12*T23*T34*T45;
T06=T01*T12*T23*T34*T45*T56;

p1=1;p2=1;p3=0;p4=1;p5=1;p6=1;
z0=[T01(1,3) T01(2,3) T01(3,3)].';
z1=[T02(1,3) T02(2,3) T02(3,3)].';
z2=[T03(1,3) T03(2,3) T03(3,3)].';
z3=[T04(1,3) T04(2,3) T04(3,3)].';
z4=[T05(1,3) T05(2,3) T05(3,3)].';
z5=[T06(1,3) T06(2,3) T06(3,3)].';

Jaco=[p1*z0 p2*z1 p3*z2 p4*z3 p5*z4 p6*z5];


end
