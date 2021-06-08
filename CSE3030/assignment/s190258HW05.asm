TITLE ListSum

COMMENT @
�ۼ���: 20190258 ������
<����>
	inBuffer :  ����ڰ� �Է��� ���ڿ��� �����ϴ� ����
	inBufferN :  ����ڰ� �Է��� ���ڿ��� ũ�⸦ �����ϴ� ����
	intArray :  ���ڿ����� ��ȯ�� ������ ����� �迭
	intArrayN :  �迭�� ũ��
<���>	
	����ڿ��� �Է¹��� string�� GetIntArr�� �̿��� 
	int �迭�� �ٲ� ��, GetArrSum�� �̿��� �ش� �迭�� ���� ����ϴ� ���α׷�
@

INCLUDE Irvine32.inc

ParseStrAndInsertNum PROTO

GetIntArr PROTO,
		arrPtr: DWORD,
		strSize: DWORD

GetArrSum PROTO,
		arrPtr: DWORD,
		arrSize: DWORD

.data
BUF_SIZE EQU 256
inBuffer		BYTE BUF_SIZE DUP(?)										; input string buffer (EOS is 0)
inBufferN		DWORD ?
intArray		SDWORD BUF_SIZE/2 DUP(?)
intArrayN		DWORD ?
inputMsg		BYTE "Enter number(<ent> to exit) : ", 0
endMsg		BYTE "Bye!", 0

.code
main PROC
start:
		mov		edx,OFFSET inputMsg	
		call WriteString
		call Crlf
		mov		edx, OFFSET inBuffer
		mov		ecx,	BUF_SIZE-1
		call ReadString
		or			eax, eax																; check input exists
		jz	fin
		mov		inBufferN, eax
		INVOKE GetIntArr, ADDR intArray, inBufferN
		mov		intArrayN, ebx
		INVOKE GetArrSum, ADDR intArray, intArrayN
		cmp		eax, 0
		jl printNeg
		call WriteDec																	; write sum of array(EAX)
		jmp newLine
printNeg:
		call WriteInt
newLine:
		call Crlf
		xor		eax, eax																
		jmp start
fin:	mov		edx, OFFSET endMsg											; write end mss if there is no input
		call WriteString
		exit
main ENDP


;------------------------------------------------------------------------------
;ParseStrAndInsertNum PROC USES ecx edx
;
; esi�� ����Ű�� string�� ���ؼ� edx�� �Ѿ�� ũ�⸸ŭ(������ �̵�)
; ParseInteger32�� string parameter�� �Ѱ� int�� ��ȯ ��,
; ����ڰ� ������ int array�� �����ϴ� procedure
;
; call args:
;	EDX = size of subString
;	EDI = OFFSET intArray for new  element
;	ESI =  OFFSET inputString which points end of Substring
; return args
;	EDI = OFFSET intArray for next element 
;-------------------------------------------------------------------------------
ParseStrAndInsertNum PROC USES ecx edx
	mov		ecx, edx																	; set subString size
	mov		edx, esi
	sub		edx, ecx																	; set start OFFSET of subString
	call ParseInteger32
	mov		[edi], eax																	; insert number in intArray
	add		edi, 4
	ret
ParseStrAndInsertNum ENDP


;------------------------------------------------------------------------------
;GetIntArr PROC USES edx
;
;edx�� ����Ű�� string�� ������ int �迭�� �ٲپ��ִ� procedure
;
; call args:
;	EDX = OFFSET input String
;	DWORD arrPtr = OFFSET returned intArray
;	DWORD strSize =  inputString size
; return args
;	EBX = size of intArray
;-------------------------------------------------------------------------------
GetIntArr PROC USES edx,
	arrPtr: DWORD,
	strSize: DWORD
		mov		esi, edx																	; set esi points input String
		mov		edi, arrPtr
		mov		ecx, strSize
		xor		ebx, ebx																	; initialize arrSize
		xor		edx, edx																	; initialize subString size
L1:	mov		al, [esi]
		cmp		al, 20h																		; check char is space
		jz	insertEle
		cmp		al, 2bh																		; check char is '+'
		jz	nextIter
		inc		edx
		jmp nextIter
insertEle:
		push	ecx
		or			edx, edx
		jz nextIter
		call ParseStrAndInsertNum
		inc		ebx																			; increase arrSize
		pop		ecx
		xor		edx, edx
nextIter:
		inc		esi
		loop L1
		or			edx, edx																	; check whether there is extra subString
		jz endProc
		call ParseStrAndInsertNum
		inc		ebx																			; increase arrSize
endProc:
		ret
GetIntArr ENDP


;------------------------------------------------------------------------------
;GetArrSum PROC USES esi ecx
;
; ����ڰ� �ѱ� int�迭�� arrSize��ŭ�� �迭 ���� ��ȯ�ϴ� procedure
;
; call args:
;	DWORD arrPtr = OFFSET returned intArray
;	DWORD arrSize =  intArray size
; return args
;	EAX = sum of intArray
;-------------------------------------------------------------------------------
GetArrSum PROC USES esi ecx,
	arrPtr: DWORD,
	arrSize: DWORD
	mov		esi, arrPtr
	mov		ecx, arrSize
	xor		eax, eax
L1:
	add		eax, [esi]																			; add elements
	add		esi, 4
	loop	L1
	ret
GetArrSum ENDP

END main