`timescale 1ns / 1ps

module jk_flipflop
(
	input clk,
	input J,
	input K,
	output reg Q,
	output Qbar
);
assign Qbar = ~Q;
always @ (posedge clk)
begin
	case({J,K})
		2'b00 : Q <= Q;
		2'b01 : Q <= 1'b0;
		2'b10 : Q <= 1'b1;
		2'b11 : Q <= ~Q;
		default : Q <= 1'b0;
	endcase
end
endmodule