function rotmat2aa(R)
	%  addtwo(x,y)  Adds two numbers, vectors, whatever, and
	%               print the result = x + y
	
    B=eye(3);
    C=R-B;
    
    Axis=null(C)
    
    %Calculate the trace, which is the sum of the diagonal elements
    %of the rotation matrix
    Trace=R(1)+R(5)+R(9);
    
    Theta=acos((Trace-1)/2)
    
    
    