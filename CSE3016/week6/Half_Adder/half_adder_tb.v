`timescale 1ns / 1ps

module inv_tb();

reg a, b;
wire s, c;

inv u_inv(
.A(a),
.B(b),
.C(c),
.S(s));

initial begin
a = 1'b0;
b = 1'b0;
end

always begin
a = #100 ~a;
b = #150 ~b;
end

initial begin
#1000
$finish;
end

endmodule
