module priority_encoder(input A, B, C, D, output X, Y);
    assign X = A | B;
    assign Y = A | (~B&C);
endmodule
