;============================================================
; File: JaDll.asm									;
;															;
; An assembly project, which contains a pocedure for	 	;
; edge detection algorithm in images						;
;															;
; Creator: Adrian Zarêba									;					
;															;
; Version:		
;		5.12.22
;		2.12.22
;		18.11.22
;		16.11.22
;		3.11.22
; 0.1 / 22.10.2022 - file and initial comments created		;
; Past versions/Version history:							;
; -															;
;============================================================


;NOTATKI
;[+4] przesuwa o 1 index (32bity);
;r9d - 32 bit
;r9b - 8 bit
;r9w - 16 bit
;r9 - 64 bit

.data
center WORD -4
borders WORD 1
zero WORD 0
channels Qword 1
maxrgbvalue WORD 255
;center real4 -4.0
;borders real4 1.0
;zero real4 0.0

.code

;================================================================================================================
; Procedure: EdgeDetectionFilter																								;
; Description:																									;
;	Imposes edge detection filter on image represented as an array of pixels(r g b). The filter is based		;
; 	 on multiplication of neighbouring pixels and matrix of weights.											;
;    It works on two arrays stored in memory.																	;
;																												;
; Parameters:																									;
;  rdx = image height - in pixels,																				;
;  rcx = image width - in pixels,																				;
;  r8 = original image source - address in memory of pixel array which represents original image to be filtered ;
;  r9 = edited image source - address in memory of pixel array which represents a new filtered image,			;
;	 all changes are to be made on this array																	;
;  Uses registers: RAX, RBX, RDI, R10, R11, R12, R13															;
;================================================================================================================
EdgeDetectionFilter proc 

mov rax, 0 ;Y - counter for outer loop
mov rbx, 0 ;X - counter for inner loop

ROWS:		;outer loop, height,Y
COLLUMNS:	;inner loop, width, X
;------------
MOV rdi, rax  ;POS
imul rdi, rcx ;>
add rdi, rbx  ;>this gives pos
;++++++

MOV R10, 0
MOV R10B, BYTE ptr[r8+rdi]	;Read value from tab (from specific adress)  
IMUL R10W, center	

;PREVIOUS (LEFT) PIXEL
MOV R11, 0
MOV R11B, BYTE ptr[R8+RDI-1]
ADD R10W, R11W

;NEXT (RIGHT) PIXEL
MOV R11, 0
MOV R11B, BYTE ptr[R8+RDI+1]
ADD R10W, R11W
;+++++++++++

;BELOW PIXEL
mov r12, rcx
add r12, rdi
MOV R11, 0
MOV R11B, BYTE ptr[r8+r12]
ADD R10W, R11W

;TOP PIXEL
mov r13, rcx 
mov r12, rdi
sub r12, r13
MOV R11B, BYTE ptr[r8+r12]
ADD R10W, R11W

CMP R10W, zero
JL REDUCE_NEG

CMP R10W, 200
JG REDUCE_BIG
END_OF_RED:

MOV BYTE ptr[r9+rdi], R10B	;Insert value to tab (to specific adress)
;mov dword ptr[r8+rdi], r10d	;Insert value to tab (to specific adress)

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

REDUCE_NEG:		;Accesible only by jump
MOV R10W, zero		;Make color value fit its lower boundary
JMP END_OF_RED	;Jump back to the loop
REDUCE_BIG:		;Accesible only by jump
MOV R10W, maxrgbvalue	;Make color value fit its upper boundary
JMP END_OF_RED	;Jump back to the loop

EdgeDetectionFilter endp
end