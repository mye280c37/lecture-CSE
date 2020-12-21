`timescale 1ns / 1ps

module d_latch_tb();
reg D,E,clk;
wire Q, nQ;

d_latch set(D, E, Q, nQ);

initial begin
clk = 1'b 0;
D = 1'b 1;
E = 1'b 0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
D <= ~D;
E <= #20 ~E;
end

endmodule
