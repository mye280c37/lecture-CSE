`timescale 1ns / 1ps

module inv_tb();
reg aa, bb, cc, clk;
wire d;

inv u_inv(
.a(aa),
.b(bb),
.c(cc),
.d(d));

initial begin
aa = 1'b1;
bb = 1'b1;
cc = 1'b1;
clk = 1'b0;
end

always clk = #100 ~clk;

always @(posedge clk) begin
aa <= ~aa;
bb <= ~bb;
cc <= ~cc;
end

initial begin
#1000
$finish;
end

endmodule
