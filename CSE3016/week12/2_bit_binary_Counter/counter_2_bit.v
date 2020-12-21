`timescale 1ns / 1ps

module two_bit_counter(input clk, output [1:0] Q);
	wire [1:0] q;

  jkfflop first(1'b1, 1'b1, clk, q[0]);
  jkfflop second(Q[0], Q[0], clk, q[1]);  
  
	assign Q = q;
endmodule

module jkfflop(input J, K, clk, output reg Q);
  initial Q = 0;

  always @(negedge clk) begin
    case({J,K})
      2'b00 : Q <= Q   ;
      2'b01 : Q <= 1'b0;
      2'b10 : Q <= 1'b1;
      2'b11 : Q <= ~Q  ;
    endcase
  end
endmodule