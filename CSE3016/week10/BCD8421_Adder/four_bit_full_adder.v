`timescale 1ns / 1ps

module four_bit_adder(Sum, Cout, Cin, X, Y);

output [3:0]Sum;
output  Cout;
input  Cin;
input  [3:0]X,Y;
wire C1,C2,C3;

full_adder FA1(.S(Sum[0]),.Cout(C1),.A(X[0]),.B(Y[0]),.Cin(Cin));
full_adder FA2(.S(Sum[1]),.Cout(C2),.A(X[1]),.B(Y[1]),.Cin(C1));
full_adder FA3(.S(Sum[2]),.Cout(C3),.A(X[2]),.B(Y[2]),.Cin(C2));
full_adder FA4(.S(Sum[3]),.Cout(Cout),.A(X[3]),.B(Y[3]),.Cin(C3));

endmodule