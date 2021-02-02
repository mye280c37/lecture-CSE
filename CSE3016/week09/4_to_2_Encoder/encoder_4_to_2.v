`timescale 1ns / 1ps

module encoder_4_to_2(input A, B, C, D, output E1, E2);    
    assign E1 = A|B;
    assign E2 = A|C;
endmodule

