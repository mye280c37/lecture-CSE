`timescale 1ns / 1ps

module shift_register_tb();
	reg IN, clk;
	wire [3:0] L;
	
	shift_register set(IN, clk, L);
	
	initial begin
		IN = 1'b1;
		clk = 1'b0;
	end
	
	always clk = #20 ~clk;
	always IN = #25 ~IN;
endmodule