;============================================================
; File: JaDll.asm											;
;															;
; An assembly project, which contains a pocedure for	 	;
; edge detection algorithm in images						;
;															;
; Creator: Adrian Zarêba									;					
;															;
; Version:													;
; 0.4 / 12.12.2022	 - final touches						;
; Past versions/Version history:							;
; 0.3 / 5.12.2022	 - some instrucions moved to sse		;
; 0.2.1 / 2.12.2022  - vetical shift bug removed			;
; 0.2 / 18.11.2022	 - implementation of the filter			;
; 0.1.2 / 16.11.2022 - iteration through pixels				;
; 0.1.1 / 3.11.2022	 - loop constructed						;
; 0.1 / 22.10.2022	 - file and initial comments created	;
;============================================================

.data
CENTER WORD -4		; Weight of the center pixel
MAXRGB WORD 255		; Max value for color in rgb format (as int, not float)
MAXVAL WORD 200		; Lowered limit of max color value for better highlighting of white areas

.code
;================================================================================================================
; Procedure: EdgeDetectionFilter																				;
; Description:																									;
;	Imposes edge detection filter on image represented as an array of pixels(grayscale). The filter is based	;
; 	 on multiplication of neighbouring pixels and matrix of weights(kernel).									;
;    The kernel is represented as 3x3 matrix: 0,1,0																;
;											  1,-4,1															;
;										      0,1,0																;
;    It works on two arrays stored in memory, one contains original images and servers as a reference,			;
;	   second works as an output image.																			;
;	 This procedure can work for parts of images, passed as number of rows, cut form image, it is on the user	;
;	 to make sure that no out of bounds or access violation errors occur.										;
;																												;
; Parameters:																									;
;  RDX = image height - in pixels, it's important to pass it smaller by 1 than it is in reality					;
;  RCX = image width - in pixels, should correspond to original image width										;
;  R8 = original image source - address in memory of pixel array which represents original image or part of it  ;
;  R9 = edited image source - address in memory of pixel array which represents a new image or part of it, all	;
;	 changes are to be made on this array																		;
;																												;
; A procedure also uses these registers: RAX, RBX, RDI, R12, R13, XMM0, XMM1, XMM2								;
;================================================================================================================
EdgeDetectionFilter proc 

MOV RAX, 0									;Y - counter for outer loop
MOV RBX, 0									;X - counter for inner loop

ROWS:										;Outer loop, height of the image, Y axis
COLLUMNS:									;Inner loop, width of the image, X axis
;-------------------Inner loop-----------------------;
MOV RDI, RAX  								;Calculating position in array for current pixel 
IMUL RDI, RCX 							    ; which means calculating an offset for the table
ADD RDI, RBX								;Calculated offset now stored in RDI, for duration of inner loop

;Get center pixel form memory and multiply it by weight
VPBROADCASTB XMM0, BYTE PTR[RDI+R8]			;Get pixel value
PSRLDQ XMM0, 15								;Shift for better clarity
VPBROADCASTW XMM1, CENTER					;Give weight
PMULLD XMM0, XMM1							;-||-

;Get *left pixel* form memory and add its value to value of previous one
VPBROADCASTB XMM1, BYTE PTR[RDI+R8-1]		;Get pixel value
PSRLDQ XMM1, 15								;Shift for better clarity
PADDW XMM0, XMM1							;Add pixel values together

;Get *right pixel* form memory and add its value to cumulative value of the rest
VPBROADCASTB XMM1, BYTE PTR[RDI+R8+1]		;Get pixel value
PSRLDQ XMM1, 15								;Shift for better clarity
PADDW XMM0, XMM1							;Add pixel values together

;Get * lower center pixel* form memory and add its value to cumulative value of the rest
MOV R12, RCX								;Calculate offset towards position of center pixel					
ADD R12, RDI								;-||-
VPBROADCASTB XMM1, BYTE PTR[R8+R12]			;Get pixel value		
PSRLDQ XMM1, 15								;Shift for better clarity
PADDW XMM0, XMM1							;Add pixel values together

;Get *upper center pixel* form memory and add its value to cumulative value of the rest
MOV R13, RCX								;Calculate offset towards position of center pixel	
MOV R12, RDI								;-||-
SUB R12, R13								;-||-
VPBROADCASTB XMM1, BYTE PTR[R8+R12]			;Get pixel value
PSRLDQ XMM1, 15								;Shift for better clarity
PADDW XMM0, XMM1							;Add pixel values together

;Compare obtained value with pixels max value bounds
MOVDQA XMM2, XMM0							;Store new pixel value for comparison

PXOR XMM1, XMM1								;Clear XMM1, now its all 0
PCMPGTW XMM1, XMM2							;Check if XMM1(Zero) is greater than pixel value(XMM2)
MOVD R12, XMM1								;Move resoult of comparison to R12, FF if true, 0 if false
CMP R12B, 255								;See comment above
JE REDUCE_NEG								;Jump if resoult od comparison was: True

VPBROADCASTW XMM1, MAXVAL					;Set max pixel value in xmm1
PCMPGTW XMM2, XMM1							;Check if new pixel value(XMM2) is greater than max value(XMM1)
MOVD R12, XMM2								;Move resoult of comparison to R12, FF if true, 0 if false
CMP R12B, 255								;See comment above
JE REDUCE_BIG								;Jump if resoult od comparison was: True
END_OF_REDUCTION:

MOVD R12D, XMM0								;Move new pixel value to R12
MOV BYTE PTR[RDI+R9], R12B					;Insert new pixel value to output table

INC	RBX										;Increment counter for inner loop
CMP	RBX, RCX								;Check if loop has ended
JL	COLLUMNS								;Jump if loop still continues
;------------End of inner loop---------------------;
MOV RBX, 0									;Reset counter for inner loop

INC RAX										;Increment counter for outer loop
CMP RAX, RDX								;Check if loop has ended
JL	ROWS  									;Jump if loop still continues
;-----------End of outer loop----------------------;

RET											;End of the procedure, reached when iteration through two loops is completed

REDUCE_NEG:									;Accesible only by jump
PXOR XMM0, XMM0								;Make pixel color value fit its lower boundary(0)
JMP END_OF_REDUCTION						;Jump back to the loop
REDUCE_BIG:									;Accesible only by jump
VPBROADCASTW XMM0, MAXRGB					;Make pixel color value fit its upper boundary(255)
JMP END_OF_REDUCTION						;Jump back to the loop

EdgeDetectionFilter endp					;Bye
end