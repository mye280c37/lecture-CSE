`timescale 1ns / 1ps

module inv(a, b, c, d, e);
input a, b, c;
output d, e;

assign d = a&b;
assign e = d&c;
endmodule
