`timescale 1ns / 1ps

module half_adder_tb();
    reg a, b, clk;
    wire s, c;

    half_adder set(a, b, s, c);

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
