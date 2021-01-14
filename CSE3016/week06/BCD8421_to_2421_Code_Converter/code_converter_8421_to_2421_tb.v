`timescale 1ns / 1ps

module converter_8421_2421_tb();
    reg a, b, c, d, clk;
    wire x, y, z, t;

    converter_8421_2421 set(a, b, c, d, x, y, z, t);

    initial begin
        a = 1'b0;
        b = 1'b0;
        c = 1'b0;
        d = 1'b0;
        clk = 1'b1;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        a <= #350 ~a;
        b <= #150 ~b;
        c <= #50 ~c;
        d <= ~d;
    end

    always begin
        #1000
        $finish;
    end
endmodule
