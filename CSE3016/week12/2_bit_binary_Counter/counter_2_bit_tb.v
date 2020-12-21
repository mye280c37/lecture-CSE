`timescale 1ns / 1ps

module two_bit_counter_tb();
reg clk;
wire [1:0] out;

two_bit_counter set(clk, out);

initial clk = 1'b0;

always clk = #20 ~clk;

endmodule