`timescale 1ns / 1ps

module half_subractor(A, B, D, b);
    input A, B;
    output D, b;

    assign b = (~A)&B;
    assign D = A^B;
endmodule
