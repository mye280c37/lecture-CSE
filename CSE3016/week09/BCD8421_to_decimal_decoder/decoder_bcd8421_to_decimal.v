module decoder_bcd8421_to_decimal(input A, B, C, D, output D0, D1, D2, D3);
    assign D0 = (~A)&(~B)&(~C)&(~D);
    assign D1 = (~A)&(~B)&(~C)&D;
    assign D2 = (~A)&(~B)&C&(~D);
    assign D3 = (~A)&(~B)&C&D;
    assign D4 = (~A)&B&(~C)&(~D);
    assign D5 = (~A)&B&(~C)&D;
    assign D6 = (~A)&(~B)&C&(~D);
    assign D7 = (~A)&B&C&D;
    assign D8 = A&(~B)&(~C)&(~D);
    assign D9 = A&(~B)&(~C)&D;
endmodule
