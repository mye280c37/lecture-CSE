`timescale 1ns / 1ps

module rs_latch_nand(input R, input S, output Q, output nQ);
assign Q =  ~(R&nQ);
assign nQ =  ~(S&Q);
endmodule
