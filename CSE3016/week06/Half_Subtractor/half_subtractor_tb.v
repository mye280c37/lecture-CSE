`timescale 1ns / 1ps

module half_subractor_tb();
    reg a, b, clk;
    wire d, br;

    half_subractor set(a, b, d, br);

    initial begin
        a = 1'b0;
        b = 1'b0;
        clk = 1'b1;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        a <= #50 ~a;
        b <= ~b;
    end

    initial begin
        #1000
        $finish;
    end
endmodule