`timescale 1ns / 1ps
module comparator_2_tb();
    reg [1:0] a, b;
    reg clk;
    wire f1, f2, f3;

    comparator_2 set(a, b, f1, f2, f3);

    initial begin
        clk = 1'b1;
        a = 2'b00;
        b = 2'b00;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        a[1] <= #350 ~a[1];
        a[0] <= #150 ~a[0];
        b[1] <= #50 ~b[1];
        b[0] <= ~b[0];
    end
endmodule
