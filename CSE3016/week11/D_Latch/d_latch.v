`timescale 1ns / 1ps

module d_latch
(
 input D,                                                            //??? ??? : D?? enable
 input enable,
 output reg Q ,
 output reg nQ                                                    //??¨ö?? Q
);

always @(D or enable)                                          //D?? enable ????? ??? ?? ????
begin
 if(enable) begin
  Q=D;  
  nQ = ~D;
  end                                                 //enable?? 1?? ???, Q<=D(??¨ö?? ???)
 else begin
  Q=Q;
  nQ = nQ;
end                                                          //enable?? 0?? ??? Q<=Q(????????)

end

endmodule