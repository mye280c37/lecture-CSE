`timescale 1ns / 1ps

module ring_counter(clk, rst, L, p);
	input clk, rst;	
	output [3:0] L;
	output p;
	
	reg prs;
	wire [3:0] l;
	
	initial prs = 0;
	
	always @(negedge rst) begin
		prs = 1;
	end
	
	dff d0(prs|L[0], clk, rst, l[3]);
	dff d1(L[3], clk, rst, l[2]);
	dff d2(L[2], clk, rst, l[1]);
	dff d3(L[1], clk, rst, l[0]);
	
	always @(posedge clk) begin
		if(prs)
			prs = #1 0;
	end
	assign L = l;
	assign p = prs;
endmodule

module dff(input D, clk, rst, output reg Q);
	initial Q = 0;
	
	always @(rst)
		Q <= 0;
	
	always @(posedge clk)                                    
		Q <= D;
endmodule