`timescale 1ns / 1ps

module inv(A, B, C, D, P, PEC);
input A, B, C, D, P;
output PEC;

assign PEC = ~(A^B^C^D^P);
endmodule
