`timescale 1ns / 1ps

module and_gate_3_A_tb();

    reg aa, bb, cc, clk;
    wire d;

    and_gate_3_A set(aa, bb, cc, d);

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
