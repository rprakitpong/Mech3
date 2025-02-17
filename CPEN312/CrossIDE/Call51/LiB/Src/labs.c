/*-------------------------------------------------------------------------
   abs.c: computes absolute value of an integer.

   Copyright (C) 2004 - Maarten Brock, sourceforge.brock@dse.nl

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
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
-------------------------------------------------------------------------*/

#include <stdlib.h>

static void dummy(void) __naked
{
    __asm
    public	_labs
_labs:
    jnb	acc.7, L00001?
    mov	r2,a
    clr	c
    clr	a
    subb a,dpl
    mov	dpl,a
    clr	a
    subb a,dph
    mov	dph,a
    clr	a
    subb a,b
    mov	b,a
    clr	a
    subb a,r2
L00001?:
    ret
    __endasm;
}

//END OF MODULE
