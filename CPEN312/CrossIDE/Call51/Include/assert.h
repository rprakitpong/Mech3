/*-------------------------------------------------------------------------
  assert.h - header file for assert ANSI routine

             Written By -  Sandeep Dutta . sandeep.dutta@usa.net (1999)

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

   In other words, you are welcome to use, share and improve this program.
   You are forbidden to forbid anyone else to use, share and improve
   what you give them.   Help stamp out software-hoarding!
-------------------------------------------------------------------------*/

#undef assert

#ifdef NDEBUG

/* Debugging disabled -- do not evaluate assertions. */
#define assert(x) ((void)0)

#else

/* Debugging enabled -- verify assertions at run time. */
void _assert(char *, const char *, unsigned int);
#define assert(x) ((x) == 0 ? _assert(#x, __FILE__, __LINE__):(void)0)
#define ASSERT(x) ((x) == 0 ? _assert(#x, __FILE__, __LINE__):(void)0)

#endif
