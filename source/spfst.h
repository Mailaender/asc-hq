//     $Id: spfst.h,v 1.22 2000-09-02 15:36:50 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.21  2000/09/02 13:59:50  mbickel
//      Worked on AI
//      Started using doxygen
//
//     Revision 1.20  2000/09/01 15:47:50  mbickel
//      Added Astar path finding code
//      Fixed: viewid crashed
//      Fixed display error in ynswitch ( krkr.cpp )
//
//     Revision 1.19  2000/08/12 12:52:54  mbickel
//      Made DOS-Version compile and run again.
//
//     Revision 1.18  2000/08/12 09:17:36  gulliver
//     *** empty log message ***
//
//     Revision 1.17  2000/08/02 10:28:27  mbickel
//      Fixed: generator vehicle not working
//      Streams can now report their name
//      Field information shows units filename
//
//     Revision 1.16  2000/07/23 17:59:53  mbickel
//      various AI improvements
//      new terrain information window
//
//     Revision 1.15  2000/07/16 14:57:44  mbickel
//      Datafile versioning
//
//     Revision 1.14  2000/07/16 14:20:06  mbickel
//      AI has now some primitive tactics implemented
//      Some clean up
//        moved weapon functions to attack.cpp
//      Mount doesn't modify PCX files any more.
//
//     Revision 1.13  2000/07/06 11:07:29  mbickel
//      More AI work
//      Started modularizing the attack formula
//
//     Revision 1.12  2000/07/02 21:04:14  mbickel
//      Fixed crash in Replay
//      Fixed graphic errors in replay
//
//     Revision 1.11  2000/06/28 19:26:18  mbickel
//      fixed bug in object generation by building removal
//      Added artint.cpp to makefiles
//      Some cleanup
//
//     Revision 1.10  2000/06/08 21:03:43  mbickel
//      New vehicle action: attack
//      wrote documentation for vehicle actions
//
//     Revision 1.9  2000/05/30 18:39:27  mbickel
//      Added support for multiple directories
//      Moved DOS specific files to a separate directory
//
//     Revision 1.8  2000/05/23 20:40:52  mbickel
//      Removed boolean type
//
//     Revision 1.7  2000/04/27 16:25:30  mbickel
//      Attack functions cleanup
//      New vehicle categories
//      Rewrote resource production in ASC resource mode
//      Improved mine system: several mines on a single field allowed
//      Added unitctrl.* : Interface for vehicle functions
//        currently movement and height change included
//      Changed timer to SDL_GetTicks
//
//     Revision 1.6  2000/04/17 16:27:23  mbickel
//      Optimized vehicle movement for SDL version
//
//     Revision 1.5  1999/12/28 21:03:24  mbickel
//      Continued Linux port
//      Added KDevelop project files
//
//     Revision 1.4  1999/11/25 22:00:14  mbickel
//      Added weapon information window
//      Added support for primary offscreen frame buffers to graphics engine
//      Restored file time handling for DOS version
//
//     Revision 1.3  1999/11/22 18:28:02  mbickel
//      Restructured graphics engine:
//        VESA now only for DOS
//        BASEGFX should be platform independant
//        new interface for initialization
//      Rewrote all ASM code in C++, but it is still available for the Watcom
//        versions
//      Fixed bugs in RLE decompression, BI map importer and the view calculation
//
//     Revision 1.2  1999/11/16 03:42:35  tmwilson
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

#ifndef spfst_h
  #define spfst_h

/*! \file spfst.h
    \brief map accessing routines used by ASC and the mapeditor


*/




  #include "newfont.h"
  #include "keybp.h"
  #include "basegfx.h"
  #include "mousehnd.h"
  #include "typen.h"

#pragma pack(1)

   struct Schriften {          
               pfont        smallarial;
               pfont        smallsystem;
               pfont        large;
               pfont        arial8; 
               pfont        guifont;
               pfont        guicolfont;
               pfont        monogui;
            } ; 
   extern Schriften schriften;

   extern int dataVersion;

   class tcursor { 
           public:
              int       posx, posy;
              char      an; 
              int       color; 

              int  gotoxy (int x, int y, int disp = 1 );     // result: 0: map wurde nicht neu angezeigt     1: map wurde neu angezeigt
              void show ( void );
              void hide ( void );
              void setcolor ( int col );
              void init ( void );
              void display ( void );
              void reset ( void );
              void*        markfield; 
              void*        picture; 
              void*        orgpicture;
              int          actpictwidth;

              int         checkposition ( int x, int y );

              virtual void getimg  ( void );
              virtual void putimg  ( void );
              virtual void putbkgr ( void );
              int          oposx, oposy;
              void*      backgrnd; 
              virtual void checksize ( void );
   };

  class   tsearchfields {
                public:
                    int         startx, starty;
                    int         abbruch;
                    int         maxdistance, mindistance;
                    int         xp, yp;
                    int         dist;
                    tsearchfields ( void );
                    virtual void testfield ( void ) = 0;
                    void initsuche ( int  sx, int  sy, word max, word min );
                    virtual void startsuche ( void );
                 };


  extern tcursor cursor; 
  extern pmap actmap; 


  extern int  terraintypenum, vehicletypenum, buildingtypenum, technologynum, objecttypenum;


  extern char godview, tempsvisible; 

  extern int lasttick;   /*  f?r paintvehicleinfo  */ 

/*!
  \brief calculate the height difference between two levels of height
  Since floating and ground based are assumed to be the same effective height, a simple subtraction isn't sufficient.
 */
extern int getheightdelta ( int height1, int height2 );

extern void  movecursor(tkey         ch);

extern void  displaymap(void);


  /*  zugriffe auf map und andere strukturen  */ 

/*!
  \brief returns the field that is selected with the cursor
 */
extern pfield getactfield(void);

/*!
  \brief returns the field at the given coordinates
 */
extern pfield getfield(int x, int y);

extern pfield getbuildingfield( const pbuilding    bld,
                              shortint     x,
                              shortint     y);

extern void  getbuildingfieldcoordinates( const pbuilding    bld,
                                         shortint     x,
                                         shortint     y,
                                         int     &    xx,
                                         int     &    yy);

/*!
  \brief returns the x coordinate of the cursor location
 */
extern word  getxpos(void);

/*!
  \brief returns the y coordinate of the cursor location
 */
extern word  getypos(void);


/*!
  evaluates the visibility of a field
  \param pe the field to be evaluated
  \param player the player who is 'looking'
 */
extern bool fieldvisiblenow( const pfield pe, int player = actmap->actplayer );

/*!
  evaluates the visibility of a field
  \param pe the field to be evaluated
  \param player the player who is 'looking'
  \return visible_not .. visible_all
 */
extern int fieldVisibility  ( const pfield pe, int player = actmap->actplayer );

extern int getdiplomaticstatus( int b );

extern int getdiplomaticstatus2( int c, int b);

extern void  removevehicle(pvehicle *   vehicle);

extern void  generatevehicle_ka(pvehicletype fztyp,
                             int col,
                             pvehicle &   vehicle);
// Die Einheit wird automatisch vollgef?llt.
//  => Nur f?r Karteneditor


extern void         generate_vehicle(pvehicletype fztyp,
                             int col,
                             pvehicle &   vehicle);


extern void  putbuilding(int          x,
                         int          y,
                         int          color,
                         pbuildingtype buildingtyp,
                         int          compl,
                         int          ignoreunits = 0 ); // f?r Kartened

extern void  putbuilding2(integer      x,
                          integer      y,
                          int color,
                          pbuildingtype buildingtyp);  // f?r Spiel


extern void  removebuilding(pbuilding *  bld);


/*  hilfsfunktionen zum handhaben des mapes  */ 

extern void  calculateallobjects(void);

extern void  calculateobject(integer      x,
                              integer      y,
                              char      mof,
                              pobjecttype obj);

extern void  generatemap( const pwterraintype bt,
                               int          xsize,
                               int          ysize);

extern void  putstreets2( int          x1,
                          int          y1,
                          int          x2,
                          int          y2,
                          pobjecttype obj );

extern void  getnextfield(int &    x,
                          int &    y,
                          int direc);

extern void  getnextfielddir(int &    x,
                             int &    y,
                             int direc,
                             int sdir);

extern int   getdirection(    int      x1,
                              int      y1,
                              int      x2,
                              int      y2);

extern int resizemap( int top, int bottom, int left, int right );

extern void  clearfahrspuren(void);

extern void  initmap(void);

  /*  vehicle  */ 

extern int fieldaccessible( const pfield        field,
                            const pvehicle     vehicle,
                            int  uheight = -1 );

  /*  sonstiges  */ 


extern void* getmineadress( int num , int uncompressed = 0 );

extern void         initspfst( int x = 10, int y = 20 );

extern void generatespfdspaces();

extern void         checkfieldsformouse ( void );

extern void  checkunitsforremoval ( void );
extern void checkobjectsforremoval ( void );

extern int          getmaxwindspeedforunit ( const pvehicle eht );
extern int          getwindheightforunit   ( const pvehicle eht );
extern void         resetbuildingpicturepointers ( pbuilding bld );
extern void         resetallbuildingpicturepointers ( void );

extern int          terrainaccessible (  const pfield        field, const pvehicle     vehicle, int uheight = -1 );
extern int          terrainaccessible2 ( const pfield        field, const pvehicle     vehicle, int uheight = -1 );  
               /* same as terrainaccessible, but it returns why the unit cannot drive onto the terrain
                  returns:  -1   very deep water required to submerge deep
                            -2   deep water required to submerge 
                            -3   unit cannot drive onto terrain
               */

//! return the screencoordinates of the upper left position of the displayed map
extern int getmapposx ( void );  

//! return the screencoordinates of the upper left position of the displayed map
extern int getmapposy ( void );

class tgeneraldisplaymapbase {
           protected:
             struct {
                   struct {
                      int x1, y1, x2, y2;
                   } disp;
                   int     numberoffieldsx;
                   int     numberoffieldsy;
                   int     orgnumberoffieldsx;
                   int     orgnumberoffieldsy;
                   void*   vfbadress;
                   int     vfbheight;
                   int     vfbwidth;
                 } dispmapdata;

              struct {
                       void*   address;
                       tgraphmodeparameters parameters;
              } vfb;

           public:
              tmouserect invmousewindow;
              virtual int getfieldsizex ( void ) = 0;
              virtual int getfieldsizey ( void ) = 0;
              virtual int getfielddistx ( void ) = 0; 
              virtual int getfielddisty ( void ) = 0;
              virtual int getfieldposx ( int x, int y ) = 0; 
              virtual int getfieldposy ( int x, int y ) = 0;

              virtual void pnt_terrain ( void ) = 0;
              virtual void pnt_main ( void ) = 0;
              virtual void cp_buf ( void ) = 0;
              void setmouseinvisible ( void );
              void restoremouse ( void );
              tgeneraldisplaymapbase ( void );
};

#ifndef FREEMAPZOOM

class tgeneraldisplaymap : public tgeneraldisplaymapbase {
      protected:
         #ifndef HEXAGON
          char**     viereck; 
         #endif

          void putdirecpict ( int xp, int yp,  const void* ptr );
          void pnt_terrain_rect ( void );

          void clearvf ( void );
          virtual void displayadditionalunits ( int height );

      public:
          void calcviereck(void);
          int playerview;
          virtual void init ( int xs, int ys );

          virtual void pnt_terrain ( void );
          virtual void pnt_main ( void );

          virtual int  getscreenxsize( int target = 0 );   // since the screen sizes for the mapeditor and the game may be different target = 1 return the maximum of both 
          virtual int  getscreenysize( int target = 0 );
          virtual int getfieldsizex ( void ) { return fieldsizex; };
          virtual int getfieldsizey ( void ) { return fieldsizey; };
          virtual int getfielddistx ( void ) { return fielddistx; };
          virtual int getfielddisty ( void ) { return fielddisty; };
          virtual int getfieldposx ( int x, int y ) ; 
          virtual int getfieldposy ( int x, int y ) ;
      };



class tdisplaymap : public tgeneraldisplaymap {
        protected:
          struct {
                    pvehicle eht;
                    int xpos, ypos;
                    int dx,   dy;
                    int hgt;
                 } displaymovingunit ;

          struct {
             #ifndef HEXAGON
              int*    spacingbuf;
              int*    direcpictbuf;
             #endif
              int*    screenmaskbuf;
          } displaybuffer;
          int resolutionx;
          int resolutiony;

          virtual void displayadditionalunits ( int height );

          void generate_map_mask ( int* sze );

          tgraphmodeparameters rgmp;
          int game_x;
          int maped_x;

          virtual void gnt_terrain ( void );

       public:
          void* getbufptr( void ) { return dispmapdata.vfbadress; };
          virtual void init ( int xs, int ys );
          void setxsizes ( int _game_x, int _maped_x );
         #ifndef HEXAGON
          void generatespfdspaces ( void );
          void generatespfdptrs ( int xp, int yp );
         #endif

          void setup_map_mask ( void );


          virtual void pnt_terrain ( void );
          virtual void cp_buf ( void );
		
		  virtual void cp_buf ( int x1, int y1, int x2, int y2 );

          void  movevehicle( int x1,int y1, int x2, int y2, pvehicle eht, int height1, int height2, int fieldnum, int totalmove );
          void  deletevehicle ( void ); 

          void resetmovement ( void );
          virtual int  getscreenxsize( int target = 0 );
     } ;

#else

class tgeneraldisplaymap : public tgeneraldisplaymapbase {
      protected:
          int zoom;

          void putdirecpict ( int xp, int yp,  const void* ptr );
          void pnt_terrain_rect ( void );

          struct {
             int xsize, ysize;
          } window;

          virtual void displayadditionalunits ( int height );

          virtual void _init ( int xs, int ys );

      public:
          virtual void init ( int xs, int ys );
          int playerview;

          virtual void pnt_terrain ( void );
          virtual void pnt_main ( void );
          virtual void setnewsize ( int _zoom );

          virtual int  getscreenxsize( int target = 0 );   // since the screen sizes for the mapeditor and the game may be different target = 1 return the maximum of both 
          virtual int  getscreenysize( int target = 0 );
          virtual int getfieldsizex ( void );
          virtual int getfieldsizey ( void );
          virtual int getfielddistx ( void );
          virtual int getfielddisty ( void );
      };



class tdisplaymap : public tgeneraldisplaymap {
         tgraphmodeparameters oldparameters;
        protected:
          struct {
                    pvehicle eht;
                    int xpos, ypos;
                    int dx,   dy;
                    int hgt;
                 } displaymovingunit ;

          int windowx1, windowy1;

          virtual void displayadditionalunits ( int height );

          void generate_map_mask ( int* sze );

          tgraphmodeparameters rgmp;

          int* copybufsteps;
          int* copybufstepwidth;
          int vfbwidthused;
          void calcdisplaycache( void );

       public:
          virtual void init ( int x1, int y1, int x2, int y2 );
          virtual void setnewsize ( int _zoom );


          virtual void cp_buf ( void );
          virtual void cp_buf ( int x1, int y1, int x2, int y2 );

          void  movevehicle( int x1,int y1, int x2, int y2, pvehicle eht, int height1, int height2, int fieldnum, int totalmove );
          void  deletevehicle ( void ); 

          void resetmovement ( void );

          virtual int getfieldposx ( int x, int y ) ; 
          virtual int getfieldposy ( int x, int y ) ;
          tdisplaymap ( void );
     } ;
#endif







extern tdisplaymap idisplaymap;
extern int showresources;
extern void checkplayernames ( void );

extern int   getfieldundermouse ( int* x, int* y );

extern int getcrc ( const pvehicletype fzt );
extern int getcrc ( const ptechnology tech );
extern int getcrc ( const pobjecttype obj );
extern int getcrc ( const pterraintype bdn );
extern int getcrc ( const pbuildingtype bld );

extern void writemaptopcx ( void );

class tlockdispspfld {
      public:
        tlockdispspfld ( void );
        ~tlockdispspfld ();
      };

extern int lockdisplaymap;

extern int beeline ( int x1, int y1, int x2, int y2 );
extern int beeline ( const pvehicle a, const pvehicle b );
extern void smooth ( int what );
extern void  stu_height ( pvehicle vehicle );


extern pterraintype getterraintype_forid ( int id, int crccheck = 1 );
extern pobjecttype getobjecttype_forid ( int id, int crccheck = 1 );
extern pvehicletype getvehicletype_forid ( int id, int crccheck = 1 );
extern pbuildingtype getbuildingtype_forid ( int id, int crccheck = 1 );
extern ptechnology gettechnology_forid ( int id, int crccheck = 1 );

extern pterraintype getterraintype_forpos ( int pos, int crccheck = 1 );
extern pobjecttype getobjecttype_forpos ( int pos, int crccheck = 1 );
extern pvehicletype getvehicletype_forpos ( int pos, int crccheck = 1 );
extern pbuildingtype getbuildingtype_forpos ( int pos, int crccheck = 1 );
extern ptechnology gettechnology_forpos ( int pos, int crccheck = 1 );

extern void addterraintype ( pterraintype bdt );
extern void addobjecttype ( pobjecttype obj );
extern void addvehicletype ( pvehicletype vhcl );
extern void addbuildingtype ( pbuildingtype bld );
extern void addtechnology ( ptechnology tech );


typedef dynamic_array<pvehicletype> VehicleTypeVector;
extern VehicleTypeVector& getvehicletypevector ( void );

typedef dynamic_array<pterraintype> TerrainTypeVector;
extern TerrainTypeVector& getterraintypevector ( void );

typedef dynamic_array<pbuildingtype> BuildingTypeVector;
extern BuildingTypeVector& getbuildingtypevector ( void );

typedef dynamic_array<pobjecttype> ObjectTypeVector;
extern ObjectTypeVector& getobjecttypevector ( void );


class tpaintmapborder {
          protected:
            struct {
               int x1, y1, x2, y2;
               int initialized;
            } rectangleborder;
          public:
            virtual void paintborder ( int x, int y ) = 0;
            virtual void paint ( int resavebackground = 0 ) = 0;
            virtual int getlastpaintmode ( void ) = 0;
            virtual void setrectangleborderpos ( int x1, int y1, int x2, int y2 ) {
               rectangleborder.x1 = x1;
               rectangleborder.x2 = x2;
               rectangleborder.y1 = y1;
               rectangleborder.y2 = y2;
               rectangleborder.initialized = 1;
            };
            tpaintmapborder ( void ) {
               rectangleborder.initialized = 0;
            };
      };

extern tpaintmapborder* mapborderpainter;
extern void swapbuildings ( pbuilding orgbuilding, pbuilding building );
// extern void swapvehicles ( pvehicle orgvehicle, pvehicle transport );

extern void checkformousescrolling ( void );

class tmousescrollproc : public tsubmousehandler {
         public:
           void mouseaction ( void );
};
extern tmousescrollproc mousescrollproc ;
extern const int mousehotspots[9][2];

#ifdef FREEMAPZOOM
class ZoomLevel {
         int zoom;
         int queried;
       public:
         int getzoomlevel ( void );
         void setzoomlevel ( int newzoom );
         int getmaxzoom( void );
         int getminzoom( void );
         ZoomLevel ( void );
      };
extern ZoomLevel zoomlevel;
#endif


class tdrawline8 : public tdrawline {
         public: 
           void start ( int x1, int y1, int x2, int y2 );
           virtual void putpix ( int x, int y );
           virtual void putpix8 ( int x, int y ) = 0;
       };

class MapDisplayInterface {
         public:
           virtual int displayMovingUnit ( int x1,int y1, int x2, int y2, pvehicle vehicle, int height1, int height2, int fieldnum, int totalmove ) = 0;
           virtual void deleteVehicle ( pvehicle vehicle ) = 0;
           virtual void displayMap ( void ) = 0;
           virtual void displayPosition ( int x, int y ) = 0;
           virtual void resetMovement ( void ) = 0;
           virtual void startAction ( void ) = 0;
           virtual void stopAction ( void ) = 0;
           virtual void displayActionCursor ( int x1, int y1, int x2, int y2 ) = 0;
           virtual ~MapDisplayInterface () {};
       };

class MapDisplay : public MapDisplayInterface {
           dynamic_array<int> cursorstat;
           int cursorstatnum;
         public:
           int displayMovingUnit ( int x1,int y1, int x2, int y2, pvehicle vehicle, int height1, int height2, int fieldnum, int totalmove );
           void deleteVehicle ( pvehicle vehicle );
           void displayMap ( void );
           void displayPosition ( int x, int y );
           void resetMovement ( void );
           void startAction ( void );
           void stopAction ( void );
           void displayActionCursor ( int x1, int y1, int x2, int y2 ) {};
    };

extern MapDisplay defaultMapDisplay;

#ifdef _NOASM_
 int  rol ( int valuetorol, int rolwidth );
 void setvisibility ( word* visi, int valtoset, int actplayer );
#else
 #include "dos/spfldutl.h"
#endif

#pragma pack()

#endif


