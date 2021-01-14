`timescale 1ns / 1ps

module full_subtractor_tb();
    reg a, b, b_n_1, clk;
    wire d, b_n;

    full_subtractor set(a, b, b_n_1, d, b_n);

    initial begin
        a = 1'b0;
        b = 1'b0;
        b_n_1 = 1'b0;
        clk = 1'b1;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        a <= #150 ~a;
        b <= #50 ~b;
        b_n_1 <= ~b_n_1;
    end

    initial begin
        #1000
        $finish;
    end
endmodule
