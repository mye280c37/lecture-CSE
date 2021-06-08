TITLE UphillHeight 

COMMENT @
작성자: 20190258 김혜린
<변수>
	eax: maxHeight
	ebx: currentItem, tmpHeight
	ecx: test case counter, list item counter
	edx: nextItem, nextItem과 currentItem의 높이차
	esi: memory offset
<기능>	
	각 test case에 대해 (주어진 list size)-1만큼 순회하면서
	바로 양 옆 element에 대해 오르막 상태가 유지 중이라면 tmpHeight에 높이차를 더하고,
	오르막이 끝났을 경우, 해당 오르막의 높이인 tmpHeight와 
	지금까지의 탐색으로 저장된 maxHeight를 비교하여 해당 test case의 maxHeight를 구한 후 출력한다.
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
			push	ebx												; tmpHeight 0으로 초기화한 후 push
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
					push  ebx										; 0으로 초기화한 후 push tmpHeight 
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