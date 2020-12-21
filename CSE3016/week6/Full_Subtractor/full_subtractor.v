`timescale 1ns / 1ps

module inv(A, B, b_n_1, D, b_n);
input A, B, b_n_1;
output D, b_n;

assign b_n = (b_n_1&(~(A^B)))|((~A)&B);
assign D = A^B^b_n_1;
endmodule
