/***************************************************************************
                          mapalgorithms.h  -  description
                             -------------------
    begin                : Thu Oct 5 2000
    copyright            : (C) 2000 by Martin Bickel
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

#ifndef mapalgorithmsH
 #define mapalgorithmsH

 #include "typen.h"
 #include "vehicle.h"
 #include "libs/loki/Functor.h"

  /** searches fields in hexagonal "circles" around a field and calls testfield for each field
  */
  class   SearchFields {
                protected:
                    pmap gamemap;
                    MapCoordinate startPos;
                    bool        cancelSearch;
                    int         firstDistance, lastDistance;
                    int         dist;
                    virtual void testfield ( const MapCoordinate& pos ) = 0;
                public:
                    SearchFields ( pmap _gamemap );
                    void initsearch ( const MapCoordinate& startPosition, int _firstDistance, int _lastDistance );
                    virtual void startsearch ( void );
                    virtual ~SearchFields() {};
                 };

  typedef Loki::Functor<void, TYPELIST_1(const MapCoordinate&) > FieldIterationFunctor;
  extern void circularFieldIterator( pmap gamemap, const MapCoordinate& center, int startDist, int stopDist, FieldIterationFunctor functor ); 

                 
  /** draws a straight line on the hexagonal map and calls putpix8 for each field.
      Awfully unoptimized!
  */
  class tdrawgettempline  {
                  int freefields;
                  int num;
                  int sx, sy;

                  static int initialized;
                  static double dirs[ sidenum ];
                  static double offset;

                  void init ( void );

               protected:
                  pmap gamemap;

               public:
                   int tempsum;
                   tdrawgettempline ( int _freefields, pmap _gamemap );

                   void start ( int x1, int y1, int x2, int y2 );

                   virtual void putpix8 ( int x, int y );
                   double winkel ( int x, int y );
                   int winkelcomp ( double w1, double w2 );
                   virtual ~tdrawgettempline() {};
              };

//! changes x and y to the coordinates of the neighbouring field of (x/y) in the direction direc
extern void  getnextfield(int &    x,
                          int &    y,
                          int direc);

//! returns the coordinate of the field that is adjecent to the given field in the direction of direc
extern MapCoordinate3D  getNeighbouringFieldCoordinate( const MapCoordinate3D& pos, int direc);
extern MapCoordinate    getNeighbouringFieldCoordinate( const MapCoordinate  & pos, int direc);


/** gets the direction from x1/y1 to x2/y2
  \returns -1 if the fields are identical
*/
extern int   getdirection(    int      x1,
                              int      y1,
                              int      x2,
                              int      y2);
extern int   getdirection( const MapCoordinate& start, const MapCoordinate& dest );

//! returns the distance between (x1/y1) and (x2/y2)
extern int beeline ( int x1, int y1, int x2, int y2 );

//! returns the distance between the units a and b
extern int beeline ( const Vehicle* a, const Vehicle* b );

//! returns the distance between map positions a and b
extern int beeline ( const MapCoordinate& a, const MapCoordinate& b );

//! caches some calculations for the effects that wind has on the movement of units
class WindMovement {
      int wm[6];
   public:
      WindMovement ( const Vehicle* vehicle );
      int getDist ( int dir );
};


#endif

