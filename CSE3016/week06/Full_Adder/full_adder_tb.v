`timescale 1ns / 1ps

module full_adder_tb();
    reg a, b, c_in, clk;
    wire s, c_out;

    full_adder set(a, b, c_in, s, c_out);

    initial begin
        a = 1'b0;
        b = 1'b0;
        c_in = 1'b0;
        clk = 1'b1;
    end

    always clk = #25 ~clk;

    always @(posedge clk) begin
        a <= #150 ~a;
        b <= #50 ~b;
        c_in <= ~c_in;
    end

    initial begin
        #1000
        $finish;
    end
endmodule
