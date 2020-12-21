`timescale 1ns / 1ps

module rs_latch_tb();
reg R,S,clk;
reg Q, nQ;

rs_latch set(R, S, Q, nQ);

initial begin
clk = 1'b 0;
S = 1'b 1;
R = 1'b 0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
S <= ~S;
R <= #20 ~R;
end

endmodule
