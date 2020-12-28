`timescale 1ns / 1ps

module or_gate_4_B_tb();

    reg aa, bb, cc, dd, clk;
    wire e, f, g;

    or_gate_4_B set(aa, bb, cc, dd, e, f, g);

    initial begin
        aa = 1'b0;
        bb = 1'b0;
        cc = 1'b0;
        dd = 1'b0;
        clk = 1'b0;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        aa <= #350 ~aa;
        bb <= #150 ~bb;
        cc <= #50 ~cc;
        dd <= ~dd;
    end

    initial begin
        #1000
        $finish;
    end
    
endmodule
