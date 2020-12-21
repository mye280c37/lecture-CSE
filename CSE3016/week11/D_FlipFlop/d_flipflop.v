`timescale 1ns / 1ps

module d_flipflop 
(
 input clk,                                                                        // �Է�:Ŭ��,���½�ȣ, D�Էµ�����
 input D,
 output reg Q,                                                                  // ��� : Q, Qbar
 output Qbar
);
assign Qbar = ~Q;
always @(posedge clk)                                    //Ŭ�� ��¿����̰ų� ���� ��¿����� ��
begin
 Q <= D;                                                                     //���½�ȣ ���� �� Q=D(�������� D)
end
endmodule 