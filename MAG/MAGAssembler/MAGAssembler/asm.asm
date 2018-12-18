.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
		includelib ../Debug/Lib.lib
	ExitProcess PROTO :DWORD

	outputn PROTO: DWORD
	outputr PROTO: DWORD
	len PROTO: DWORD
	pows PROTO: DWORD, :DWORD

.stack 4096
.const
	L0 DWORD 3
	L1 DWORD 2
	L2 DWORD 17
	L3 DWORD 88
	L4 DWORD 7
	L5 BYTE "Its my course project.", 0
	L6 DWORD 6
	L7 BYTE "Hello World!", 0
.data
	afuncc DWORD ?
	bfunce DWORD ?
	cfuncz DWORD ?
	maine DWORD ?
	mainf DWORD ?
	maing DWORD ?
	mainresul DWORD ?

.code

afunc PROC afunca : SDWORD, afuncb : SDWORD
	push afunca
	push afuncb
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L0
	pop eax
	pop ebx
	mul ebx
	push eax
	pop afuncc
	push afuncc
	ret
afunc ENDP

bfunc PROC bfuncd : DWORD
	push bfuncd
	pop edx
	push bfuncd
		call len
	push eax
	pop bfunce
	push bfunce
	ret
bfunc ENDP

cfunc PROC cfuncx : SDWORD, cfuncy : SDWORD
	push cfuncx
	push cfuncy
	pop edx
	pop edx
	push cfuncy
	push cfuncx
		call pows
	push eax
	pop cfuncz
	push cfuncz
	ret
cfunc ENDP

main PROC
	push L0
	push L1
	push L2
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop maine
	push L3
	pop mainf
	push maine
	push mainf
	pop edx
	pop edx
	push mainf
	push maine
		call afunc
	push eax
	push L4
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop maing
	push maing
		call outputn
	push offset L5
	pop mainresul
	push mainresul
	pop edx
	push mainresul
		call bfunc
	push eax
	pop maing
	push maing
		call outputn
	push L0
	push L6
	pop edx
	pop edx
	push L6
	push L0
		call cfunc
	push eax
	pop maing
	push maing
		call outputn
	push offset L7
		call outputr
	push 0
	call ExitProcess
main ENDP
end main