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


/* unit header for: artint.c -- made by tptc - translate pascal to c */

  struct tartintconfig { 
                  boolean      movesearchshortestway;   /*  k�rzesten oder nur irgendeinen  */ 
                  boolean      lookintotransports;   /*  gegnerische transporter einsehen  */ 
                  boolean      lookintobuildings; 
               }; 
extern tartintconfig artintconfig;

// extern void  computerturn(void);

extern int getposval(void);

extern void  longdistmove(void);

