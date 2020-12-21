`timescale 1ns / 1ps
module inv_tb();
reg a, b, c, d, p, clk;
wire pec;

inv u_inv(
.A(a),
.B(b),
.C(c),
.D(d),
.P(p),
.PEC(pec));

initial begin
clk = 1'b0;
a = 1'b0;
b = 1'b0;
c = 1'b0;
d = 1'b0;
p = 1'b0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
a <= #160 ~a;
b <= #80 ~b;
c <= #40 ~c;
d <= #20 ~d;
p <= #10 ~p;
end

initial begin
#800
$finish;
end

endmodule
