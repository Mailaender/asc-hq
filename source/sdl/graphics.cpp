/***************************************************************************
                         graphics.cpp  -  description
                             -------------------
    begin                : Sat Dec 18 1999
    copyright            : (C) 1999 by Martin Bickel
    email                : bickel@asc-hq.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//     $Id: graphics.cpp,v 1.4 2000-01-04 19:43:55 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.3  2000/01/02 19:47:09  mbickel
//      Continued Linux port
//      Fixed crash at program exit
//
//     Revision 1.2  2000/01/01 19:04:20  mbickel
//     /tmp/cvsVhJ4Z3
//
//     Revision 1.1  1999/12/28 21:03:31  mbickel
//      Continued Linux port
//      Added KDevelop project files
//


#include <stdlib.h>
#include "graphics.h"
#include "../basegfx.h"
#include "SDL.h"



SDL_Surface *screen = NULL;


int reinitgraphics(int modenum)
{
  return 1;
}

int initgraphics ( int x, int y, int depth )
{
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
     fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
     return -1;
  }

  /* Clean up on exit */
  atexit(SDL_Quit);

  /* Initialize the display in a 640x480 8-bit palettized mode */
  screen = SDL_SetVideoMode(x, y, depth, SDL_SWSURFACE | SDL_FULLSCREEN );
  if ( screen == NULL ) {
     fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",x,y,depth, SDL_GetError());
     return -1;
  }

  agmp->resolutionx = x;
  agmp->resolutiony = y;
  agmp->windowstatus = 100;
  agmp->scanlinelength = screen->w;
  agmp->scanlinenumber = screen->h;
  agmp->bytesperscanline = x * depth/8;
  agmp->byteperpix = screen->format->BytesPerPixel ;
  agmp->linearaddress = (int) screen->pixels;
/*
            char          redmasksize       ;
            char          redfieldposition  ;
            char          greenmasksize     ;
            char          greenfieldposition;
            char          bluemasksize      ;
            char          bluefieldposition ;
*/
  agmp->bitperpix = screen->format->BitsPerPixel;
//            char          memorymodel;
  agmp->directscreenaccess = 0;

  *hgmp = *agmp;

	graphicinitialized = 1;
   return 1;
}
             // returns > 0  modenum to reestablish this mode
             //         < 0 : error

void  closegraphics ( void )
{
	SDL_FreeSurface ( screen );
	screen = NULL;
}



//*********** Misc ************


int copy2screen( void )
{
   SDL_UpdateRect ( screen , 0,0,0,0 );
}

int copy2screen( int x1, int y1, int x2, int y2 )
{
   if ( x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1 )
      SDL_UpdateRect ( screen , 0,0,0,0 );
   else
      SDL_UpdateRect ( screen , x1, y1, x2-x1+1, y2-y1+1 );
}


void setdisplaystart( int x, int y)
{
}

void set_vgapalette256 ( dacpalette256 pal )
{
	SDL_Color spal[256];
	int col;
	for ( int i = 0; i < 256; i++ ) {
	   for ( int c = 0; c < 3; c++ ) {
         if ( pal[i][c] == 255 )
            col = activepalette[i][c];
         else {
            col = pal[i][c];
            activepalette[i][c] = col;
         }
         switch ( c ) {
            case 0: spal[i].r = col * 4; break;
            case 1: spal[i].g = col * 4; break;
		      case 2: spal[i].b = col * 4; break;
		   };
      }
	
	
	}	
	int res = SDL_SetColors ( screen, spal, 0, 256 );
	// printf("result of setting the palette is %d \n", res );
}

int dont_use_linear_framebuffer;

