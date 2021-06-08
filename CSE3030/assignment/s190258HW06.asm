TITLE Duplicate Character

COMMENT @
작성자: 20190258 김혜린
<변수>
	stdinHandle	: stdinput handler
	stdoutHandle	: stdout handler
	inputStr			: Read_a_Line을 통해 읽은 문자열 한 줄
	outputStr			: k 번 복제한 결과 문자열
	Single_Buf__	: Read_a_Line에서 읽어들인 한 문자를 담는 변수
	Byte_Read__	: ReadFile에서 읽은 byte 개수를 담는 변수
	Byte_Write__	: WriteFile에서 쓴 byte 개수를 담는 변수
	CRLF_				: WriteFile에서 줄바꿈을 위해 사용될 변수

	레지스터의 주요 사용 용도는 아래와 같다.
			EAX			: HANDLE, data for procedure input
			EBX			: temporary data
			ECX			: string size
			EDX, ESI	: string OFFSET
<기능>	
	입력에 대해 Read_a_Line procedure를 이용해 한 줄씩 읽고,
	해당 line의 제일 앞에 주어진 k만큼 DuplicateChar procedure을 이용해
	k 뒤에 이어 나오는 target string의 각 문자를 k번 복제해 출력한다.
@

INCLUDE Irvine32.inc

Read_a_Line PROTO
DuplicateChar PROTO

CR=0Dh
LF=0Ah

.data?
stdinHandle		HANDLE ?
stdoutHandle	HANDLE ?
inputStr		BYTE 21 DUP(?)
outputStr		BYTE 181 DUP(?)
Single_Buf__ BYTE ?		; two underscores(__)
Byte_Read__ DWORD ?		;  "
Byte_Write__	DWORD ?	

.data
CRLF_			BYTE 0dh, 0ah


.code
main PROC
	INVOKE GetStdHandle, STD_INPUT_HANDLE
	mov stdinHandle, eax													; get stdinHandle
	INVOKE GetStdHandle, STD_OUTPUT_HANDLE
	mov stdoutHandle, eax												; get stdoutHandle
start:	
	mov	eax, stdinHandle
	mov edx, OFFSET inputStr
	call Read_a_Line 
	cmp ecx, 0
		jz fin

	;; duplicate each character of string k times
	mov edx, OFFSET inputStr
	xor eax, eax
	mov al, BYTE PTR [edx]
	cmp al, 20h
		jz fin																		; if there are only blanks, exit program
	sub eax, 30h																; get k
	add edx, 2																	; move to start offset of target string
	sub ecx, 2																	; get target string size
	mov esi, OFFSET outputStr
	call DuplicateChar

	;; write output
	mul ecx
	mov ecx, eax
	mov eax, stdoutHandle
	INVOKE WriteFile, EAX, ADDR outputStr, ECX, 
				ADDR Byte_Write__, 0
	pushad
	INVOKE WriteFile, stdoutHandle, ADDR CRLF_, 2,
				ADDR Byte_Write__, 0
	popad
	jmp start
fin:
	exit
main ENDP

Read_a_Line PROC
;; Input			EAX: File Handle
;;					EDX: Buffer offset to store string
;; Output		ECX: # of chars read(0 if none(i.e. EOF))
;; Function
;;		Read a line from a ~.txt file until CR, LF.
;;		CR, LF are ignored and 0 is appended at the end.
;;		ECX only counts valid chars just before CR.
	xor ecx, ecx		; reset counter
Read_Loop:
		;; Note: Win32 API founctions do not preserve
		;;			EAX, EBX, ECX, and EDX.
		push eax																		; save registers
		push ecx
		push edx
		; read single char
		INVOKE ReadFile, EAX, OFFSET Single_Buf__,
					1, OFFSET Byte_Read__, 0
		pop edx																		; restore registers
		pop ecx
		pop eax
		cmp DWORD PTR Byte_Read__, 0								; check # of chars read
			je Read_End															; if read nothing, return

		;; Each end of line consists of CR and then LF
		mov bl, Single_Buf__
		cmp bl, CR
			je Read_Loop															; if CR, read once again
		cmp bl, LF
			je Read_End															; End of line detected, return
	
		mov [edx], bl
		inc edx																		; ++1 buf pointer
		inc ecx																			; ++1 char counter
	jmp Read_Loop

Read_End:
	mov BYTE PTR [edx], 0													; append 0 at the end
	ret
Read_a_Line ENDP


DuplicateChar PROC USES ebx ecx
;;input		EAX: k
;;				EDX: offset of target string
;;				ESI: offset for store output
;;				ECX: length of target string
;;Function
;;	duplicate each character of target string k times 
;;	and store in ESI
read_char:	
		push ecx
		mov ecx, eax																	; ecx=k
		mov	bl, [edx]																	; duplicate a character k times
duplicate_k:
			mov [esi], bl
			inc esi
		loop duplicate_k
		pop ecx
		inc edx
	loop read_char
	ret
DuplicateChar ENDP

END main