`timescale 1ns / 1ps

module up_down_counter(input clk, S, output [3:0] Q);
	wire [3:0] q;
	
	jkff jk0(1,1,clk, q[0]);
	jkff jk1(((~Q[0])&(~S))|(Q[0]&S), ((~Q[0])&(~S))|(Q[0]&S), clk, q[1]);
	jkff jk2((~Q[1]&~Q[0]&~S)|(Q[1]&Q[0]&S), (~Q[1]&~Q[0]&~S)|(Q[1]&Q[0]&S), clk, q[2]);
	jkff jk3((~Q[2]&~Q[1]&~Q[0]&~S)|(Q[2]&Q[1]&Q[0]&S), 
(~Q[2]&~Q[1]&~Q[0]&~S)|(Q[2]&Q[1]&Q[0]&S), clk, q[3]);
	
	assign Q = q;
endmodule

module jkff(input J, K, clk, output reg Q);
	initial Q = 0;
	
	always @(posedge clk)
	begin
		Q = (J&(~Q))|((~K)&Q);
	end
endmodule