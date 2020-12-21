`timescale 1ns/1ps

module inverter_tb();
    reg x, clk;
    wire y;

    inverter set(x, y);

    initial begin
      clk = 1'b0;
      x = 1'b0;
    end

    always clk = #50 ~clk;

    always @(posedge clk)
        x = ~x;
endmodule