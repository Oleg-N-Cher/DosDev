/*
*  The body prefix file of the Ofront runtime system, Version 1.0
*
*  Copyright (c) Software Templ, 1994, 1995
*
*  Module SYSTEM is subject to change any time without prior notification.
*  Software Templ disclaims all warranties with regard to module SYSTEM,
*  in particular shall Software Templ not be liable for any damage resulting
*  from inappropriate use or modification of module SYSTEM.
*
*  Version 1.1  jt, 24.11.95  fixes for correct pointer arithmetic on Cray computers
*
*/

#include "SYSTEM.oh"
#ifndef __STDC__
#  include "stdarg.h"
#else
#  include "varargs.h"
#endif

extern void exit (int status);

/* runtime system routines */
extern void SYSTEM_INIT (int argc, long argvadr);
extern void SYSTEM_HALT (int n);
extern SHORTINT SYSTEM_ASH (SHORTINT x, BYTE n);
extern INTEGER SYSTEM_ASHL (INTEGER x, BYTE n);
extern long SYSTEM_MOD (unsigned long x, unsigned long y);
extern int SYSTEM_STRCMP (CHAR *x, CHAR *y);
export SYSTEM_PTR SYSTEM_NEWBLK (SHORTINT size);

#define SYSTEM_malloc(size)	(SYSTEM_PTR)malloc(size)

/*================================== Header ==================================*/

/* runtime system variables */
SHORTINT SYSTEM_argc;
SYSTEM_ADRINT SYSTEM_argv;

/*--------------------------------- Cut here ---------------------------------*/
SHORTINT SYSTEM_ASH (SHORTINT x, BYTE n)
{
	if (n >= 0) return x << n;
	return x >> (-n);
}

/*--------------------------------- Cut here ---------------------------------*/
INTEGER SYSTEM_ASHL (INTEGER x, BYTE n)
{
	if (n >= 0) return x << n;
	return x >> (-n);
}

/*--------------------------------- Cut here ---------------------------------*/
SHORTINT  SYSTEM_ABSS (SHORTINT x)  { return __ABS(x); }
/*--------------------------------- Cut here ---------------------------------*/
INTEGER   SYSTEM_ABS  (INTEGER x)   { return __ABS(x); }
/*--------------------------------- Cut here ---------------------------------*/
SHORTREAL SYSTEM_ABSF (SHORTREAL x) { return __ABS(x); }
/*--------------------------------- Cut here ---------------------------------*/
REAL      SYSTEM_ABSD (REAL x)      { return __ABS(x); }

/*--------------------------------- Cut here ---------------------------------*/
long SYSTEM_MOD (unsigned long x, unsigned long y)
{ unsigned long m;
  if ((long) x >= 0) return (x % y);
  else { m = (-x) % y;
    if (m != 0) return (y - m); else return 0;
  }
}

/*--------------------------------- Cut here ---------------------------------*/
int SYSTEM_STRCMP (CHAR *x, CHAR *y)
{long i = 0; CHAR ch1, ch2;
  do {ch1 = x[i]; ch2 = y[i]; i++;
    if (!ch1) return -(int)ch2;
  } while (ch1==ch2);
  return (int)ch1 - (int)ch2;
}

/*--------------------------------- Cut here ---------------------------------*/
void SYSTEM_HALT (int n)
{
  exit(n);
}

/*--------------------------------- Cut here ---------------------------------*/
SYSTEM_PTR SYSTEM_NEWBLK (SHORTINT size)
{
  SYSTEM_PTR mem = SYSTEM_malloc(size);
  __ASSERT(mem != NIL, 0xFF);
  return mem;
}

/*--------------------------------- Cut here ---------------------------------*/
/*
#define _DYNARRAY struct {
  INTEGER len[1]; // Length of allocated memory: LEN()
  CHAR data[1];   // Array data
} */
SYSTEM_PTR SYSTEM_NEWARR (SHORTINT size)
{
  SYSTEM_PTR arrPtr = SYSTEM_NEWBLK(sizeof(SHORTINT) + size);
  *((SHORTINT*)arrPtr) = size;
  return arrPtr;
}

/* ----------- end of SYSTEM.co ------------- */
