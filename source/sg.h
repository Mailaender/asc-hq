/*! \file sg.h
    \brief Interface for various global functions and variables
*/

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


#ifndef sgH
#define sgH

#include "dialog.h"

enum tuseractions { ua_repainthard,     ua_repaint, ua_help, ua_dispvehicleimprovement, ua_mainmenu, ua_mntnc_morefog,
                    ua_mntnc_lessfog,   ua_mntnc_morewind,   ua_mntnc_lesswind, ua_mntnc_rotatewind, ua_changeresourceview,
                    ua_benchgamewv,     ua_benchgamewov,     ua_viewterraininfo, ua_unitweightinfo,  ua_writemaptopcx,  ua_writescreentopcx,
                    ua_startnewsinglelevel, ua_changepassword, ua_gamepreferences, ua_bi3preferences,
                    ua_exitgame,        ua_newcampaign,      ua_loadgame,  ua_savegame, ua_setupalliances, ua_settribute, ua_giveunitaway,
                    ua_vehicleinfo,     ua_researchinfo,     ua_unitstatistics, ua_buildingstatistics, ua_newmessage, ua_viewqueuedmessages,
                    ua_viewsentmessages, ua_viewreceivedmessages, ua_viewjournal, ua_editjournal, ua_viewaboutmessage, ua_continuenetworkgame,
                    ua_toggleunitshading, ua_computerturn, ua_setupnetwork, ua_howtostartpbem, ua_howtocontinuepbem, ua_mousepreferences,
                    ua_selectgraphicset, ua_UnitSetInfo, ua_GameParameterInfo, ua_GameStatus, ua_viewunitweaponrange, ua_viewunitmovementrange,
                    ua_aibench, ua_networksupervisor, ua_selectPlayList, ua_soundDialog, ua_reloadDlgTheme, ua_showPlayerSpeed, ua_renameunit,
                    ua_statisticdialog, ua_viewPipeNet, ua_cancelResearch, ua_showResearchStatus, ua_exportUnitToFile, ua_viewButtonPanel, ua_viewWindPanel,
                    ua_clearImageCache, ua_viewUnitInfoPanel, ua_cargosummary, ua_viewUnitInfoDialog, ua_showsearchdirs };

extern void execuseraction ( tuseractions action );

//! switches the event handling between paragui and legacy depending on function called
extern void execUserAction_ev( tuseractions action );


extern pprogressbar actprogressbar ;


#endif

