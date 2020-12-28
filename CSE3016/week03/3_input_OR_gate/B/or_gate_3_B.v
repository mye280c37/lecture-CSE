`timescale 1ns / 1ps

module or_gate_3_B(a, b, c, d, e);
    input a, b, c;
    output d, e;

    assign d = a|b;
    assign e = d|c;
endmodule
