`timescale 1ns / 1ps
                  

module inv_tb();

reg a,b,c,d,e,f,g,h,s0,s1,s2,clk;
wire out;

inv set(a,b,c,d,e,f,g,h,s0,s1,s2,out);

initial begin
a = 1'b1;
b = 1'b1;
c = 1'b1;
d = 1'b1;
e = 1'b1;
f = 1'b1;
g = 1'b1;
h = 1'b1;
s0 = 1'b0;
s1 = 1'b0;
s2 = 1'b0;
clk = 1'b0;
end

always clk = #10 ~clk;

always @(posedge clk) begin
s0 <= ~s0;
s1 <= #20 ~s1;
s2 <= #40 ~s2;
a <= ~a;
b <= #10 ~b;
c <= #20 ~c;
d <= #30 ~d;
e <= #40 ~e;
f <= #50 ~f;
g <= #60 ~g;
h <= #70 ~h;
end
endmodule
