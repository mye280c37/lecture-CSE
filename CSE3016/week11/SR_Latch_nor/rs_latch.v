`timescale 1ns / 1ps

module rs_latch (input R, input S, output Q, output nQ);
wire q, nq;

assign Q = q;
assign nQ = nq;

assign q = ~(R|nq);
assign nq = ~(S|q);

endmodule
