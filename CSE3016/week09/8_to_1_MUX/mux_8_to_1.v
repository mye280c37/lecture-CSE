`timescale 1ns / 1ps

module mux_8_to_1(input A, B, C, D, E, F, G, H, S0, S1, S2, output OUT);     
    wire sig1,sig2,sig3,sig4,sig5,sig6,sig7,sig8;

    assign sig1 = ~S0 & ~S1 & ~S2;    
    assign sig2 = ~S0 & ~S1 & S2;    
    assign sig3 = ~S0 & S1 & ~S2;    
    assign sig4 = ~S0 & S1 & S2;    
    assign sig5 = S0 & ~S1 & ~S2;    
    assign sig6 = S0 & ~S1 & S2;    
    assign sig7 = S0 & S1 & ~S2;    
    assign sig8 = S0 & S1 & S2;   

    assign OUT = (A&sig1) | (B&sig2) | (C&sig3) | (D&sig4) | (E&sig5) | (F&sig6) | (G&sig7) | (H&sig8); 
endmodule
