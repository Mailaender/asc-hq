/** \file edglobal.cpp
    \brief various functions for the mapeditor
*/

//     $Id: edglobal.cpp,v 1.62.2.5 2005-06-09 20:27:13 mbickel Exp $

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
#include "mapdisplay.h"
#include "itemrepository.h"
#include "clipboard.h"
#include "resourceplacementdialog.h"
#include "weatherdialog.h"
#include "maped-mainscreen.h"


   const char* execactionnames[execactionscount] = {
        "End MapEdit",
        "Help",
        "Goto EditMode",
        "Select terrain",
        "Select terrainAll",
        "Select unit",
        "Select color",
        "Select building",
        "Select special object",
        "Select mine",
        "Select weather",
        "Setup alliances",
        "Toggle ResourceMode",
        "Change UnitDirection",
        "Asc-Resource Mode",
        "Write Map2PCX",
        "Load map",
        "Change players",
        "New map",
        "Goto PolygonMode",
        "Rebuild Display",
        "Open UnitInfo",
        "View map",
        "About",
        "Create resources",
        "View/Change cargo",
        "View/Change resources",
        "Change TerrainDirection",
        "View/Change Events",
        "Toggle Fillmode",
        "Mapgenerator",
        "Use active field values as selection",
        "Delete active thing",
        "Show palette",
        "View/Change minestrength",
        "View/Change mapvalues",
        "View/Change production",
        "Save map",
        "View/Change item Values",
        "Mirror CX-Pos",
        "Mirror CY-Pos",
        "Place terrain",
        "Place Unit",
        "Place building",
        "Place special object",
        "Place mine",
        "Place active thing",
        "Delete Unit",
        "Delete building",
        "Delete selected object",
        "Delete topmost object",
        "Delete all objects",
        "Delete mine",
        "AboutBox",
        "Save map as ...",
        "End PolygonMode",
        "Smooth coasts",
        "Import BI-Map",
        "SEPERATOR",
        "BI-Resource Mode",
        "Resize map",
        "Insert BI map",
        "Set zoom level",
        "Move Building",
        "set weather of whole map",
        "set map parameters",
        "terrain info",
        "set unit filter",
        "select graphic set",
        "unitset transformation",
        "Unitset Information",
        "switch maps",
        "transform map",
        "Edit Map Archival Information",
        "Display Resource Comparison",
        "specify unit production",
        "Paste",
        "Copy",
        "Cut",
        "Save Clipboard",
        "Load Clipboard",
        "Set Turn Number",
        "Show Pipeline Net",
        "Edit Technologies",
        "Edit ResearchPoints",
        "Generate TechTree",
        "Edit TechAdapter",
        "Reset Player Data...",
        "Fill map with resources",
        "setup weather generation" };


SigC::Signal0<void> mapChanged;
        
        
// �S Infomessage

int infomessage( char* formatstring, ... )
{
   char stringtooutput[200];
   char* b;
   char* c = new char[200];
   // int linenum = 0;

   memset (stringtooutput, 0, sizeof ( stringtooutput ));

   b = stringtooutput;

   va_list paramlist;
   va_start ( paramlist, formatstring );

   vsprintf ( stringtooutput, formatstring, paramlist );

   va_end ( paramlist );

   npush ( activefontsettings );
   activefontsettings.justify = lefttext;
   activefontsettings.font = schriften.smallarial;
   activefontsettings.color = lightgray;
   activefontsettings.markcolor = red;
   activefontsettings.background = 0;
   activefontsettings.length = agmp->resolutionx - ( 640 - 387);

   int yy = agmp->resolutiony - ( 480 - 450 );
   showtext3c( stringtooutput, 37, yy );

   npop( activefontsettings );

   if ( formatstring == NULL  ||  formatstring[0] == 0 )
      lastdisplayedmessageticker = 0xffffff;
   else
      lastdisplayedmessageticker = ticker;


   delete ( c );

   return ++actdisplayedmessage;
}


ASCString getbipath ( void )
{
   ASCString filename = getbi3path();
   appendbackslash( filename );
   filename += "mis";
   filename += pathdelimitterstring;
   filename += "*.dat";

   int cnt = 0;

   while ( !exist ( filename )) {
      filename = editString("enter Battle Isle path", filename );
      if ( filename.empty() )
         return "";

      appendbackslash(filename);
      
      CGameOptions::Instance()->bi3.dir = filename;
      CGameOptions::Instance()->setChanged ( 1 );

      filename += "mis";
      filename += pathdelimitterstring;
      filename += "*.dat";
      
      cnt++;
      #if CASE_SENSITIVE_FILE_NAMES == 1
      if (!exist ( filename ) && cnt == 1 )
         displaymessage("The 'mis' and 'ger' / 'eng' directories must be lower case to import files from them !", 1 );
      #endif
   }

   return getbi3path();
}


void showPipeNet()
{
   static bool isShown = false;

   if ( isShown ) {
      actmap->cleartemps();
      displaymap();
      isShown = false;
   } else {
      TerrainBits tb = getTerrainBitType(cbpipeline);
      for ( int x = 0; x < actmap->xsize; ++x )
         for ( int y = 0; y < actmap->ysize; ++y ) {
             pfield fld = actmap->getField ( x, y );
             if ( (fld->bdt & tb).any() )
                fld->a.temp = 1;
         }
      displaymap();
   }
   isShown = true;
}

// �S ExecAction

void         execaction_ev(int code)
{
   getPGApplication().enableLegacyEventHandling ( true );
   execaction(code);
   getPGApplication().enableLegacyEventHandling ( false );
}


void execaction(int code)
{
   switch(code) {
    case act_help :   if ( polyfieldmode ) help ( 1040 );
                       else help(1000);
       break;
    case act_selbodentypAll : mainScreenWidget->selectTerrain();
       break;
    case act_selunit : mainScreenWidget->selectVehicle();
       break;
    case act_selcolor : {
                       ch = 0;
                       selcolor( ct_f5 );
                     }
       break;
    case act_selbuilding : mainScreenWidget->selectBuilding(); 
       break;
    case act_selobject : mainScreenWidget->selectObject();
       break;
    case act_selmine : {
                       ch = 0;
                       selmine( ct_f8 );
                     }
       break;
    case act_selweather : {
                       ch = 0;
                       selweather( ct_f9  );   // !!!!!         // Test (Boolean) Testet, ob das wetter auch verf�gbar ist f�r bodentyp
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
    case act_maptopcx : //writemaptopcx ();  
       break;
    case act_loadmap :   {
                            if (mapsaved == false )
                               if (choice_dlg("Map not saved ! Save now ?","~y~es","~n~o") == 1) 
                                  k_savemap(false);

                            pmap oldmap = actmap;
                            actmap = NULL;
                            try {
                                k_loadmap();
                            }
                            catch ( ... ) {
                                displaymessage ( "error loading file",1 );
                            }
                            if ( !actmap ) {
                                actmap = oldmap;
                                oldmap = NULL;
                            } else {
                               delete oldmap;
                               oldmap = NULL;
                            }
                            displaymap();
                          } 
       break;
    case act_changeplayers : playerchange();
       break;
    case act_newmap :   newmap();
       break;
       /*
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
       */
    case act_unitinfo :  vehicle_information();
       break;
    case act_viewmap :  
             {
             while (mouseparams.taste != 0)
                releasetimeslice();
             // showmap ();
             displaymap();
             }
       break;
    case act_changeunitdir : {
                      pf2 = getactfield();
                      if ( (pf2 != NULL) && (pf2->vehicle != NULL ) ){
                         pf2->vehicle->direction++;
                         if (pf2->vehicle->direction>sidenum-1) pf2->vehicle->direction = 0;
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
    case act_createresources2 : resourcePlacementDialog();
       break;
    case act_changecargo :   {
                 if ( getactfield()->building )                    
                    building_cargo( getactfield()->building );
                 else 
                    if ( getactfield()->vehicle )
                       unit_cargo( getactfield()->vehicle );
              }
       break;
    case act_changeterraindir : {
                      pf2 = getactfield();
                      if (pf2 != NULL) {
                         pf2->direction++;
                         if (pf2->direction>sidenum-1) pf2->direction = 0;
                         mapsaved = false;
                         displaymap();
                      }
                   }
       break;
    case act_events :   event();
       break;
       /*
    case act_fillmode :   if ( polyfieldmode == false ) {   
                 if (tfill == true) tfill = false;
                 else tfill = true; 
                 fillx1 = cursor.posx + actmap->xpos;
                 filly1 = cursor.posy + actmap->ypos; 
                 pdbaroff(); 
              } 
       break;
       */
    case act_mapgenerator : mapgenerator();
       break;
    case act_setactivefieldvals : {
                  pfield fld = getactfield();

                  if ( fld->vehicle ) {
                     auswahlf = vehicleTypeRepository.getObject_byID ( fld->vehicle->typ->id );
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
                  if ( !fld->objects.empty() ) {
                     actobject = fld->objects.begin()->typ ;
                     lastselectiontype = cselobject;
                     setnewobjectselection ( actobject );
                  } else {
                     auswahl = fld->typ->terraintype;
                     lastselectiontype = cselbodentyp;
                     setnewterrainselection ( auswahl );
                  }
                  // showallchoices();
               }
       break;
       
    case act_deletething : {
                         pf2 = getactfield();
                         mapsaved = false;
                         if (pf2 != NULL) {
                            if (pf2->vehicle != NULL)
                               delete pf2->vehicle;
                            else
                               if (pf2->building != NULL)
                                  delete pf2->building;
                               else
                                  if ( !pf2->mines.empty() )
                                     pf2->removemine( -1 );
                                  else
                                     pf2->removeobject( NULL );

                            mapsaved = false;
                            displaymap();
                         }
                      }
        break;
    case act_deleteunit : {
                         pf2 = getactfield();
                         if (pf2 != NULL)
                            if (pf2->vehicle != NULL) {
                               delete pf2->vehicle;
                               mapsaved = false;
                               displaymap();
                            }
                         }
        break;
     case act_deletebuilding : {
                         pf2 = getactfield();
                         if (pf2 != NULL)
                            if (pf2->building != NULL) {
                               delete pf2->building;
                               mapsaved = false;
                               displaymap();
                            }
                      }
        break;
     case act_deleteobject : {
                         pf2 = getactfield();
                         if ( pf2 ) {
                            mapsaved = false;
                            pf2->removeobject( actobject );
                            displaymap();
                         }
                      }
        break;
     case act_deletetopmostobject : {
                         pf2 = getactfield();
                         if ( pf2 ) {
                            mapsaved = false;
                            pf2->removeobject( NULL );
                            displaymap();
                         }
                      }
        break;
     case act_deleteallobjects : {
                         pf2 = getactfield();
                         if ( pf2 ) {
                            mapsaved = false;
                            pf2->objects.clear( );
                            calculateallobjects();
                            displaymap();
                         }
                      }
        break;
     case act_deletemine : {
                         pf2 = getactfield();
                         if (pf2 != NULL) {
                            mapsaved = false;
                            pf2->removemine( -1 );
                            displaymap();
                         }
                      }
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
                 pf2 = getactfield();
                 if ( pf2  ) {
                    if ( pf2->vehicle ) {
                       changeunitvalues(pf2->vehicle);
                       displaymap();
                    }
                    else if ( pf2->building ) {
                       changebuildingvalues(*pf2->building);
                    } /* endif */
                 } /* endif */
              } 
              break;
              /*
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
       */
    case act_placebodentyp : placebodentyp();
       break;
    case act_placebuilding : placebuilding(farbwahl,auswahlb,true);
       break;
    case act_placeobject : placeobject();
       break;
    case act_placemine : placemine();
       break;
    case act_placething : if ( getSelection() ) {
                              getSelection()->place( actmap->getCursor() );
                              mapChanged();
                          }    
       break;
       /*
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
       */
    case act_end : {
       if ( mapSwitcher.getDefaultAction() == MapSwitcher::select ) {
          execaction(act_switchmaps);
          ch = ct_invvalue;
       } else
          if (choice_dlg("Do you really want to quit ?","~y~es","~n~o") == 1) {
             if (mapsaved == false )
                if (choice_dlg("Map not saved ! Save now ?","~y~es","~n~o") == 1) 
                   k_savemap(false);
                   
             getPGApplication().Quit();
          }
       }   
       break;
    case act_about :
    case act_aboutbox : {
         help(1020);
         tviewanytext vat;
         ASCString msg = kgetstartupmessage();
         vat.init ( "about", msg.c_str() );
         vat.run();
         vat.done();
      }
      break;
   case act_smoothcoasts : {
            ForestCalculation::smooth ( 6, actmap, NULL );
            displaymap();
      }
      break;
   case act_import_bi_map : {
         ASCString path = getbipath();
         if ( path.empty() )
            break;

         ASCString wildcard = path + "mis" + pathdelimitterstring + "*.dat" ;

         ASCString filename;
         fileselectsvga ( wildcard, filename, true );
         if ( !filename.empty() ) {
            TerrainType::Weather* t = auswahl->weather[auswahlw];
            if ( !t )
               t = auswahl->weather[0];
            importbattleislemap ( path.c_str(), filename.c_str(), t );
            displaymap();
         }
      }
      break;
   case act_insert_bi_map : {
         ASCString path = getbipath();
         if ( path.empty() )
            break;

         ASCString wildcard = path + "mis" + pathdelimitterstring + "*.dat" ;

         ASCString filename;
         fileselectsvga ( wildcard, filename, true );
         if ( !filename.empty() ) {
            insertbattleislemap ( actmap->getCursor().x, actmap->getCursor().y, path.c_str(), filename.c_str() );
            displaymap();
         }
      }
      break;
   case act_resizemap : resizemap();
      break;
   case act_movebuilding: movebuilding();
      break;
   case act_setactweatherglobal: setweatherall ( auswahlw );
                                 displaymap();
      break;
   case act_setmapparameters: setmapparameters();
      break;
   case act_terraininfo: viewterraininfo();
      break;
   case act_setunitfilter: selectunitsetfilter();
      break;
   case act_selectgraphicset: selectgraphicset();
                              // showallchoices();
      break;
   case act_setzoom : choosezoomlevel();
      break;
   case act_unitsettransformation: unitsettransformation();
      break;
   case act_unitSetInformation: viewUnitSetinfo();
      break;
   case act_selbodentyp: if ( mapSwitcher.getDefaultAction() == MapSwitcher::select ) {
                            execaction ( act_setactivefieldvals );
                            /*
                            auswahl = getactfield()->typ->terraintype;
                            setnewterrainselection ( auswahl );
                            showallchoices();
                            */
                         } else
                            lastselectiontype = cselbodentyp;
                         execaction(act_switchmaps);
                         break;
   case act_switchmaps: mapSwitcher.toggle();
                        displaymap();
                        showStatusBar();
      break;
   case act_transformMap: transformMap();
      break;
   case act_editArchivalInformation: editArchivalInformation();
      break;
   case act_displayResourceComparison : resourceComparison();
      break;
   case act_specifyunitproduction: unitProductionLimitation();
      break;
   case act_pasteFromClipboard: if ( !getactfield()->getContainer() ) {
                                   ClipBoard::Instance().place( actmap->getCursor() );
                                   mapsaved = false;
                                   displaymap();
                                }
      break;
   case act_copyToClipboard: if ( getactfield()->vehicle ) {
                                ClipBoard::Instance().clear();
                                ClipBoard::Instance().addUnit( getactfield()->vehicle );
                             } else
                                if ( getactfield()->building ) {
                                   ClipBoard::Instance().clear();
                                   ClipBoard::Instance().addBuilding( getactfield()->building );
                                }
      break;
   case act_cutToClipboard: if ( getactfield()->vehicle ) {
                                ClipBoard::Instance().clear();
                                ClipBoard::Instance().addUnit( getactfield()->vehicle );
                                execaction ( act_deleteunit );
                                mapsaved = false;
                             } else
                                if ( getactfield()->building ) {
                                   ClipBoard::Instance().clear();
                                   ClipBoard::Instance().addBuilding( getactfield()->building );
                                   execaction ( act_deletebuilding );
                                   mapsaved = false;
                                }
      break;
   case act_saveClipboard:  saveClipboard();
      break;

   case act_readClipBoard:  readClipboard();
      break;
   case act_setTurnNumber:  actmap->time.set ( getid("Turn",actmap->time.turn(),0,maxint), 0 );
      break;
   case act_showPipeNet: showPipeNet();
      break;
   case act_editResearch:  editResearch();
      break;
   case act_editResearchPoints:  editResearchPoints();
      break;
   case act_generateTechTree: generateTechTree();
      break;
   case act_editTechAdapter: editTechAdapter();
      break;
   case act_resetPlayerData: resetPlayerData();
      break;
   case act_setactnewweather: weatherConfigurationDialog();
      break;

    }
}

