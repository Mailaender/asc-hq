//     $Id: timer.cpp,v 1.2 2000-01-04 19:43:55 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.1  1999/12/28 21:03:31  mbickel
//      Continued Linux port
//      Added KDevelop project files
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

#include <stdlib.h>
#include "../timer.h"

#include "SDL.h"

#define timerintr 0x08
#define pit_freq 0x1234DD  

    static int  ticker = 0;
    static int  clock_ticks, counter,tticker;
    char         init=0;



void starttimer(void)
{
   tticker = ticker;
}

char time_elapsed(int time)
{
   if (tticker + time <= ticker) return 1;
   else return 0;
}

void ndelay(int time)
{ 
  long l;

   l = ticker; 
   do { 
   }  while ((ticker - l > time));
} 


Uint32 callback ( Uint32 interval )
{
   ticker++;
   return ++interval;
}

static Uint32 ticktock(Uint32 interval)
{
	++ticker;
	return(interval++);
}

void inittimer(int frequence)
{ 
   if (init != 0) return;
	if ( SDL_Init(SDL_INIT_TIMER) < 0 ) {
		fprintf(stderr, "Couldn't load SDL: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_SetTimer( 10, ticktock);
   init = 1;
} 


void closetimer(void)
{ 
   if (init == 0) return;
   SDL_SetTimer ( 0, NULL );
}
