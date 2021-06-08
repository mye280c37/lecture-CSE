TITLE Equation Calculation using Add and Subtract

COMMENT @
�ۼ���: 20190258 ������

���: 90x1-30x2+19x3�� 16(5x1-2x2+x3)+2(5x1+x2+x3)+x3�� �ɰ��� ����� ���̰�
x1, x2, x3�� ������ �� ���� �ٸ� �������� �� ���� register�� �̿��Ͽ�
�� ���� register���� 8(5x1-2x2+x3)�� (5x1+x2+x3)�� ���� �� ������ �����ϰ�
������ register�� �޸𸮿��� ������ �Űܿ� ����ϴ� �뵵�� �� ���̴�.

���� ����� eax�� ����ǰ� WriteInt�� ���� ����� ���� ��µȴ�.

���: eax�� ����� ���
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