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

//float __slong2fs (long x)
static void dummy(void) __naked
{
    __asm
    public	___slong2fs
    ___slong2fs:
    mov	r4, a
    mov	r3, b
    mov	r2, dph
    mov	r1, dpl
    mov	a, #158
    public	slong2fs_doit
    slong2fs_doit:
    mov	exp_a, a
    clr	sign_a
    mov	a, r4
    jnb	acc.7, slong2fs_positive
    setb	sign_a
    mov	a, r1
    cpl	a
    add	a, #1
    mov	r1, a
    mov	a, r2
    cpl	a
    addc	a, #0
    mov	r2, a
    mov	a, r3
    cpl	a
    addc	a, #0
    mov	r3, a
    mov	a, r4
    cpl	a
    addc	a, #0
    mov	r4, a
    slong2fs_positive:
    lcall	fs_normalize_a
    ljmp	fs_round_and_return
    __endasm;
}

#else

/* convert signed long to float */
float __slong2fs (signed long sl)
{
    if (sl<0)
        return -__ulong2fs(-sl);
    else
        return __ulong2fs(sl);
}

#endif
