`timescale 1ns / 1ps

module deMorgan1_A_tb();
    reg aa, bb, clk;
    wire c;

    deMorgan1_A set(aa, bb, c);

    initial begin
        aa = 1'b0;
        bb = 1'b0;
        clk = 1'b1;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        aa <= #50 ~aa;
        bb <= ~bb;
    end

    initial begin
        #1000
        $finish;
    end
endmodule
