/*-------------------------------------------------------------------------
   float.h - ANSI functions forward declarations

   Written By -  Sandeep Dutta . sandeep.dutta@usa.net (1998)

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
-------------------------------------------------------------------------*/

#ifndef __C51_FLOAT_H
#define __C51_FLOAT_H 1

#include <limits.h>

#define FLT_RADIX       2
#define FLT_MANT_DIG    24
#define FLT_EPSILON     1.192092896E-07F
#define FLT_DIG         6
#define FLT_MIN_EXP     (-125)
#define FLT_MIN         1.175494351E-38F
#define FLT_MIN_10_EXP  (-37)
#define FLT_MAX_EXP     (+128)
#define FLT_MAX         3.402823466E+38F
#define FLT_MAX_10_EXP  (+38)

/* the following deal with IEEE single-precision numbers */
#define EXCESS		126
#define SIGNBIT		((unsigned long)0x80000000)
#define __INFINITY	((unsigned long)0x7F800000)
#define HIDDEN		(unsigned long)(1ul << 23)
#define SIGN(fp)	(((unsigned long)(fp) >> (8*sizeof(fp)-1)) & 1)
#define EXP(fp)		(((unsigned long)(fp) >> 23) & (unsigned int) 0x00FF)
#define MANT(fp)	(((fp) & (unsigned long)0x007FFFFF) | HIDDEN)
#define NORM            0xff000000
#define PACK(s,e,m)	((s) | ((unsigned long)(e) << 23) | (m))

float __uchar2fs (unsigned char);
float __schar2fs (signed char);
float __uint2fs (unsigned int);
float __sint2fs (signed int);
float __ulong2fs (unsigned long);
float __slong2fs (signed long);
unsigned char __fs2uchar (float);
signed char __fs2schar (float);
unsigned int __fs2uint (float);
signed int __fs2sint (float);
unsigned long __fs2ulong (float);
signed long __fs2slong (float);

float __fsadd (float, float);
float __fssub (float, float);
float __fsmul (float, float);
float __fsdiv (float, float);

char __fslt (float, float);
char __fseq (float, float);
char __fsgt (float, float);


#if defined(C51_FLOAT_LIB) && defined(C51_mcs51) && !defined(C51_USE_XSTACK) && !defined(_C51_NO_ASM_LIB_FUNCS)

#define FLOAT_ASM_MCS51

/* This adds extra code for proper round-off, in
   an attempt to match the results from gcc. */
#define FLOAT_FULL_ACCURACY

/* This adds about 66 bytes to the code size and
   significantly speeds up shift operations more
   than 8 bits (common when subtracting numbers
   of significantly different magnitude and scaling
   to fixed point) */
#define FLOAT_SHIFT_SPEEDUP

#define sign_a  psw.1
#define sign_b  psw.5
#define exp_a dpl
#define exp_b dph
#endif	/* using mcs51 assembly */


#endif	/* __C51_FLOAT_H */

