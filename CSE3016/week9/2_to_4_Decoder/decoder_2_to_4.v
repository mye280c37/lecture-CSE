`timescale 1ns / 1ps

module inv(
input A,
input B,
output D0,
output D1,
output D2,
output D3
    );    

assign D0 =  ~(~A&~B);
assign D1 = ~(~A&B);
assign D2 = ~(A&~B);
assign D3 = ~(A&B);

endmodule
