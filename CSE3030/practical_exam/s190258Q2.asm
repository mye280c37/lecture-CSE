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
	;; �� ĭ ���(front)
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
;; ���ڿ� �ű��
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
	;; �� ĭ ���(back)
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
	;; ��� ���
	mov		edx, OFFSET outBuffer
	call	WriteString
	call  Crlf
	cmp		edi, 1
	jz backToOrg
	;; �� �� ��ĭ ���� 1����
	inc ebx
	;; copy�ؾ� �ϴ� ���� �� 2�� ����
	sub		eax, 2
	;; inBuffer ������ �ѱ��� �ű��
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