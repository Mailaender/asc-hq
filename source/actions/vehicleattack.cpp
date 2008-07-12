/*
     This file is part of Advanced Strategic Command; http://www.asc-hq.de
     Copyright (C) 1994-2008  Martin Bickel  and  Marc Schellenberger
 
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


#include "vehicleattack.h"

#include "../vehicle.h"
#include "../gamemap.h"
#include "../attack.h"
#include "../spfst.h"
#include "../viewcalculation.h"

#include "destructunit.h"
#include "changeunitmovement.h"
#include "inflictunitdamage.h"

#include "../mapdisplayinterface.h"

     
VehicleAttackAction::VehicleAttackAction( GameMap* gamemap, int vehicleID, const MapCoordinate& target, int weapon )
   : UnitAction( gamemap, vehicleID )
{
   this->target = target;
   this->weapon = weapon;
}
      
      
ASCString VehicleAttackAction::getDescription() const
{
   ASCString res = "Attack at " + target.toString();
   if ( getUnit(false) ) 
      res += " with unit " + getUnit(false)->getName();
   return  res;
}
      
      
void VehicleAttackAction::readData ( tnstream& stream ) 
{
   UnitAction::readData( stream );
   int version = stream.readInt();
   if ( version != 1 )
      throw tinvalidversion ( "VehicleAttack", 1, version );
   
   weapon = stream.readInt();
   target.read( stream );
};
      
      
void VehicleAttackAction::writeData ( tnstream& stream )
{
   UnitAction::writeData( stream );
   stream.writeInt( 1 );
   stream.writeInt( weapon );
   target.write( stream );
};


GameActionID VehicleAttackAction::getID()
{
   return ActionRegistry::VehicleAttack;
}

ActionResult VehicleAttackAction::runAction( const Context& context )
{
   tfight* battle = NULL;
   
   tfield* fld = getMap()->getField( target );
   
   Vehicle* attacker = getUnit();
   Vehicle* attackee = fld->vehicle;
   
   if ( fld->vehicle ) {
      battle = new tunitattacksunit ( attacker, attackee, true, weapon );
   } else {
      if ( fld->building ) 
         battle = new tunitattacksbuilding ( getUnit(), target.x, target.y , weapon );
      else
         battle = new tunitattacksobject ( getUnit(), target.x, target.y, weapon );
   }
   
   bool shown;
   if ( context.display && fieldvisiblenow ( getMap()->getField (target), context.viewingPlayer ) ) {
      context.display->displayActionCursor ( getUnit()->getPosition(), target );
      context.display->showBattle( *battle );
      context.display->removeActionCursor ( );
      shown = true;
   } else {
      battle->calc();
      shown = false;
   }

   /*
   if ( !getUnit()->typ->hasFunction( ContainerBaseType::MoveAfterAttack )) {
      GameAction* a = new ChangeUnitMovement( getMap(), getUnit()->networkid, 0 );
      a->execute( context );
   }
   */

   battle->setresult ( context );

   evaluateviewcalculation( getMap() );

   if ( context.display && shown )
      context.display->displayMap();

   return ActionResult(0);
}


ActionResult VehicleAttackAction::undoAction( const Context& context )
{
   evaluateviewcalculation( getMap() );
   if ( context.display )
      context.display->displayMap();
   return ActionResult(0);
}

