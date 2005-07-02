/***************************************************************************
                           sg.cpp  -  description
                             -------------------
    begin                : a long time ago...
    copyright            : (C) 1994-2003 by Martin Bickel
    email                : bickel@asc-hq.org
 ***************************************************************************/

/*! \file sg.cpp
    \brief THE main program: ASC
*/


/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/*!
   \mainpage 

   \section a short walk through the source
 
   THE central class of ASC is tmap in gamemap.h . 
   It is the anchor where nearly all elements of ASC are chained to. The global 
   variable #actmap is a pointer to the active map. There can be a maximum of
   8 players on a map, plus neutral units (which are handled like a 9th player). 
   Hence the array of 9 tmap::Player classes in tmap. 
   
   Each player has units and buildings, which are stored in the lists 
   tmap::Player::vehicleList and tmap::Player::buildingList . 
   The terms units and vehicles are used synonymously in ASC. Since unit was a 
   reserved word in Borland Pascal, we decided to use the term vehicle instead. 
   But now, with ASC written in C++,  'unit' is also used.
   
   Every building and unit is of a certain 'type': Vehicletype and BuildingType .
   These are stored in the data files which are loaded on startup and are globally 
   available. They are not modified during runtime in any way and are referenced
   by the instances of Vehicle and Building. The Vehicletype has information that are shared
   by all vehicles of this 'type', like speed, weapon systems, accessable
   terrain etc, while the vehicle stores things like remaining movement for this
   turn, ammo, fuel and cargo.
   
   The primary contents of a map are its fields ( tfield). Each field has again a pointer 
   to a certain weather of a TerrainType. Each TerrainType has up to 5 
   different weathers ("dry (standard)","light rain", "heavy rain", "few snow",
   "lot of snow"). If there is a unit or a building standing on a field, the field
   has a pointer to it: tfield::vehicle and tfield::building .
   
   On the field can be several instances of Object. Objects are another central class of 
   ASC. Roads, pipleines, trenches and woods are examples of objects.
 
*/

#include "global.h"

#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <new>
#include <cstdlib>
#include <ctype.h>
#include <signal.h>
#include <algorithm>
#include <memory>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "paradialog.h"

#include "vehicletype.h"
#include "buildingtype.h"
#include "ai/ai.h"
#include "basegfx.h"
#include "misc.h"
#include "loadpcx.h"
#include "newfont.h"
#include "events.h"
#include "typen.h"
#include "spfst.h"
#include "loaders.h"
#include "dlg_box.h"
#include "stack.h"
#include "controls.h"
#include "dlg_box.h"
#include "dialog.h"
#include "pd.h"
#include "strtmesg.h"
#include "gamedlg.h"
#include "network.h"
#include "building.h"
#include "sg.h"
#include "soundList.h"
#include "gameoptions.h"
#include "loadimage.h"
#include "astar2.h"
#include "errors.h"
#include "password.h"
#include "password_dialog.h"
#include "viewcalculation.h"
#include "replay.h"
#include "graphicset.h"
#include "loadbi3.h"
#include "itemrepository.h"
#include "music.h"
#include "messagedlg.h"
#include "statisticdialog.h"
#include "clipboard.h"
#include "mapdisplay2.h"
#include "guiiconhandler.h"
#include "guifunctions.h"
#include "iconrepository.h"
#include "dashboard.h"
#include "gamedialog.h"
#include "weathercast.h"
#include "asc-mainscreen.h"

// #define MEMCHK

#include "memorycheck.cpp"



class tsgonlinemousehelp : public tonlinemousehelp
{
   public:
      tsgonlinemousehelp ( void );
};

tsgonlinemousehelp :: tsgonlinemousehelp ( void )
{
   helplist.num = 12;

   static tonlinehelpitem sghelpitems[12]  = {{{ 498, 26, 576, 36}, 20001 },
         {{ 498, 41, 576, 51}, 20002 },
         {{ 586, 26, 612, 51}, 20003 },
         {{ 499, 57, 575, 69}, 20004 },
         {{ 499, 70, 575, 81}, 20005 },
         {{ 577, 58, 610, 68}, 20006 },
         {{ 577, 70, 610, 80}, 20007 },
         {{ 502, 92, 531,193}, 20008 },
         {{ 465, 92, 485,194}, 20009 },
         {{ 551, 92, 572,193}, 20010 },
         {{ 586, 90, 612,195}, 20011 },
         {{ 473,agmp->resolutiony - ( 480 - 449 ), 601,agmp->resolutiony - ( 480 - 460 )}, 20016 }};

   for ( int i = 0; i< helplist.num; i++ ) {
      sghelpitems[i].rect.x1 = agmp->resolutionx - ( 640 - sghelpitems[i].rect.x1 );
      sghelpitems[i].rect.x2 = agmp->resolutionx - ( 640 - sghelpitems[i].rect.x2 );
   }

   helplist.item = sghelpitems;
}

tsgonlinemousehelp* onlinehelp = NULL;




class tsgonlinemousehelpwind : public tonlinemousehelp
{
   public:
      tsgonlinemousehelpwind ( void );
} ;

tsgonlinemousehelpwind :: tsgonlinemousehelpwind ( void )
{
   helplist.num = 3;

   static tonlinehelpitem sghelpitemswind[3]  = { {{ 501,224, 569,290}, 20013 },
         {{ 589,228, 609,289}, 20014 },
         {{ 489,284, 509,294}, 20015 }};

   for ( int i = 0; i< helplist.num; i++ ) {
      sghelpitemswind[i].rect.x1 = agmp->resolutionx - ( 640 - sghelpitemswind[i].rect.x1 );
      sghelpitemswind[i].rect.x2 = agmp->resolutionx - ( 640 - sghelpitemswind[i].rect.x2 );
   }

   helplist.item = sghelpitemswind;
}

tsgonlinemousehelpwind* onlinehelpwind = NULL;




#define messagedisplaytime 300



pfield        getSelectedField(void)
{
   return actmap->getField( actmap->getCursor() ); 
} 


#define mmaintainence

bool maintainencecheck( void )
{
   int res = 0;
   if ( res )
      return true;

#ifdef maintainence
   int num = 0;

   for ( int i = 0; i < 8; i++ )
      if ( actmap->player[i].stat == Player::human  && actmap->player[i].exist())
         num++;

   if ( actmap->campaign )
      num++;

   if ( actmap->network )
      num++;

   if ( num <= 1 )
      return 1;
   else
      return 0;

#else
   return false;
#endif
}


void* loadpcx2raw( const ASCString& file )
{
   int pcxwidth,imgwidth;
   int pcxheight,imgheight;
   int depth = pcxGetColorDepth ( file, &pcxwidth, &pcxheight );
   if ( depth > 8 )
      fatalError(file + " could not be loaded: only 8 bit images supported");

   tvirtualdisplay vdp ( pcxwidth, pcxheight, 255, 8 );
   loadpcxxy ( file, 0, 0, 0, &imgwidth, &imgheight );
   void* img = new char[imagesize (0, 0, imgheight-1, imgwidth-1)];
   getimage ( 0, 0, imgwidth-1, imgheight-1, img );
   return img;
}






void         loadMoreData(void)
{
   int          w;
   {
      tnfilestream stream ( "height2.raw", tnstream::reading );
      for (int i=0;i<3 ;i++ )
         for ( int j=0; j<8; j++)
            stream.readrlepict( &icons.height2[i][j], false, &w );
   }

   {
      tnfilestream stream ("farbe.raw",tnstream::reading);
      for (int i=0;i<8 ;i++ )
         stream.readrlepict( &icons.player[i], false, &w );
   }

   {
      tnfilestream stream ("allianc.raw",tnstream::reading);
      for ( int i=0;i<8 ;i++ ) {
         stream.readrlepict(   &icons.allianz[i][0], false, &w );
         stream.readrlepict(   &icons.allianz[i][1], false, &w );
         stream.readrlepict(   &icons.allianz[i][2], false, &w );
      } /* endfor */
   }

   {
      tnfilestream stream ("weapicon.raw",tnstream::reading);
      for ( int i=0; i<14 ;i++ )
         stream.readrlepict(   &icons.unitinfoguiweapons[i], false, &w );
   }

   {
      tnfilestream stream ("expicons.raw",tnstream::reading);
      for ( int i=0; i<=maxunitexperience ;i++ )
         stream.readrlepict(   &icons.experience[i], false, &w );
   }

   /*
   {
      tnfilestream stream ("hexinvi2.raw",tnstream::reading);
      stream.readrlepict(   &icons.view.va8, false, &w);
   }

   {
      tnfilestream stream ("hexinvis.raw",tnstream::reading);
      stream.readrlepict(   &icons.view.nv8, false, &w);
      void* u = uncompress_rlepict ( icons.view.nv8 );
      if ( u ) {
         asc_free( icons.view.nv8 );
         icons.view.nv8 = u;
      }
   }

   {
      tnfilestream stream ("fg8.raw",tnstream::reading);
      stream.readrlepict(   &icons.view.fog8, false, &w);
   }
     */
   {
      tnfilestream stream ("windrose.raw",tnstream::reading);
      stream.readrlepict(   &icons.windbackground, false, &w);
   }

   dataLoaderTicker();
   {
      tnfilestream stream ("hexfld_a.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.mark.active, false, &w);
   }

   dataLoaderTicker();
   {
      tnfilestream stream ("hexfld.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.mark.inactive, false, &w);
   }

   {
      tnfilestream stream ("in_ach.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.mark.movein_active, false, &w);
   }

   {
      tnfilestream stream ("in_h.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.mark.movein_inactive, false, &w);
   }

   {
      tnfilestream stream ("build_ah.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.mark.repairactive, false, &w);
   }

   {
      tnfilestream stream ("build_h.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.mark.repairinactive, false, &w);
   }

   {
      tnfilestream stream ("hexbuild.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.container_window, false, &w);
   }

   dataLoaderTicker();


   loadpalette();
   for (w=0;w<256 ;w++ ) {
      palette16[w][0] = pal[w][0];
      palette16[w][1] = pal[w][1];
      palette16[w][2] = pal[w][2];
      xlattables.nochange[w] = w;
   } /* endfor */

   dataLoaderTicker();

   loadicons();

   dataLoaderTicker();

   loadmessages();

   dataLoaderTicker();
   {
      tnfilestream stream ("waffen.raw",tnstream::reading);
      int num = stream.readInt();

      static int xlatselectweaponguiicons[12] = { 2, 7, 6, 3, 4, 9, 0, 5, 10, 11, 11, 11 };

      for ( int i = 0; i < num; i++ )
         stream.readrlepict(   &icons.selectweapongui[xlatselectweaponguiicons[i]], false, &w );
      stream.readrlepict(   &icons.selectweaponguicancel, false, &w );
      stream.readrlepict(   &icons.selectweapongui[12], false, &w );
   }

   {
      tnfilestream stream ("knorein.raw",tnstream::reading);
      stream.readrlepict(   &icons.guiknopf, false, &w );
   }

   {
      tnfilestream stream ("compi2.raw",tnstream::reading);
      stream.readrlepict(   &icons.computer, false, &w );
   }

   {
      tnfilestream stream ("pfeil-a0.raw",tnstream::reading);
      for (int i=0; i<8 ;i++ ) {
         stream.readrlepict(   &icons.pfeil2[i], false, &w );
      } /* endfor */
   }

   {
      tnfilestream stream ("gebasym2.raw",tnstream::reading);
      for ( int i = 0; i < 12; i++ )
         for ( int j = 0; j < 2; j++ )
            stream.readrlepict(   &icons.container.lasche.sym[i][j], false, &w );
   }

   {
      tnfilestream stream ("netcontr.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.netcontrol.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.netcontrol.inactive, false, &w );
      stream.readrlepict(   &icons.container.subwin.netcontrol.active, false, &w );
   }

   {
      tnfilestream stream ("ammoprod.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.ammoproduction.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.ammoproduction.button, false, &w );
      stream.readrlepict(   &icons.container.subwin.ammoproduction.buttonpressed, false, &w );
      for ( int i = 0; i < 4; i++ )
         stream.readrlepict(   &icons.container.subwin.ammoproduction.schieber[i], false, &w );
      stream.readrlepict(   &icons.container.subwin.ammoproduction.schiene, false, &w );
   }

   dataLoaderTicker();
   {
      tnfilestream stream ("resorinf.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.resourceinfo.start, false, &w );
   }

   {
      tnfilestream stream ("windpowr.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.windpower.start, false, &w );
   }

   {
      tnfilestream stream ("solarpwr.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.solarpower.start, false, &w );

   }

   {
      tnfilestream stream ("ammotran.raw", tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.ammotransfer.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.ammotransfer.button, false, &w );
      stream.readrlepict(   &icons.container.subwin.ammotransfer.buttonpressed, false, &w );
      for ( int i = 0; i < 4; i++ )
         stream.readrlepict(   &icons.container.subwin.ammotransfer.schieber[i], false, &w );
      stream.readrlepict(   &icons.container.subwin.ammotransfer.schieneinactive, false, &w );
      stream.readrlepict(   &icons.container.subwin.ammotransfer.schiene, false, &w );
      if ( dataVersion >= 2 ) {
         stream.readrlepict(   &icons.container.subwin.ammotransfer.singlepage[0], false, &w );
         stream.readrlepict(   &icons.container.subwin.ammotransfer.singlepage[1], false, &w );
         stream.readrlepict(   &icons.container.subwin.ammotransfer.plus[0], false, &w );
         stream.readrlepict(   &icons.container.subwin.ammotransfer.plus[1], false, &w );
         stream.readrlepict(   &icons.container.subwin.ammotransfer.minus[0], false, &w );
         stream.readrlepict(   &icons.container.subwin.ammotransfer.minus[1], false, &w );
      }

   }

   {
      tnfilestream stream ("research.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.research.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.research.button[0], false, &w );
      stream.readrlepict(   &icons.container.subwin.research.button[1], false, &w );
      stream.readrlepict(   &icons.container.subwin.research.schieber, false, &w );
   }

   {
      tnfilestream stream ("pwrplnt2.raw",tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.conventionelpowerplant.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.conventionelpowerplant.schieber, false, &w );
      //stream.readrlepict(   &icons.container.subwin.conventionelpowerplant.button[1], false, &w );
   }





   int m; 
   {
      tnfilestream stream ( "bldinfo.raw", tnstream::reading );
      stream.readrlepict( &icons.container.subwin.buildinginfo.start, false, &m );
      for ( int i = 0; i < 8; i++ )
         stream.readrlepict( &icons.container.subwin.buildinginfo.height1[i], false, &m );
      for ( int i = 0; i < 8; i++ )
         stream.readrlepict( &icons.container.subwin.buildinginfo.height2[i], false, &m );
      stream.readrlepict( &icons.container.subwin.buildinginfo.repair, false, &m );
      stream.readrlepict( &icons.container.subwin.buildinginfo.repairpressed, false, &m );
      stream.readrlepict( &icons.container.subwin.buildinginfo.block, false, &m );
   }


   {
      tnfilestream stream ("mining2.raw", tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.miningstation.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.miningstation.zeiger, false, &w );
      /*
      for ( i = 0; i < 2; i++ )
         stream.readrlepict(   &icons.container.subwin.miningstation.button[i], false, &w );
      for ( i = 0; i < 2; i++ )
         stream.readrlepict(   &icons.container.subwin.miningstation.resource[i], false, &w );
      for ( i = 0; i < 3; i++ )
         stream.readrlepict(   &icons.container.subwin.miningstation.axis[i], false, &w );
      for ( i = 0; i < 2; i++ )
         stream.readrlepict(   &icons.container.subwin.miningstation.pageturn[i], false, &w );
      stream.readrlepict(   &icons.container.subwin.miningstation.graph, false, &w );
      */
   }

   {
      tnfilestream stream ("mineral.raw", tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.mineralresources.start, false, &w );
      stream.readrlepict(   &icons.container.subwin.mineralresources.zeiger, false, &w );
   }

   {
      tnfilestream stream ("tabmark.raw", tnstream::reading);
      stream.readrlepict (   &icons.container.tabmark[0], false, &w );
      stream.readrlepict (   &icons.container.tabmark[1], false, &w );
   }


   {
      tnfilestream stream ("traninfo.raw", tnstream::reading);
      stream.readrlepict(   &icons.container.subwin.transportinfo.start, false, &w );
      for ( int i = 0; i < 8; i++ )
         stream.readrlepict(   &icons.container.subwin.transportinfo.height1[i], false, &w );
      for ( int i = 0; i < 8; i++ )
         stream.readrlepict(   &icons.container.subwin.transportinfo.height2[i], false, &w );
      stream.readrlepict(   &icons.container.subwin.transportinfo.sum, false, &w );
   }

   dataLoaderTicker();
   {
      tnfilestream stream ("attack.raw", tnstream::reading);
      stream.readrlepict (   &icons.attack.bkgr, false, &w );
      icons.attack.orgbkgr = NULL;
   }

   {
      tnfilestream stream ("hexfeld.raw", tnstream::reading);
      stream.readrlepict ( &icons.fieldshape, false, &w );
   }

   {
      tnfilestream stream ("mapbkgr.raw", tnstream::reading);
      stream.readrlepict ( &icons.mapbackground, false, &w );
   }

   {
      tnfilestream stream ("hex2oct.raw", tnstream::reading);
      stream.readrlepict (   &icons.hex2octmask, false, &w );
   }

   {
      tnfilestream stream ("weapinfo.raw", tnstream::reading);
      for ( int i = 0; i < 5; i++ )
         stream.readrlepict (   &icons.weaponinfo[i], false, &w );
   }

}




void loadMap()
{
   ASCString s1;

   mousevisible(false);
   fileselectsvga(mapextension, s1, true );

   if ( !s1.empty() ) {
      mousevisible(false);
      displaymessage("loading map %s",0, s1.c_str() );
      loadmap( s1.c_str() );
      actmap->startGame();

      next_turn();

      removemessage();
      if (actmap->campaign != NULL) {
         delete  ( actmap->campaign );
         actmap->campaign = NULL;
      }

      displaymap();
      updateFieldInfo();
      moveparams.movestatus = 0;
   }
   mousevisible(true);
}


void loadGame()
{
   mousevisible(false);

   ASCString s1;
   fileselectsvga(savegameextension, s1, true );

   if ( !s1.empty() ) {
      mousevisible(false);
      displaymessage("loading %s ",0, s1.c_str());
      loadgame(s1.c_str() );
      removemessage();
      if ( !actmap || actmap->xsize == 0 || actmap->ysize == 0 )
         throw  NoMapLoaded();

      if ( actmap->network )
         setallnetworkpointers ( actmap->network );

      computeview( actmap );
      displaymap();
      updateFieldInfo();
      moveparams.movestatus = 0;
   }
   mousevisible(true);
}


void saveGame( bool as )
{
   ASCString s1;

   int nameavail = 0;
   if ( !actmap->preferredFileNames.savegame[actmap->actplayer].empty() )
      nameavail = 1;

   if ( as || !nameavail ) {
      mousevisible(false);
      fileselectsvga(savegameextension, s1, false );
   } else
      s1 = actmap->preferredFileNames.savegame[actmap->actplayer];

   if ( !s1.empty() ) {
      actmap->preferredFileNames.savegame[actmap->actplayer] = s1;

      mousevisible(false);
      displaymessage("saving %s", 0, s1.c_str());
      savegame(s1.c_str());

      removemessage();
      displaymap();
   }
   mousevisible(true);
}



void         newcampaign(void)
{
   tchoosenewcampaign tnc;
   tnc.init();
   tnc.run();
   tnc.done();
}



void         newsinglelevel(void)
{
   tchoosenewsinglelevel tnc;

   tnc.init();
   tnc.run();
   tnc.done();
   // actmap->player[0].exist();
}

void         startnewsinglelevelfromgame(void)
{
   newsinglelevel();
   if ( !actmap )
      throw NoMapLoaded();
   computeview( actmap );
   displaymap();
}



void loadStartupMap ( const char *gameToLoad=NULL )
{
   if ( gameToLoad && gameToLoad[0] ) {
      try {
         if ( patimat ( tournamentextension, gameToLoad )) {

            if( validateemlfile( gameToLoad ) == 0 )
               fatalError( "Email gamefile %s is invalid. Aborting.", gameToLoad );

            try {
               tnfilestream gamefile ( gameToLoad, tnstream::reading );
               tnetworkloaders nwl;
               nwl.loadnwgame( &gamefile );
               if ( actmap->network )
                  setallnetworkpointers ( actmap->network );
            } catch ( tfileerror ) {
               fatalError ( "%s is not a legal email game.", gameToLoad );
            }
         } else if( patimat ( savegameextension, gameToLoad )) {
            if( validatesavfile( gameToLoad ) == 0 )
               fatalError ( "The savegame %s is invalid. Aborting.", gameToLoad );

            try {
               loadgame( gameToLoad );
               computeview( actmap );
            } catch ( tfileerror ) {
               fatalError ( "%s is not a legal savegame. ", gameToLoad );
            }

         } else if( patimat ( mapextension, gameToLoad )) {
            if( validatemapfile( gameToLoad ) == 0 )
               fatalError ( "Mapfile %s is invalid. Aborting.", gameToLoad );

            try {
               loadmap( gameToLoad );
               computeview( actmap );
               if ( actmap->network )
                  setallnetworkpointers ( actmap->network );
            } catch ( tfileerror ) {
               fatalError ( "%s is not a legal map. ", gameToLoad );
            }
         } else
            fatalError ( "Don't know how to handle the file %s ", gameToLoad );

      }
      catch ( InvalidID err ) {
         displaymessage( err.getMessage().c_str(), 2 );
      } /* endcatch */
      catch ( tinvalidversion err ) {
         if ( err.expected < err.found )
            displaymessage( "File/module %s has invalid version.\nExpected version %d\nFound version %d\nPlease install the latest version from www.asc-hq.org", 2, err.getFileName().c_str(), err.expected, err.found );
         else
            displaymessage( "File/module %s has invalid version.\nExpected version %d\nFound version %d\nThis is a bug, please report it!", 2, err.getFileName().c_str(), err.expected, err.found );
      }
   } else {  // resort to loading defaults

      ASCString s = CGameOptions::Instance()->startupMap; 

      if ( s.empty() )
         s = "asc001.map";


      int maploadable;
      {
         tfindfile ff ( s );
         string filename = ff.getnextname();
         maploadable = validatemapfile ( filename.c_str() );
      }

      if ( !maploadable ) {

         tfindfile ff ( mapextension );
         string filename = ff.getnextname();

         if ( filename.empty() )
            displaymessage( "unable to load startup-map",2);

         while ( !validatemapfile ( filename.c_str() ) ) {
            filename = ff.getnextname();
            if ( filename.empty() )
               displaymessage( "unable to load startup-map",2);

         }
         s = filename;
      }

      loadmap(s.c_str());

      displayLogMessage ( 6, "initializing map..." );
      actmap->startGame();
      displayLogMessage ( 6, "done\n Setting up Resources..." );
      actmap->setupResources();
      displayLogMessage ( 6, "done\n" );
   }
}


void         startnextcampaignmap( int id)
{
   tcontinuecampaign ncm;
   ncm.init();
   ncm.setid(id);
   ncm.run();
   ncm.done();
}


void benchgame ( int mode )
{
   int t2;
   int t = ticker;
   int n = 0;
   do {
      if ( mode <= 1 ) {
         if ( mode == 1 )
            computeview( actmap );
         displaymap();
      } else
         copy2screen();

      n++;
      t2 = ticker;
   } while ( t + 1000 > t2 ); /* enddo */
   double d = 100 * n;
   d /= (t2-t);
   char buf[100];
   sprintf ( buf, "%3.1f", d );
   displaymessage2 ( " %s fps ", buf );
}

class WeaponRange : public SearchFields
{
   public:
      int run ( const Vehicle* veh );
      void testfield ( const MapCoordinate& mc )
      {
         gamemap->getField( mc )->tempw = 1;
      };
      WeaponRange ( pmap _gamemap ) : SearchFields ( _gamemap )
      {}
      ;
};

int  WeaponRange :: run ( const Vehicle* veh )
{
   int found = 0;
   if ( fieldvisiblenow ( getfield ( veh->xpos, veh->ypos )))
      for ( int i = 0; i < veh->typ->weapons.count; i++ ) {
         if ( veh->typ->weapons.weapon[i].shootable() ) {
            initsearch ( veh->getPosition(), veh->typ->weapons.weapon[i].maxdistance/minmalq, (veh->typ->weapons.weapon[i].mindistance+maxmalq-1)/maxmalq );
            startsearch();
            found++;
         }
      }
   return found;
}


void viewunitweaponrange ( const Vehicle* veh, tkey taste )
{
   if ( veh && !moveparams.movestatus  ) {
      actmap->cleartemps ( 7 );
      WeaponRange wr ( actmap );
      int res = wr.run ( veh );
      if ( res ) {
         displaymap();

         if ( taste != ct_invvalue ) {
            while ( skeypress ( taste )) {

               while ( keypress() )
                  r_key();

               releasetimeslice();
            }
         } else {
            int mb = mouseparams.taste;
            while ( mouseparams.taste == mb && !keypress() )
               releasetimeslice();
            while ( keypress() )
               r_key();
         }

         actmap->cleartemps ( 7 );
         displaymap();
      }
   }
}


void viewPipeNet( tkey taste )
{

   if ( !moveparams.movestatus ) {
      actmap->cleartemps ( 7 );
      TerrainBits tb = getTerrainBitType(cbpipeline);
      for ( int x = 0; x < actmap->xsize; ++x )
         for ( int y = 0; y < actmap->ysize; ++y ) {
             pfield fld = actmap->getField ( x, y );
             if ( fieldvisiblenow( fld ))
                if ( (fld->bdt & tb).any() || fld->building )
                   fld->a.temp = 1;
         }

      displaymap();

      if ( taste != ct_invvalue ) {
         while ( skeypress ( taste )) {
            while ( keypress() )
               r_key();

            releasetimeslice();
         }
      } else {
         int mb = mouseparams.taste;
         while ( mouseparams.taste == mb && !keypress() )
            releasetimeslice();

         while ( keypress() )
            r_key();
      }
      actmap->cleartemps ( 7 );
      displaymap();
   }
}


void viewunitmovementrange ( Vehicle* veh, tkey taste )
{
   if ( veh && !moveparams.movestatus && fieldvisiblenow ( getfield ( veh->xpos, veh->ypos ))) {
      actmap->cleartemps ( 7 );
      TemporaryContainerStorage tcs ( veh, true );
      veh->reactionfire.disable();
      veh->setMovement ( veh->typ->movement[log2(veh->height)]);
      int oldcolor = veh->color;
      veh->color = actmap->actplayer*8;
      VehicleMovement vm ( NULL, NULL );
      if ( vm.available ( veh )) {
         vm.execute ( veh, -1, -1, 0, -1, -1 );
         veh->color = oldcolor;
         if ( vm.reachableFields.getFieldNum()) {
            for  ( int i = 0; i < vm.reachableFields.getFieldNum(); i++ )
               if ( fieldvisiblenow ( vm.reachableFields.getField ( i ) ))
                  vm.reachableFields.getField ( i )->a.temp = 1;
            for  ( int j = 0; j < vm.reachableFieldsIndirect.getFieldNum(); j++ )
               if ( fieldvisiblenow ( vm.reachableFieldsIndirect.getField ( j )))
                  vm.reachableFieldsIndirect.getField ( j )->a.temp = 1;

            displaymap();

            if ( taste != ct_invvalue ) {
               while ( skeypress ( taste )) {
                  while ( keypress() )
                     r_key();

                  releasetimeslice();
               }
            } else {
               int mb = mouseparams.taste;
               while ( mouseparams.taste == mb && !keypress() )
                  releasetimeslice();

               while ( keypress() )
                  r_key();
            }
            actmap->cleartemps ( 7 );
            displaymap();
         }
      }
      veh->color = oldcolor;
      tcs.restore();
   }
}


void renameUnit()
{
   if ( actmap ) {
      pfield fld = getSelectedField();
      if ( fld && fld->vehicle && fld->vehicle->getOwner() == actmap->actplayer )
         fld->vehicle->name = editString ( "unit name", fld->vehicle->name );
      if ( fld && fld->building && fld->building->getOwner() == actmap->actplayer )
         fld->building->name = editString ( "building name", fld->building->name );
   }
}


void calcCargoSummary( ContainerBase* cb, map<int,int>& summary )
{
   for ( int i = 0; i < 32; ++i )
      if ( cb->loading[i] ) {
         calcCargoSummary( cb->loading[i], summary );
         summary[cb->loading[i]->typ->id] += 1;
      }
}

void showCargoSummary()
{
   typedef map<int,int> Summary;
   Summary summary;

   pfield fld = getSelectedField();
   if ( fld && fld->vehicle && fld->vehicle->getOwner() == actmap->actplayer ) {
      calcCargoSummary( fld->vehicle, summary );

      ASCString s;
      for ( Summary::iterator i = summary.begin(); i != summary.end(); ++i )
         s += vehicleTypeRepository.getObject_byID( i->first )->name + ": " + strrr(i->second) + "\n";

      tviewanytext vat ;
      vat.init ( "Cargo information", s.c_str(), 20, -1 , 450, 480 );
      vat.run();
      vat.done();
   }
}


void showSearchPath()
{

      ASCString s;
      for ( int i = 0; i < getSearchPathNum(); ++i )
         s += getSearchPath ( i ) + "\n"; 

      s += "\n";
      s += "Configuration file used: \n";
      s += getConfigFileName();

      tviewanytext vat ;
      vat.init ( "Search Path", s.c_str(), 20, -1 , 450, 480 );
      vat.run();
      vat.done();
}

#include "textfiletags.h"

static const char* paneName[5]  = { "information", "movement", "weapons", "transport", "description" };

class UnitInfoDialog : public Panel {
        const Vehicle* veh;
        const Vehicletype* vt;
        PG_Widget* weaponGraph;
        int currentWeapon;
        typedef vector< pair<int,int> > EntranceHeights;
        EntranceHeights entranceHeights;
        Surface infoImage;

         void registerSpecialDisplay( const ASCString& name )
         {
            SpecialDisplayWidget* sdw = dynamic_cast<SpecialDisplayWidget*>( FindChild( name, true ) );
            if ( sdw )
               sdw->display.connect( SigC::slot( *this, &UnitInfoDialog::painter ));
         };

         void registerSpecialInput( const ASCString& name )
         {
            SpecialInputWidget* siw = dynamic_cast<SpecialInputWidget*>( FindChild( name, true ) );
            if ( siw )
               siw->sigMouseButtonDown.connect( SigC::slot( *this, &UnitInfoDialog::onClick ));
         };

         bool onClick ( PG_MessageObject* obj, const SDL_MouseButtonEvent* event ) {
            PG_Widget* w = dynamic_cast<PG_Widget*>(obj);
            if ( w ) {
               click( w->GetName() );
               return true;
            } 
            return false;
         };

         bool onEntranceClick ( PG_MessageObject* obj, const SDL_MouseButtonEvent* event, int entranceNum ) {
            if ( vt ) {
               PG_Widget* swi = FindChild( "single_weapon_info", true );
               if ( swi ) {
                  ContainerBaseType::TransportationIO tio = vt->entranceSystems[entranceNum];
                  setWidgetTransparency( "pad_transport_in",      tio.mode & ContainerBaseType::TransportationIO::In      ? 0 : 255 );
                  setWidgetTransparency( "pad_transport_out",     tio.mode & ContainerBaseType::TransportationIO::Out     ? 0 : 255 );
                  setWidgetTransparency( "pad_transport_docking", tio.mode & ContainerBaseType::TransportationIO::Docking ? 0 : 255 );

                  for ( int i = 0; i < cmovemalitypenum; ++i )
                     if ( (vt->vehicleCategoriesStorable & (1<<i)) && (tio.vehicleCategoriesLoadable & (1<<i)))
                        setImage( ASCString("unitpad_transport_") + unitCategoryTags[i], IconRepository::getIcon("pad_symbol_ok.png") );
                     else
                        setImage( ASCString("unitpad_transport_") + unitCategoryTags[i], IconRepository::getIcon("pad_symbol_no.png") );

                  ASCString s;
                  for ( int i = 0; i < cvehiclefunctionsnum; ++i )
                     if ( tio.requireUnitFunction & (1 << i)) {
                        if ( s.length() )
                           s += ", ";
                        s += cvehiclefunctions[i];
                     }
                  setLabelText( "unitpad_transport_specialfunctions", s );

                  setLabelText( "unitpad_transport_attackafterwards", tio.disableAttack ? "no" : "yes" );

                  entranceHeights.clear();
                  for ( int i = 0; i < 8; ++i )
                     if ( vt->height & (1 << i) & tio.container_height )
                        for ( int j = 0; j < 8; ++j )
                           if ( !tio.height_abs || tio.height_abs & (1 <<j ))
                              if ( tio.height_rel == -100 || getheightdelta( i, j ) == tio.height_rel  )
                                 entranceHeights.push_back( make_pair(i,j)); 

                  PG_Widget* w = FindChild( "unitpad_transport_leveldisplay", true );
                  if ( w )
                     w->Update();
               }

               for ( int i = 0; i < vt->entranceSystems.size(); ++i ) {
                  ASCString n = "pad_transport_square" + ASCString::toString(i);
                  PG_Widget* w = FindChild( n, true );
                  if ( w ) {
                     if ( i == entranceNum ) 
                        w->SetTransparency( 0 );
                        // w->SetVisible(true );
                     else
                        w->SetTransparency( 255 );
                        // w->SetVisible(false  );
                     // w->Update();
                  }
               }
               Update();
            }
            return true;
         };

         bool onWeaponClick ( PG_MessageObject* obj, const SDL_MouseButtonEvent* event, int weaponNum ) {
            if ( vt ) {
               PG_Widget* swi = FindChild( "single_weapon_info", true );
               if ( swi )
                  assignWeaponInfo( this, swi, vt->weapons.weapon[weaponNum] );

               for ( int i = 0; i < vt->weapons.count; ++i ) {
                  ASCString n = "pad_weaponbar" + ASCString::toString(i);
                  PG_Widget* w = FindChild( n, true );
                  if ( w ) {
                     if ( i == weaponNum )
                        w->SetTransparency( 0 );
                        // w->SetVisible(true );
                     else
                        // w->SetVisible(false );
                        w->SetTransparency( 255 );
                     // w->Update();
                  }
               }
               Update();
               currentWeapon = weaponNum;
               if ( weaponGraph )
                  weaponGraph->Update();
            }
            return true;
         };

         SPoint getWeaponGraphCoords( int maxdist, int maxstrength, int dist, int strength )
         {
            const int border  = 0;
            SPoint p;
            if( maxdist < 2 )
               maxdist = 2;

            p.x = (weaponGraph->Width() - 2 * border ) * dist / maxdist + border;
            p.y = weaponGraph->Height() - border - (weaponGraph->Height() - 2 * border ) * strength / maxstrength ;
            p.x += weaponGraph->my_xpos;
            p.y += weaponGraph->my_ypos;
            return p;
         }

         void painter ( const PG_Rect &src, const ASCString& name, const PG_Rect &dst)
         {
            Surface screen = Surface::Wrap( PG_Application::GetScreen() );

            if ( name == "unitpad_unitsymbol" ) 
               if ( vt )
                  vt->paint( screen, SPoint( dst.x, dst.y ), veh ? veh->getOwner() : 0 );

            if ( name == "unitpad_weapon_diagram" ) {
               if ( vt && weaponGraph ) {
                  int maxdist  = 0;
                  int maxstrength = 0;
                  for ( int i = 0; i < vt->weapons.count; ++i )
                     if ( vt->weapons.weapon[i].shootable() ) {
                        maxdist = max ( maxdist, vt->weapons.weapon[i].maxdistance );
                        maxstrength = max ( maxstrength, vt->weapons.weapon[i].maxstrength );
                     }

                  setLabelText( "unitpad_weapon_diagram_maxdist", maxdist / maxmalq );
                  setLabelText( "unitpad_weapon_diagram_maxstrength", maxstrength );

                  if( maxdist > 0 && maxstrength > 0 )
                     for ( int i = 0; i < vt->weapons.count; ++i ) {
                        int mind = (vt->weapons.weapon[i].mindistance+maxmalq-1) / maxmalq;
                        int maxd = vt->weapons.weapon[i].maxdistance / maxmalq;
                        int linewidth = currentWeapon == i ? 2 : 1 ;
                        if ( mind == maxd ) {
                           SPoint p = getWeaponGraphCoords( maxdist/maxmalq, maxstrength, mind, vt->weapons.weapon[i].maxstrength );
                           PG_Draw::DrawLine( PG_Application::GetScreen(), p.x , p.y - 2, p.x , p.y + 2, 0xffffff, linewidth );
                           PG_Draw::DrawLine( PG_Application::GetScreen(), p.x - 2, p.y , p.x + 2, p.y , 0xffffff, linewidth );
                        } else {
                           SPoint p = getWeaponGraphCoords( maxdist/maxmalq, maxstrength, mind, vt->weapons.weapon[i].maxstrength );
                           SPoint p2 = getWeaponGraphCoords( maxdist/maxmalq, maxstrength, maxd, vt->weapons.weapon[i].minstrength );
                           PG_Draw::DrawLine( PG_Application::GetScreen(), p.x , p.y , p2.x, p2.y , 0xffffff, linewidth );
                        }
                     }
               }
            }
            if ( name == "unitpad_transport_transporterlevel" || name == "unitpad_transport_unitlevel" ) {
               int xoffs = 0;
               for ( EntranceHeights::iterator i = entranceHeights.begin(); i != entranceHeights.end(); ++i ) {
                  Surface& icon = IconRepository::getIcon( ASCString("height-a") + ASCString::toString( name == "unitpad_transport_unitlevel" ? i->second : i->first) + ".png");
                  screen.Blit( icon, SPoint( dst.x + xoffs, dst.y ));
                  xoffs += icon.w() + 5;
               }
            }
         };

         void activate( const ASCString& pane ) {
            PG_Application::SetBulkMode();
            for ( int i = 0; i < 5; ++i )
                if ( ASCString( paneName[i]) != pane )
                   hide( paneName[i] );
                   
            for ( int i = 0; i < 5; ++i )
                if ( ASCString( paneName[i]) == pane )
                   show( paneName[i] );
            PG_Application::SetBulkMode(false);
            Update();
         };

         void click( const ASCString& name ) {
            for ( int i = 0; i < 5; ++i)
               if ( name == ASCString("padclick_") + paneName[i] ) 
                  activate(paneName[i]);
            if ( name == "padclick_exit" )
               QuitModal();
         };

     public:
        
        
        UnitInfoDialog (PG_Widget *parent, const Vehicle* vehicle, const Vehicletype* vehicleType ) 
           : Panel( parent, PG_Rect::null, "UnitInfoDialog", false ), veh(vehicle), vt( vehicleType ), weaponGraph(NULL), currentWeapon(-1) {
               sigClose.connect( SigC::slot( *this, &UnitInfoDialog::QuitModal ));

               if( veh )
                  vt = veh->typ;

               try {
                  setup();
               }
               catch ( ParsingError err ) {
                  displaymessage( err.getMessage(), 1 );
                  return;
               }
               catch ( ... ) {
                  displaymessage( "unknown exception", 1 );
                  return;
               }

               if ( !vt->infoImageFilename.empty() && exist( vt->infoImageFilename )) {
                  PG_Image* img = dynamic_cast<PG_Image*>(FindChild( "picture" ));
                  if ( img ) {
                     tnfilestream stream ( vt->infoImageFilename, tnstream::reading );
                     infoImage.readImageFile( stream );
                     img->SetDrawMode( PG_Draw::STRETCH );
                     img->SetImage( infoImage.getBaseSurface(), false );
                  }
               }

               if ( veh )
                  setLabelText( "unitpad_unitname", veh->getName() );
               else
                  if ( vt )
                     setLabelText( "unitpad_unitname", vt->getName() );

               setLabelText( "unitpad_unitcategory", cmovemalitypes[ vt->movemalustyp ] );
               registerSpecialDisplay( "unitpad_unitsymbol");
               registerSpecialDisplay( "unitpad_weapon_diagram");
               registerSpecialDisplay( "unitpad_transport_transporterlevel");
               registerSpecialDisplay( "unitpad_transport_unitlevel");
               weaponGraph = FindChild( "unitpad_weapon_diagram", true );

               if ( vt ) {
                  setLabelText( "unitpad_unitarmor", vt->armor );
                  setLabelText( "unitpad_unitweight", vt->weight );
                  setLabelText( "unitpad_unitview", vt->view );
                  setLabelText( "unitpad_unitjamming", vt->jamming );
                  setLabelText( "unitpad_unitcostenergy", vt->productionCost.energy );
                  setLabelText( "unitpad_unitcostmaterial", vt->productionCost.material );
                  setLabelText( "unitpad_unitcostfuel", vt->productionCost.fuel );
                  setLabelText( "unitpad_unittankfuel", vt->tank.fuel );
                  setLabelText( "unitpad_unittankenergy", vt->tank.energy );
                  setLabelText( "unitpad_unittankmaterial", vt->tank.material );

                  ASCString abilities;
                  for ( int i = 0; i < cvehiclefunctionsnum; ++i )
                     if ( vt->functions & (1 << i)) 
                        abilities += cvehiclefunctions[i] + ASCString("\n");
                  setLabelText( "unitpad_unitabilities", abilities );


                  setLabelText( "unitpad_unitmove_unitfuelconsumption", vt->fuelConsumption );
                  for ( int i = 0; i< 8; ++i )
                     setLabelText( ASCString("unitpad_unitmove_") + heightTags[i], vt->movement[i] );

                  if ( vt->maxwindspeedonwater < 255 && vt->maxwindspeedonwater > 0 )
                     setLabelText( "unitpad_unitmove_windresistance", vt->maxwindspeedonwater );
                  else
                     setLabelText( "unitpad_unitmove_windresistance", "-" );

                  setLabelText( "unitpad_transport_maxtotalweight", vt->maxLoadableWeight );
                  setLabelText( "unitpad_transport_maxsingleweight", vt->maxLoadableUnitSize );
                  setLabelText( "unitpad_transport_loadableunits", vt->maxLoadableUnits );


               }




               for ( int i = 0; i < 5; ++i )
                  registerSpecialInput( ASCString("padclick_") + paneName[i] );
               registerSpecialInput( "padclick_exit" );

               setLabelText( "unitpad_description_text", vt->infotext );
               
              activate(paneName[0]);
               
           };

      void userHandler( const ASCString& label, PropertyReadingContainer& pc, PG_Widget* parent, WidgetParameters widgetParams ) 
      {
         if ( label == "unitpad_heightchange" && vt ) {
            int yoffset = 0;
            for ( int i = 0; i < vt->heightChangeMethodNum; ++i ) {
               int srcLevelCount = 0;
               for ( int j = 0; j < 8; ++j )
                  if ( vt->height & vt->heightChangeMethod[i].startHeight & (1 << j)) 
                     ++srcLevelCount;

               pc.openBracket( "LineWidget" );
               PG_Rect r = parseRect( pc, parent);
               r.y += yoffset;
               r.my_height *= (srcLevelCount-1) / 3 + 1;

               SpecialInputWidget* sw = new SpecialInputWidget ( parent, r );
               parsePanelASCTXT( pc, sw, widgetParams );
               pc.closeBracket();
               yoffset += sw->Height();



               int xoffs = 0;
               int yoffs = 0;
               int counter = 0;
               for ( int j = 0; j < 8; ++j )
                  if ( vt->height & vt->heightChangeMethod[i].startHeight & (1 << j))  {
                     ASCString filename = "height-a" + ASCString::toString(j) + ".png";
                     xoffs = IconRepository::getIcon(filename).w() * (counter % 3 );
                     yoffs = IconRepository::getIcon(filename).h() * (counter / 3 );
                     new PG_Image( sw, PG_Point( xoffs, yoffs ), IconRepository::getIcon(filename).getBaseSurface(), false );
                     ++counter;
                  }

               ASCString delta = ASCString::toString( vt->heightChangeMethod[i].heightDelta );
               if ( vt->heightChangeMethod[i].heightDelta > 0 )
                  delta = "+" + delta;
               setLabelText( "unitpad_move_changeheight_change", delta, sw );
               
               setLabelText( "unitpad_move_changeheight_movepoints", vt->heightChangeMethod[i].moveCost, sw );
               setLabelText( "unitpad_move_changeheight_distance", vt->heightChangeMethod[i].dist, sw );
            }
         }
         if ( label == "unitpad_terrainaccess" && vt ) {
            int yoffset = 0;
            for ( int i = 0; i < cbodenartennum ; ++i ) {
               if ( vt->terrainaccess.terrain.test(i) || vt->terrainaccess.terrainkill.test(i) || vt->terrainaccess.terrainnot.test(i) || vt->terrainaccess.terrainreq.test(i) ) {
                  pc.openBracket( "LineWidget" );
                  PG_Rect r = parseRect( pc, parent);
                  r.y += yoffset;

                  
                  SpecialInputWidget* sw = new SpecialInputWidget ( parent, r );
                  parsePanelASCTXT( pc, sw, widgetParams );
                  pc.closeBracket();
                  yoffset += sw->Height();

                  setLabelText( "unitpad_unitmove_terraintype", cbodenarten[i], sw);

                  PG_Widget* w = sw->FindChild("unitpad_unitmove_terrainaccess", true);
                  if ( w ) {
                     int xoffs = 0;
                     static const char* iconName[] = {"pad_symbol_ok.png", "pad_symbol_warn.png", "pad_symbol_no.png", "pad_symbol_kill.png" };  
                     const TerrainBits* bits[] = { &vt->terrainaccess.terrain, &vt->terrainaccess.terrainreq, &vt->terrainaccess.terrainnot, &vt->terrainaccess.terrainkill };
                     for ( int icon = 0; icon < 4; ++icon ) {
                        bool set = bits[icon]->test(i);

                        if ( set ) {
                           PG_Image* img = new PG_Image( w, PG_Point( xoffs, 0 ), IconRepository::getIcon( iconName[icon] ).getBaseSurface(), false );
                           xoffs += img->Width();
                        }
                     }
                  }
               }
            }
         }
         if ( label == "unitpad_weaponlist" && vt ) {
            int yoffset = 0;
            for ( int i = 0; i < vt->weapons.count ; ++i ) {
               pc.openBracket( "LineWidget" );
               PG_Rect r = parseRect( pc, parent);
               r.y += yoffset;

               
               SpecialInputWidget* sw = new SpecialInputWidget ( parent, r );
               parsePanelASCTXT( pc, sw, widgetParams );
               rename( "pad_weaponbar", "pad_weaponbar" + ASCString::toString( i ));
               pc.closeBracket();
               yoffset += sw->Height();

               assignWeaponInfo( this, sw, vt->weapons.weapon[i] );
               sw->sigMouseButtonDown.connect( SigC::bind( SigC::slot( *this, &UnitInfoDialog::onWeaponClick ), i));
            }
         }
         if ( label == "entrancesystems" && vt ) {
            int xoffset = 0;
            for ( int i = 0; i < vt->entranceSystems.size() ; ++i ) {
               pc.openBracket( "LineWidget" );
               PG_Rect r = parseRect( pc, parent);
               r.x += xoffset;

               SpecialInputWidget* sw = new SpecialInputWidget ( parent, r );
               parsePanelASCTXT( pc, sw, widgetParams );
               rename( "pad_transport_square", "pad_transport_square" + ASCString::toString( i ));
               pc.closeBracket();

               setLabelText( "unitpad_transport_entrancenumber", i+1, sw );

               xoffset += sw->Width();

               // assignWeaponInfo( this, sw, vt->weapons.weapon[i] );
               sw->sigMouseButtonDown.connect( SigC::bind( SigC::slot( *this, &UnitInfoDialog::onEntranceClick ), i));
            }
         }
      }; 
        
};



// user actions using the old event system
void execuseraction ( tuseractions action )
{
   switch ( action ) {
      case ua_repainthard  :
      case ua_repaint      :
         repaintdisplay();
         break;

      case ua_help         :
         help(20);
         break;

      case ua_howtostartpbem :
         help(21);
         break;

      case ua_howtocontinuepbem :
         help(22);
         break;

      case ua_dispvehicleimprovement    :
      /*
         displaymessage("Research:\n%s %d \n%s %d \n%s %d \n"
                        "%s %d \n%s %d \n%s %d \n"
                        "%s %d \n%s %d \n%s %d \n"
                        "%s %d",1,
                        cwaffentypen[0], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[0]),
                        cwaffentypen[1], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[1]),
                        cwaffentypen[2], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[2]),
                        cwaffentypen[3], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[3]),
                        cwaffentypen[4], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[4]),
                        cwaffentypen[5], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[5]),
                        cwaffentypen[6], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[6]) ,
                        cwaffentypen[7], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[7])  ,
                        cwaffentypen[10], (actmap->player[actmap->actplayer].research.unitimprovement.weapons[10])     ,
                        "armor",         (actmap->player[actmap->actplayer].research.unitimprovement.armor));
                        */
         break;

      case ua_mainmenu:
         if (choice_dlg("do you really want to close the current game ?","~y~es","~n~o") == 1) {
            delete actmap;
            actmap = NULL;
            throw NoMapLoaded();
         }
         break;
/*
      case ua_mntnc_morefog:
         if (actmap->weather.fog < 255   && maintainencecheck() ) {
            actmap->weather.fog++;
            computeview( actmap );
            displaymessage2("fog intensity set to %d ", actmap->weather.fog);
            displaymap();
         }
         break;

      case ua_mntnc_lessfog:
         if (actmap->weather.fog  && maintainencecheck()) {
            actmap->weather.fog--;
            computeview( actmap );
            displaymessage2("fog intensity set to %d ", actmap->weather.fog);
            displaymap();
         }
         break;

      case ua_mntnc_morewind:
         if ((actmap->weather.windSpeed < 254) &&  maintainencecheck()) {
            actmap->weather.windSpeed+=2;
            displaywindspeed (  );
            updateFieldInfo();
         }
         break;

      case ua_mntnc_lesswind:
         if ((actmap->weather.windSpeed > 1)  && maintainencecheck() ) {
            actmap->weather.windSpeed-=2;
            displaywindspeed (  );
            updateFieldInfo();
         }
         break;

      case ua_mntnc_rotatewind:
         if ( maintainencecheck() ) {
            if (actmap->weather.windDirection < sidenum-1 )
               actmap->weather.windDirection++;
            else
               actmap->weather.windDirection = 0;
            displaymessage2("wind dir set to %d ", actmap->weather.windDirection);
            updateFieldInfo();
            displaymap();
         }
         break;
*/
      case ua_changeresourceview:
         showresources++;
         if ( showresources >= 3 )
            showresources = 0;
         displaymap();
         break;

      case ua_benchgamewov:
         benchMapDisplay();
         // benchgame( 0 );
         break;

      case ua_benchgamewv :
         benchgame( 1 );
         break;

      case ua_viewterraininfo:
         viewterraininfo();
         break;

      case ua_writemaptopcx :
         // writemaptopcx ();
         break;

      case ua_writescreentopcx:
         {
            char* nm = getnextfilenumname ( "screen", "pcx", 0 );
            writepcx ( nm, 0, 0, agmp->resolutionx-1, agmp->resolutiony-1, pal );
            displaymessage2( "screen saved to %s", nm );
         }
         break;

      case ua_startnewsinglelevel:
         startnewsinglelevelfromgame();
         break;

      case ua_changepassword:
         {
            bool success;
            do {
               Password oldpwd = actmap->player[actmap->actplayer].passwordcrc;
               actmap->player[actmap->actplayer].passwordcrc.reset();
               success = enterpassword ( actmap->player[actmap->actplayer].passwordcrc, true, true );
               if ( !success )
                  actmap->player[actmap->actplayer].passwordcrc = oldpwd;
            } while ( actmap->player[actmap->actplayer].passwordcrc.empty() && success && viewtextquery ( 910, "warning", "~e~nter password", "~c~ontinue without password" ) == 0 ); /* enddo */
         }
         break;

      case ua_gamepreferences:
         gamepreferences();
         break;

      case ua_mousepreferences:
         mousepreferences();
         break;

      case ua_bi3preferences:
         bi3preferences();
         break;

      case ua_exitgame:
         if (choice_dlg("do you really want to quit ?","~y~es","~n~o") == 1)
            getPGApplication().Quit();
         break;

      case ua_newcampaign:
         newcampaign();
         computeview( actmap );
         displaymap();
         break;

      case ua_loadgame:
         loadGame();
         break;

      case ua_savegame:
         saveGame( true );
         break;

      case ua_setupalliances:
         setupalliances();
         logtoreplayinfo ( rpl_alliancechange );
         logtoreplayinfo ( rpl_shareviewchange );

         if ( actmap->shareview && actmap->shareview->recalculateview ) {
            logtoreplayinfo ( rpl_shareviewchange );
            computeview( actmap );
            actmap->shareview->recalculateview = 0;
            displaymap();
         }
         updateFieldInfo();
         break;

      case ua_settribute :
         settributepayments ();
         break;

      case ua_giveunitaway:
         if ( actmap && actmap->getgameparameter( cgp_disableUnitTransfer ) == 0 )
            giveunitaway ( actmap->getField( actmap->getCursor() ));
         else
            displaymessage("Sorry, this function has been disabled when starting the map!", 1 );
         break;
      case ua_renameunit:
         renameUnit();
         break;

      case ua_researchinfo:
         researchinfo ();
         break;

      case ua_unitstatistics:
         statisticarmies();
         break;

      case ua_buildingstatistics:
         statisticbuildings();
         break;

      case ua_newmessage:
         newmessage();
         break;

      case ua_viewqueuedmessages:
         viewmessages( "queued messages", actmap->unsentmessage, 1, 0 );
         break;

      case ua_viewsentmessages:
         viewmessages( "sent messages", actmap->player[ actmap->actplayer ].sentmessage, 0, 0 );
         break;

      case ua_viewreceivedmessages:
         viewmessages( "received messages", actmap->player[ actmap->actplayer ].oldmessage, 0, 1 );
         break;

      case ua_viewjournal:
         viewjournal();
         break;

      case ua_editjournal:
         editjournal();
         break;

      case ua_viewaboutmessage:
         {
            help(30);
            tviewanytext vat;
            ASCString s = getstartupmessage();

#ifdef _SDL_
            char buf[1000];
            SDL_version compiled;
            SDL_VERSION(&compiled);
            sprintf(buf, "\nCompiled with SDL version: %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
            s += buf;

            sprintf(buf, "Linked with SDL version: %d.%d.%d\n", SDL_Linked_Version()->major, SDL_Linked_Version()->minor, SDL_Linked_Version()->patch);
            s += buf;
#endif

            vat.init ( "about", s.c_str() );
            vat.run();
            vat.done();
         }
         break;

      case ua_continuenetworkgame:
         continuenetworkgame();
         displaymap();
         break;

      case ua_toggleunitshading:
         CGameOptions::Instance()->units_gray_after_move = !CGameOptions::Instance()->units_gray_after_move;
         CGameOptions::Instance()->setChanged();
         displaymap();
         while ( mouseparams.taste )
            releasetimeslice();

         if ( CGameOptions::Instance()->units_gray_after_move )
            displaymessage("units that can not move will now be displayed gray", 3);
         else
            displaymessage("units that can not move and cannot shoot will now be displayed gray", 3);
         break;

      case ua_computerturn:
         if ( maintainencecheck() || 1) {
            displaymessage("This function is under development and for programmers only\n"
                           "unpredictable things may happen ...",3 ) ;

            if (choice_dlg("do you really want to start the AI?","~y~es","~n~o") == 1) {

               if ( !actmap->player[ actmap->actplayer ].ai )
                  actmap->player[ actmap->actplayer ].ai = new AI ( actmap, actmap->actplayer );

               savegame ( "aistart.sav" );
               actmap->player[ actmap->actplayer ].ai->run();
            }
         }
         break;
      case ua_setupnetwork:
         if ( actmap->network )
            setupnetwork ( actmap->network );
         else
            displaymessage("This map is not played across a network",3 );
         break;
      case ua_selectgraphicset:
         selectgraphicset();
         break;
      case ua_UnitSetInfo:
         viewUnitSetinfo();
         break;
      case ua_GameParameterInfo:
         showGameParameters();
         break;
      case ua_viewunitweaponrange:
         viewunitweaponrange ( getSelectedField()->vehicle, ct_invvalue );
         break;

      case ua_viewunitmovementrange:
         viewunitmovementrange ( getSelectedField()->vehicle, ct_invvalue );
         break;

      case ua_aibench:
         if ( maintainencecheck() && 0 ) {
            if ( !actmap->player[ actmap->actplayer ].ai )
               actmap->player[ actmap->actplayer ].ai = new AI ( actmap, actmap->actplayer );

            if ( AI* ai = dynamic_cast<AI*>( actmap->player[ actmap->actplayer ].ai )) {
               savegame ( "ai-bench-start.sav" );
               ai->run( true );
            }
         }
         break;
      case ua_networksupervisor:
         networksupervisor();
         displaymap();
         break;

      case ua_selectPlayList:
         selectPlayList();
         break;
      case ua_statisticdialog:
         statisticDialog();
         break;

      case ua_showPlayerSpeed:
         showPlayerTime();
         break;
      case  ua_cancelResearch:
         if ( actmap->player[actmap->actplayer].research.activetechnology ) {
            ASCString s = "do you really want to cancel the current research project ?\n";
            // s += strrr ( actmap->player[actmap->actplayer].research.progress );
            // s += " research points will be lost.";
            if (choice_dlg(s.c_str(),"~y~es","~n~o") == 1) {
               actmap->player[actmap->actplayer].research.progress = 0;
               actmap->player[actmap->actplayer].research.activetechnology = NULL;
            }
         } else
            displaymessage("you are not researching anything", 3);
         break;
      case ua_showResearchStatus: {
            ASCString s;
            s += "Current technology:\n";
            if ( actmap->player[actmap->actplayer].research.activetechnology )
               s += actmap->player[actmap->actplayer].research.activetechnology->name;
            else
               s += " - none - ";
            s += "\n\n";

            s += "Research Points: \n";
            s += strrr( actmap->player[actmap->actplayer].research.progress );
            if ( actmap->player[actmap->actplayer].research.activetechnology )
               s += ASCString(" / ") + strrr ( actmap->player[actmap->actplayer].research.activetechnology->researchpoints );
            s += "\n\n";

            s+= "Research Points Plus \n";
            int p = 0;
            for ( Player::BuildingList::iterator i = actmap->player[actmap->actplayer].buildingList.begin(); i != actmap->player[actmap->actplayer].buildingList.end(); ++i )
               p += (*i)->researchpoints;


            s += strrr ( p );

            s += "\n\n";

            s+= "Developed Technologies: \n";
            for ( vector<int>::iterator i = actmap->player[actmap->actplayer].research.developedTechnologies.begin(); i != actmap->player[actmap->actplayer].research.developedTechnologies.end(); ++i ) {
               Technology* t = technologyRepository.getObject_byID( *i );
               if ( t )
                  s += t->name + "\n";
            }


            tviewanytext vat ;
            vat.init ( "Research Status", s.c_str(), 20, -1 , 450, 480 );
            vat.run();
            vat.done();
         }
         break;
      case ua_exportUnitToFile:
         if ( getSelectedField()->vehicle && getSelectedField()->vehicle->getOwner() == actmap->actplayer ){
            ASCString s = "do you really want to cut this unit from the game?";
            if (choice_dlg(s.c_str(),"~y~es","~n~o") == 1) {
               Vehicle* veh = getSelectedField()->vehicle;
               ClipBoard::Instance().clear();
               ClipBoard::Instance().addUnit( veh );

               ASCString filename;
               fileselectsvga(clipboardFileExtension, filename, false);
               if ( !filename.empty() ) {
                  tnfilestream stream ( filename, tnstream::writing );
                  ClipBoard::Instance().write( stream );
                  logtoreplayinfo ( rpl_cutFromGame, veh->networkid );
                  veh->prepareForCleanRemove();
                  delete veh;
                  computeview( actmap );
                  displaymap();
               }
            }
         }
         break;
      case ua_cargosummary: showCargoSummary();
         break;

      case ua_showsearchdirs: showSearchPath();
         break;

      };
}




// user actions using the new event system
void execuseraction2 ( tuseractions action )
{
   switch ( action ) {
   
      case ua_unitweightinfo:
         if ( fieldvisiblenow  ( getSelectedField() )) {
            Vehicle* eht = getSelectedField()->vehicle;
            if ( eht && getdiplomaticstatus ( eht->color ) == capeace )
               displaymessage(" weight of unit: \n basic: %d\n+cargo:%d\n= %d",1 ,eht->typ->weight, eht->cargo(), eht->weight() );
         }
         break;
      case ua_GameStatus:
         displaymessage ( "Current game time is:\n turn %d , move %d ", 3, actmap->time.turn(), actmap->time.move() );
         break;
      case ua_soundDialog:
          SoundSettings::soundSettings( NULL );
         break;
      case ua_reloadDlgTheme:
             getPGApplication().reloadTheme();
             SoundSettings::soundSettings( NULL );
         break;
      case ua_viewButtonPanel:  mainScreenWidget->spawnPanel( MainScreenWidget::ButtonPanel );
         break;
      case ua_viewWindPanel:     mainScreenWidget->spawnPanel( MainScreenWidget::WindInfo );
         break;
      case ua_clearImageCache:  IconRepository::clear();
         break;
      case ua_viewUnitInfoPanel: mainScreenWidget->spawnPanel( MainScreenWidget::UnitInfo );
         break;
      case ua_viewOverviewMapPanel: mainScreenWidget->spawnPanel( MainScreenWidget::OverviewMap );
         break;
      case ua_vehicleinfo: {
            pfield fld = actmap->getField( actmap->getCursor() );
            if ( fld && fld->vehicle ) {
               UnitInfoDialog* uid = new UnitInfoDialog( NULL, fld->vehicle, NULL );
               uid->Show();
               uid->RunModal();
               delete uid;
            }
         }
         break;
      case ua_weathercast: weathercast();
      break;
      default:
         break;
   }

}




void execUserAction_ev( tuseractions action )
{
   getPGApplication().enableLegacyEventHandling ( true );
   execuseraction( action );
   getPGApplication().enableLegacyEventHandling ( false );
   execuseraction2( action );
}




bool mainloopidle(  )
{
   if ( actmap ) {
      while ( actmap->player[ actmap->actplayer ].queuedEvents )
         checkevents( &getDefaultMapDisplay() );

      checktimedevents( &getDefaultMapDisplay() );

      checkforvictory();
   }
   return false;
}

void  mainloop2()
{
   displayLogMessage ( 4, "Spawning MainScreenWidget\n ");

   dataLoaderTicker();

   mainScreenWidget = new MainScreenWidget( getPGApplication());

   getPGApplication().setFullscreenImage( );
   getPGApplication().activateProgressBar( false, dataLoaderTicker );

   mainScreenWidget->Show();

   displayLogMessage ( 7, "Entering mainloop\n");
   
   getPGApplication().Run();
   displayLogMessage ( 7, "mainloop exited\n");
}

void  mainloop ( void )
{
   do {
      viewunreadmessages();
      activefontsettings.background=0;
      activefontsettings.length=50;
      activefontsettings.color=14;

      // mainloopgeneralmousecheck ( );

      /************************************************************************************************/
      /*        Pulldown Men?                                                                       . */
      /************************************************************************************************/

      while ( actmap->player[ actmap->actplayer ].queuedEvents )
         checkevents( &getDefaultMapDisplay() );

      checktimedevents( &getDefaultMapDisplay() );

      checkforvictory();

      releasetimeslice();

   }  while ( true );

}



pfont load_font ( const char* name )
{
   tnfilestream stream ( name , tnstream::reading );
   return loadfont ( &stream );
}



void loaddata( int resolx, int resoly, const char *gameToLoad=NULL )
{

   schriften.smallarial = load_font("smalaril.fnt");
   schriften.large = load_font("usablack.fnt");
   schriften.arial8 = load_font("arial8.fnt");
   schriften.smallsystem = load_font("msystem.fnt");
   schriften.guifont = load_font("gui.fnt");
   schriften.guicolfont = load_font("guicol.fnt");
   schriften.monogui = load_font("monogui.fnt");
  #if 0
   TTF_Init();
    tnfilestream fs( "C:\\Programme\\ascdev\\asc\\data\\dialog\\asc\\font.ttf", tnstream::reading );
    std::cout << fs.getLocation() << " size:" << fs.getSize() << std::endl; //Ausgabe stimmt
    SDL_RWops* ops = SDL_RWFromStream( &fs );
    if(!ops){//Ist false
       std::cout << "loading failed" << std::endl;
    }
    TTF_Font* myFont = TTF_OpenFontIndexRW(ops, 0, 14,0); //klappt nicht
    //SDL_RWclose(ops);
    /*std::FILE* filep = fopen(file.c_str(), "r");
    SDL_RWops* ops2 = SDL_RWFromFP( filep, 0 );
    myFont = TTF_OpenFontRW(ops2, 0, size);
    */
    //myFont = TTF_OpenFont(file.c_str(), size);
    if(0 == myFont){ //Wird betreten
       printf("TTF_OpenFontRW: %s\n", TTF_GetError());
    }
#endif

   dataLoaderTicker();

   GraphicSetManager::Instance().loadData();

   dataLoaderTicker();
   
   loadAllData();
  
   
   activefontsettings.markfont = schriften.guicolfont;
   shrinkfont ( schriften.guifont, -1 );
   shrinkfont ( schriften.guicolfont, -1 );
   shrinkfont ( schriften.monogui, -1 );
   pulldownfont = schriften.smallarial ;

   dataLoaderTicker();

   SoundList::init();

   dataLoaderTicker();

   loadMoreData();

   dataLoaderTicker();

   registerDataLoader ( new PlayListLoader() );
   registerDataLoader ( new BI3TranslationTableLoader() );

   

   loadUnitSets();

   loadStartupMap( gameToLoad );

   dataLoaderTicker();

   displayLogMessage ( 6, "done\n" );

   dataLoaderTicker();

 
   registerGuiFunctions( GuiFunctions::primaryGuiIcons );
}





//! A Paragui widget that fills the whole screen and redraws it whenever Paragui wants to it.


void runmainmenu ( void )
{
/*
   MainMenuPullDown pd;
   pd.init();
   backgroundpict.paint();
   pd.baron();
   // loadFullscreenImage ( "title.jpg" );

   do {
      tkey ch = ct_invvalue;
      if (keypress()) {
         ch = r_key();

         switch (ch) {
            case ct_f3:
               execuseraction ( ua_continuenetworkgame );
               break;
            case 'R':
               execuseraction ( ua_repainthard );
               break;
            case ct_stp + ct_l:
               execuseraction ( ua_loadgame );
               break;
            case ct_stp + ct_n:
               execuseraction ( ua_startnewsinglelevel );
               break;
            case ct_x + ct_stp:
               execuseraction ( ua_exitgame );
               break;
         };
      }

      pd.key = ch;
      pd.checkpulldown();

      if (pd.action2execute >= 0 ) {
         tuseractions ua = (tuseractions) pd.action2execute;
         pd.action2execute = -1;
         execuseraction ( ua );
         pd.redraw();
      }

      releasetimeslice();
   } while ( !actmap  ); 
*/
}



struct GameThreadParams
{
   ASCString filename;
   ASC_PG_App& application;
   GameThreadParams( ASC_PG_App& app ) : application ( app ){};
};

int gamethread ( void* data )
{
   GameThreadParams* gtp = (GameThreadParams*) data;

   loadpalette();

   int resolx = agmp->resolutionx;
   int resoly = agmp->resolutiony;
   virtualscreenbuf.init();

   try {
      getPGApplication().activateProgressBar( true, dataLoaderTicker );
      getPGApplication().setFullscreenImage( "title.jpg" );
      loaddata( resolx, resoly, gtp->filename.c_str() );
   }
   catch ( ParsingError err ) {
      displaymessage ( "Error parsing text file " + err.getMessage(), 2 );
   }
   catch ( tfileerror err ) {
      displaymessage ( "Error loading file " + err.getFileName(), 2 );
   }
   catch ( ASCexception ) {
      displaymessage ( "loading of game failed", 2 );
   }
   catch ( ... ) {
      displaymessage ( "caught undefined exception", 2 );
   }

   displayLogMessage ( 5, "loaddata completed successfully.\n" );
   setvgapalette256(pal);


   displayLogMessage ( 5, "starting music..." );
   startMusic();
   displayLogMessage ( 5, " done \n" );

   onlinehelp = new tsgonlinemousehelp;
   onlinehelpwind = new tsgonlinemousehelpwind;

   gameStartupComplete = true;

   repaintDisplay.connect( repaintMap );

   displayLogMessage ( 5, "entering outer main loop.\n" );
   do {
      try {
         if ( !actmap || actmap->xsize <= 0 || actmap->ysize <= 0 ) {
            displayLogMessage ( 8, "gamethread :: starting main menu.\n" );
            runmainmenu();
         } else {
            if ( actmap->actplayer == -1 ) {
               displayLogMessage ( 8, "gamethread :: performing next_turn..." );
               next_turn();
               displayLogMessage ( 8, "done.\n" );
            }

            displayLogMessage ( 8, "gamethread :: Painting background pict..." );

            if ( !gtp->filename.empty() && patimat ( tournamentextension, gtp->filename.c_str() ) ) {
               displayLogMessage ( 5, "Initializing network game..." );
               initNetworkGame ( );
               displayLogMessage ( 5, "done\n" );
            }

            displayLogMessage ( 8, "gamethread :: displaying map..." );
            // displaymap();
            displayLogMessage ( 8, "done.\n" );

            moveparams.movestatus = 0;

            displayLogMessage ( 8, "gamethread :: painting gui icons..." );
            // actgui->painticons();
            displayLogMessage ( 8, "done.\n" );
            mousevisible(true);

            updateFieldInfo();

            displayLogMessage ( 5, "entering inner main loop.\n" );
            mainloop2();
            mousevisible ( false );
         }
      } /* endtry */
      catch ( NoMapLoaded ) { } /* endcatch */
      catch ( LoadNextMap lnm ) {
         if ( actmap->campaign ) {
            startnextcampaignmap( lnm.id );
         } else {
           viewtext2(904);
           if (choice_dlg("Do you want to continue playing ?","~y~es","~n~o") == 2) {
              delete actmap;
              actmap = NULL;
           } else {
              actmap->continueplaying = 1;
              if ( actmap->replayinfo ) {
                 delete actmap->replayinfo;
                 actmap->replayinfo = NULL;
              }
           }
         }
      }
   } while ( false );
   return 0;
}


// including the command line parser, which is generated by genparse
#include "clparser/asc.cpp"

int main(int argc, char *argv[] )
{
   assert ( sizeof(PointerSizedInt) == sizeof(int*));

   Cmdline* cl = NULL;
   auto_ptr<Cmdline> apcl ( cl );
   try {
      cl = new Cmdline ( argc, argv );
   } catch ( string s ) {
      cerr << s.c_str();
      exit(1);
   }

   /*
   if ( cl->next_param() < argc ) {
      cerr << "invalid command line parameter\n";
      exit(1);
   }*/

   if ( cl->v() ) {
      ASCString msg = getstartupmessage();
      printf( msg.c_str() );
      exit(0);
   }

   if ( cl->w() )
      fullscreen = SDL_FALSE;

   if ( cl->f() )
      fullscreen = SDL_TRUE;

   verbosity = cl->r();

   displayLogMessage( 1, getstartupmessage() );

   initFileIO( cl->c().c_str() );  // passing the filename from the command line options

   try {
      checkDataVersion();
      // check_bi3_dir ();
   } catch ( tfileerror err ) {
      displaymessage ( "unable to access file %s \n", 2, err.getFileName().c_str() );
   }
   catch ( ... ) {
      displaymessage ( "loading of game failed during pre graphic initializing", 2 );
   }

   if ( CGameOptions::Instance()->forceWindowedMode && !cl->f() )  // cl->f == force fullscreen command line param
      fullscreen = SDL_FALSE;

   SDLmm::Surface* icon = NULL;
   try {
      tnfilestream iconl ( "icon_asc.gif", tnstream::reading );
      SDL_Surface *icn = IMG_Load_RW ( SDL_RWFromStream( &iconl ), 1);
      SDL_SetColorKey(icn, SDL_SRCCOLORKEY, *((Uint8 *)icn->pixels));
      icon = new SDLmm::Surface ( icn );
   } catch ( ... ) {}


   int xr = 800;
   int yr = 600;
   // determining the graphics resolution
   if ( CGameOptions::Instance()->xresolution != 800 )
      xr = CGameOptions::Instance()->xresolution;
   if ( cl->x() != 800 )
      xr = cl->x();

   if ( CGameOptions::Instance()->yresolution != 600 )
      yr = CGameOptions::Instance()->yresolution;
   if ( cl->y() != 600 )
      yr = cl->y();


   SoundSystem soundSystem ( CGameOptions::Instance()->sound.muteEffects, CGameOptions::Instance()->sound.muteMusic, cl->q() || CGameOptions::Instance()->sound.off );

   soundSystem.setMusicVolume ( CGameOptions::Instance()->sound.musicVolume );
   soundSystem.setEffectVolume ( CGameOptions::Instance()->sound.soundVolume );

   

   ASC_PG_App app ( "asc2_dlg" );
//   app.sigKeyUp.connect( SigC::slot(&GameDialog::gameDialog ));

   app.sigAppIdle.connect ( SigC::slot( mainloopidle ));


   int flags = SDL_SWSURFACE;
   if ( fullscreen )
      flags |= SDL_FULLSCREEN;


   SDL_WM_SetIcon( icon->GetSurface(), NULL );
   app.InitScreen( xr, yr, 32, flags);
  
//   initASCGraphicSubsystem ( app.GetScreen(), icon );

   
   setWindowCaption ( "Advanced Strategic Command" );
      
   GameThreadParams gtp ( app );
   gtp.filename = cl->l();

   if ( cl->next_param() < argc )
      for ( int i = cl->next_param(); i < argc; i++ )
         gtp.filename = argv[i];


   {
      int w;
      tnfilestream stream ("mausi.raw", tnstream::reading);
      stream.readrlepict(   &icons.mousepointer, false, &w );
   }


   try {
      // this starts the gamethread procedure, whichs will run the entire game
      initializeEventHandling ( gamethread, &gtp, icons.mousepointer );
   }
   catch ( bad_alloc ) {
      fatalError ("Out of memory");
   }

   closegraphics();

   delete actmap;
   actmap = NULL;
   
   writegameoptions ( );

   delete onlinehelp;
   onlinehelp = NULL;

   delete onlinehelpwind;
   onlinehelpwind = NULL;

#ifdef MEMCHK
   verifyallblocks();
#endif

   #ifdef NO_PARAGUI
   SDL_Quit();
   #endif

   return(0);
}

