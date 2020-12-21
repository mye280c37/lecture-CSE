`timescale 1ns / 1ps

module inv_tb();
reg a, b, c, d;
wire x, y, z, t;

inv u_inv(
.A(a),
.B(b),
.C(c),
.D(d),
.x(x),
.y(y),
.z(z),
.t(t));

initial begin
a = 1'b1;
b = 1'b0;
c = 1'b0;
d = 1'b0;
end

always begin
a = #50 ~a;
b = #75 ~b;
c = #100 ~c;
d = #125 ~d;
end

initial begin
#1000
$finish;
end

endmodule
