`timescale 1ns / 1ps

module d_flipflop_tb();

reg clk, D, sign;
wire Q, Qbar;

d_flipflop set(clk, D, Q, Qbar);

initial begin
	clk = 1'b0;
	D = 1'b1;
	sign = 1'b0;
end

always sign = #55 ~sign;

always clk = #10 ~clk;

always @(posedge sign) D <= ~D;
 
endmodule
