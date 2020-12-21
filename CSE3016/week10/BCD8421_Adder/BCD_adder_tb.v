`timescale 1ns / 1ps

module bcd_adder_tb();

reg [3:0] A;
reg [3:0] B;
reg Cin;
wire [3:0] Sum;
wire [3:0] S;
wire Cout, K;
bcd_adder dut(Sum,S,Cout,K,Cin,A,B);    
initial begin
 A = 4'b0011;B=4'b0011;Cin = 1'b0; #100;
 A = 4'b1001;B=4'b0111;Cin = 1'b0; #100;
 A = 4'b0010;B=4'b0101;Cin = 1'b0; #100;
end
endmodule
