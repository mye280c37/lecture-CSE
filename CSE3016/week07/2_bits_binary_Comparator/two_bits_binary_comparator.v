`timescale 1ns / 1ps

module comparator_2(A, B, F1, F2, F3);
    input [1:0] A, B;
    output F1, F2, F3;

    // A>B
    assign F1 = (A[1]&(~B[1]))|(A[0]&(~B[1])&(~B[0]))|(A[1]&A[0]&(~B[0]));
    // A=B
    assign F2 = (~(A[1]^B[1]))&(~(A[0]^B[0]));
    // A<B
    assign F3 = ((~A[1])&B[1])|((~A[1])&(~A[0])&B[0])|((~A[0])&B[1]&B[0]);
endmodule
