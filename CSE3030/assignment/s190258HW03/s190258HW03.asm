TITLE de-cipher

COMMENT @
�ۼ���: 20190258 ������
<����>
	filename: ouput text�� filename
	filehandle: file pointer
	result: de-cipher ��� ���� ����
<���>	
	Step1. output file ����
	Step2: Loop1, Num_Str��ŭ de-cipher ���� ����
	Step3: Loop2, Cipher_Str�� �� ������ de-cipher ���� ã��(0-25 ������ index�� ���� �� key��ŭ �� index ���� �Ǵ�)
	Step4: Loop3, de-cipher�� ���ڸ� ã�� ���� key����ŭ �� ����� ������ ��� 
			26��ŭ ���� cyclic�ϰ� ���ڸ� ��Ī�� �� �ֵ��� ���ִ� block
			ecx �� ������ ���� key���� �� index�� ������ ��� �� ��, ����� ��� �������� �ʵ��� ��
@

INCLUDE Irvine32.inc

INCLUDE CSE3030_PHW03.inc

.data
filename BYTE "0s190258_out.txt", 0
filehandle DWORD ?
KEY = 10
result BYTE 10 DUP(?), 0Dh, 0Ah

.code
main PROC
	mov		edx, OFFSET filename	; file open
	call	CreateOutputFile
	mov		filehandle, eax
	mov		ecx, Num_Str
	mov		esi, 0
L1: 	push	ecx						; save loop1 counter
		mov		ecx, KEY
		mov		edi, 0
L2:			mov		al, Cipher_Str[esi]
			sub		al, 75				; 'A'�� �ش��ϴ� ���� 0���� ��� index���� �� key��ŭ ����
			push	ecx					; save loop2 counter
			movsx	ecx, al	
			mov		cx, 0001h			; ������ ���, ffff0001h, ����� ��� 00000001h
			jmp		J1
L3:				add		al, 26
				mov		ecx, 1
J1:			loop L3						; ����� ���, �ٷ� loop�� ��������
			add		al, 65				; de-cipher ���� ã��
			mov		result[edi], al		; result�� ���� ����
			inc		esi
			inc		edi
			pop		ecx					; get back loop2 counter
		loop L2
		mov		eax, filehandle			; write string to file
		mov		edx, OFFSET result
		mov		ecx, 12
		call	WriteToFile
		pop		ecx						; get back loop1 counter
		inc		esi
	loop L1
	mov		eax, filehandle				; close file
	call	CloseFile
	exit
main ENDP
END main