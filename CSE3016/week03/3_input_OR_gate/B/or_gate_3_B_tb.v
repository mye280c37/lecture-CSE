`timescale 1ns / 1ps

module or_gate_3_B_tb();

    reg aa, bb, cc, clk;
    wire d, e;

    or_gate_3_B set(aa, bb, cc, d, e);

    initial begin
        aa = 1'b0;
        bb = 1'b0;
        cc = 1'b0;
        clk = 1'b0;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        aa <= #150 ~aa;
        bb <= #50 ~bb;
        cc <= ~cc;
    end

endmodule
