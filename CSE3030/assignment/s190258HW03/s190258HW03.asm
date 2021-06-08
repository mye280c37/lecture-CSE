TITLE de-cipher

COMMENT @
작성자: 20190258 김혜린
<변수>
	filename: ouput text의 filename
	filehandle: file pointer
	result: de-cipher 결과 저장 변수
<기능>	
	Step1. output file 생성
	Step2: Loop1, Num_Str만큼 de-cipher 로직 실행
	Step3: Loop2, Cipher_Str의 각 문자의 de-cipher 문자 찾기(0-25 사이의 index로 변경 후 key만큼 뺀 index 구해 판단)
	Step4: Loop3, de-cipher의 문자를 찾기 위해 key값만큼 뺀 결과가 음수일 경우 
			26만큼 더해 cyclic하게 문자를 매칭할 수 있도록 해주는 block
			ecx 값 조절을 통해 key값을 뺀 index가 음수일 경우 한 번, 양수일 경우 실행하지 않도록 함
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
			sub		al, 75				; 'A'에 해당하는 값을 0으로 잡고 index구한 후 key만큼 빼기
			push	ecx					; save loop2 counter
			movsx	ecx, al	
			mov		cx, 0001h			; 음수일 경우, ffff0001h, 양수일 경우 00000001h
			jmp		J1
L3:				add		al, 26
				mov		ecx, 1
J1:			loop L3						; 양수일 경우, 바로 loop를 빠져나옴
			add		al, 65				; de-cipher 문자 찾기
			mov		result[edi], al		; result에 문자 복사
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