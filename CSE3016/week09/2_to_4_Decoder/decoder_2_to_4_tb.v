`timescale 1ns / 1ps

module inv_tb();
reg a, b, clk;
wire d0, d1, d2, d3;

inv set(a, b, d0, d1, d2, d3);

initial begin
clk = 1'b0;
a = 1'b0;
b = 1'b0;
end

always clk  = #10 ~clk;

always @(posedge clk) begin
a <= #20 ~a;
b <= #40 ~b;
end
endmodule
