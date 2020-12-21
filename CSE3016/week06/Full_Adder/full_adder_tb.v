`timescale 1ns / 1ps

module inv_tb();

reg a, b, c_in;
wire s, c_out;

inv u_inv(
.A(a),
.B(b),
.C_in(c_in),
.S(s),
.C_out(c_out));

initial begin
a = 1'b0;
b = 1'b0;
c_in = 1'b0;
end

always begin
a = #50 ~a;
b = #100 ~b;
c_in = #150 ~c_in;
end

initial begin
#1000
$finish;
end

endmodule
