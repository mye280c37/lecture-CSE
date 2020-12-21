`timescale 1ns / 1ps

module add_sub_4_tb();

reg [3:0] A;
reg [3:0] B;
reg C0;
wire [3:0] S;
wire C4;
add_sub_4 dut(S,C4,C0,A,B);    
initial begin
 A = 4'b0011;B=4'b0011;C0 = 1'b0; #100;
 A = 4'b1011;B=4'b0111;C0 = 1'b1; #100;
 A = 4'b1111;B=4'b1111;C0 = 1'b1; #100;
end
endmodule
