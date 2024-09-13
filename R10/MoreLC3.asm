; Recitation MoreLC3
; Author: Riley Radici
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

            .ORIG x3000

            JSR mirror               ; call function
            HALT

; Parameter and return value
Param           .BLKW 1              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                           ; Mirrors bits 7:0 to 15:8
                                 ; ~20 lines of assembly code

            LD R0,Param          ; load pattern
            ADD R1,R0,#0		 ; Make copy of R0 to R1
            LD R2,Mask			 ; Load Mask into R2
            AND R1,R1,R2		 ; Use mask to clear bits 15:8 in result
            
            AND R2,R2,#0		 ; Initialize R2 to 1 (SOURCE MASK)
            ADD R2,R2,#1
            AND R3,R3,#0		 ; Initialize R3 to 1 (DESTINATION MASK)
            ADD R3,R3,#1
            AND R4,R4,#0		 ; Initialize R4 to 8 (COUNTER)
            ADD R4,R4,#8
                       
Loop        ADD R3,R3,R3		 ; Write a loop to shift R3 left by 8 bits
            ADD R4,R4,#-1
            BRp Loop
            
            AND R4,R4,#0	     ; Initialize R4 to 8 again
            ADD R4,R4,#8
            
Loop2       AND R5,R0,R2
            BRz Label
            ADD R1,R3,R1
Label		ADD R2,R2,R2
			ADD R3,R3,R3
			ADD R4,R4,#-1
			BRp Loop2 
			                   
            ST R1,Result         ; store result
            RET
            
;--------------------------------------------------------------------------
           .END
