`timescale 1ns / 1ps

module inv(
input A,
input B,
input C,
input D,
output E1,
output E2
    );    

assign E1 = A|B;
assign E2 = A|C;

endmodule

