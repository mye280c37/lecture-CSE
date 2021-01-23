`timescale 1ns / 1ps

module even_parity_checker(A, B, C, D, P, PEC);
    input A, B, C, D, P;
    output PEC;

    assign PEC = A^B^C^D^P;
endmodule
