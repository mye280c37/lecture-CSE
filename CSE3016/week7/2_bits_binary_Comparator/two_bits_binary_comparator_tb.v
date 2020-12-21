`timescale 1ns / 1ps
module inv_tb();
reg a, b, c, d, clk;
wire f1, f2, f3;

inv u_inv(
.A(a),
.B(b),
.C(c),
.D(d),
.F1(f1),
.F2(f2),
.F3(f3));

initial begin
clk = 1'b0;
a = 1'b0;
b = 1'b0;
c = 1'b0;
d = 1'b0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
a <= #80 ~a;
b <= #40 ~b;
c <= #20 ~c;
d <= #10 ~d;
end

initial begin
#400
$finish;
end

endmodule
