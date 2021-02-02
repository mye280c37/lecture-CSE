`timescale 1ns / 1ps

module decoder_4_to_16(
    A, B, C, D,
    O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15
 );
    
    input A, B, C, D;
    output O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15;
    wire d0, d1, d2, d3;

    demux_1_to_4 DE41(1, A, B, d0, d1, d2, d3); 
    demux_1_to_4 de41_0(d0,C,D,O0, O1, O2, O3);
    demux_1_to_4 de41_1(d1,C,D, O4, O5, O6, O7);
    demux_1_to_4 de41_2(d2,C,D, O8, O9, O10, O11);
    demux_1_to_4 de41_3(d3,C,D, O12, O13, O14, O15);

endmodule
