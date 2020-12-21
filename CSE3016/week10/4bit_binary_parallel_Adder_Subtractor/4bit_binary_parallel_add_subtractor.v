`timescale 1ns / 1ps
module add_sub_4(Sum ,Cout , sig , X ,Y);

output [3:0]Sum;
output  Cout;
input  sig;
input  [3:0]X,Y;
wire C1,C2,C3;

full_adder FA1(.S(Sum[0]),.Cout(C1),.A(X[0]),.B(Y[0]^sig),.Cin(sig));
full_adder FA2(.S(Sum[1]),.Cout(C2),.A(X[1]),.B(Y[1]^sig),.Cin(C1));
full_adder FA3(.S(Sum[2]),.Cout(C3),.A(X[2]),.B(Y[2]^sig),.Cin(C2));
full_adder FA4(.S(Sum[3]),.Cout(Cout),.A(X[3]),.B(Y[3]^sig),.Cin(C3));

endmodule