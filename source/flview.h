//     $Id: flview.h,v 1.5 2000-08-12 12:52:47 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.4  2000/05/23 20:40:45  mbickel
//      Removed boolean type
//
//     Revision 1.3  2000/03/29 09:58:46  mbickel
//      Improved memory handling for DOS version
//      Many small changes I can't remember ;-)
//
//     Revision 1.2  1999/11/16 03:41:43  tmwilson
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

typedef struct tfliheader {
     int      flicsize;
     word         magic; 
     word         frames; 
     word         width, height, depth; 
     word         flags, speed; 
     int       next, frit;
     pascal_byte          enhance[102];
} tfliheader;

typedef struct tframeheader {
     int      framesize; 
     word         magic; 
     word         chunkcount;
     pascal_byte          enhance[8];
} tframeheader;


class tflicview {
   public :
        tfliheader         fliheader;
        tframeheader    frameheader;
        dacpalette256   flcpal;
        pascal_byte                *flcmem;
        char           endit,endatkey;
        pascal_byte               playspeed;
        word               flc_xpos,flc_ypos;
        int                  lasttimer,timerdiff;
        tkey                flkey;
        pascal_byte                convtable[256];
        signed short int           p1, p2, p3, p4, p5, p6, pc;
        signed short int           x,y,skipcnt;
        signed pascal_byte                szcnt,playcount;


        void init(void);
        pascal_byte loadflic(char *name);
        pascal_byte loadconvtable(char *name);
        pascal_byte viewflc(void);
        pascal_byte viewconvflc(void);
        void waitnextframe(void);
        void done(void);
};

extern void showflic(char *name,int x, int y);
extern void showconvflic(char *name,int x, int y);
extern void flicplayer(char *name,int x, int y); //mit Fktns-Tasten
extern void play_flc(int unitid,int prevx,int prevy);
