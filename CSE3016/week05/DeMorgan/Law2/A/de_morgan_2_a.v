`timescale 1ns / 1ps

module deMorgan2_A(a, b, c);
    input a, b;
    output c;

    assign c = ~(a&b);
endmodule
