`timescale 1ns / 1ps

module ring_counter_tb();
	reg clk, rst;
	wire [3:0] L;
	
	ring_counter set(clk, rst, L);
	
	initial begin
		clk = 1'b0;
		rst = 1'b1;
	end
	
	always rst = #197 ~rst;
	always clk = #10 ~clk;
endmodule