`timescale 1ns / 1ps

module inv_tb();
reg a,b,c,d,clk;
wire e1, e2;

inv set(a,b,c,d,e1,e2);

initial begin
clk = 1'b0;
a = 1'b0;
b = 1'b0;
c = 1'b0;
d = 1'b0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
a <= #20 ~a;
b <= #40 ~b;
c <= #80 ~c;
d <= #160 ~d;
end

endmodule
