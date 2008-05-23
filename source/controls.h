/*! \file controls.h
   Controlling units (which is graudally moved to vehicletype.cpp and unitctrl.cpp );
   Resource networks
   Things that are run when starting and ending someones turn   
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

#if defined(karteneditor) 
 #error the mapeditor should not need to use controls.h !
#endif


#ifndef controlsH
#define controlsH
#include "typen.h"
#include "astar2.h"



   //! some old system for keeping track which unit action is currently running. As units actions are moved to unitctrl.cpp , this structure is beeing replaced by #pendingVehicleActions
   struct tmoveparams { 
                        unsigned char         movestatus;       /*  Folgende Modi sind definiert : 
                                                                             0:  garnichts, standard
                                                                             72: putstreet
                                                                             90: putmine
                                                                             111: putbuilding l1
                                                                             112: putbuilding l2
                                                                             115: removebuilding
                                                                             120: construct vehicle
                                                                             130: external loading
                                                                             140: jumpdrive
                                                                   */

                        int           movesx, movesy, moveerr; 
                        Vehicle*     vehicletomove;
                        int          newheight; 
                        int          oldheight; 
                        char         heightdir; 
                        BuildingType* buildingtobuild;   /*  nur bei movestatus = 111  */ 
                        int          movespeed;
                        int          uheight;
                        tmoveparams() { reset(); };
                        void reset();
                     }; 
  //! see #tmoveparams
  extern tmoveparams moveparams; 



/*! calculates the movement cost for moving vehicle from start to dest.
    \returns : first: movement ; second: fuel consumption
*/
extern pair<int,int> calcMoveMalus( const MapCoordinate3D& start,
                                    const MapCoordinate3D& dest,
                                    const Vehicle*     vehicle,
                                    WindMovement* wm = NULL,
                                    bool*  inhibitAttack = NULL,
                                    bool container2container  = false );

//! return the distance between x1/y1 and x2/y2 using the power of the wind factors precalculated in #WindMovement
extern int windbeeline ( const MapCoordinate& start, const MapCoordinate& dest, WindMovement* wm );


/////////////////////////////////////////////////////////////////////
///// old vehicle actions
/////////////////////////////////////////////////////////////////////


//! An old procedure for building vehicle (like turrets) with a unit.
extern void  constructvehicle( Vehicletype* tnk );

//! A helper function for #constructvehicle
extern void build_vehicles_reset( void );

//! An old procedure for putting and removing mines.
extern void  putMine( const MapCoordinate& pos, int typ, int delta );

//! An old procedure for removing a building with a vehicle
extern void         destructbuildinglevel2( int xp, int yp);

//! An old procedure for removing a building with a vehicle
extern void         destructbuildinglevel1( int xp, int yp);



//! dissects a vehicle; if you haven't researched this vehicle type you will get some research points for it.
extern void dissectvehicle ( Vehicle* eht );




// extern int searchexternaltransferfields ( Building* bld );

extern Resources getDestructionCost( Building* bld, Vehicle* veh );


//! checks if a new technology must be chosen by the current player. Runs the appropriate dialogs
extern void researchCheck( Player& player );

#endif
