function y=invKarm(input)
dx=input(1)/2;
dy=input(2)/2;
dz=input(3);
L1=1;L2=1;L6=0.2;

 ca2=(dx^2+dy^2-L1^2-L2^2)/(2*L1*L2);
 
 if dx>=0 && dy>=0
 a2=atan(sqrt(1-ca2^2)/ca2);
 else
 a2=atan(-sqrt(1-ca2^2)/ca2);
 end
     

 B=acos((dx^2+dy^2+L1^2-L2^2)/(2*L1*sqrt(dx^2+dy^2)));
 a1=atan(dy/dx)+B;
 y=[2*a1 2*a2 dz+L6 0 0 0];

end

