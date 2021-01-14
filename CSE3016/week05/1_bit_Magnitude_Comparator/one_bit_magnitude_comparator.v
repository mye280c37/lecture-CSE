`timescale 1ns / 1ps

module comparator_1(a, b, eq, neq, a_big, b_big);
    input a, b;
    output eq, neq, a_big, b_big;

    assign eq = ~(a^b);
    assign neq = a^b;
    assign a_big = a&(~b);
    assign b_big = (~a)&b;
endmodule
