function y=invKgripper(input)
ax=input(1);
ay=input(2);
az=input(3)-1.5;

a1=atan(ay/ax);

a2=atan(az/(sqrt(ax^2+ay^2)));  

a3=0;
    y=[0 0 0 2*a1 2*a2 a3];
end