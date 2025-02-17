/*  frexpf.c: Returns the exponent and mantisa of a 32 bit float.

    Copyright (C) 2001-2011  Jesus Calvino-Fraga, jesusc (at) ece.ubc.ca

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA */

#include <math.h>
#include <errno.h>

#pragma overlayto ?lib?dseg?1

#ifdef C51_STACK_AUTO
#define data
#endif

float frexpf(const float x, int *pw2)
{
    union float_long fl;
	data long int i;
	
    fl.f=x;
    /* Find the exponent (power of 2) */
    i  = ( fl.l >> 23) & 0x000000ff;
    i -= 0x7e;
    *pw2 = i;
    fl.l &= 0x807fffff; /* strip all exponent bits */
    fl.l |= 0x3f000000; /* mantissa between 0.5 and 1 */
    return(fl.f);
}
