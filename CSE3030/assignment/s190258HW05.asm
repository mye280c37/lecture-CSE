TITLE ListSum

COMMENT @
작성자: 20190258 김혜린
<변수>
	inBuffer :  사용자가 입력한 문자열을 저장하는 변수
	inBufferN :  사용자가 입력한 문자열의 크기를 저장하는 변수
	intArray :  문자열에서 변환된 수들이 저장될 배열
	intArrayN :  배열의 크기
<기능>	
	사용자에게 입력받은 string을 GetIntArr을 이용해 
	int 배열로 바꾼 뒤, GetArrSum을 이용해 해당 배열의 합을 출력하는 프로그램
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
; esi가 가리키는 string에 대해서 edx로 넘어온 크기만큼(앞으로 이동)
; ParseInteger32의 string parameter로 넘겨 int로 반환 후,
; 사용자가 설정한 int array에 삽입하는 procedure
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
;edx가 가리키는 string의 내용을 int 배열로 바꾸어주는 procedure
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
; 사용자가 넘긴 int배열의 arrSize만큼의 배열 합을 반환하는 procedure
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