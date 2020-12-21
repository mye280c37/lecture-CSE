`timescale 1ns / 1ps

module full_subtractor(input a, b, b_in, output sub, b_out);
    assign sub = a^b^b_in;
    assign b_out = ~a&((b^b_in)|(b&b_in));
endmodule

module full_subtractor_4(input [3:0] a, [3:0] b, b_in, output [3:0] sub, b_out);
    wire b1, b2, b3;

    full_subtractor fs0(sub[0], a[0], b[0], b_in);
    full_subtractor fs1(sub[0], a[0], b[0], b_in);
    full_subtractor fs2(sub[0], a[0], b[0], b_in);
    full_subtractor fs3(sub[0], a[0], b[0], b_in);
endmodule