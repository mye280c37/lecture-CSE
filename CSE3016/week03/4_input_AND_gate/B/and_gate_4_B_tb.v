`timescale 1ns / 1ps

module inv_tb();

reg aa, bb, cc, dd, clk;
wire e, f, g;

inv u_inv(
.a(aa),
.b(bb),
.c(cc),
.d(dd),
.e(e),
.f(f),
.g(g)
);

initial begin
aa = 1'b0;
bb = 1'b0;
cc = 1'b0;
dd = 1'b0;
clk = 1'b0;
end

always clk = #100 ~clk;

always @(posedge clk) begin
aa <= ~aa;
bb <= ~bb;
cc <= ~cc;
dd <= ~dd;
end

initial begin
#1000
$finish;
end

endmodule
