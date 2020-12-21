`timescale 1ns / 1ps
module bcd_adder(Sum, S, Cout, K, Cin, A, B);

output [3:0]Sum, S;
output  Cout, K;
input  Cin;
input  [3:0]A,B;
wire C1,C2,C3,C4;

// 입력값 A+B에 대한 parallel adder
four_bit_adder FFA1 (.Sum(S), .Cout(K), .Cin(Cin), .X(A), .Y(B));

assign Cout = ((S[1]|S[2])&S[3])|K;

// 보수회로
full_adder SFA1(.S(Sum[0]),.Cout(C1),.A(S[0]),.B(0),.Cin(Cin));
full_adder SFA2(.S(Sum[1]),.Cout(C2),.A(S[1]),.B(Cout),.Cin(C1));
full_adder SFA3(.S(Sum[2]),.Cout(C3),.A(S[2]),.B(Cout),.Cin(C2));
full_adder SFA4(.S(Sum[3]),.Cout(C4),.A(S[3]),.B(0),.Cin(C3));

endmodule