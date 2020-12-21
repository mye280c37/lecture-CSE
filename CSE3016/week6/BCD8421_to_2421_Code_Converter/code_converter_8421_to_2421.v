`timescale 1ns / 1ps

module inv(A,B,C,D,x,y,z,t);
input A, B, C, D;
output x, y, z, t;

assign x = ~((~(B&C))&(~(B&C))&(~A));
assign y = ~((~A)&(~(B&(~D)))&(~(B&C)));
assign z = ~((~A)&(~((~B)&C))&(~(B&(~C)&D)));
assign t = D;
endmodule
