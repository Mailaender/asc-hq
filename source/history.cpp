/*! \file history.cpp
    \brief Originally planed to provide history functions for ASC, but was never finished. Long derelicted. 
*/

//     $Id: history.cpp,v 1.4 2004-06-23 19:36:21 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.3  2001/02/11 11:39:37  mbickel
//      Some cleanup and documentation
//
//     Revision 1.2  1999/11/16 03:41:50  tmwilson
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


/*
 * Generated by TPTC - Translate Pascal to C
 *     Version 1.7 03/26/88   (C) 1988 S.H.Smith
 */
//#include "tptcmac.h"
#include <tpascal.inc>
#include "typen.h"
#include "config.h"
#ifdef STDC_HEADERS
#include <stdlib.h>
#else
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#else
char *malloc (int);
#endif
#endif


#define statc 0    /* StatisticCOlor */ 
      #define hm   1.3    /* STatistic-Multiplikator Maxwert ist HM * gr��er als echter Maxwert */ 



     #define trounddata struct rounddata * 
     typedef struct rounddata { 
                  word         vehicle; 
                  word         buildings; 
                  int      energy; 
                  int      plus_energy; 
                  int      material; 
                  int      plus_material; 
                  int      sprit; 
                  int      plus_fuel; 
                  int      research; 
                  word         devtechs; 
               } rounddata;
               #undef trounddata
               typedef struct rounddata *trounddata; 
     #define pround struct tround * 
     typedef struct tround { 
               int      nr; 
               pround       next; 
               trounddata   player[9]; 
            } tround;
            #undef pround
            typedef struct tround *pround; 

pround       rounds; 
    pround       asr, ar; 
    pvehicle     ae; 
    pbuilding    ab; 


void         countunits(void)
{ byte         i, j; 
    boolean      ex; 

   ar = rounds; 
   do { 
      if (ar != NULL) ar = ar->next; 
   }  while (!(ar == NULL)); 
   ar = (tround *)malloc(sizeof(*ar));
   ar->next = NULL; 
   for (i = 0; i <= 8; i++) ar->player[i] = NULL; 
   { void *with1 = &map; 
      ar->nr = turn; 
      for (i = 0; i <= 8; i++) 
         if (with1->player[i].existent == true) { void *with2 = &with1->player[i]; 
            ar->player[i] = (rounddata *)malloc(sizeof(*ar->player[i]));
            ar->player[i]->vehicle = 0; 
            ar->player[i]->buildings = 0; 
            ar->player[i]->material = 0; 
            ar->player[i]->plus_material = 0; 
            ar->player[i]->energy = 0; 
            ar->player[i]->plus_energy = 0; 
            ar->player[i]->sprit = 0; 
            ar->player[i]->plus_fuel = 0; 
            ar->player[i]->research = 0; 
            ar->player[i]->devtechs = 0; 
            if (firstvehicle != NULL) { 
               ae = firstvehicle; 
               do { 
                  if (ae != NULL) { 
                     inc(ar->player[i]->vehicle); 
                     ae = ae->next; 
                  } 
               }  while (!(ae == NULL)); 
            } 
            if (firstbuilding != NULL) { 
               ab = firstbuilding; 
               inc(ar->player[i]->buildings); 
               do { 
                  if (ab != NULL) { 
                     inc(ar->player[i]->buildings); 
                     inc(ar->player[i]->material,ab->a.material); 
                     inc(ar->player[i]->plus_material,ab->plus.a.material); 
                     inc(ar->player[i]->energy,ab->a.energy); 
                     inc(ar->player[i]->plus_energy,ab->plus_energy); 
                     inc(ar->player[i]->sprit,ab->sprit); 
                     inc(ar->player[i]->plus_fuel,ab->plus.a.fuel); 
                     inc(ar->player[i]->research,ab->researchpoints); 
                     j = 0; 
                     do { 
                        if (with2->research.developedtechnologies[j] != NULL) inc(j); 
                     }  while (!(with2->research.developedtechnologies[j] == NULL)); 
                     ar->player[i]->devtechs = j; 
                     ab = ab->next; 
                  } 
               }  while (!(ab == NULL)); 
            } 
            } 
         
      } 
   
   asr = rounds; 
   ex = false; 
   if (asr != NULL) { 
      do { 
         if (asr != NULL) { 
            if (asr->next == NULL) ex = true; 
            else asr = asr->next; 
         } 
      }  while (!(ex == true)); 
      asr->next = ar; 
   } 
   else displaymessage("History not started !","",0); 
} 


void         starthistory(void)
{ byte         i; 

   rounds = malloc(sizeof(*rounds));
   for (i = 0; i <= 8; i++) rounds->player[i] = NULL; 
   rounds->nr = 0; 
   rounds->next = NULL; 
} 


void         delhistory(void)
{ byte         i; 

   while (rounds != NULL) { 
      ar = rounds; 
      for (i = 0; i <= 8; i++) if (ar->player[i] != NULL) { 
         dispose(&ar->player[i]); 
         ar->player[i] = NULL; 
      } 
      dispose(&ar); 
      ar = NULL; 
      rounds = rounds->next; 
      ar = rounds; 
   } 
} 

typedef struct xy { 
           int      x, y; 
        } xy; 

  /*         TShowHistory=(TDialogBox)
                        Action,ShowFlag,LId:Byte;
                        Max,Min,RoundNr:int;
                        Zplayer:ARRAY [0..8] OF Boolean;
                        PixS,MaxPix:XY;
                        Zoomx,ZoomY:Real;
                        procedure Init;
                        PROCEDURE Run; virtual;
                        PROCEDURE ButtonPressed(id:Byte); virtual;
                        FUNCTION GetData(P:PRound; player:Byte):int;
                        PROCEDURE GetInfo(VAR Mn,Mx,Round:int);
                        PROCEDURE PaintStat(Flag,id:Byte);
                        procedure Done;
                     END; */ 


void         tshowhistoryinit(void)
{ 
  word         w, i; 
  #define kg   15  

   inherited(); init(); 
   action = 0; 
   title = "History"; 
   sbld(x1,"%d",50); 
   xsize = 540; 
   y1 = 30; 
   ysize = 420; 
   maxpix.x = xsize - 60; 
   maxpix.y = ysize - 245; 
   pixs.x = 40 + x1; 
   pixs.y = ysize - 55 + y1; 
   lid = 0; 

   w = (xsize - 20) / 4; 
   windowstyle = windowstyle ^ dlg_in3d; 
   showflag = 1; 
   for (i = 0; i <= 8; i++) if (actmap->player[i].existent == true) zplayer[i] = true; 
   else zplayer[i] = false; 

     /* FOR i:=0 TO 3 DO BEGIN
      AddButton('',30+i*60,50,30+KG+i*60,50+KG,3,1,i+2,True);
      AddEingabe(i+2,Addr(Zplayer[i]),0,dblue);
   END;

   FOR i:=4 TO 7 DO BEGIN
      AddButton('',30+(i-4)*60,80,30+KG+(i-4)*60,80+KG,3,1,i+2,True);
      AddEingabe(i+2,Addr(Zplayer[i]),0,dblue);
   END;

   AddButton('',270,50,270+KG,50+KG,3,1,10,True);
   AddEingabe(10,Addr(Zplayer[8]),0,dblue);

   AddKey(2,CT_1);
   AddKey(3,CT_2);
   AddKey(4,CT_3);
   AddKey(5,CT_4);
   AddKey(6,CT_5);
   AddKey(7,CT_6);
   AddKey(8,CT_7);
   AddKey(9,CT_8);
   AddKey(10,CT_9); */ 

   addbutton("Units",20,120,w,140,0,1,11,true); 
   addbutton("Buildings",20,155,w,175,0,1,12,true); 

   addbutton("Energy",20 + w,120,2 * w,140,0,1,13,true); 
   addbutton("Energy +",20 + w,155,2 * w,175,0,1,14,true); 

   addbutton("Material",20 + 2 * w,120,3 * w,140,0,1,15,true); 
   addbutton("Material +",20 + 2 * w,155,3 * w,175,0,1,16,true); 

   addbutton("Fuel",20 + 3 * w,120,4 * w,140,0,1,17,true); 
   addbutton("Fuel +",20 + 3 * w,155,4 * w,175,0,1,28,true); 

   addbutton("Research",330,45,xsize - 20,65,0,1,19,true); 
   addbutton("Developed Techs",330,80,xsize - 20,100,0,1,20,true); 

   addbutton("~D~one",10,ysize - 30,xsize - 10,ysize - 10,0,1,24,true); 

   buildgraphics(); 
   rahmen(true,x1 + 20,y1 + 40,x1 + 300 + kg,y1 + 90 + kg); 

     /* FOR i:=0 TO 3 DO BEGIN
      NBar(x1+50+i*60,y1+50,x1+50+KG+i*60,y1+50+KG,20+i*8);
   END;
   FOR i:=4 TO 7 DO BEGIN
      NBar(x1+50+(i-4)*60,y1+80,x1+50+KG+(i-4)*60,y1+80+KG,20+i*8);
   END;
   NBar(x1+290,y1+50,x1+290+KG,y1+50+KG,20+8*8); */ 

   paintstat(0,0); 

   mousevisible(true); 
} 


void         tshowhistoryrun(void)
{ 
   do { 
      inherited(); run(); 
   }  while (!((taste == ct_esc) || (action == 1))); 
} 


void         tshowhistorybuttonpressed(void)
{ 
     /* IF (id>=2) AND (id<=10) THEN
      IF Zplayer[id-2] THEN PaintStat(2,id-2)
      ELSE PaintStat(1,id-2); */ 
   if ((id >= 11) && (id <= 20) && (id != lid)) { 
      showflag = id - 10; 
      paintstat(0,0); 
   } 
   if (id == 24) action = 1; 
   lid = id; 
} 


void         showplayerstat(byte         sp,
                             boolean      del)
{ 
   lastp[sp].x = pixs.x; 
   lastp[sp].y = pixs.y; 
   if (del) setcolor(dblue); 
   else setcolor(20 + sp * 8); 
   ar = rounds; 
   while (ar != NULL) { 
      w = getdata(ar,sp); 
      if (w != -1) { 
         line(lastp[sp].x,lastp[sp].y,pixs.x + round(ar->nr * zoomx),pixs.y - round(w * zoomy)); 
         lastp[sp].x = pixs.x + round(ar->nr * zoomx); 
         lastp[sp].y = pixs.y - round(w * zoomy); 
      } 
      ar = ar->next; 
   } 
} 


void         tshowhistorypaintstat(byte         flag,
                                   byte         id)
{ word         sp, b; 
    pround       ar; 
    int      w; 
    xy           lastp[9]; 

#define xstep 50    /* X-Beschriftungs-Abstand */ 
      #define ystep 50    /* Y-Beschriftungs-Abstand */ 
      #define linemx 5    /* X-Linien-L�nge */ 
      #define linemy 5    /* Y-Linien-L�nge */ 



   if (flag == 0) { 
      getinfo(min,max,roundnr); 
      if (max == 1) max = round(max * 1.5); 
      else max = round(max * hm); 
      if (roundnr > 0) zoomx = maxpix.x / roundnr; 
      else zoomx = 9; 
      if (max > 0) zoomy = maxpix.y / max; 
      else zoomy = 1; 
      if ((zoomy == 0) || (zoomx == 0)) return;
      nbar(pixs.x - 39,pixs.y - maxpix.y,pixs.x + maxpix.x,pixs.y + 10,dblue); 
      { void *with1 = &activefontsettings; 
         justify = centertext; 
         color = statc; 
         background = dblue; 
         return 25; 
         } 
      
      nline(pixs.x - 5,pixs.y,pixs.x + maxpix.x + 5,pixs.y,statc); 
      nline(pixs.x,pixs.y - maxpix.y - 5,pixs.x,pixs.y + 5,statc); 
      b = 0; 
      while (b < round(maxpix.x / zoomx)) { 
         showtext2(strr(b),pixs.x + round(b * zoomx) - 10,pixs.y + 5); 
         nline(pixs.x + round(b * zoomx),pixs.y + linemy,pixs.x + round(b * zoomx),pixs.y - linemy,statc); 
         if (round(xstep / zoomx) == 0) inc(b,1); 
         else inc(b,round(xstep / zoomx)); 
      } 
      { void *with1 = &activefontsettings; 
         justify = righttext; 
         } 
      
      b = 0; 
      while (b < round(maxpix.y / zoomy)) { 
         showtext2(strr(b),pixs.x - 38,pixs.y - round(b * zoomy) - 5); 
         nline(pixs.x - linemx,pixs.y - round(b * zoomy),pixs.x + linemx,pixs.y - round(b * zoomy),statc); 
         if (round(ystep / zoomy) == 0) inc(b,1); 
         else inc(b,round(ystep / zoomy)); 
      } 
      for (sp = 0; sp <= 8; sp++) lastp[sp].x = pixs.x; 
      for (sp = 0; sp <= 8; sp++) lastp[sp].y = pixs.y; 
      ar = rounds; 
      while (ar != NULL) { 
         for (sp = 8; sp >= 0; sp--) 
            if ((zplayer[sp]) && (ar->player[sp] != NULL)) { 
               w = getdata(ar,sp); 
               if (w != -1) { 
                  setcolor(20 + sp * 8); 
                  line(lastp[sp].x,lastp[sp].y,pixs.x + round(ar->nr * zoomx),pixs.y - round(w * zoomy)); 
                  lastp[sp].x = pixs.x + round(ar->nr * zoomx); 
                  lastp[sp].y = pixs.y - round(w * zoomy); 
               } 
            } 
         ar = ar->next; 
      } 
   } 
   else if (flag == 1) { 
      showplayerstat(id,true); 
      for (sp = 0; sp <= 8; sp++) 
         if (zplayer[sp]) showplayerstat(sp,false); 
      nline(pixs.x - 5,pixs.y,pixs.x + maxpix.x + 5,pixs.y,statc); 
      nline(pixs.x,pixs.y - maxpix.y - 5,pixs.x,pixs.y + 5,statc); 
   } 
   else showplayerstat(id,false); 
} 


long *       tshowhistorygetdata(struct *     p,
                                 int *        player)
{ 
   getdata = -1; 
   if (p == NULL) return;
   if (p->player[player] == NULL) return;
   switch (showflag) {
      
      case 1:   getdata = p->player[player]->vehicle; 
      break; 
      
      case 2:   getdata = p->player[player]->buildings; 
      break; 
      
      case 3:   getdata = p->player[player]->energy; 
      break; 
      
      case 4:   getdata = p->player[player]->plus.energy; 
      break; 
      
      case 5:   getdata = p->player[player]->material; 
      break; 
      
      case 6:   getdata = p->player[player]->plus.material; 
      break; 
      
      case 7:   getdata = p->player[player]->sprit; 
      break; 
      
      case 8:   getdata = p->player[player]->plus.fuel; 
      break; 
      
      case 9:   getdata = p->player[player]->research; 
      break; 
      
      case 10:   getdata = p->player[player]->devtechs; 
   break; 
   } 
} 


void         tshowhistorygetinfo(long *       mn,
                                 long *       mx,
                                 long *       round)
{ pround       p; 
    int      getdat, player; 

   mn = 200000000; 
   mx = 0; 
   round = -1; 
   if (rounds->next == NULL) return;
   round = 0; 
   p = rounds; 
   while (p != NULL) { 
      for (player = 0; player <= 8; player++) 
         if (p->player[player] != NULL) { 
            switch (showflag) {
               
               case 1:   getdat = p->player[player]->vehicle; 
               break; 
               
               case 2:   getdat = p->player[player]->buildings; 
               break; 
               
               case 3:   getdat = p->player[player]->energy; 
               break; 
               
               case 4:   getdat = p->player[player]->plus.energy; 
               break; 
               
               case 5:   getdat = p->player[player]->material; 
               break; 
               
               case 6:   getdat = p->player[player]->plus.material; 
               break; 
               
               case 7:   getdat = p->player[player]->sprit; 
               break; 
               
               case 8:   getdat = p->player[player]->plus.fuel; 
               break; 
               
               case 9:   getdat = p->player[player]->research; 
               break; 
               
               case 10:   getdat = p->player[player]->devtechs; 
            break; 
            } 
            if (getdat > mx) mx = getdat; 
            if (getdat < mn) mn = getdat; 
         } 
      p = p->next; 
      inc(round); 
   } 
} 

  /* procedure TShowHistoryDone;
BEGIN
   inherited Done;
END; */ 


  /* PROCEDURE ShowHistory;
VAR ShowHistory:TShowHistory;
BEGIN
   ShowHistory.Init;
   ShowHistory.Run;
   ShowHistory.Done;
END; */ 



