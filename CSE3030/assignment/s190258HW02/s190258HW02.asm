TITLE Equation Calculation using Add and Subtract

COMMENT @
작성자: 20190258 김혜린

기능: 90x1-30x2+19x3를 16(5x1-2x2+x3)+2(5x1+x2+x3)+x3로 쪼개어 계산할 것이고
x1, x2, x3를 제외한 그 외의 다른 변수없이 세 개의 register를 이용하여
두 개의 register에는 8(5x1-2x2+x3)와 (5x1+x2+x3)을 저장 후 연산을 진행하고
마지막 register는 메모리에서 변수를 옮겨와 사용하는 용도로 쓸 것이다.

최종 결과는 eax에 저장되고 WriteInt를 통해 저장된 값이 출력된다.

출력: eax에 저장된 결과
@

INCLUDE Irvine32.inc

INCLUDE CSE3030_PHW02.inc

.code
main PROC
	mov eax, x1		; eax <- x1
	mov ebx, eax	; ebx <- x1
	add eax, eax
	add eax, eax
	add eax, ebx	; eax <- 5x1
	mov ebx, x2		; ebx <- x2
	mov edx, eax	; edx <- 5x1
	sub eax, ebx	
	sub eax, ebx	; eax <- 5x1-2x2
	add edx, ebx	; edx <- 5x1+x2
	mov ebx, x3		; ebx <- x3
	add eax, ebx	; eax <- 5x1-2x2+x3
	add edx, ebx	; edx <- 5x1+x2+x3
	add eax, eax	; eax <- 2eax
	add eax, eax
	add eax, eax	; eax <- 8(5x1-2x2+x3)
	add eax, edx	; eax <- 8(5x1-2x2+x3)+(5x1+x2+x3)
	add eax, eax	; eax <- 2{8(5x1-2x2+x3)+(5x1+x2+x3)} = 16(5x1-2x2+x3)+2(5x1+x2+x3)
	add eax, ebx	; eax <- 16(5x1-2x2+x3)+2(5x1+x2+x3)+x3 = 90x1-30x2+19x3
	call WriteInt	; print result

	exit
main ENDP
END main