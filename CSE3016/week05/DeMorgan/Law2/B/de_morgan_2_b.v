`timescale 1ns / 1ps

module deMorgan2_B(a, b, c);
    input a, b;
    output c;

    assign c = (~a)|(~b);
endmodule
