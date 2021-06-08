TITLE Add and Subtract

INCLUDE Irvine32.inc

.data
var1 DWORD 1000h    ; 32 bit variable var1
var2 DWORD 4000h
sum DWORD 0

.code
main PROC
	mov eax, var1    ; eax <- 10000h
	add eax, var2    ; eax <- 50000h
	sub eax, 2000h    ; eax <- 30000h
	mov sum, eax    ; sum<-eax
	call DumpRegs

	exit
main ENDP
END main