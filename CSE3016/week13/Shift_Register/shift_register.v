`timescale 1ns / 1ps

module shift_register(IN, clk,  L);
	input IN, clk;
	output [3:0] L;
	wire [3:0] l;
	dff d0(IN, clk, l[0]);
	dff d1(L[0], clk, l[1]);
	dff d2(L[1], clk, l[2]);
	dff d3(L[2], clk, l[3]);
	assign L = l;
endmodule

module dff(input D, clk, output reg Q);
	initial Q = 0;
	always @(posedge clk)                                    
	begin
		 Q <= D;                                                                     
	end
endmodule