/*  tanhf.c: Computes tanh(x) where x is a 32-bit float as outlined in [1].

    Copyright (C) 2001, 2002  Jesus Calvino-Fraga, jesusc (at) ece.ubc.ca

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

/* [1] William James Cody and W.  M.  Waite.  _Software manual for the
   elementary functions_, Englewood Cliffs, N.J.:Prentice-Hall, 1980. */

/* Version 1.0 - Initial release */

#include <math.h>
#include <errno.h>

#pragma overlayto ?lib?dseg?2

#ifdef C51_STACK_AUTO
#define data
#endif

#define P0 -0.8237728127E+0
#define P1 -0.3831010665E-2
#define Q0  0.2471319654E+1
#define Q1  0.1000000000E+1

/* ln(3)/2 */
#define K1  0.5493061443E+0
/* SBIG=[ln(2)+(t+1)*ln(B)]/2 */
#define SBIG 9.01091

#define P(g) ((P1*g+P0)*g)
#define Q(g) (Q1*g+Q0)

float tanhf(const float x)
{
    data float f, g, r;

    f=fabsf(x);
    if(f>SBIG) r=1.0;
    else if(f>K1)
    {
        r=0.5-1.0/(expf(f+f)+1.0);
        r+=r;
    }
    else if(f<EPS) r=f;
    else
    {
        g=f*f;
        r=f+f*(P(g)/Q(g));
    }
    if(x<0.0) r=-r;
    return r;
}

