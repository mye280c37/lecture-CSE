`timescale 1ns / 1ps

module d_flipflop 
(
 input clk,                                                                        // 입력:클럭,리셋신호, D입력데이터
 input D,
 output reg Q,                                                                  // 출력 : Q, Qbar
 output Qbar
);
assign Qbar = ~Q;
always @(posedge clk)                                    //클럭 상승에지이거나 리셋 상승에지일 때
begin
 Q <= D;                                                                     //리셋신호 없을 시 Q=D(다음상태 D)
end
endmodule 