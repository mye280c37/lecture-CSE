`timescale 1ns / 1ps

module decoder_sim();
reg a,b,c,d,clk;
wire O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15;

decoder_4_to_16 set(
a,b,c,d,
O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15
);

initial begin
clk = 1'b0;
a = 1'b0;
b = 1'b0;
c = 1'b0;
d = 1'b0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
a <= ~a;
b <= #20 ~b;
c <= #40 ~c;
d <= #80 ~d;
end


endmodule
