`timescale 1ns / 1ps

module decade_counter(input clk, output [3:0] Q);
  wire [3:0] q;

  jkfflop first(1'b1 , 1'b1, clk , q[0]);
  jkfflop second(~Q[3]&Q[0],~Q[3]&Q[0], clk, q[1]);  
  jkfflop third(Q[1]&Q[0], Q[1]&Q[0], clk ,q[2]);
  jkfflop fourth(Q[2]&Q[1]&Q[0], Q[0], clk, q[3]);

  assign Q = q;
endmodule

module jkfflop(input  J, K , clk, output reg Q);
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