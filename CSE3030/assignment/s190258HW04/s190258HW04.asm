TITLE UphillHeight 

COMMENT @
�ۼ���: 20190258 ������
<����>
	eax: maxHeight
	ebx: currentItem, tmpHeight
	ecx: test case counter, list item counter
	edx: nextItem, nextItem�� currentItem�� ������
	esi: memory offset
<���>	
	�� test case�� ���� (�־��� list size)-1��ŭ ��ȸ�ϸ鼭
	�ٷ� �� �� element�� ���� ������ ���°� ���� ���̶�� tmpHeight�� �������� ���ϰ�,
	�������� ������ ���, �ش� �������� ������ tmpHeight�� 
	���ݱ����� Ž������ ����� maxHeight�� ���Ͽ� �ش� test case�� maxHeight�� ���� �� ����Ѵ�.
@

INCLUDE Irvine32.inc

INCLUDE CSE3030_PHW04.inc

.data
dwordPtr=TYPE HEIGHT


.code
main PROC
	mov		ecx, TN												; get test case
	or			ecx, ecx
	jz	fin																; finish program if there is no test case
	mov		esi, OFFSET CASE								; get base address of CASE
L1:		push	ecx	
			mov		ecx, [esi]										; get list_size
			dec		ecx
			xor		eax, eax										; initialize maxHeight
			xor		ebx, ebx
			push	ebx												; tmpHeight 0���� �ʱ�ȭ�� �� push
			or			ecx, ecx
			jz	endL
L2: 				add		esi, dwordPtr
					mov		ebx, [esi]								; get currentItem
					mov		edx, [esi+dwordPtr]			; get nextItem
					sub		edx,  ebx
					jbe	checkH
					pop		ebx										; pop tmpHeight
					add		ebx, edx								; if uphill state continues: update tmpHeight
					push	ebx										; push tmpHeight
					loop L2
checkH:		pop		ebx										; pop tmpHeight
					cmp		ebx, eax								
					jbe		init
					mov		eax, ebx								; update maxHeight
init:				xor		ebx, ebx
					push  ebx										; 0���� �ʱ�ȭ�� �� push tmpHeight 
					or			ecx, ecx
					jz	endL
					loop L2
endL:	call		WriteDec
			mov		al, 0Dh
			call		WriteChar
			mov		al, 0Ah
			call		WriteChar
			add		esi, dwordPtr*2							; go to next list_size offset
			pop		ebx												; pop tmpHeight
			pop		ecx
			loop L1
fin: 	exit
main ENDP
END main