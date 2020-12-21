`timescale 1ns / 1ps

module demux_1_to_4(F, a, b, A, B, C, D);
input a, b, F;
output A, B, C, D;

assign A = (~a)&(~b)&F;
assign B = (~a)&b&F;
assign C = a&(~b)&F;
assign D = a&b&F;

endmodule
