`timescale 1ns / 1ps

module inv(A, B, C_in, S, C_out);
input A, B, C_in;
output S, C_out;

assign C_out = (C_in&(A^B))|(A&B);
assign S = A^B^C_in;
endmodule
