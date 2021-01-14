`timescale 1ns / 1ps

module comparator_1_tb();
    reg aa, bb, clk;
    wire eq, neq, a_big, b_big;

    comparator_1 set(aa, bb, eq, neq, a_big, b_big);

    initial begin
        aa = 1'b1;
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
