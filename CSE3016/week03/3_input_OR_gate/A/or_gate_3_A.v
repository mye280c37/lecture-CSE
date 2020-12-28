`timescale 1ns / 1ps

module or_gate_3_A(a, b, c, d);
    input a, b, c;
    output d;

    assign d = a|b|c;
endmodule
