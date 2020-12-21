`timescale 1ns / 1ps

module decade_counter_tb( );
	reg clk;
	wire [3:0] Q;
	
	decade_counter set(clk,  Q);
	
	initial clk = 1'b0;
	
	always clk =#10 ~clk;
endmodule