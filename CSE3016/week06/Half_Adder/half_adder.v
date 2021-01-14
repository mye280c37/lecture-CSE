`timescale 1ns / 1ps

module half_adder(A, B, S, C);
    input A, B;
    output S, C;

    assign C = A&B;
    assign S = A^B;
endmodule
