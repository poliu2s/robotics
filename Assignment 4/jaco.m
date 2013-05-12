function [Jacobian,Jacob_inv]=Robot(q) 
%Robot(1 2 3 4 5 6)
a1 = q(1);
a2 = q(2);
d3 = q(3);
a4 = q(4);
a5 = q(5);
a6 = q(6);

%function T = DH(q)

L1=1; L2=1; L3=0.5; L6=0.2;
        
        input = [pi/2+a1 L6+L3 L1  0;  
                  a2   0    L2     0;
                 -pi/2 -L3+d3 0 -pi/2;
                 -pi/2+a4 0 0 -pi/2;
                 -pi/2+a5 0 0 pi/2;
                 -pi/2+a6 -L6 0 0];	

   % function output = TRANS(input,i)

    T01 =	[cos(input(1,1)) -sin(input(1,1))*cos(input(1,4)) sin(input(1,1))*sin(input(1,4)) (input(1,3))*cos(input(1,1));
              sin(input(1,1)) cos(input(1,1))*cos(input(1,4)) -cos(input(1,1))*sin(input(1,4)) (input(1,3))*sin(input(1,1));
                 0					sin(input(1,4))       			 cos(input(1,4))            input(1,2)				 	 ;
                 0          0               		   0                     1           ];
    T12 =	[cos(input(2,1)) -sin(input(2,1))*cos(input(2,4)) sin(input(2,1))*sin(input(2,4)) (input(2,3))*cos(input(2,1));
              sin(input(2,1)) cos(input(2,1))*cos(input(2,4)) -cos(input(2,1))*sin(input(2,4)) (input(2,3))*sin(input(2,1));
                 0					sin(input(2,4))       			 cos(input(2,4))            input(2,2)				 	 ;
                 0          0               		   0                     1           ];
    T23 =	[cos(input(3,1)) -sin(input(3,1))*cos(input(3,4)) sin(input(3,1))*sin(input(3,4)) (input(3,3))*cos(input(3,1));
              sin(input(3,1)) cos(input(3,1))*cos(input(3,4)) -cos(input(3,1))*sin(input(3,4)) (input(3,3))*sin(input(3,1));
                 0					sin(input(3,4))       			 cos(input(3,4))            input(3,2)				 	 ;
                 0          0               		   0                     1           ];
    T34 =	[cos(input(4,1)) -sin(input(4,1))*cos(input(4,4)) sin(input(4,1))*sin(input(4,4)) (input(4,3))*cos(input(4,1));
              sin(input(4,1)) cos(input(4,1))*cos(input(4,4)) -cos(input(4,1))*sin(input(4,4)) (input(4,3))*sin(input(4,1));
                 0					sin(input(4,4))       			 cos(input(4,4))            input(4,2)				 	 ;
                 0          0               		   0                     1           ];
    T45 =	[cos(input(5,1)) -sin(input(5,1))*cos(input(5,4)) sin(input(5,1))*sin(input(5,4)) (input(5,3))*cos(input(5,1));
              sin(input(5,1)) cos(input(5,1))*cos(input(5,4)) -cos(input(5,1))*sin(input(5,4)) (input(5,3))*sin(input(5,1));
                 0					sin(input(5,4))       			 cos(input(5,4))            input(5,2)				 	 ;
                 0          0               		   0                     1           ];
    T56=	[cos(input(6,1)) -sin(input(6,1))*cos(input(6,4)) sin(input(6,1))*sin(input(6,4)) (input(6,3))*cos(input(6,1));
              sin(input(6,1)) cos(input(6,1))*cos(input(6,4)) -cos(input(6,1))*sin(input(6,4)) (input(6,3))*sin(input(6,1));
                 0					sin(input(6,4))       			 cos(input(6,4))            input(6,2)				 	 ;
                 0          0               		   0                     1           ];         
    
    T0  = eye(4);   O_0 = T0(1:3,4);     k0 = [0 0 1]';
    T01 = T0*T01;   O_1 = T01(1:3,4);    k1 = [T01(1:3,3)];
    T02 = T01*T12;  O_2 = T02(1:3,4);    k2 = [T02(1:3,3)];
    T03 = T02*T23;  O_3 = T03(1:3,4);    k3 = [T03(1:3,3)];
    T04 = T03*T34;  O_4 = T04(1:3,4);    k4 = [T04(1:3,3)];
    T05 = T04*T45;  O_5 = T05(1:3,4);    k5 = [T05(1:3,3)];
    T06 = T05*T56;  O_6 = T06(1:3,4);    k6 = [T06(1:3,3)];
    
    Jacobian=[cross(k0,(O_6-O_0)), cross(k1,(O_6-O_1)), k2, cross(k3,(O_6-O_3)), cross(k4,(O_6-O_4)), cross(k5,(O_6-O_5));
                k0, k1, zeros(3,1), k3, k4, k5];

    Jacob_inv = inv(Jacobian + eye*1E-1)

end


