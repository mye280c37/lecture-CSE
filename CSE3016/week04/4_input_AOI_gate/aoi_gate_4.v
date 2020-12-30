`timescale 1ns / 1ps

module aoi_gate_4(a, b, c, d, e, f, g);
    input a, b, c, d;
    output e, f, g;

    assign e = a&b;
    assign f = c&d;
    assign g = ~(e|f);
endmodule
