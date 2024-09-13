; P5 Assignment
; Author: Riley Radici
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine          (option 0)
                .FILL IntSub         ; Address of IntSub routine          (option 1)
                .FILL IntMul         ; Address of IntMul routine          (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine        (option 3)
                .FILL BinaryXOr      ; Address of BinaryXOr routine       (option 4)
                .FILL LeftShift      ; Address of LeftShift routine       (option 5)
                .FILL RightArithShift; Address of RightArithShift routine (option 6)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return values for all functions
; Try changing the .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Option          .FILL #0             ; Which function to call
Param1          .BLKW 1              ; Space to specify first parameter
Param2          .BLKW 1              ; Space to specify second parameter
Result          .BLKW 1              ; Space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
IntAdd          LD R0,Param1         ; Result is Param1 + Param2
                LD R1,Param2         ; Your code goes here (~4 lines)
                ADD R2,R1,R0
                ST R2,Result
                RET
;------------------------------------------------------------------------------
IntSub          LD R0,Param1         ; Result is Param1 - Param2
                LD R1,Param2         ; Your code goes here (~6 lines)
                NOT R1,R1
                ADD R1,R1,#1
                ADD R2,R1,R0
                ST R2,Result
                RET
;------------------------------------------------------------------------------
IntMul          AND R2,R2,#0
				LD R0,Param1         ; Result is Param1 * Param2
                LD R1,Param2         ; Your code goes here (~9 lines)
                BRz Skip
Loop0			ADD R2,R2,R0
				ADD R1,R1,#-1
				BRp Loop0
Skip            ST R2,Result
                RET
;------------------------------------------------------------------------------
BinaryOr        LD R0,Param1         ; Result is Param1 | Param2
                LD R1,Param2         ; Your code goes here (~7 lines)
                AND R2,R2,#0
                NOT R0,R0
                NOT R1,R1
                AND R2,R1,R0
                NOT R2,R2
                ST R2,Result
                RET
;------------------------------------------------------------------------------
BinaryXOr       LD R0,Param1         ; Result is Param1 ^ Param2
                LD R1,Param2         ; Your code goes here
                AND R2,R2,#0
                AND R2,R0,R1
                NOT R2,R2
                AND R0,R0,R2
                NOT R0,R0
                AND R1,R1,R2
                NOT R1,R1
                AND R2,R1,R0
                NOT R2,R2
                ST R2,Result
                RET
;------------------------------------------------------------------------------
LeftShift       LD R0,Param1         ; Result is Param1 << Param2
                LD R1,Param2         ; (Fill vacant positions with 0's)
Loop1           ADD R0,R0,R0         ; Your code goes here (~7 lines)
                ADD R1,R1,#-1
                BRp Loop1
                ST R0,Result                     
                RET
;------------------------------------------------------------------------------
RightArithShift LD R0,Param1         ; Result is Param1 >> Param2 with sign extension
                LD R1,Param2         ; Your code goes here (~23 lines)
                AND R2,R2,#0
                AND R3,R2,#0
                AND R4,R4,#0
                
                ADD R2,R2,#1		 ; R2 SOURCE MASK
                ADD R3,R3,#1		 ; R3 DESTINATION MASK
                
Ext1			ADD R2,R2,R2		 ; Extend source mask by Param2
                ADD R1,R1,#-1
                BRp Ext1
                
Loop2           AND R1,R0,R2		 ; Inspect bit k using the source mask
				BRz isZero
                ADD R4,R4,R3
isZero          ADD R3,R3,R3
				ADD R2,R2,R2
                BRnp Loop2
                
                AND R1,R1,#0
                ADD R1,R1,#15
                AND R2,R2,#0
                ADD R2,R2,#1
                
Ext2			ADD R2,R2,R2		 ; Extend source mask by 15
                ADD R1,R1,#-1
                BRp Ext2
                
                AND R1,R0,R2
                BRz SZ
                
Loop3			ADD R4,R4,R3
				ADD R3,R3,R3
                BRnp Loop3
                
SZ        		ST R4,Result
                RET
;------------------------------------------------------------------------------
                .END
