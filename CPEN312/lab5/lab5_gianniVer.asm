$modde0cv

	CSEG at 0
	ljmp mycode

dseg at 30h

x:		ds	4
y:		ds	4
bcd:	ds	5
operation: ds 1

bseg

mf:		dbit 1

$include(math32.asm)

	CSEG

; Look-up table for 7-seg displays
myLUT:
    DB 0C0H, 0F9H, 0A4H, 0B0H, 099H        ; 0 TO 4
    DB 092H, 082H, 0F8H, 080H, 090H        ; 4 TO 9

showBCD MAC
	; Display LSD
    mov A, %0
    anl a, #0fh
    movc A, @A+dptr
    mov %1, A
	; Display MSD
    mov A, %0
    swap a
    anl a, #0fh
    movc A, @A+dptr
    mov %2, A
ENDMAC

Display:
	mov dptr, #myLUT
	showBCD(bcd+0, HEX0, HEX1)
	showBCD(bcd+1, HEX2, HEX3)
	showBCD(bcd+2, HEX4, HEX5)
    ret

MYRLC MAC
	mov a, %0
	rlc a
	mov %0, a
ENDMAC

Shift_Digits:
	mov R0, #4 ; shift left four bits
Shift_Digits_L0:
	clr c
	MYRLC(bcd+0)
	MYRLC(bcd+1)
	MYRLC(bcd+2)
	MYRLC(bcd+3)
	MYRLC(bcd+4)
	djnz R0, Shift_Digits_L0
	; R7 has the new bcd digit	
	mov a, R7
	orl a, bcd+0
	mov bcd+0, a
	; bcd+3 and bcd+4 don't fit in the 7-segment displays so make them zero
	clr a
	mov bcd+4, a
	ret

Wait50ms:
;33.33MHz, 1 clk per cycle: 0.03us
	mov R0, #30
L3: mov R1, #74
L2: mov R2, #250
L1: djnz R2, L1 ;3*250*0.03us=22.5us
    djnz R1, L2 ;74*22.5us=1.665ms
    djnz R0, L3 ;1.665ms*30=50ms
    ret
    
; Check if SW0 to SW9 are toggled up.  Returns the toggled switch in
; R7.  If the carry is not set, no toggling switches were detected.
ReadNumber:
	mov r4, SWA ; Read switches 0 to 7
	mov a, SWB ; Read switches 8 to 9
	anl a, #00000011B ; Only two bits of SWB available
	mov r5, a
	mov a, r4
	orl a, r5
	jz ReadNumber_no_number
	lcall Wait50ms ; debounce
	mov a, SWA
	clr c
	subb a, r4
	jnz ReadNumber_no_number ; it was a bounce
	mov a, SWB
	anl a, #00000011B
	clr c
	subb a, r5
	jnz ReadNumber_no_number ; it was a bounce
	mov r7, #16 ; Loop counter
ReadNumber_L0:
	clr c
	mov a, r4
	rlc a
	mov r4, a
	mov a, r5
	rlc a
	mov r5, a
	jc ReadNumber_decode
	djnz r7, ReadNumber_L0
	sjmp ReadNumber_no_number	
ReadNumber_decode:
	dec r7
	setb c
ReadNumber_L1:
	mov a, SWA
	jnz ReadNumber_L1
ReadNumber_L2:
	mov a, SWB
	jnz ReadNumber_L2
	ret
ReadNumber_no_number:
	clr c
	ret
	
mycode:
	mov SP, #7FH
	clr a
	mov LEDRA, a
	mov LEDRB, a
	mov bcd+0, a
	mov bcd+1, a
	mov bcd+2, a
	mov bcd+3, a
	mov bcd+4, a
	mov x, a
	mov x+1, a
	mov x+2, a
	mov x+3, a
	mov y, a
	mov y+1, a
	mov y+2, a
	mov y+3, a
	mov operation, a
	lcall Display

forever:
check_muldiv:
	jb KEY.0, check_add
check_mul:
	jb KEY.3, check_div
	mov operation, #00000100b
	jnb KEY.3, $
	lcall bcd2hex
	lcall copy_xy ;stores things in y
	Load_X(0)
	lcall hex2bcd
	lcall Display
	ljmp forever
check_div:
	jb KEY.2, check_muldiv
	mov operation, #00001000b
	jnb KEY.2, $
	lcall bcd2hex
	lcall copy_xy ;stores things in y
	Load_X(0)
	lcall hex2bcd
	lcall Display
	ljmp forever

check_add:
	jb KEY.3, check_sub
	mov operation, #00000001b
	jnb KEY.3, $
	lcall bcd2hex
	lcall copy_xy ;stores things in y
	Load_X(0)
	lcall hex2bcd
	lcall Display
	ljmp forever
	
check_sub:
	jb KEY.2, check_equal
	mov operation, #000000010b
	jnb KEY.2, $
	lcall bcd2hex
	lcall copy_xy ;stores things in y
	Load_X(0)
	lcall hex2bcd
	lcall Display
	ljmp forever
	
check_equal: 
	jb KEY.1, read_things
	jnb KEY.1, $
	lcall bcd2hex
	mov a, operation
	jb acc.0, do_add
	jb acc.1, do_sub
	jb acc.2, do_mul
	jb acc.3, do_div
if_equal:
do_add:
	lcall xchg_xy
	lcall add32
	lcall hex2bcd
	lcall Display
	ljmp forever
do_sub:
	lcall xchg_xy
	lcall sub32
	lcall hex2bcd
	lcall Display
	ljmp forever
do_mul:
	lcall xchg_xy
	lcall mul32
	lcall hex2bcd
	lcall Display
	ljmp forever
do_div:
	lcall xchg_xy
	lcall div32
	lcall hex2bcd
	lcall Display
	ljmp forever
	
read_things:	
	lcall ReadNumber
	jnc no_new_digit
	lcall Shift_Digits
	lcall Display
no_new_digit:
	ljmp forever
	
end
