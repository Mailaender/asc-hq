//     $Id: stack.cpp,v 1.3 2000-12-23 13:19:47 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.2  1999/11/16 03:42:36  tmwilson
//     	Added CVS keywords to most of the files.
//     	Started porting the code to Linux (ifdef'ing the DOS specific stuff)
//     	Wrote replacement routines for kbhit/getch for Linux
//     	Cleaned up parts of the code that gcc barfed on (char vs unsigned char)
//     	Added autoconf/automake capabilities
//     	Added files used by 'automake --gnu'
//
//
/*
    This file is part of Advanced Strategic Command; http://www.asc-hq.de
    Copyright (C) 1994-1999  Martin Bickel  and  Marc Schellenberger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING. If not, write to the 
    Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
    Boston, MA  02111-1307  USA
*/


#include <string.h>

#include "stack.h"


#define stacksize 10000  

char*        stackpointer = NULL;
int          stackofs = 0;

const int magic = 0x12345678;

void         push_data(char *       daten,
                      int          size)
{ 
  memcpy(stackpointer+stackofs, daten, size);
  stackofs+=size;
} 



void         pop_data(char *       daten,
                     int          size)
{ 
  if (stackofs < size) 
      throw fatalstackerror();
  
  stackofs-=size;
  memcpy(daten, stackpointer + stackofs, size);
} 


void         pushdata(char *       daten,
                      int          size)
{ 
   if ( !stackpointer ) {
      stackpointer = new char [ stacksize ];
      stackofs = 0;
   }
   push_data ( daten, size );
   push_data ( (char*) &magic, sizeof ( magic ));
} 


void         popdata(char *       daten,
                     int          size)
{ 
   int m;
   pop_data ( (char*) &m, sizeof ( m ));
   if ( m != magic )
      throw fatalstackerror();
   pop_data ( daten, size );
} 


int          stackfree(void)
{ 
  return ( stacksize - stackofs);
} 

