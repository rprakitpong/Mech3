/* Tiny printf routine for use with c51/mcs51
 * Copyright (c) 2004, Paul Stoffregen, paul@pjrc.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*
 * This tiny printf uses minimal code space, and it is fully reentrant
 * and register bank neutral (usually safe to call from within an
 * interrupt routine).  Code size is under 270 bytes.  Only one library
 * function is called (_gptrget, 41 bytes), in addition to calls to
 * putchar().
 *
 * Five simple formats are supported
 *
 *	%d	signed 16 bit integer decimal (-32768 to 32767)
 *	%u	unsigned 16 bit integer decimal (0 to 65535)
 *	%s	string, takes a 24 bit generic pointer
 *	%c	character.  You must explicitly cast to char in C51
 *	%x	16 bit integer in hex (0 to FFFF)
 *
 * For a more complete printf that supports longs, floating point and
 * field width, try using printf_fast() or printf_large().
 */


/* This removes the negative number code, causing "%d" to be the same
   as "%u".  If you don't care about printing negative numbers, this
   will save 21 bytes of code. */
/* #define ALWAYS_PRINT_UNSIGNED */

/* Directly output characters to the serial port using simple polling,
   rather than calling putchar().  This saves 14 bytes, plus the size
   of putchar. */
/* #define DIRECT_SERIAL_OUTPUT */



/* extern void putchar(char ); */


#define print_zero_flag PSW.5


#if !defined(C51_mcs51) || defined(C51_USE_XSTACK) || defined(_C51_NO_ASM_LIB_FUNCS)
/* Does printf_tiny really work on ds390 and ds400?
   If it does, enable them in the line above */
#if defined(_C51_BUILD_LIB)
/* Disable all warnings if building a library */
#pragma disable_warning 190
#elif defined(C51_USE_XSTACK)
#warning "printf_tiny not built, does not support --xstack"
#elif defined(_C51_NO_ASM_LIB_FUNCS)
#warning "printf_tiny not built, _C51_NO_ASM_LIB_FUNCS defined"
#else
/* Disable "ISO C forbids an empty source file" wraning message */
#pragma disable_warning 190
#endif
#else /* defines are compatible with printf_tiny */



void printf_tiny(__code const char *fmt, ...) __reentrant
{
    fmt;	/* suppress unreferenced variable warning */

    __asm

    printf_begin:
    mov	a, _bp		; r0 will point to va_args (stack)
    add	a, #253
    mov	r0, a		; r0 points to MSB of fmt
    mov	dph, @r0
    dec	r0
    mov	dpl, @r0	; dptr has address of fmt
    dec	r0


    printf_main_loop:
    clr	a
    movc	a, @a+dptr	; get next byte of fmt string
    inc	dptr
    add	a, #256 - 37
    jz	printf_format	; check for '%'
    add	a, #37
    jz	printf_end_h
    lcall	printf_putchar
    sjmp	printf_main_loop
    printf_end_h:
    ljmp	printf_end


    printf_format:
    setb	print_zero_flag
    clr	a
    movc	a, @a+dptr	; get next byte of data format
    inc	dptr
    push	dph
    push	dpl

    printf_format_s:
#ifdef USE_FLOATS
    cjne	a, #'s', printf_format_f
#else
    cjne	a, #'s', printf_format_c
#endif
    printf_string:
    ; print a string... just grab each byte with __gptrget
    ; the user much pass a 24 bit generic pointer
    mov	b, @r0		; b has type of address (generic *)
    dec	r0
    mov	dph, @r0
    dec	r0
    mov	dpl, @r0	; dptr has address of users string
    dec	r0
    printf_str_loop:
    lcall	__gptrget
    jz	printf_format_done
    inc	dptr
    lcall	printf_putchar
    sjmp	printf_str_loop

#ifdef USE_FLOATS
    printf_format_f:
    cjne	a, #'f', printf_format_c
    printf_float: ; The user passed a float
    mov	a, @r0
    dec	r0
    mov	b, @r0
    dec	r0
    mov	dph, @r0
    dec	r0
    mov	dpl, @r0
    dec	r0
    push ar0
    lcall __ftoa
    pop ar0
    printf_float_loop:
    lcall	__gptrget
    jz	printf_format_done
    inc	dptr
    lcall	printf_putchar
    sjmp	printf_float_loop
#endif

    printf_format_c:
    cjne	a, #'c', printf_format_d
    dec	r0
    mov	a, @r0		; Acc has the character to print
    dec	r0
    lcall	printf_putchar
    sjmp	printf_format_done


    printf_format_d:
    cjne	a, #'d', printf_format_u
#ifndef ALWAYS_PRINT_UNSIGNED
    mov	a, @r0
    jnb	acc.7, printf_uint
    dec	r0
    mov	a, @r0
    cpl	a
    add	a, #1
    mov	@r0, a
    inc	r0
    mov	a, @r0
    cpl	a
    addc	a, #0
    mov	@r0, a
    mov	a, #'-'
    lcall	printf_putchar
#endif
    sjmp	printf_uint


    printf_format_x:
    cjne	a, #'x', printf_format_u
    mov	dph, @r0
    dec	r0
    mov	dpl, @r0
    dec	r0
    clr	a
    printf_hex:
    lcall	printf_phex_lsn
    mov	a, dph
    lcall	printf_phex_msn
    mov	a, dph
    lcall	printf_phex_lsn
    mov	a, dpl
    lcall	printf_phex_msn
    mov	a, dpl
    lcall	printf_phex_lsn
    jnb	print_zero_flag, printf_format_done
    mov	a, #'0'
    lcall	printf_putchar
    printf_format_done:
    pop	dpl
    pop	dph
    ljmp	printf_main_loop


    printf_format_u:
    cjne	a, #'u', printf_format_done
    printf_uint:
    mov	a, @r0
    mov	r2, a
    dec	r0
    mov	a, @r0
    mov	r1, a
    dec	r0
    printf_int2bcd:
    mov	r4, #16
    mov	r5, #39
    lcall	div_by_sub
    mov	r7, a
    mov	r4, #232
    mov	r5, #3
    lcall	div_by_sub
    swap	a
    mov	dph, a
    mov	r4, #100
    mov	r5, #0
    lcall	div_by_sub
    orl	dph, a
    mov	a, r1
    mov	b, #10
    div	ab
    swap	a
    orl	a, b
    mov	dpl, a
    mov	a, r7
    sjmp	printf_hex


    ; Divide r2/r1 by r5/r4 using successive subtraction
    ; returns quotient in r2/r1 and remainder in acc.
    div_by_sub:
    mov     r3, #0
    div_by_sub_loop:
    inc     r3
        clr     c
        mov     a, r1
        subb    a, r4
        mov     r1, a
        mov     a, r2
        subb    a, r5
        mov     r2, a
        jnc     div_by_sub_loop
        dec     r3
        mov     a, r1
        add     a, r4
        mov     r1, a
        mov     a, r2
        addc    a, r5
        mov     r2, a
        mov     a, r3
        ret


    ; print a hex digit, either upper 4 bit (msn) or lower 4 bits (lsn)
    printf_phex_msn:
    swap	a
    printf_phex_lsn:
    anl	a, #15
    jnz	printf_phex_ok
    jb	print_zero_flag, printf_ret
    printf_phex_ok:
    clr	print_zero_flag
    add	a, #0x90
    da	a
    addc    a, #0x40
    da	a
    printf_putchar:
#ifdef DIRECT_SERIAL_OUTPUT
    jnb	ti, printf_putchar
    clr	ti
    mov	sbuf, a
#else
    push	dph
    push	dpl
    push	b
    mov	dpl, a
    mov	a, r0
    push	acc
    lcall	_putchar
    pop	acc
    mov	r0, a
    pop	b
    pop	dpl
    pop	dph
#endif
    printf_ret:
    ret


    printf_end:
    __endasm;
}


#endif /* defines compatible with printf_tiny */
