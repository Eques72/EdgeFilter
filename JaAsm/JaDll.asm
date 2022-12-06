;============================================================
; File: JaDll.asm											;
;															;
; An assembly project, which contains a pocedure for	 	;
; edge detection algorithm in images						;
;															;
; Creator: Adrian Zarêba									;					
;															;
; Version:													;
; 0.3 / 5.12.2022	 - some instrucions moved to sse		;
; Past versions/Version history:							;
; 0.2.1 / 2.12.2022  - vetical shift bug removed			;
; 0.2 / 18.11.2022	 - implementation of the filter			;
; 0.1.2 / 16.11.2022 - iteration through pixels				;
; 0.1.1 / 3.11.2022	 - loop constructed						;
; 0.1 / 22.10.2022	 - file and initial comments created	;
;============================================================

.data
CENTER WORD -4
MAXRGB WORD 255
MAXVAL WORD 200

.code
;================================================================================================================
; Procedure: EdgeDetectionFilter																				;
; Description:																									s;
;	Imposes edge detection filter on image represented as an array of pixels(r g b). The filter is based		;
; 	 on multiplication of neighbouring pixels and matrix of weights.											;
;    It works on two arrays stored in memory.																	;
;																												;
; Parameters:																									;
;  RDX = image height - in pixels,																				;
;  RCX = image width - in pixels,																				;
;  R8 = original image source - address in memory of pixel array which represents original image to be filtered ;
;  R9 = edited image source - address in memory of pixel array which represents a new filtered image,			;
;	 all changes are to be made on this array																	;
;  Uses registers: RAX, RBX, RDI, R12, R13, XMM0, XMM1, XMM2													;
;================================================================================================================
EdgeDetectionFilter proc 

mov rax, 0 ;Y - counter for outer loop
mov rbx, 0 ;X - counter for inner loop

ROWS:		;Outer loop, height of the image, Y axis
COLLUMNS:	;Inner loop, width of the image, X axis
;------------
MOV rdi, rax  ; Calculating position of the pixel 
imul rdi, rcx ;  which means calculating an offset for the table
add rdi, rbx  ; Calculated offset now stored in RDI

;Get center pixel and give it weight
VPBROADCASTB XMM0, BYTE PTR[RDI+R8] 
PSRLDQ XMM0, 15
VPBROADCASTW XMM1, CENTER
PMULLD XMM0, XMM1

;LEFT PIXEL
VPBROADCASTB XMM1, BYTE PTR[RDI+R8-1]
PSRLDQ XMM1, 15
PADDW XMM0, XMM1

;RIGHT PIXEL
VPBROADCASTB XMM1, BYTE PTR[RDI+R8+1]
PSRLDQ XMM1, 15
PADDW XMM0, XMM1

;BELOW PIXEL
mov r12, rcx
add r12, rdi
VPBROADCASTB XMM1, BYTE PTR[R8+R12] 
PSRLDQ XMM1, 15
PADDW XMM0, XMM1

;TOP PIXEL
mov r13, rcx 
mov r12, rdi
sub r12, r13
VPBROADCASTB XMM1, BYTE PTR[R8+R12] 
PSRLDQ XMM1, 15
PADDW XMM0, XMM1

;COMP MANOVER
MOVDQA XMM2, XMM0

pxor  xmm1, xmm1
PCMPGTW xmm1, xmm2 ;if first is greater
movd r12, xmm1
CMP r12b, 255 
JE REDUCE_NEG

VPBROADCASTW xmm1, MAXVAL
PCMPGTW xmm2,xmm1 ;if first is greater
movd r12, xmm2
CMP r12b, 255 
JE REDUCE_BIG
END_OF_RED:

movd r12d, XMM0
MOV BYTE PTR[RDI+R9], R12B ;Insert value to tab (to specific adress)

INC	rbx			;inner loop
CMP	rbx, rcx	;inner loop
JL	COLLUMNS	;inner loop

mov rbx, 0		;reset inner loop
;------------
INC rax			;outer loop
cmp rax, rdx	;outer loop
JL	ROWS  		;outer loop
;------------

ret

REDUCE_NEG:				;Accesible only by jump
pxor xmm0, xmm0			;Make color value fit its lower boundary
JMP END_OF_RED			;Jump back to the loop
REDUCE_BIG:				;Accesible only by jump
VPBROADCASTW XMM0, MAXRGB	;Make color value fit its upper boundary
JMP END_OF_RED			;Jump back to the loop

EdgeDetectionFilter endp
end