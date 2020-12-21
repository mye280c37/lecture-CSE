`timescale 1ns / 1ps

module rs_flipflop(
    input clk,
    input S,
    input R,
    output Q,
    output Qbar
    );
reg M,N;

always @(posedge clk) begin
  M <= ~(R|Qbar);
  N <= ~(S|Q) ;
end
assign Q = M;
assign Qbar = N;

endmodule