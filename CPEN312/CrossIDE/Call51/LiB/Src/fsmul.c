/* Floating point library in optimized assembly for 8051
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


#define C51_FLOAT_LIB
#include <float.h>


#ifdef FLOAT_ASM_MCS51

// float __fsmul (float a, float b) __reentrant
static void dummy(void) __naked
{

    // extract the two inputs, placing them into:
    //      sign     exponent   mantissa
    //      ----     --------   --------
    //  a:  sign_a   exp_a      r4/r3/r2
    //  b:  sign_b   exp_b      r7/r6/r5	__asm

    __asm

    public	___fsmul
    ___fsmul:

    lcall	fsgetargs

    ; first check if either input is zero
    cjne	r4, #0, L00002?
    L00001?:
    ljmp	fs_return_zero

    L00002?:
    mov	a, r7
    jz	L00001?

    ; compute final sign bit
    jnb	sign_b, L00003?
    cpl	sign_a
    L00003?:

    ; check if either input is infinity
    mov	a, exp_b
    cjne	a, #0xFF, L00004?
    ljmp	fs_return_inf
    L00004?:
    mov	a, exp_a
    cjne	a, #0xFF, L00005?
    ljmp	fs_return_inf
    L00005?:

    ; add the exponents
    add	a, exp_b
    ; if carry then no underflow
    jc	L00006?
    add	a, #130
    jc	L00007?
    ljmp	fs_return_zero

    L00006?:
    add	a, #131
    dec	a
    jnc	L00007?
    ljmp	fs_return_inf

    L00007?:
    mov	exp_a, a

    ; now we need to multipy r4/r3/r2 * r7/r6/r5
    ; ------------------------------------------
    ;	                        r2 * r5		<< 0
    ;	            r3 * r5  +  r2 * r6		<< 8
    ;	r4 * r5  +  r3 * r6  +  r2 * r7		<< 16
    ;	r4 * r6  +  r3 * r7			<< 24
    ;	r4 * r7					<< 32
    ;
    ; This adds quite a bit of code, but it is a LOT faster
    ; than three calls to __mululong...

    ; output goes into r4/r3/r2/r1/r0/xx

    mov	a, r2
    mov	b, r5
    mul	ab			; r2 * r5
    ; discard lowest 8 bits
    mov	r0, b
    ; range 0-FE

    mov	a, r2
    mov	b, r6
    mul	ab			; r2 * r6
    add	a, r0
    mov	r0, a
    clr	a
    addc	a, b
    mov	r1, a
    ; range 0-FEFF

    mov	a, r3
    mov	b, r5
    mul	ab			; r3 * r5
    add	a, r0
    ; discard lowest 8 bits
    mov	a, r1
    addc	a, b
    mov	r1, a
    clr	a
    rlc	a
    xch	a, r2
    ; range 0-1FD

    mov	b, r7
    mul	ab			; r2 * r7
    add	a, r1
    mov	r1, a
    mov	a, r2
    addc	a, b
    mov	r2, a
    ; range 0-FFFE

    mov	a, r3
    mov	r0, a
    mov	b, r6
    mul	ab			; r3 * r6
    add	a, r1
    mov	r1, a
    mov	a, r2
    addc	a, b
    mov	r2, a
    clr	a
    rlc	a
    mov	r3, a
    ; range 0-1FDFF

    mov	a, r4
    mov	b, r5
    mul	ab			; r4 * r5
    add	a, r1
    mov	r1, a
    mov	a, r2
    addc	a, b
    mov	r2, a
    clr	a
    addc	a, r3
    mov	r3, a
    ; range 0-2FC00

    mov	a, r0 ; r3
    mov	b, r7
    mul	ab			; r3 * r7
    add	a, r2
    mov	r2, a
    mov	a, r3
    addc	a, b
    mov	r3, a
    clr	a
    rlc	a
    xch	a, r4
    ; range 0-100FD00

    mov	r5, a
    mov	b, r6
    mul	ab			; r4 * r6
    add	a, r2
    mov	r2, a
    mov	a, r3
    addc	a, b
    mov	r3, a
    clr	a
    addc	a, r4
    mov	r4, a
    ; range 0-1FEFE00

    mov	a, r5 ; r4
    mov	b, r7
    mul	ab			; r4 * r7
    add	a, r3
    mov	r3, a
    mov	a, r4
    addc	a, b
    mov	r4, a
    ; range 40000000-FFFFFE00

    jb	acc.7, L00010?
    lcall	fs_normalize_a

    L00010?:
    ljmp	fs_round_and_return
    __endasm;
}

#else

/*
** libgcc support for software floating point.
** Copyright (C) 1991 by Pipeline Associates, Inc.  All rights reserved.
** Permission is granted to do *anything* you want with this file,
** commercial or otherwise, provided this message remains intact.  So there!
** I would appreciate receiving any updates/patches/changes that anyone
** makes, and am willing to be the repository for said changes (am I
** making a big mistake?).
**
** Pat Wood
** Pipeline Associates, Inc.
** pipeline!phw@motown.com or
** sun!pipeline!phw or
** uunet!motown!pipeline!phw
*/

/* (c)2000/2001: hacked a little by johan.knol@iduna.nl for c51 */

union float_long
{
    float f;
    unsigned long l;
};

/* multiply two floats */
float __fsmul (float a1, float a2)
{
    volatile union float_long fl1, fl2;
    volatile unsigned long result;
    volatile int exp;
    char sign;

    fl1.f = a1;
    fl2.f = a2;

    if (!fl1.l || !fl2.l)
        return (0);

    /* compute sign and exponent */
    sign = SIGN (fl1.l) ^ SIGN (fl2.l);
    exp = EXP (fl1.l) - EXCESS;
    exp += EXP (fl2.l);

    fl1.l = MANT (fl1.l);
    fl2.l = MANT (fl2.l);

    /* the multiply is done as one 16x16 multiply and two 16x8 multiples */
    result = (fl1.l >> 8) * (fl2.l >> 8);
    result += ((fl1.l & (unsigned long) 0xFF) * (fl2.l >> 8)) >> 8;
    result += ((fl2.l & (unsigned long) 0xFF) * (fl1.l >> 8)) >> 8;

    /* round, phase 1 */
    result += 0x40;

    if (result & SIGNBIT)
    {
        /* round, phase 2 */
        result += 0x40;
        result >>= 8;
    }
    else
    {
        result >>= 7;
        exp--;
    }

    result &= ~HIDDEN;

    /* pack up and go home */
    if (exp >= 0x100)
        fl1.l = (sign ? SIGNBIT : 0) | __INFINITY;
    else if (exp < 0)
        fl1.l = 0;
    else
        fl1.l = PACK (sign ? SIGNBIT : 0 , exp, result);
    return (fl1.f);
}

#endif
