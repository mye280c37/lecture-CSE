`timescale 1ns / 1ps

module inv_tb();

reg a, b, b_n_1;
wire d, b_n;

inv u_inv(
.A(a),
.B(b),
.b_n_1(b_n_1),
.D(d),
.b_n(b_n));

initial begin
a = 1'b0;
b = 1'b0;
b_n_1 = 1'b0;
end

always begin
a = #50 ~a;
b = #100 ~b;
b_n_1 = #150 ~b_n_1;
end

initial begin
#1000
$finish;
end

endmodule
