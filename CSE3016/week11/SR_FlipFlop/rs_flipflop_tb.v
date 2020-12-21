`timescale 1ns / 1ps

module rs_flipflop_tb();
reg clk, S, R, sign;
wire Q, Qbar;

rs_flipflop set(clk, S, R, Q, Qbar);

initial begin
clk = 1'b0;
S = 1'b1;
R = 1'b0;
sign = 1'b0;
end

always sign = #55 ~sign;

always clk = #10 ~clk;

always @(posedge sign) begin
S <= ~S;
R <= #20 ~R;
end

endmodule
