TITLE 

INCLUDE Irvine32.inc

BUF_SIZE EQU 256

.data
inBuffer		BYTE BUF_SIZE DUP(?)
outBuffer		BYTE BUF_SIZE DUP(?)
inputMsg		BYTE "Enter a string : ", 0
endMsg		BYTE "Bye!", 0

.code
main PROC
start:
	mov		edx,OFFSET inputMsg	
	call WriteString
	mov		edx, OFFSET inBuffer
	mov		ecx,	BUF_SIZE-1
	call ReadString
	or			eax, eax																; check input exists
	jz	fin
	mov		esi, OFFSET inbuffer
	xor		ebx, ebx
	mov		edi, 0
	push eax
hourglass:
	mov		edx, OFFSET outBuffer
	;; 빈 칸 담기(front)
	cmp ebx, 0
	jz step2
	push ebx
copyBlankFront:
	mov BYTE PTR [edx], 20h
	inc edx
	dec ebx
	cmp ebx, 0
	jg copyBlankFront
	pop ebx
step2:
;; 문자열 옮기기
	mov		ecx, eax
	push esi
	push ebx
	xor	ebx, ebx
copyStr:
	mov		bl, BYTE PTR [esi]
	mov		BYTE PTR [edx], bl
	inc edx
	inc esi
	loop copyStr
	pop ebx
	pop esi
	;; 빈 칸 담기(back)
	cmp ebx, 0
	jz result
	push ebx
copyBlankBack:
	mov BYTE PTR [edx], 20h
	inc edx
	dec ebx
	cmp ebx, 0
	jg copyBlankBack
	pop ebx
result:
	;; 결과 출력
	mov		edx, OFFSET outBuffer
	call	WriteString
	call  Crlf
	cmp		edi, 1
	jz backToOrg
	;; 앞 뒤 빈칸 개수 1증가
	inc ebx
	;; copy해야 하는 글자 수 2개 감소
	sub		eax, 2
	;; inBuffer 시작점 한글자 옮기기
	inc		esi	
	cmp		eax, 0
	jg hourglass
	mov	edi, 1
	dec ebx
	add eax, 2
	dec esi
backToOrg:
	dec ebx
	add eax, 2
	dec esi
	cmp ebx, 0
	jge hourglass
	call  Crlf
	pop eax
	mov ecx, eax
	mov edx, OFFSET outBuffer
initOut:
	mov   BYTE PTR [edx], 0 
	inc edx
	loop initOut
	jmp start
fin:	
	mov		edx, OFFSET endMsg											; write end mss if there is no input
	call WriteString
	exit
main ENDP
END main