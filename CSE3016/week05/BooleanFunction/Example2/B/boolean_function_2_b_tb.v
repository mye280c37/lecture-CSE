`timescale 1ns / 1ps

module boolean_func2_B_tb();
    reg aa, bb, cc, clk;
    wire d;

    boolean_func2_B set(aa, bb, cc, d);

    initial begin
        aa = 1'b0;
        bb = 1'b0;
        cc = 1'b0;
        clk = 1'b1;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        aa <= #150 ~aa;
        bb <= #50 ~bb;
        cc <= ~cc;
    end

    initial begin
        #1000
        $finish;
    end
endmodule
