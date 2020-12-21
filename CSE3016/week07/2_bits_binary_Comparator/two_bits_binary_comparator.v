`timescale 1ns / 1ps

module inv(A,B,C,D,F1,F2,F3);
input A, B, C, D;
output F1, F2, F3;

assign F1 = (A&~(C))|(B&(~C)&(~D))|(A&B&(~D));
assign F2 = (~(A^B))&(~(C^D));
assign F3 = (~(A)&C)|((~A)&(~B)&D)|((~B)&C&D);
endmodule
