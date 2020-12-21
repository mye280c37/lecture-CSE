`timescale 1ns / 1ps

module inv_tb();
reg aa, bb, clk;
wire eq, neq, a_big, b_big;

inv u_inv(
.a(aa),
.b(bb),
.eq(eq),
.neq(neq),
.a_big(a_big),
.b_big(b_big));

initial begin
aa = 1'b1;
bb = 1'b0;
clk = 1'b1;
end

always clk = #100 ~clk;

always @(posedge clk) begin
aa <= ~aa;
bb <= ~bb;
end

initial begin
#1000
$finish;
end
endmodule
