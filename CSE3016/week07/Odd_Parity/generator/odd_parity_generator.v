`timescale 1ns / 1ps

module odd_parity_generator(A, B, C, D, P);
    input A, B, C, D;
    output P;

    assign P = ~((A^B)^(C^D));
endmodule
