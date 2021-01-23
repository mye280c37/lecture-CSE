`timescale 1ns / 1ps

module odd_parity_checker_tb();
    reg a, b, c, d, p, clk;
    wire pec;

    odd_parity_checker set(a, b, c, d, p, pec);

    initial begin
        clk = 1'b1;
        a = 1'b0;
        b = 1'b0;
        c = 1'b0;
        d = 1'b0;
        p = 1'b0;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        a <= #750 ~a;
        b <= #350 ~b;
        c <= #150 ~c;
        d <= #50 ~d;
        p <= ~p;
    end
endmodule
