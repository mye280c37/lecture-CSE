`timescale 1ns / 1ps

module jk_flipflop_tb( );
reg clk, J, K, sign;
wire Q, Qbar;

jk_flipflop set(clk, J, K, Q, Qbar);

initial begin
clk = 1'b0;
J = 1'b1;
K = 1'b0;
sign = 1'b0;
end

always sign = #55 ~sign;

always clk = #10 ~clk;

always @(posedge sign) begin
J <= ~J;
K <= #20 ~K;
end

endmodule
