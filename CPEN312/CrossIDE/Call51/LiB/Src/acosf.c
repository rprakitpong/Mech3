/*  acosf.c: Computes arc cosine of a 32-bit float

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

float asincosf(const float x, const bit isacos);

float acosf(const float x)
{
    if (x == 1.0) return 0.0;
    else if (x ==-1.0) return PI;
    else if (x == 0.0) return HALF_PI;
    else               return asincosf(x, 1);
}
