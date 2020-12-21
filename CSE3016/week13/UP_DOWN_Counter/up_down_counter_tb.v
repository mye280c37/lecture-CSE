`timescale 1ns / 1ps

module up_down_counter_tb();
	reg clk, S;
	wire [3:0] Q;
	
	up_down_counter set(clk, S, Q);
	
	initial begin
		clk = 1'b0;
		S = 1'b0;
	end
	
	always clk = #5 ~clk;
	always S = #200 ~S;
endmodule