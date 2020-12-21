`timescale 1ns / 1ps

module inv(a, b, c);
input a, b;
output c;

assign c = (~a)|(~b);
endmodule
