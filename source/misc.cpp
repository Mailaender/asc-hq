//     $Id: misc.cpp,v 1.21 2001-10-21 13:16:59 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.20  2001/10/16 19:58:19  mbickel
//      Added title screen for mapeditor
//      Updated source documentation
//
//     Revision 1.19  2001/08/09 14:50:37  mbickel
//      Added palette.map to data directory
//      Improved usability of terrain selection in mapeditor
//      New terrain translation in bi3 import function
//      Better error messages in text parser
//      Better error message: duplicate ID
//
//     Revision 1.18  2001/08/06 20:54:43  mbickel
//      Fixed lots of crashes related to the new text files
//      Fixed delayed events
//      Fixed crash in terrin change event
//      Fixed visibility of mines
//      Fixed crashes in event loader
//
//     Revision 1.17  2001/07/25 19:01:32  mbickel
//      Started adding text file formats
//
//     Revision 1.16  2001/01/28 23:19:55  mbickel
//      Finally, the linux version compiles again too...
//
//     Revision 1.15  2001/01/28 21:39:30  mbickel
//      Updated Borland C++ Building project files
//      Fixed some compilation problems with Borland
//      Made weaponguide compilable again
//
//     Revision 1.14  2000/10/12 19:51:44  mbickel
//      Added a stub program for generating a weapon guide
//      Added makefiles to compile this weaponguide with the free borland C++
//        compiler
//      Made some adjustments to basic IO file for compiling them with borland
//        C++
//
//     Revision 1.13  2000/10/11 14:26:43  mbickel
//      Modernized the internal structure of ASC:
//       - vehicles and buildings now derived from a common base class
//       - new resource class
//       - reorganized exceptions (errors.h)
//      Split some files:
//        typen -> typen, vehicletype, buildingtype, basecontainer
//        controls -> controls, viewcalculation
//        spfst -> spfst, mapalgorithm
//      bzlib is now statically linked and sources integrated
//
//     Revision 1.12  2000/09/16 11:47:29  mbickel
//      Some cleanup and documentation again
//
//     Revision 1.11  2000/09/07 15:49:44  mbickel
//      some cleanup and documentation
//
//     Revision 1.10  2000/05/07 12:53:59  mbickel
//      some minor adjustments
//
//     Revision 1.9  2000/05/06 20:25:23  mbickel
//      Fixed: -recognition of a second mouse click when selection a pd menu item
//             -movement: fields the unit can only pass, but not stand on them,
//                        are marked darker
//             -intedit/stredit: mouseclick outside is like hitting enter
//
//     Revision 1.8  2000/03/11 18:22:07  mbickel
//      Added support for multiple graphic sets
//
//     Revision 1.7  2000/02/03 20:54:41  mbickel
//      Some cleanup
//      getfiletime now works under Linux too
//
//     Revision 1.6  2000/01/24 08:16:49  steb
//     Changes to existing files to implement sound.  This is the first munge into
//     CVS.  It worked for me before the munge, but YMMV :)
//
//     Revision 1.5  2000/01/02 19:47:08  mbickel
//      Continued Linux port
//      Fixed crash at program exit
//
//     Revision 1.4  1999/12/28 21:03:08  mbickel
//      Continued Linux port
//      Added KDevelop project files
//
//     Revision 1.3  1999/11/18 17:31:15  mbickel
//      Improved BI-map import translation tables
//      Moved macros to substitute Watcom specific routines into global.h
//
//     Revision 1.2  1999/11/16 03:42:05  tmwilson
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <iostream>

#ifdef _WIN32_
#include <windows.h>
#endif

#include "global.h"
#include "tpascal.inc"
#include "misc.h"
#include "ascstring.h"

const char* digit[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
const char* letter[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", 
                         "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };


char strstring[1000];


int min ( int a, int b )
{
   if ( a > b )
      return b;
   else
      return a;
}

int min ( int a, int b, int c )
{
   return min ( a, min ( b, c ));
}


int max ( int a, int b )
{
   if ( a > b )
      return a;
   else
      return b;
}

int max ( int a, int b, int c )
{
   return max ( a, max ( b, c ));
}


#ifndef UseMemAvail 
int memavail ( void )
{
   return 0x7fffffff ;
}
#endif



/** Count the number of zero bits on the LSB side of "zahl"
 */
int log2(int zahl)
{
   char log;
   log = 0;
   if (zahl != 0) {
      while ((zahl & 1) == 0)  {
        zahl>>=1;
        log++;
      }
   }
   return log;
}


char* strr ( int a ) {
   char* s;
   s = new char [33];
   itoa ( a, s, 10 );
   return s;
}


char* strrr ( int a ) {
   itoa ( a, strstring, 10 );
   return strstring;
}

char* strrr ( double f ) {
   sprintf(strstring,"%f",f);
   return strstring;
}


void beep ( void )
{
   printf("\a");
}


typedef unsigned int UNS_32_BITS;


static UNS_32_BITS crc_32_tab[] = { /* CRC polynomial 0xedb88320 */
0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};


#define UPDC32(octet,crc) (crc_32_tab[((crc) ^ (octet)) & 0xff] ^ ((crc) >> 8))


int  crc32buf(const void *vbuf, int len)
{
      const char* buf = (const char*) vbuf;

      unsigned int crc;
      unsigned int oldcrc32;

      oldcrc32 = 0xFFFFFFFF;

      for ( ; len; --len, ++buf)
      {
            oldcrc32 = UPDC32(*buf, oldcrc32);
      }

      return crc = oldcrc32 = ~oldcrc32;

}


#ifndef HAVE_STRICMP
char *strupr (const char *a)
{
   int i;
   int j;
   char *b;

   j = strlen (a);
   b = (char *) malloc (j);
   for (i = 0; i < j; i++)
     b[i] = toupper (a[i]);
   return (b);
}
#endif

#ifndef HAVE_ITOA
char* itoa ( int a, char* b, int c)
{
   sprintf(b, "%d", a );
   return b;
}
#endif

#ifdef converter

void fatalError ( const ASCString& text )
{
   fprintf ( stderr, text.c_str() );

   #ifdef _WIN32_
   MessageBox(NULL, text.c_str(), "Fatal Error", MB_ICONERROR | MB_OK | MB_TASKMODAL );
   #endif

   exit ( 1 );
}


void fatalError ( const char* formatstring, ... )
{
   va_list paramlist;
   va_start ( paramlist, formatstring );

   char buf[10000];
   vsprintf ( buf, formatstring, paramlist );
   fatalError ( ASCString ( buf ));
}



void warning ( const ASCString& output )
{
   cerr << "ASC: " << output.c_str() << endl;
}

#endif
