`timescale 1ns / 1ps

module encoder_4_to_2_tb();
    reg a,b,c,d,clk;
    wire e1, e2;

    encoder_4_to_2 set(a, b, c, d, e1, e2);

    initial begin
        clk = 1'b1;
        a = 1'b0;
        b = 1'b0;
        c = 1'b0;
        d = 1'b0;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
    a <= #350 ~a;
    b <= #150 ~b;
    c <= #50 ~c;
    d <= ~d;
    end
endmodule
