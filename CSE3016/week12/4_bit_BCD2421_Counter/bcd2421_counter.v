`timescale 1ns / 1ps

module BCD2421_counter(input clk, output [3:0] Q );
wire [3:0] q;

jkff jkq0(1'b1, 1'b1, clk, q[0]);
jkff jkq1(Q[0]|((~Q[3])&Q[2]), Q[0], clk, q[1]);
jkff jkq2(Q[1]&Q[0], (~Q[3])|(Q[1]&Q[0]), clk, q[2]);
jkff jkq3(Q[2], Q[2]&Q[1]&Q[0], clk, q[3]);

assign Q = q;
endmodule

module jkff(input  J, K , clk,  output reg Q);
initial Q = 0;

  always @(posedge clk) begin
    case({J,K})
      2'b00 : Q <= Q   ;
      2'b01 : Q <= 1'b0;
      2'b10 : Q <= 1'b1;
      2'b11 : Q <= ~Q  ;
    endcase
  end
endmodule