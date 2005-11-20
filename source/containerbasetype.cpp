/***************************************************************************
                          containerbasetype.h  -  description
                             -------------------
    begin                : Sun Feb 18 2001
    copyright            : (C) 2001 by Martin Bickel
    email                : bickel@asc-hq.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "containerbasetype.h"
#include "textfiletags.h"
#include "stringtokenizer.h"
#include "textfile_evaluation.h"
#include "vehicletype.h"
#include "graphics/blitter.h"




const char*  ccontainerfunctions[ContainerBaseType::functionNum+1]  =
              { "HQ",
                "training",
                "internal vehicle production",
                "ammunition production",
                "internal unit repair",
                "recycling",
                "research",
                "sonar",
                "view satellites",
                "view mines",
                "wind power plant",
                "solar power plant",
                "matter converter",
                "mining station",
                "construct units that cannot move out",
                "resource sink",
                "external energy transfer",
                "external material transfer",
                "external fuel transfer",
                "external ammo transfer",
                "external repair",
                "no object chaining",
                "self destruct on conquer",
               "paratrooper",
               "mine-layer",
               "cruiser landing",
               "conquer buildings",
               "move after attack",
               "construct ALL buildings",
               "external vehicle production",
               "construct specific buildings",
               "icebreaker",
               "cannot be refuelled in air",
               "makes tracks",
               "drill for mineral resources manually",
               "search for mineral resources automatically",
               "no reactionfire",
               "auto repair",
               "Kamikaze only",
               "immune to mines",
               "jams only own field",
               "move with reaction fire on",
               "only move to and from transports" };


ContainerBaseType :: ContainerBaseType ()
{
   maxLoadableUnits = 0;
   maxLoadableUnitSize = 0;
   maxLoadableWeight = maxint;
   vehicleCategoriesStorable = -1;
   id = 0;
   jamming = 0;
   view = 0;
}

ContainerBaseType::TransportationIO::TransportationIO()
{
  mode = 0;
  height_abs = 0;
  height_rel = 0;
  container_height = 0;
  vehicleCategoriesLoadable = -1;
  dockingHeight_abs = 0;
  dockingHeight_rel = 0;
  requireUnitFunction = 0;
  disableAttack = false;
  movecost = -1;
}


void ContainerBaseType :: TransportationIO :: runTextIO ( PropertyContainer& pc )
{
   pc.addTagInteger( "Mode", mode, entranceModeNum, entranceModes );
   pc.addTagInteger( "UnitHeightAbs", height_abs, choehenstufennum, heightTags );
   pc.addInteger( "UnitHeightRel", height_rel, -100 );
   pc.addTagInteger( "ContainerHeight", container_height, choehenstufennum, heightTags );
   pc.addTagInteger( "CategoriesNOT", vehicleCategoriesLoadable, cmovemalitypenum, unitCategoryTags, true );
   pc.addTagInteger( "DockingHeightAbs", dockingHeight_abs, choehenstufennum, heightTags, 0 );
   pc.addInteger( "DockingHeightRel", dockingHeight_rel, -100 );
   pc.addTagInteger( "RequireUnitFunction", requireUnitFunction, cvehiclefunctionsnum, vehicleAbilities, 0 );
   pc.addBool( "DisableAttack", disableAttack, false );
   pc.addInteger( "MoveCost", movecost, -1 );
   if ( movecost < 10 && movecost >= 0 )
      fatalError ( "MoveCost for TransportationIO is lower than 10! file: " + pc.getFileName() );
}


void ContainerBaseType :: runTextIO ( PropertyContainer& pc )
{
   pc.openBracket ( "Transportation" );
    int num = entranceSystems.size();
    pc.addInteger ( "EntranceSystemNum", num, 0 );
    entranceSystems.resize(num);
    for ( int i = 0; i < num; i++ ) {
       pc.openBracket ( ASCString("EntranceSystem") + strrr(i) );
       entranceSystems[i].runTextIO( pc );
       pc.closeBracket();
    }
    pc.addInteger ( "MaxLoadableUnits", maxLoadableUnits, 0 );
    if ( maxLoadableUnits > 18 )
       maxLoadableUnits = 18;

    pc.addInteger ( "MaxLoadableUnitSize", maxLoadableUnitSize, maxint );
    pc.addInteger ( "MaxLoadableMass", maxLoadableWeight, maxint );
    pc.addTagInteger( "CategoriesNOT", vehicleCategoriesStorable, cmovemalitypenum, unitCategoryTags, -1, true );
   pc.closeBracket();

   pc.addString( "Name", name );

   pc.addString( "Infotext", infotext, "" );

   while ( infotext.find ( "#CRT#" ) != ASCString::npos )
      infotext.replace ( infotext.find ( "#CRT#" ), 5, "\n" );
   while ( infotext.find ( "#crt#" ) != ASCString::npos )
      infotext.replace ( infotext.find ( "#crt#" ), 5, "\n" );
   while ( infotext.find ( "\r" ) != ASCString::npos )
      infotext.replace ( infotext.find ( "\r" ), 1, "" );

   pc.addInteger( "ID", id );
   pc.addInteger( "View", view );
   if ( view > 255 )
      view = 255;

   pc.addInteger( "Jamming", jamming, 0 );
   pc.addString( "InfoImage", infoImageFilename, "" );
}


bool ContainerBaseType :: vehicleFit ( const Vehicletype* fzt ) const
{
   if ( maxLoadableUnits > 0 )
      if ( maxLoadableWeight > 0 )
         if ( vehicleCategoriesStorable & (1<<fzt->movemalustyp) )
            if ( maxLoadableUnitSize >= fzt->maxsize() )
               return true;

   return false;
}

const int containerBaseTypeVersion = 2;


void ContainerBaseType :: read ( tnstream& stream )
{
   int version = stream.readInt();
   if ( version > containerBaseTypeVersion || version < 1 ) {
      ASCString s = "invalid version for reading ContainerBaseType: ";
      s += strrr ( version );
      throw ASCmsgException ( s );
   }
   maxLoadableUnits = stream.readInt();
   maxLoadableUnitSize = stream.readInt();
   maxLoadableWeight = stream.readInt();
   vehicleCategoriesStorable = stream.readInt();
   int num = stream.readInt();
   entranceSystems.resize(num);
   for ( int i = 0; i < num; i++ )
      entranceSystems[i].read( stream );

   if ( version >= 2 )
      infoImageFilename = stream.readString();
}

void ContainerBaseType :: write ( tnstream& stream ) const
{
   stream.writeInt( containerBaseTypeVersion );
   stream.writeInt( maxLoadableUnits );
   stream.writeInt( maxLoadableUnitSize );
   stream.writeInt( maxLoadableWeight );
   stream.writeInt( vehicleCategoriesStorable );
   stream.writeInt( entranceSystems.size() );
   for ( int i = 0; i < entranceSystems.size(); i++ )
      entranceSystems[i].write( stream );
   stream.writeString( infoImageFilename );
}

const int containerBaseTypeTransportVersion = 2;


void ContainerBaseType :: TransportationIO :: read ( tnstream& stream )
{
   int version = stream.readInt();
   if ( version > containerBaseTypeTransportVersion || version < 1 ) {
      ASCString s = "invalid version for reading ContainerBaseTypeTransportation: ";
      s += strrr ( version );
      throw ASCmsgException ( s );
   }
   mode = stream.readInt();
   height_abs = stream.readInt();
   height_rel = stream.readInt();
   container_height = stream.readInt();
   vehicleCategoriesLoadable = stream.readInt();
   dockingHeight_abs = stream.readInt();
   dockingHeight_rel = stream.readInt();
   requireUnitFunction = stream.readInt();
   disableAttack = stream.readInt();
   if ( version >= 2 )
      movecost = stream.readInt();
   else
      movecost = -1;
   
}

void ContainerBaseType :: TransportationIO :: write ( tnstream& stream ) const
{
   stream.writeInt ( containerBaseTypeTransportVersion );
   stream.writeInt ( mode );
   stream.writeInt ( height_abs );
   stream.writeInt ( height_rel );
   stream.writeInt ( container_height );
   stream.writeInt ( vehicleCategoriesLoadable );
   stream.writeInt ( dockingHeight_abs );
   stream.writeInt ( dockingHeight_rel );
   stream.writeInt ( requireUnitFunction );
   stream.writeInt ( disableAttack );
   stream.writeInt ( movecost );
}


