//     $Id: edglobal.cpp,v 1.25 2001-01-21 16:37:16 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.24  2000/12/26 21:04:34  mbickel
//      Fixed: putimageprt not working (used for small map displaying)
//      Fixed: mapeditor crashed on generating large maps
//
//     Revision 1.23  2000/11/29 11:05:27  mbickel
//      Improved userinterface of the mapeditor
//      map::preferredfilenames uses now strings (instead of char*)
//
//     Revision 1.22  2000/11/29 09:40:19  mbickel
//      The mapeditor has now two maps simultaneously active
//      Moved memorychecking functions to its own file: memorycheck.cpp
//      Rewrote password handling in ASC
//
//     Revision 1.21  2000/10/18 14:14:06  mbickel
//      Rewrote Event handling; DOS and WIN32 may be currently broken, will be
//       fixed soon.
//
//     Revision 1.20  2000/10/14 14:16:04  mbickel
//      Cleaned up includes
//      Added mapeditor to win32 watcom project
//
//     Revision 1.19  2000/10/11 14:26:30  mbickel
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
//     Revision 1.18  2000/08/12 12:52:46  mbickel
//      Made DOS-Version compile and run again.
//
//     Revision 1.17  2000/08/06 11:39:03  mbickel
//      New map paramter: fuel globally available
//      Mapeditor can now filter buildings too
//      Fixed unfreed memory in fullscreen image loading
//      Fixed: wasted cpu cycles in building
//      map parameters can be specified when starting a map
//      map parameters are reported to all players in multiplayer games
//
//     Revision 1.16  2000/08/02 15:52:55  mbickel
//      New unit set definition files
//      demount accepts now more than one container file
//      Unitset information dialog added
//
//     Revision 1.15  2000/07/31 18:02:53  mbickel
//      New configuration file handling
//      ASC searches its data files in all directories specified in ascrc
//      Renamed all tools so they begin with asc
//
//     Revision 1.14  2000/07/29 14:54:25  mbickel
//      plain text configuration file implemented
//
//     Revision 1.13  2000/06/28 19:26:15  mbickel
//      fixed bug in object generation by building removal
//      Added artint.cpp to makefiles
//      Some cleanup
//
//     Revision 1.12  2000/05/11 20:12:05  mbickel
//      mapedit(lin) can now import BI3 maps
//
//     Revision 1.11  2000/05/10 19:55:49  mbickel
//      Fixed empty loops when waiting for mouse events
//
//     Revision 1.10  2000/04/27 16:25:21  mbickel
//      Attack functions cleanup
//      New vehicle categories
//      Rewrote resource production in ASC resource mode
//      Improved mine system: several mines on a single field allowed
//      Added unitctrl.* : Interface for vehicle functions
//        currently movement and height change included
//      Changed timer to SDL_GetTicks
//
//     Revision 1.9  2000/04/01 11:38:37  mbickel
//      Updated the small editors
//      Added version numbering
//
//     Revision 1.8  2000/03/16 14:06:54  mbickel
//      Added unitset transformation to the mapeditor
//
//     Revision 1.7  2000/03/11 18:22:04  mbickel
//      Added support for multiple graphic sets
//
//     Revision 1.6  2000/02/02 20:48:34  mbickel
//      Fixed bug in BI3 path verification
//
//     Revision 1.5  2000/01/04 19:43:51  mbickel
//      Continued Linux port
//
//     Revision 1.4  1999/12/29 12:50:43  mbickel
//      Removed a fatal error message in GUI.CPP
//      Made some modifications to allow platform dependant path delimitters
//
//     Revision 1.3  1999/12/27 12:59:52  mbickel
//      new vehicle function: each weapon can now be set to not attack certain
//                            vehicles
//
//     Revision 1.2  1999/11/16 03:41:33  tmwilson
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

#include <stdarg.h>
#include "global.h"
#include "vehicletype.h"
#include "buildingtype.h"
#include "edmisc.h"
#include "loadbi3.h"
#include "edevents.h"
#include "edgen.h"
#include "edselfnt.h"
#include "edglobal.h"
#include "gameoptions.h"

mc_check mc;


   const char* execactionnames[execactionscount] = {"End MapEdit","Help","Goto EditMode","Select terrain","Select unit",
      "Select color","Select building","Select special object","Select mine","Select weather","Setup alliances",
      "Toggle ResourceMode","Change UnitDirection","Asc-Resource Mode","Write Map2PCX","Load map",
      "Change players","New map","Goto PolygonMode","Rebuild Display","Open UnitInfo","View map","About",
      "Change GlobalDirection","Create resources","View/Change cargo","View/Change resources","Change TerrainDirection",
      "View/Change Events","Toggle Fillmode","Mapgenerator","Use active field values as selection","Delete active thing","Show palette",
      "View/Change minestrength","View/Change mapvalues","View/Change production","Save map","View/Change UnitValues",
      "Mirror CX-Pos","Mirror CY-Pos","Place terrain","Place Unit","Place building","Place special object","Place mine",
      "Place active thing","Delete Unit","Delete building","Delete special object","Delete mine","AboutBox","Save map as ...",
      "End PolygonMode","Smooth coasts","Import BI-Map","SEPERATOR","BI-Resource Mode","Insert BI map", "Set zoom level", 
      "Move Building", "set weather of whole map", "set map parameters", "terrain info", "set unit filter", "select graphic set",
      "unitset transformation", "Unitset Information", "switch maps"};


// �S Infomessage

int infomessage( char* formatstring, ... )
{
   char stringtooutput[200];
   char* b;
   char* a = formatstring;
   char* c = new char[200];
   char* d;
   // int linenum = 0;
   int i;

   memset (stringtooutput, 0, sizeof ( stringtooutput ));

   b = stringtooutput;

   va_list paramlist;
   va_start ( paramlist, formatstring );

   while (*a != 0) {
      if (*a == '%' ) {
         switch (a[1]) {
         case 'c': 
            *b = va_arg ( paramlist, char );
            b++;
            break;
         case 'd':
         case 'i':
         case 'u':
            i = va_arg ( paramlist, int );
            itoa ( i, c, 10 );
            i=0;
            while (c[i]) {
               *b = c[i];
               b++;
               i++;
            } /* endwhile */
            break;
         case 'o':
            i = va_arg ( paramlist, int );
            itoa ( i, c, 8 );
            i=0;
            while (c[i]) {
               *b = c[i];
               b++;
               i++;
            } /* endwhile */
            break;
         case 'p':
         case 'x':
            i = va_arg ( paramlist, int );
            itoa ( i, c, 16 );
            i=0;
            while (c[i]) {
               *b = c[i];
               b++;
               i++;
            } /* endwhile */
            break;
         case 'X':
            i = va_arg ( paramlist, int );
            itoa ( i, c, 16 );
            strupr ( c );
            i=0;
            while (c[i]) {
               *b = c[i];
               b++;
               i++;
            } /* endwhile */
            break;
         case 's':
            d = va_arg ( paramlist, char* );
            while (*d) {
               *b = *d;
               b++;
               d++;
            } /* endwhile */
            break;
         } /* endswitch */
         a+=2;
      } else {
         *b = *a;
         b++;
         a++;
      } /* endif */
   } /* endwhile */
   *b = 0;

   va_end ( paramlist );



   npush ( activefontsettings );
   activefontsettings.justify = lefttext;
   activefontsettings.font = schriften.smallarial;
   activefontsettings.color = lightgray;
   activefontsettings.markcolor = red;
   activefontsettings.background = 0;
   activefontsettings.length = agmp->resolutionx - ( 640 - 387);

   int yy = agmp->resolutiony - ( 480 - 450 );
   setinvisiblemouserectanglestk ( 37, yy, 37 + activefontsettings.length, yy + activefontsettings.font->height );
   showtext3c( stringtooutput, 37, yy );
   getinvisiblemouserectanglestk();

   npop( activefontsettings );

   if ( formatstring == NULL  ||  formatstring[0] == 0 )
      lastdisplayedmessageticker = 0xffffff;
   else
      lastdisplayedmessageticker = ticker;
   

   delete ( c );

   return ++actdisplayedmessage;
}

//�S MC_CHeck

void mc_check::on(void)
{
   if (mycursor.an == false ) {
      int ms = getmousestatus(); 
      if (ms == 1) { 		//mouse off
         if (mstatus == 0) mousevisible(true);
         else mstatus++;
      } else { 			//mouse on
         mstatus++;
      }
      if (cursor.an == false) {  //cursor off
         if (cstatus == 0) cursor.show();
         else cstatus++;
      } else { 			//cursor on
         cstatus++;
      } /* endif */
   }
}

void mc_check::off(void)
{
   if (mycursor.an == false ) {
      int ms = getmousestatus(); 
      if (ms == 1) { 		//mouse off
         mstatus--;
      } else { 			//mouse on
         if (mstatus == 0) mousevisible(false);
         else mstatus--;
      }
      if (cursor.an == false) {  	//cursor off
         cstatus--;
      } else { 			//cursor on
         if (cstatus == 0) cursor.hide();
         else cstatus--;
      } /* endif */
   }
}



class  GetString : public tdialogbox {
          public :
              int action;
              char* buf;
              void init(char* _title);
              virtual void run(void);
              virtual void buttonpressed(int id);
           };

void         GetString::init(char* _title)
{ 
   tdialogbox::init(); 
   title = _title; 
   x1 = 120; 
   xsize = 400; 
   y1 = 150; 
   ysize = 140; 
   action = 0; 

   windowstyle = windowstyle ^ dlg_in3d; 

   addbutton("~D~one",20,ysize - 40,100,ysize - 20,0,1,1,true); 
   addkey(1,ct_enter); 
   addbutton("~C~ancel",120,ysize - 40,200,ysize - 20,0,1,2,true); 
   addkey(2, ct_esc );

   addbutton("",20,60,xsize - 20,80,1,1,3,true); 
   addeingabe(3,buf,0,1000);

   buildgraphics(); 

   mousevisible(true); 
} 


void         GetString::run(void)
{ 
   if ( pcgo ) {
      delete pcgo;
      pcgo = NULL;
   }
   pbutton pb = firstbutton;
   while ( pb &&  (pb->id != 3)) 
      pb = pb->next;

   if ( pb )
      if ( pb->id == 3 )
         execbutton( pb , false );

   do { 
      tdialogbox::run(); 
   }  while ( !action ); 
} 


void         GetString::buttonpressed(int         id)
{ 
   tdialogbox::buttonpressed(id); 
   switch (id) {
      
      case 1:   
      case 2:   action = id; 
   break; 
   } 
} 


char*    getstring( char*  title, char* orgval )

{ 
   GetString     gi;

   gi.buf = orgval;
   gi.init( title );
   gi.run();
   gi.done();
   if ( gi.action == 2 )
      return NULL;
   else
      return gi.buf;
} 

char* getbipath ( void )
{
   char filename[1000];
   if ( getbi3path() )
      strcpy ( filename, getbi3path() );
   else
      filename[0] = 0;

   char filename2[1000];
   strcpy ( filename2, filename );
   appendbackslash( filename2 );
   strcat ( filename2, "mis");
   strcat ( filename2, pathdelimitterstring );
   strcat ( filename2, "*.dat");

   int cnt = 0;

   while ( !exist ( filename2 )) {
      char* res = getstring("enter Battle Isle path", filename );
      if ( res == NULL )
         return NULL;

      CGameOptions::Instance()->setChanged ( 1 );

      strcpy ( filename2, filename );
      appendbackslash( filename2 );
      strcat ( filename2, "mis");
      strcat ( filename2, pathdelimitterstring );
      strcat ( filename2, "*.dat");
      cnt++;
      #if CASE_SENSITIVE_FILE_NAMES == 1
      if (!exist ( filename2 ) && cnt == 1 )
         displaymessage("The 'mis' and 'ger' / 'eng' directories must be lower case to import files from them !", 1 );
      #endif
   }
   appendbackslash( filename );
   char* buf = strdup ( filename );
   CGameOptions::Instance()->bi3.dir.setName( filename );

   return buf;
}

// �S ExecAction

void execaction(int code)
{
   switch(code) {
    case act_help :   if ( polyfieldmode ) help ( 1040 );
                       else help(1000);
       break;
    case act_selbodentyp : {
                        ch = 0;
                        cursor.hide();
                        selterraintype( ct_f3 );
                        cursor.show();
                     }
       break;
    case act_selunit : {
                       ch = 0;
                       cursor.hide();
                       selvehicletype( ct_f4 );
                       cursor.show();
                     }
       break;
    case act_selcolor : {
                       ch = 0;
                       cursor.hide();
                       selcolor( ct_f5 );
                       cursor.show();
                     }
       break;
    case act_selbuilding : {
                       ch = 0;
                       cursor.hide();
                       selbuilding( ct_f6);
                       cursor.show();
                     }
       break;
    case act_selobject : {
                       ch = 0;
                       cursor.hide();
                       selobject( ct_f7 );
                       cursor.show();
                     }
       break;
    case act_selmine : {
                       ch = 0;
                       cursor.hide();
                       selmine( ct_f8 );
                       cursor.show();
                     }
       break;
    case act_selweather : {
                       ch = 0;
                       cursor.hide();
                       selweather( ct_f9  );   // !!!!!         // Test (Boolean) Testet, ob das wetter auch verf�gbar ist f�r bodentyp
                       cursor.show();                           // True : WIRD getestet / false : kein Test
                     }
       break;
    case act_setupalliances :  setupalliances();
       break;
    case act_toggleresourcemode :  {
                      if (showresources < 2) showresources++;
                      else showresources = 0;
                      displaymap();
       }
       break;
    case act_changeglobaldir : {
                                  auswahld++;
                                  if (auswahld > sidenum-1) auswahld = 0;
                                 //// if ( selectnr > cselcolor) selectnr = cselbodentyp; ???????
                                  showallchoices();
                                }
       break;
    case act_asc_resource :   {
                                  actmap->_resourcemode = false;
                                  displaymessage ( "ASC Resource mode enabled", 3 );
                                }
       break;
    case act_bi_resource :   {
                                  actmap->_resourcemode = true;
                                  displaymessage ( "Battle Isle Resource mode enabled", 3 );
                               }
       break;
    case act_maptopcx : writemaptopcx ();  
       break;
    case act_loadmap :   {
                            if (mapsaved == false )
                               if (choice_dlg("Map not saved ! Save now ?","~y~es","~n~o") == 1) 
                                  k_savemap(false);

                             k_loadmap();   
 
                             actmap->player[8].firstvehicle = NULL;
 
                             pdbaroff(); 
                          } 
       break;
    case act_changeplayers : playerchange();
       break;
    case act_newmap :   newmap();
       break;
    case act_polymode :   {
          getpolygon(&pfpoly);
          if (pfpoly != NULL ) {
             tfill = false;
             polyfieldmode = true;

             tchangepoly cp;

             cp.poly = pfpoly;
             cp.setpolytemps(1);
             cursor.gotoxy(1,1);
             
             displaymap();
             pdbaroff();
          }
       }
       break;            
    case act_repaintdisplay :   repaintdisplay();
       break;
    case act_unitinfo :  vehicle_information();
       break;
    case act_viewmap :  
             {
             while (mouseparams.taste != 0)
                releasetimeslice();
             cursor.hide();
             showmap ();
             displaymap();
             cursor.show();
             }
       break;
    case act_changeunitdir : {
                      pf = getactfield();
                      if ( (pf != NULL) && (pf->vehicle != NULL ) ){
                         pf->vehicle->direction++;
                         if (pf->vehicle->direction>sidenum-1) pf->vehicle->direction = 0;
                         mapsaved = false;
                         displaymap();
                      } 
                   }
       break;
    case act_changeresources :   changeresource();
       break;
    case act_createresources : { 
                           tputresourcesdlg prd;
                           prd.init();
                           prd.run();
                           prd.done();
                         }
       break;
    case act_changecargo :   {
                 cursor.hide(); 
                 if ( getactfield()->building )                    
                    building_cargo( getactfield()->building );
                 else 
                    if ( getactfield()->vehicle )
                       unit_cargo( getactfield()->vehicle );
                 cursor.show(); 
              } 
       break;
    case act_changeterraindir : {
                      pf = getactfield();
                      if (pf != NULL) {
                         pf->direction++;
                         if (pf->direction>sidenum-1) pf->direction = 0;
                         mapsaved = false;
                         displaymap();
                      } 
                   }
       break;
    case act_events :   event();
       break;
    case act_fillmode :   if ( polyfieldmode == false ) {   
                 if (tfill == true) tfill = false; 
                 else tfill = true; 
                 fillx1 = cursor.posx + actmap->xpos; 
                 filly1 = cursor.posy + actmap->ypos; 
                 pdbaroff(); 
              } 
       break;
    case act_mapgenerator : mapgenerator();
       break;
    case act_setactivefieldvals : {
                  pfield fld = getactfield();

                  if ( fld->vehicle ) {
                     auswahlf = fld->vehicle->typ;
                     altefarbwahl = farbwahl;
                     farbwahl = fld->vehicle->color/8;
                     lastselectiontype = cselunit;
                     setnewvehicleselection ( auswahlf );
                  } else
                  if ( fld->building ) {
                     auswahlb = fld->building->typ;
                     altefarbwahl = farbwahl;
                     farbwahl = fld->building->color/8;
                     lastselectiontype = cselbuilding;
                     setnewbuildingselection ( auswahlb );
                  } else
                  if ( fld->object && fld->object->objnum ) {
                     actobject = fld->object->object[ fld->object->objnum -1 ]->typ ;
                     lastselectiontype = cselobject;
                     setnewobjectselection ( actobject );
                  } else {
                     auswahld = fld->direction;
                     auswahl = fld->typ->terraintype;
                     lastselectiontype = cselbodentyp;
                     setnewterrainselection ( auswahl );
                  }
                  showallchoices();
               }
       break;
       
    case act_deletething : {
                         pf = getactfield();
                         mapsaved = false;
                         if (pf != NULL) {
                            if (pf->vehicle != NULL) removevehicle(&pf->vehicle);
                            else if (pf->building != NULL) removebuilding(&pf->building); 
                            else {
                                     pf->removeobject( actobject );
                                     pf->removemine( -1 );
                                   }
                            mapsaved = false;
                            displaymap();
                         }
                      } 
        break;
    case act_deleteunit : {
                         pf = getactfield();
                         if (pf != NULL) 
                            if (pf->vehicle != NULL) {
                               removevehicle(&pf->vehicle);
                               mapsaved = false;
                               displaymap();
                            }
                         }
        break;
     case act_deletebuilding : {
                         pf = getactfield();
                         if (pf != NULL) 
                            if (pf->building != NULL) { 
                               removebuilding(&pf->building); 
                               mapsaved = false;
                               displaymap();
                            }
                      }
        break;
     case act_deleteobject : {
                         pf = getactfield();
                         if (pf != NULL) {
                            mapsaved = false;
                            pf->removeobject( actobject );
                            displaymap();
                         }
                      }
        break;
     case act_deletemine : {
                         pf = getactfield();
                         if (pf != NULL) {
                            mapsaved = false; 
                            pf->removemine( -1 );
                            displaymap();
                         }
                      }
        break;
    case act_showpalette : showpalette();
       break;
    case act_changeminestrength : changeminestrength();
       break;
    case act_changemapvals :   changemapvalues();
       break;                                        
    case act_changeproduction :   if ( getactfield()->building ) building_production( getactfield()->building );
       break;
    case act_savemap :  k_savemap(false);
       break;
    case act_savemapas :  k_savemap(true);
       break;
    case act_changeunitvals :   {
                 pf = getactfield();
                 if (pf != NULL ) {
                    if (pf->vehicle != NULL ) {
                       changeunitvalues(pf->vehicle); 
                       displaymap();
                    }
                    else if (pf->building != NULL ) {
                       gbde = getactfield()->building;
                       changebuildingvalues(&gbde);
                    } /* endif */
                 } /* endif */
              } 
              break;
    case act_mirrorcursorx :   {
                    cursor.gotoxy ( actmap->xsize-getxpos(), getypos() );
                    int tmp = farbwahl;
                    farbwahl = altefarbwahl;
                    altefarbwahl = tmp;
                    showallchoices();
                    showStatusBar();
                 }

       break;
    case act_mirrorcursory :   {
                    cursor.gotoxy ( getxpos(), actmap->ysize-getypos() );
                    int tmp = farbwahl;
                    farbwahl = altefarbwahl;
                    altefarbwahl = tmp;
                    showallchoices();
                    showStatusBar();
                 }
       break;
    case act_placebodentyp : placebodentyp();
       break;
    case act_placeunit : placeunit();
       break;
    case act_placebuilding : placebuilding(farbwahl,auswahlb,true);
       break;
    case act_placeobject : placeobject();
       break;
    case act_placemine : placemine();
       break;
    case act_placething : putactthing();
       break;
    case act_endpolyfieldmode : {
          if (polyfieldmode) {
             polyfieldmode = false;
             tchangepoly cp;

             cp.poly = pfpoly;
             cp.setpolytemps(0);
             
             displaymap();
             pdbaroff();
             ch = 255;
          }
       }
       break;
    case act_end : {  
       if (choice_dlg("Do you really want to quit ?","~y~es","~n~o") == 2) ch = ct_invvalue; 
          else
               {
                ch = ct_esc; //Exit MapEdit
                if (mapsaved == false )
                   if (choice_dlg("Map not saved ! Save now ?","~y~es","~n~o") == 1) k_savemap(false);
               } 
       }
       break;
    case act_about :  
    case act_aboutbox : {
         help(1020);
         tviewanytext vat;
         vat.init ( "about", kgetstartupmessage() );
         vat.run();
         vat.done();
      }
      break;
   case act_smoothcoasts : {
         #ifdef HEXAGON
            smooth ( 6 );
            displaymap();
         #endif
      }
      break;
   case act_import_bi_map : {
         #ifdef HEXAGON
         char filename2[260];
         char* path = getbipath();
         if ( !path )
            break;
            
         strcpy ( filename2, path );
         strcat ( filename2, "mis");
         strcat ( filename2, pathdelimitterstring );
         strcat ( filename2, "*.dat");

         char filename[260];
         fileselectsvga ( filename2, filename,1 );
         if ( filename[0] ) {
            strcpy ( filename2, path );
            strcat ( filename2, "mis");
            strcat ( filename2, pathdelimitterstring );
            strcat ( filename2, filename);
            TerrainType::Weather* t = auswahl->weather[auswahlw];
            if ( !t )
               t = auswahl->weather[0];
            importbattleislemap ( path, filename, t );
            displaymap();
         }
         #endif
      }
      break;
   case act_insert_bi_map : {
         #ifdef HEXAGON

         char filename2[260];

         char* path = getbipath();
         if ( !path )
            break;
            
         strcpy ( filename2, path );
         strcat ( filename2, "mis");
         strcat ( filename2, pathdelimitterstring );
         strcat ( filename2, "*.dat");

         char filename[260];
         fileselectsvga ( filename2, filename,1 );
         if ( filename[0] ) {
            strcpy ( filename2, path );
            strcat ( filename2, "mis");
            strcat ( filename2, pathdelimitterstring );
            strcat ( filename2, filename);
            insertbattleislemap ( getxpos(), getypos(), path, filename );
            displaymap();
         }
         #endif
      }
      break;
   case act_resizemap : cursor.hide();
                        resizemap();
                        cursor.checkposition ( actmap->xpos + cursor.posx, actmap->ypos + cursor.posy );
                        cursor.show();
      break;
   case act_movebuilding: movebuilding();
      break;
   case act_setactweatherglobal: setweatherall ( auswahlw, 1 );
                                 displaymap();
      break;
   case act_setmapparameters: setmapparameters();
      break;
   case act_terraininfo: viewterraininfo();
      break;
   case act_setunitfilter: selectunitsetfilter();
      break;
   case act_selectgraphicset: selectgraphicset();
      break;
  #ifdef FREEMAPZOOM    
   case act_setzoom : choosezoomlevel();
      break;
  #endif
   case act_unitsettransformation: unitsettransformation();
      break;
   case act_unitSetInformation: viewUnitSetinfo();
      break;
   case act_switchmaps: mapSwitcher.toggle();
                        displaymap();
                        showStatusBar();
      break;
    }
}

