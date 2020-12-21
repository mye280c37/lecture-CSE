`timescale 1ns / 1ps

module BCD2421_counter_tb();
	reg clk;
	wire [3:0] Q;
	
	BCD2421_counter set(clk, Q);
	
	initial clk = 1'b0;
	
	always clk =#10 ~clk;
endmodule