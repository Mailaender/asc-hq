//     $Id: typen.h,v 1.73 2000-12-31 15:25:26 mbickel Exp $
//
//     $Log: not supported by cvs2svn $
//     Revision 1.72  2000/12/28 16:58:39  mbickel
//      Fixed bugs in AI
//      Some cleanup
//      Fixed crash in building construction
//
//     Revision 1.71  2000/12/21 11:00:50  mbickel
//      Added some code documentation
//
//     Revision 1.70  2000/11/29 11:05:31  mbickel
//      Improved userinterface of the mapeditor
//      map::preferredfilenames uses now strings (instead of char*)
//
//     Revision 1.69  2000/11/29 09:40:25  mbickel
//      The mapeditor has now two maps simultaneously active
//      Moved memorychecking functions to its own file: memorycheck.cpp
//      Rewrote password handling in ASC
//
//     Revision 1.68  2000/11/15 19:28:36  mbickel
//      AI improvements
//
//     Revision 1.67  2000/11/14 20:36:45  mbickel
//      The AI can now use supply vehicles
//      Rewrote objecttype IO routines to make the structure independant of
//       the memory layout
//
//     Revision 1.66  2000/11/11 11:05:20  mbickel
//      started AI service functions
//
//     Revision 1.65  2000/11/08 19:37:40  mbickel
//      Changed the terrain types (again): "lava" now replaces "small trench"
//
//     Revision 1.64  2000/11/08 19:31:16  mbickel
//      Rewrote IO for the tmap structure
//      Fixed crash when entering damaged building
//      Fixed crash in AI
//      Removed item CRCs
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

#ifndef typen_h                                                                            
#define typen_h

#include <time.h>
#include <list>
#include <bitset>

#include "global.h"

#ifdef HAVE_LIMITS
 #include <limits>
#else
 #include <limits.h>
#endif


#include "tpascal.inc"
#include "misc.h"
#include "basestrm.h"
#include "errors.h"

#include "password.h"

#pragma pack(1)


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/// Some boring pointer definitions
///  The main structure start at line 440
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

typedef class tterrainaccess *pterrainaccess;
typedef struct tcrc *pcrc;
typedef class Vehicle  tvehicle ;
typedef class Vehicle* pvehicle ;
typedef struct tbuildrange* pbuildrange;
typedef class tobjecttype* pobjecttype;
typedef class tmap*  pmap;
typedef class tmap Map;
typedef class tevent* pevent ;
typedef class  ttechnology* ptechnology ;
typedef class tresearch* presearch ;
typedef struct tdevelopedtechnologies*  pdevelopedtechnologies;
typedef char* pchar;
typedef class tbasenetworkconnection* pbasenetworkconnection;
typedef class tnetwork* pnetwork;
typedef struct tquickview* pquickview;
typedef struct tterraintype* pterraintype;
typedef class  twterraintype* pwterraintype ;
typedef class tfield* pfield ;
typedef class tobjectcontainer* pobjectcontainer;
typedef struct tresourceview* presourceview;
typedef class tobject* pobject;
typedef class tshareview *pshareview;
                   
//////////////////////////////////////////////////////////////
///    Some miscellaneous defintions. Not very intersting...
//////////////////////////////////////////////////////////////

//! fractiton of the production cost is needed if a unit repairs something
const int repairefficiency_unit = 2;

//! fractiton of the production cost is needed if a building repairs something
const int repairefficiency_building = 3;


enum tshareviewmode { sv_none, sv_shareview };

/*
  struct PreferredFilenames {
    char* mapname[8];
    char* mapdescription_not_used_any_more[8];
    char* savegame[8];
    char* savegamedescription_not_used_any_more[8];
  };
*/

  struct PreferredFilenames {
    string mapname[8];
    string savegame[8];
  };

  class  EllipseOnScreen {
  public:
    int x1, y1, x2, y2;
    int color;
    float precision;
    int active;
    EllipseOnScreen ( void ) { active = 0; };
    void paint ( void );
  };


//! The number of different weapon types
const int waffenanzahl = 8;

//! The number of different weather; Be careful: 'fog' is included here, but it is not used and has a different concept
const int cwettertypennum = 6;

//! The number of vehicle categories; Each category has its own move malus
const int cmovemalitypenum  = 16;

//! The movemalus type for a building. It is used for #SingleWeapon.targets_not_hittable .
const int cmm_building = 11;

//! The number of levels of height
const int choehenstufennum =  8;

//! The maximum number of number of different images for a building and a weather. For example, A wind power plant might have 6 different images, depending on the direction of the wind.
const int maxbuildingpicnum  = 8;

//! The maximum number of mines that can be placed on a single field
const int maxminesonfield = 20;

//! The number of game paramters that can be specified for each map.
const int gameparameternum = 19;

//! The maximum number of objects ( #tobject ) that can be placed on a single field ( #tfield )
const int maxobjectonfieldnum = 16;

//! The maximum experience value of a #Vehicle
const int maxunitexperience = 23;

//! the number of bits that specify the terrain of a field
const int cbodenartennum = 33;


// typedef bitset<cbodenartennum> tterrainbits;


class tterrainbits {
#ifdef converter
 public:
#endif
  int terrain1;
  int terrain2;
 public:
  tterrainbits ( int i = 0 ) { 
      set ( i ); 
  };
  tterrainbits ( int i , int j ) { 
      terrain1 = i; 
      terrain2 = j; 
  };
  tterrainbits ( tterrainbits &bts ) { 
      terrain1 = bts.terrain1; 
      terrain2 = bts.terrain2; 
  };
  void set ( int i = 0, int j = 0 ) { 
     terrain1 = i; 
     terrain2 = j; 
  };

  void read ( tnstream& stream ) { 
     terrain1 = stream.readInt(); 
     terrain2 = stream.readInt(); 
  };

  void write ( tnstream& stream ) { 
     stream.writeInt( terrain1 );
     stream.writeInt ( terrain2 ); 
  };


  int get32bit ( int pos ) {
     if ( pos == 0 )
        return terrain1;
     else
        return terrain2;
  };


  int toand ( tterrainbits bts );
  int existall ( tterrainbits bdt ) {
      return  ((terrain1 & bdt.terrain1) == bdt.terrain1) && ((terrain2 & bdt.terrain2) == bdt.terrain2);
  };

  tterrainbits& operator|= ( tterrainbits tb )  { 
    terrain1 |= tb.terrain1; 
    terrain2 |= tb.terrain2; 
    return *this;
  };

  tterrainbits& operator&= ( tterrainbits tb ) { 
    terrain1 &= tb.terrain1; 
    terrain2 &= tb.terrain2; 
    return *this;
  };

  tterrainbits& operator^= ( tterrainbits tb ) { 
    terrain1 ^= tb.terrain1; 
    terrain2 ^= tb.terrain2; 
    return *this;
  };

  friend tterrainbits& operator~ ( tterrainbits &tb );
  int getcrc ( void ) {
    return crc32buf ( &terrain1, 2 * sizeof ( int ));
  }
};


/* These operators are crap. But since they are used only by tterrainaccess.accessible, which knows
   that they are crap, the system is working ...
*/


extern tterrainbits& operator~ ( tterrainbits &tb );
extern tterrainbits& operator| ( tterrainbits tb2, tterrainbits tb3 ) ;
extern int operator& ( tterrainbits tb2, tterrainbits tb3 ) ;
extern tterrainbits& operator^ ( tterrainbits tb2, tterrainbits tb3 ) ;

class tterrainaccess {
   public:
      tterrainaccess ( void ) ;
      tterrainbits  terrain;      /*  BM     befahrbare terrain: z.B. Schiene, Wasser, Wald, ...  ; es muss lediglich eins gesetzt sein */
      tterrainbits  terrainreq;   /*  BM     diese Bits M�SSEN ALLE in gesetzt sein */
      tterrainbits  terrainnot;   /*  BM     sobald eines dieser Bits gesetzt ist, kann die vehicle NICHT auf das field fahren  */
      tterrainbits  terrainkill;  /* falls das aktuelle field nicht befahrbar ist, und bei field->typ->art eine dieser Bits gesetzt ist, verschwindet die vehicle */
      int dummy[10];
      int accessible ( tterrainbits bts );
      /*
      int getcrc ( void ) {
        return terrain.getcrc() + terrainreq.getcrc()*7 + terrainnot.getcrc()*97 + terrainkill.getcrc()*997;  
      };
      */

      void read ( tnstream& stream ) {
         terrain.read ( stream );
         terrainreq.read ( stream );
         terrainnot.read ( stream );
         terrainkill.read ( stream );
         
         for ( int a = 0; a < 10; a++ )
             stream.readInt( ); //dummy
      };

      void write ( tnstream& stream ) {
         terrain.write ( stream );
         terrainreq.write ( stream );
         terrainnot.write ( stream );
         terrainkill.write ( stream );

         for ( int a = 0; a < 10; a++ )
             stream.writeInt( 0 ); //dummy
      };
      
};


struct tcrc {
  int id;
  int crc;
};


struct tbuildrange {
  int from;
  int to;
};


//! The number of different resources that ASC uses
const int resourceTypeNum = 3;
//! The number of different resources that ASC uses
const int resourceNum = resourceTypeNum;

class Resources {
  public:
     int energy;
     int material;
     int fuel;

     int& resource ( int type ) {
        switch ( type ) {
           case 0: return energy;
           case 1: return material;
           case 2: return fuel;
           default: throw OutOfRange();
        }
     };

     const int& resource ( int type ) const {
        switch ( type ) {
           case 0: return energy;
           case 1: return material;
           case 2: return fuel;
           default: throw OutOfRange();
        }
     };

     Resources ( void ) : energy ( 0 ), material ( 0 ), fuel ( 0 ) {};
     Resources ( int e, int m, int f ) : energy ( e ), material ( m ), fuel ( f ) {};
     Resources& operator-= ( const Resources& res ) { energy-=res.energy; material-=res.material; fuel-=res.fuel; return *this;};
     bool operator>= ( const Resources& res ) { return energy >= res.energy && material>=res.material && fuel>=res.fuel; };
     enum { Energy, Material, Fuel };
     void read ( tnstream& stream );
     void write ( tnstream& stream );
};

extern Resources operator- ( const Resources& res1, const Resources& res2 );


//! A mathematical matrix that can be multiplied with a #Resources instance (which is mathematically a vector) to form a new #Resources vector
class ResourceMatrix {
           float e[resourceTypeNum][resourceTypeNum];
        public:
           ResourceMatrix ( const float* f );
           Resources operator* ( const Resources& r ) const;
};

// Resources operator* ( const ResourceMatrix& m, const Resources& r );


class tbuildingtype_bi_picture {
 public:
  int num [ maxbuildingpicnum ][4][6];

  tbuildingtype_bi_picture ( void ) {
    for ( int i = 0; i < maxbuildingpicnum; i++ )
      for ( int j = 0; j < 4; j++ )
        for ( int k = 0; j < 6; j++ )
          num[i][j][k] = -1;
  };
};


//! the image for a terraintype ( #tterraintype ) that is shown on the small map
struct tquickview {
   struct {
      char p1;
      char p3[3][3];
      char p5[5][5];
   } dir[8];
};





  struct thexpic {
    void* picture;
    int   bi3pic;
    int   flip;  // Bit 1: Horizontal ; Bit 2: Vertikal
  };


typedef struct teventstore* peventstore;
struct teventstore { 
    int          num; 
    peventstore  next; 
    int      eventid[256]; 
    int      mapid[256];
};

  enum tplayerstat { ps_human, ps_computer, ps_off };

  class  tshareview {
  public:
    tshareview ( void ) { recalculateview = 0; };
    tshareview ( const tshareview* org );
    char mode[8][8];
    int recalculateview;
  };
  // mode[1][6] = visible_all    =>  Spieler 1 gibt Spieler 6 die view frei



#ifndef pmemorystreambuf_defined
  #define pmemorystreambuf_defined
  typedef class tmemorystreambuf* pmemorystreambuf;
  typedef class tmemorystream* pmemorystream;
#endif

  class treplayinfo {
  public:
    pmemorystreambuf guidata[8];
    pmemorystreambuf map[8];
    pmemorystream    actmemstream;
    treplayinfo ( void );
    ~treplayinfo ( );
  };

  typedef class  tmessage* pmessage;
  class  tmessage {
  public:
    int from;      // BM ; Bit 9 ist system
    int to;        // BM
    time_t time;
    char* text;
    int id;
    int runde;  //  Zeitpunkt des abschickens
    int move;   //  "
    pmessage next;
    tmessage ( void );
    tmessage ( pmap spfld );
    tmessage ( char* txt, int rec );  // fuer Meldungen vom System
    ~tmessage();
  };


  typedef class tmessagelist* pmessagelist;
  class tmessagelist {
  public:
    pmessage message;
    pmessagelist next;
    pmessagelist prev;
    tmessagelist( pmessagelist* prv );
    ~tmessagelist(  );
    int getlistsize ( void );  // liefert 1 falls noch weitere Glieder in der Liste existieren, sonst 0;
  };

/*
  typedef class tspeedcrccheck* pspeedcrccheck;
  typedef class tcrcblock* pcrcblock;

  class tcrcblock {
  public:
    int  crcnum;
    pcrc crc;
    int restricted;
    // restricted kennt 3 Zust�nde: 0 = nicht limitiert, neue vehicle werden nicht aufgenommen; 
    //                              1 = nicht limitiert, neue vehicle werden aufgenommen
    //                              2 = limitiert: es d?rfen nur vehicle verwendet werden, deren CRCs bekannt sind
    tcrcblock ( void );
  };


  typedef class tobjectcontainercrcs *pobjectcontainercrcs;
  class tobjectcontainercrcs {
  public:
    tcrcblock unit;
    tcrcblock building;
    tcrcblock object;
    tcrcblock terrain;
    tcrcblock technology;

    pspeedcrccheck speedcrccheck;

    tobjectcontainercrcs ( void );

    int dummy[40];
  };

*/

//! how many different target types are there?
const int aiValueTypeNum = 8;  

class AiThreat {
       public:
         const int threatTypes;
         int threat[aiValueTypeNum];
         void reset ( void );
         AiThreat ( void ) : threatTypes ( aiValueTypeNum ) { reset(); };
         AiThreat& operator+= ( const AiThreat& t );
};

//! the time in ASC, measured in turns and moves
union tgametime {
  struct { signed short move, turn; }a ;
  int abstime;
};


//! Coordinate on the twodimensional map
class MapCoordinate {
         public:
            int x;
            int y;
            MapCoordinate ( ) : x(-1), y(-1 ) {};
            MapCoordinate ( int _x, int _y) : x(_x), y(_y) {};
            bool operator< ( const MapCoordinate& mc ) const { return y < mc.y || ( y == mc.y && x < mc.x );};
      };


//! Coordinate on the map including height
class MapCoordinate3D : public MapCoordinate {
         public:
            int z;
            int getBitmappedHeight ( ) { return 1<<z; };
            int getNumericalHeight ( ) { return z; };
            MapCoordinate3D ( ) : MapCoordinate(), z(-1) {};
            MapCoordinate3D ( int _x, int _y, int _z) : MapCoordinate ( _x, _y ), z ( _z ) {};
            MapCoordinate3D ( const MapCoordinate& mc ) : MapCoordinate ( mc ), z ( -1 ) {};
      };


class AiValue {
        public:
           AiThreat threat;
           int value;
           int valueType;
           void reset ( int _valueType ) { threat.reset(); value = 0; valueType = _valueType; };

           AiValue ( int _valueType ) { reset( _valueType ); };
        };

class AiParameter : public AiValue {
           pvehicle unit;
        public:
           enum Task { tsk_nothing, tsk_tactics, tsk_tactwait, tsk_stratwait, tsk_wait, tsk_strategy, tsk_serviceRetreat, tsk_move } task;
           enum Job { job_undefined, job_fight, job_supply, job_conquer, job_build } job;
           int lastDamage;
           tgametime damageTime;

           MapCoordinate3D dest;
           int dest_nwid;
           int data;

           void reset ( pvehicle _unit );
           void resetTask ( );
           AiParameter ( pvehicle _unit );
           // AiParameter ( const AiParameter& aip );
 };

class BaseAI { 
       public: 
         virtual void run ( void ) = 0;
         virtual bool isRunning ( void ) = 0;
         virtual int getVision ( void ) = 0;
         virtual ~BaseAI () {};
      };


 typedef class  Buildingtype* pbuildingtype;
 typedef class  Vehicletype*  pvehicletype ;

 typedef class  Building* pbuilding;
 typedef class  Vehicle*  pvehicle;


//! A list that stores pointers, but deletes the objects (and not only the pointers) on destruction
template <class T> class PointerList : public list<T> {
   public:
     ~PointerList() {
        for ( iterator it=begin(); it!=end(); it++ )
            delete *it;
     };
};



/*
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
///    Now, these are the main structures ASC consists of
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
*/



class  twterraintype {
  public:
    void*        picture[8];
    void*        direcpict[8];
    int            defensebonus;
    int            attackbonus;
    int            basicjamming;
    char           movemaluscount;
    char*          movemalus;
    pterraintype  terraintype;
    pquickview     quickview;
    void           paint ( int x1, int y1 );
    int            bi_picture[6]; 
    tterrainbits   art; 
};

struct tterraintype {
    char*              name;
    int                id;
    pwterraintype   weather[cwettertypennum];
    int                neighbouringfield[8];   
};


//! An object that can be placed on fields. Roads, pipelines and ditches are examples of objects.
class tobjecttype {
  public: 
    //! the id of the object, used when referencing objects in files
    int id;

    //! bitmapped variable containing the different weather types the objects exist for
    int weather;

    //! is the object displayed under fog of war
    int visibleago;

    //! some objects are graphically linked with others on neighbouring fields. This is the number of other object types that tis one links with. See #no_autonet
    int objectslinkablenum;
    //! the array of object types that this one links with. See #objectslinkablenum
    union {
      int*            objectslinkableid;
      pobjecttype*    objectslinkable;
    };

    //! the array of pictures; this is from an old definition of object types where the picture of an object could not vary with the weather. Today the images are stored in #picture
    thexpic* oldpicture;

    //! the number of pictures for each weather. Objects which link graphically with neighbouring objects need more than one picture
    int pictnum;

    //! if an object should not be attackable, set armor to 0
    int armor;

    //! In the files and the small editors this variable may be smaller than #cmovemalitypenum, even 0; but the loader extends this to #cmovemalitypenum when an object is loaded ingame
    char  movemalus_plus_count;
    //! the movemalus_plus is added to the current movemalus of the field to form the new movemalus. Negative values are ok.
    char* movemalus_plus;

    //! In the files and the small editors this variable may be smaller than #cmovemalitypenum, even 0; but the loader extends this to #cmovemalitypenum when an object is loaded ingame.
    char  movemalus_abs_count;
    //! The movemalus_abs replaces the current movemalus of the field by a new one. Values of 0 and -1 won't affect the movemalus of the field, and values ranging from 1 to 9 must not be used.
    char* movemalus_abs;

    //! this is added to the current attackbonus of the field to form the new attackbonus. 
    int attackbonus_plus;
    //! The attackbonus_abs replaces the current attackbonus of the field by a new one. A value of -1 won't affect the attackbonus of the field
    int attackbonus_abs;

    //! this is added to the current defensebonus of the field to form the new defensebonus.
    int defensebonus_plus;
    //! The defensebonus_abs replaces the current defensebonus of the field by a new one. A value of -1 won't affect the attackbonus of the field
    int defensebonus_abs;

    //! this is added to the current basicjamming of the field to form the new jamming.
    int basicjamming_plus;
    //! basicjamming_abs replaces the current basicjamming of the field by a new one. A value < 0 won't affect the jamming of the field
    int basicjamming_abs;

    //! the level of height the object is on. This is not the simple system of 8 levels used for units and building, but one with 255 levels which are documented in docs/biimport.html
    int height;   

    //! The resources required to construct the object with a unit; Note that units usually don't have any energy available
    Resources buildcost;

    //! The resources required to remove the object with a unit; Note that units usually don't have any energy available
    Resources removecost;

    //! The movement points that are needed to build this object
    int build_movecost;  

    //! The movement points that are needed to remove this object
    int remove_movecost; 

    //! The name of the object
    char* name;

    //! if != 0 this object will not graphically connect to neighbouring objects
    int no_autonet;

    //! The terrain on which this object can be placed
    tterrainaccess terrainaccess;

    //! the terrain properties of the field will be AND-masked with this field and then OR-masked with terrain_or to form the new terrain properties
    tterrainbits terrain_and;
    tterrainbits terrain_or;
    tobjecttype ( void ) : terrain_and ( -1 ) , terrain_or ( 0 ) {};
                                  
    //! the icon used for selecting the object when executing the "build object" function of a unit. The image is automatically generated at load time
    void* buildicon;
    //! the icon used for selecting the object when executing the "remove object" function of a unit. The image is automatically generated at load time
    void* removeicon;

    //! direction lists were an attempt to allow the graphical connection of this object with neighbouring ones without having an image for each possible connection layout. The attempt failed. Don't use it any more.
    int* dirlist;
    int dirlistnum;

    //! the images of the objects
    thexpic* picture[cwettertypennum];

    //! displays the objecttype at x/y on the screen
    void display ( int x, int y );
    void display ( int x, int y, int dir, int weather = 0 );

    //! returns the pointer to the image i
    void* getpic ( int i, int weather = 0 );

    //! can the object be build on the field fld
    int  buildable ( pfield fld );

    //! if the object connects graphically with others, does it connect with buildings too
    int connectablewithbuildings ( void );


    //! reads the objecttype from a stream
    void read ( tnstream& stream );
    //! write the objecttype from a stream
    void write ( tnstream& stream );
};


//! an instance of an object type (#tobjecttype) on the map
class tobject {
    public:
       pobjecttype typ;
       int damage;
       int dir;
       int time;
       int dummy[4];
       tobject ( void );
       tobject ( pobjecttype t );
       void display ( int x, int y, int weather = 0 );
       void setdir ( int dir );
       int  getdir ( void );
};

class tmine {
   public:
      int type;
      int strength;
      int time;
      int color;
      int attacksunit ( const pvehicle veh );
};


class  tobjectcontainer {
  public:
    int minenum;
    tmine* mine[ maxminesonfield ];

    int objnum;
    pobject object[ maxobjectonfieldnum ];

    tobjectcontainer ( void );
    int checkforemptyness ( void );
    pobject checkforobject ( pobjecttype o );
};

  struct tresourceview {
    tresourceview ( void );
    char    visible;      // BM
    char    fuelvisible[8];
    char    materialvisible[8];
  };

//! a single field of the map
class  tfield { 
  public:
    //! the terraintype (#pwterraintype) of the field
    pwterraintype typ;   

    //! mineral resources on this field (should be changed to #ResourcesType sometime...)
    char         fuel, material; 

    //! can this field be seen be the player. Variable is bitmapped; two bits for each player
    Word         visible;   /*  BM  */ 

    //! in the old octagonal version of ASC it was possible to rotate the terraintype; this is not used in the hexagonal version any more
    char         direction; 

    void*      picture;   
    union  {
      struct { 
        char         temp;      
        char         temp2; 
      }a;
      word tempw;
    };
    int          temp3;
    int          temp4;
    
    pvehicle     vehicle; 
    pbuilding    building; 

    //! the mineral resources that were seen by a player on this field; since the actual amount may have decreased since the player looked, this value is not identical to the fuel and material fields.
    presourceview  resourceview;

    //! objects and mines that may be placed on the field
    pobjectcontainer      object;

    //! the terraintype properties. They determine which units can move over the field. This variable is recalculated from the terraintype and objects each time something on the field changes (#setparams)
    tterrainbits  bdt;

    //! are any events connected to this field
    int connection;
             
    //! the number of mines on the field
    int minenum ( void );

    /** add an object to the field
         \param obj The object type
         \param dir The direction of the object type; -1 to use default direction 
         \param force Put the object there even if it cannot normally be placed on this terrain 
    **/
    void addobject ( pobjecttype obj, int dir = -1, int force = 0 );

    //! removes all objects of the given type from the field
    void removeobject ( pobjecttype obj );

    //! sorts the objects. Since objects can be on different levels of height, the lower one must be displayed first
    void sortobjects ( void );

    //! deletes everything placed on the field
    void deleteeverything ( void );

    //! recalculates the terrain properties, movemalus etc from the terraintype and the objects,
    void setparams ( void );

    //! checks if there are objects from the given type on the field and returns them
    pobject checkforobject ( pobjecttype o );

    //! the defense bonus that unit get when they are attacked 
    int getdefensebonus ( void );

    //! the attack bonus that unit get when they are attacking
    int getattackbonus  ( void );

    //! the weather that is on this field
    int getweather ( void );

    //! the radar jamming that is on this field
    int getjamming ( void );
    int getmovemalus ( const pvehicle veh );
    int getmovemalus ( int type );

    //! can any of the mines on this field attack this unit
    int mineattacks ( const pvehicle veh );

    //! the player who placed the mines on this field.
    int mineowner ( void );

    //! mines may have a limited lifetime. This methods removes all mines whose maxmimum lifetime is exeeded
    void checkminetime ( int time );

    //! checks if the unit is standing on this field. Since units are being cloned for some checks, this method should be used instead of comparing the pointers to the unit
    bool unitHere ( const pvehicle veh );

    //! put a mine of type typ for player col (0..7) and a punch of strength on the field. Strength is an absolute value (unlike the basestrength of a mine or the punch of the mine-weapon, which are just factors)
    bool  putmine ( int col, int typ, int strength );

    /** removes a mine
         \param num The position of the mine; if num is -1, the last mine is removed)
    **/
    void  removemine ( int num ); // num == -1 : remove last mine

    //! some variables for the viewcalculation algorithm. see #viewcalculation.cpp for details
    struct {
      int view;
      int jamming;
      char mine, satellite, sonar, direct;
    } view[8];

  private:
    int getx( void );
    int gety( void );
    unsigned char         _movemalus[cmovemalitypenum];
};


typedef class teventtrigger_polygonentered* peventtrigger_polygonentered;
class  teventtrigger_polygonentered {
  public:
    int size;
    pvehicle vehicle;
    int      vehiclenetworkid;
    int* data;
    int tempnwid;
    int tempxpos;
    int tempypos;
    int color;                // bitmapped
    int reserved[7];
    teventtrigger_polygonentered ( void );
    teventtrigger_polygonentered ( const teventtrigger_polygonentered& poly );
    ~teventtrigger_polygonentered ( );
};


typedef class LargeTriggerData* PLargeTriggerData;
class  LargeTriggerData {
  public:
    tgametime time;
    int xpos, ypos;
    int networkid;
    pbuilding    building;
    pvehicle     vehicle;  
    int          mapid;
    int          id;  
    peventtrigger_polygonentered unitpolygon;  
    int reserved[32];
    LargeTriggerData ( void );
    LargeTriggerData ( const LargeTriggerData& data );
    ~LargeTriggerData();
};


class tevent { 
  public:
    union { 
      struct {  word         saveas; char action, num;  }a;  /*  CEventActions  */
      int      id;               /* Id-Nr      ==> Technology.Requireevent; Tevent.trigger; etc.  */ 
    } ;                                          

    pascal_byte         player;   // 0..7  fuer die normalen Spieler
    // 8 wenn das Event unabh�ngig vom Spieler sofort auftreten soll
              
    char         description[20]; 

    union {
      void*    rawdata; 
      char*    chardata;
      int*     intdata;
    };
    int          datasize; 
    pevent       next; 
    int          conn;   // wird nur im Spiel gebraucht, BIt 0 gibt an, das andere events abh�nging sind von diesem
    word         trigger[4];   /*  CEventReason  */ 
    PLargeTriggerData trigger_data[4];

    pascal_byte         triggerconnect[4];   /*  CEventTriggerConn */ 
    pascal_byte         triggerstatus[4];   /*  Nur im Spiel: 0: noch nicht erf?llt
                                         1: erf?llt, kann sich aber noch �ndern
                                         2: unwiederruflich erf?llt
                                         3: unerf?llbar */ 
    tgametime     triggertime;     // Im Karteneditor auf  -1 setzen !! 
    // Werte ungleich -1 bedeuten automatisch, dass das event bereits erf?llt ist und evt. nur noch die Zeit abzuwait ist

    struct {
      int turn;
      int move;   // negative Zahlen SIND hier zul�ssig !!! 
    } delayedexecution;

    /* Funktionsweise der verzoegerten Events: 
       Sobald die Trigger erf?llt sind, wird triggertime[0] ausgef?llt. Dadurch wird das event ausgeloest,
       sobald das Spiel diese Zeit erreicht ist, unabh�ngig vom Zustand des mapes 
       ( Trigger werden nicht erneut ausgewertet !)
    */
    tevent ( void );
    tevent ( const tevent& event );
    ~tevent ( void );
}; 

/*
  struct teventact { 
    union { 
      struct {  word         saveas, action;  }a;  // Id-Nr   ==> Technology.Requireevent; Tevent.trigger; etc.  
      int      ID;    //   CEventActions  
    };
  };
*/


  /*  Datenaufbau des triggerData fieldes: [ hi 16 Bit ] [ low 16 Bit ] [ 32 bit Integer ] [ Pointer ]      [ low 24 Bit       ]  [ high 8 Bit ]
     'turn/move',                            move           turn
     'building/unit     ',Kartened/Spiel                                                   PBuilding/Pvehicle
                          disk               ypos           xpos
     'technology researched',                                             Tech. ID
     'event',                                                             Event ID
     'tribut required'                                                                                         Hoehe des Tributes      Spieler, von dem Tribut gefordert wird 
     'all enemy *.*'                                                      Bit 0: alle nicht allierten
                                                                          Bit 1: alle, die ?ber die folgenden Bits festgelegt werden, ob alliiert oder nicht
                                                                            Bit 2 : Spieler 0
                                                                            ...
                                                                            Bit 9 : Spieler 7

     'unit enters polygon'  pointer auf teventtrigger_polygonentered

     der Rest benoetigt keine weiteren Angaben
    */ 



     /*  DatenAufbau des Event-Data-Blocks:

      TLosecampaign, TEndCampaign, TWeatherchangeCompleted
                 benoetigen keine weiteren Daten


      TNewTechnologyEvent :
                 data = NULL;
                 SaveAs = TechnologyID;
              Gilt fuer researched wie auch available

      TMessageEvent
             Data = NULL;
             SaveAs: MessageID des Abschnittes in TextDatei

      TNextMapEvent:
             Data = NULL;
             saveas: ID der n�chsten Karte;

      TRunScript+NextMapEvent:
             Data = pointer auf Dateinamen des Scriptes ( *.scr );
             saveas: ID der n�chsten Karte;

      TeraseEvent:
             data[0] = ^int
                       ID des zu loeschenden Events
             data[1] = mapid

      Tweatherchange            ( je ein int , alles unter Data )
              wetter            ( -> cwettertypen , Wind ist eigene eventaction )
              fieldadressierung      ( 1: gesamtes map     )
                      �              ( 0: polygone               )
                      �              
                      ������ 0 ���>  polygonanzahl
                      �                   ���   eckenanzahl
                      �                             ��� x position
                      �                                 y position
                      �
                      �
                      ������ 1 ���|  

      Twindchange
              intensit�t[3]         ( fuer tieffliegend, normalfliegend und hochfliegend ; -1 steht fuer keine Aenderung )
              Richtung[3]           ( dito )
 

      Tmapchange               ( je ein int , alles unter Data )        { wetter wird beibehalten ! }
            numberoffields ( nicht die Anzahl fielder insgesamt, 
               ���>  bodentypid
                     drehrichtung 
                     fieldadressierung   ( wie bei tweatherchange )


      Treinforcements        ( alles unter DATA )
             int num      // ein int , der die Anzahl der vehicle angibt. Die vehicle, die ein Transporter geladen hat, werden NICHT mitgez�hlt.
                  ����� > die vehicle, mit tspfldloaders::writeunit in einen memory-stream geschrieben. 


      TnewVehicleDeveloped
            saveas  = ID des nun zur Verf?gung stehenden vehicletypes


      Tpalettechange
           Data =  Pointer auf String, der den Dateinamen der Palettendatei enth�lt.

      Talliancechange
           Data : Array[8][8] of int                      // status der Allianzen. Sollte vorerst symetrisch bleiben, also nur jeweils 7 Werte abfragen.
                                                             Vorerst einfach Zahlwerte eingeben.
                                                             256 steht fuer unver�ndert,
                                                             257 fuer umkehrung

      TGameParameterchange    
           int nummer_des_parameters ( -> gameparametername[] )
           int neuer_wert_des_parameters

      Ellipse
           int x1 , y1, x2, y2, x orientation , y orientation


    Wenn Data != NULL ist, MUss datasize die Groesse des Speicherbereichs, auf den Data zeigt, beinhalten.

 */


class tresearchdatachange {
   public:
     word         weapons[waffenanzahl];   /*  Basis 1024  */
     word         armor;         /*  Basis 1024  */
     unsigned char         dummy[20+(12-waffenanzahl)*2];
     tresearchdatachange ( void ) {
        for ( int i = 0; i< waffenanzahl; i++ )
           weapons[i] = 1024;
        armor = 1024;
        memset ( dummy, 0, sizeof(dummy ));
     };
}; 


class  ttechnology { 
  public:
    void*      icon; 
    char*        infotext; 
    int          id; 
    int          researchpoints; 
    char*        name; 

    tresearchdatachange unitimprovement; 

    char      requireevent; 

    union { 
      ptechnology  requiretechnology[6]; 
      int      requiretechnologyid[6]; 
    };

    int          techlevelget;  // sobald dieser technologylevel erreicht ist, ist die Technologie automatisch verf?gbar
    char* pictfilename;
    int lvl;     // wird nur im Spiel benoetigt: "Level" der benoetigten Techologie. Gibt an, wieviele Basistechnologien insgesamt benoetogt werden.
    int techlevelset;
    int dummy[7];
    int  getlvl( void );
};



struct tdevelopedtechnologies {
    ptechnology               tech;
    pdevelopedtechnologies    next;
};
             
class tresearch { 
  public:
    int                     progress;
    ptechnology             activetechnology;
    tresearchdatachange     unitimprovement;
    int                     techlevel;
    pdevelopedtechnologies  developedtechnologies;

    int technologyresearched ( int id );
    int vehicletypeavailable ( const pvehicletype fztyp, pmap map );       // The map should be saved as a pointer in TRESEARCH, but this will change the size of TMAP and make all existing savegames and maps invalid ....
    int vehicleclassavailable ( const pvehicletype fztyp , int classnm, pmap map );
    void read ( tnstream& stream );
    void write ( tnstream& stream );
    tresearch ( void ) {
       progress = 0;
       activetechnology = NULL;
       techlevel = 0;
       developedtechnologies = NULL;
    };

};


class twind {
  public:
    char speed;
    char direction;
    int operator== ( const twind& b ) const;
    twind ( ) : speed ( 0 ), direction ( 0 ) {};
};


#define tnetworkdatasize 100
typedef char tnetworkconnectionparameters[ tnetworkdatasize ];
typedef tnetworkconnectionparameters* pnetworkconnectionparameters;


class tnetworkcomputer {
  public:
    char*        name;
    struct {
      int          transfermethodid;
      pbasenetworkconnection transfermethod;
      tnetworkconnectionparameters         data;
    } send, receive;
    int          existent;
    tnetworkcomputer ( void );
    ~tnetworkcomputer ( );
};


class  tnetwork {
  public:
    struct {
      char         compposition;   // Nr. des Computers, an dem der SPieler spielt    => network.computernames
      int          codewordcrc;
    } player[8];

    tnetworkcomputer computer[8];

    int computernum;
    int turn;
    struct tglobalparams {
      int enablesaveloadofgames;
      int reaskpasswords;
      int dummy[48];
    } globalparams;
    tnetwork ( void );
};


  typedef struct tdissectedunit* pdissectedunit;
  struct tdissectedunit {
    pvehicletype  fzt;
    ptechnology   tech;
    int           orgpoints;
    int           points;
    int           num;
    pdissectedunit next;
  };


//! the map. THE central structure of ASC
class tmap { 
   public:
      //! the size of the map
      word         xsize, ysize;   

      //! the coordinate of the map that is displayed on upper left corner of the screen
      word         xpos, ypos;     

      //! the array of fields
      pfield       field;           

      //! the codeword for accessing a map in a campaign
      char         codeword[11]; 

      //! the title of the map
      char*        title;

      struct Campaign {
          //! an identification for identifying a map in the chain of maps that make up a campaign
          Word         id;

          //! the id of the previous map in the campaign. This is only used as a fallback mechanism if the event based chaining fails. It will probably be discared sooner or later
          word         prevmap;   

          //! a campaign is usually designed to be played by a specific player
          unsigned char         player;   

          //! can the map be loaded just by knowing its filenmae? If 0, the codeword is required
          char      directaccess;   

      };

      //! the campaign properties of map
      Campaign*    campaign;
  
      //! the player who is currently making his moves (may be human or AI)
      signed char  actplayer; 

      //! the time in the game, mesured in a turns and moves
      tgametime    time;
  
      struct tweather {
         //! the idea of fog is to reduce the visibility, but this is currently not used
         char fog;

         //! the speed of wind, for the different levels of height ( 0=low level flight, ..., 2 = high level flight)
         twind wind[3];
      } weather;
  
      /** how are Resources handled on this map
             0= "ASC mode": complex system with mineral resources etc
             1= "BI mode": simpler system like in Battle Isle
      **/
      int _resourcemode;  
  
      //! the diplomatic status between the players
      char         alliances[8][8];

      //! the different players in ASC. There may be 8 players (0..7) and neutral units (8)
      class Player {
         public:
            //! does the player exist at all
            bool         existent;

            //! the startpoint of the linked list of units
            pvehicle     firstvehicle;

            //! the startpoint of the linked list of buildings
            pbuilding    firstbuilding;

            //! the status of the scientific research
            tresearch    research;

            //! if the player is run by an AI, this is the pointer to it
            BaseAI*      ai;

            //! the status of the player: 0=human ; 1=AI ; 2=off
            char         stat;

            //! the name of the player that is used if the player is human
            string       humanname;

            //! the name of the player that is used if the player is the AI
            string       computername;

            //! returns the name of the player depending on the status
            string       getName( ) { switch ( stat ) {
                                         case 0: return humanname;
                                         case 1: return computername;
                                         default: return "off";
                                       }
                                    };
            //! the Password required for playing this player
            Password passwordcrc;

            //! the container that stores the list of dissected units
            pdissectedunit dissectedunit;


            //! the list of messages that haven't been read by the player yet
            pmessagelist  unreadmessage;

            //! the list of messages that already have been read by the player yet
            pmessagelist  oldmessage;

            //! the list of messages that have been sent yet
            pmessagelist  sentmessage;

            //! if ASC should check all events for fullfilled triggers, this variable will be set to true. This does not mean that there really ARE events that are ready to be executed
            int queuedEvents;
      } player[9];
  
      //! a container for events that were executed during previous maps of the campaign
      peventstore  oldevents; 

      //! the list of events that haven't been triggered yet.
      pevent       firsteventtocome; 

      //! the list of events that already have been triggered.
      pevent       firsteventpassed;

      // required for loading the old map file format; no usage outside the loading routine
      // bool loadeventstore,loadeventstocome,loadeventpassed;

      int eventpassed ( int saveas, int action, int mapid );
      int eventpassed ( int id, int mapid );
  
      int          unitnetworkid;
      char         levelfinished;
      pnetwork     network;
      // int          alliance_names_not_used_any_more[8];
  
      struct tcursorpos {
        struct {
          integer cx;
          integer sx;
          integer cy;
          integer sy;
        } position[8];
      } cursorpos;


      /** The tribute can not only be used to demand resources from enemies but also to transfer resources to allies.
            tribute.avail[a][b].energy is the ammount of energy that player b may (still) extract from the net of player a
            tribute.paid[a][b].energy is the amount of energy that player b has already extracted from player a's net
            a is source player, b is destination player
       **/
      class ResourceTribute {
        public:
           Resources avail[8][8];
           Resources paid[8][8];
           bool empty ( );
           void read ( tnstream& stream );
           void write ( tnstream& stream );
      } tribute;

      //! the list of messages that were written this turn and are waiting to be processed at the end of the turn
      pmessagelist  unsentmessage;

      //! these are the messages themselfs. A #pmessagelist only stores pointers to message body which are archived here
      pmessage      message;

      //! each message has an identification number (which is incremented with each message) for referencing it in files. The id of the last message is stored here
      int           messageid;
      char*         journal;
      char*         newjournal;
      Password      supervisorpasswordcrc;

      char          alliances_at_beginofturn[8];
      // pobjectcontainercrcs   objectcrc;
      pshareview    shareview;

      //! if a player has won a singleplayer map, but wants to continue playing without any enemies, this will be set to 1
      int           continueplaying;  
      treplayinfo*  replayinfo;

      //! the player which is currently viewing the map. During replays, for example, this will be different from the player that moves units
      int           playerView;
      tgametime     lastjournalchange;

      //! in BI resource mode ( see #_resourcemode , #isResourceGlobal ) , this is where the globally available resources are stored. Note that not all resources are globally available.
      Resources     bi_resource[8];
      PreferredFilenames preferredFileNames;
      EllipseOnScreen* ellipse;
      int           graphicset;
      int           gameparameter_num;
      int*          game_parameter;
    public:
      int           mineralResourcesDisplayed;

      tmap ( void );

      void chainunit ( pvehicle unit );
      void chainbuilding ( pbuilding bld );
      pvehicle getUnit ( int x, int y, int nwid );
      pvehicle getUnit ( int nwid );
      int  getgameparameter ( int num );
      void setgameparameter ( int num, int value );
      void cleartemps( int b, int value = 0 );
      int isResourceGlobal ( int resource );
      void setupResources ( void );
      const char* getPlayerName ( int playernum );
      pfield getField ( int x, int y );
      pfield getField ( const MapCoordinate& pos );

      void calculateAllObjects ( void );

      pvehicletype getVehicleType_byId ( int id );
      void read ( tnstream& stream );
      void write ( tnstream& stream );
      ~tmap();
   private:
      pvehicle getUnit ( pvehicle eht, int nwid );

}; 




/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/// Even more miscellaneous structures...
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

enum tnetworkchannel { TN_RECEIVE, TN_SEND };


typedef struct tguiicon* pguiicon ;
struct tguiicon { 
  void*      picture[2]; 
  char         txt[31]; 
  unsigned char         id; 
  char         key[4]; 
  word         realkey[4]; 
  unsigned char         order; 
};


struct ticons { 
   struct { 
     void      *pfeil1, *pfeil2; 
   } weapinfo; 
   void*      statarmy[3]; 
   void*      height[8];      // fuer vehicleinfo - DLG-Box
   void*        height2[3][8];  // fuer vehicleinfo am map
   void*        player[8];      // aktueller Spieler in der dashboard: FARBE.RAW 
   void*        allianz[8][3];  // Allianzen in der dashboard: ALLIANC.RAW 
   void*        diplomaticstatus[8]; 
   void*        selectweapongui[12];
   void*        selectweaponguicancel;
   void*        unitinfoguiweapons[13];
   void*        experience[maxunitexperience+1];
   void*        wind[9];
   void*        windarrow;
   void*        stellplatz;
   void*        guiknopf;   // reingedr?ckter knopf
   void*        computer;
   void*        windbackground;
   void*        smallmapbackground;
   void*        weaponinfo[5];
   void*        X;
   struct {
     struct       {
         void* active;
         void* inactive;
         void* repairactive;
         void* repairinactive;
         void* movein_active;
         void* movein_inactive;
     } mark;
     struct       {
         struct {
           void* start;
           void* active;
           void* inactive;
         } netcontrol;
         struct {
           void* start;
           void* button;
           void* buttonpressed;
           void* schieber[4];
           void* schiene;
         } ammoproduction;
         struct {
           void* start;
         } resourceinfo;
         struct {
           void* start;
         } windpower;
         struct {
           void* start;
         } solarpower;
         struct {
           void* start;
           void* button;
           void* buttonpressed;
           void* schieber[4];
           void* schiene;
           void* schieneinactive;
           void* singlepage[2];
           void* plus[2];
           void* minus[2];
         } ammotransfer;
         struct {
           void* start;
           void* button[2];
           void* schieber;
         } research;
         struct {
           void* start;
           // void* button[2];
           void* schieber;
         } conventionelpowerplant;
         struct {
           void* start;
           void* height1[8];
           void* height2[8];
           void* repair;
           void* repairpressed;
           void* block;
         } buildinginfo;
         struct {
           void* start;
                  void* zeiger;
           void* button[2];
           void* resource[2];
           void* graph;
           void* axis[3];
           void* pageturn[2];
         
           void* schieber;
         } miningstation;
         struct {
           void* start;
                  void* zeiger;
           void* schieber;
         } mineralresources;
         struct {
           void* start;
           void* height1[8];
           void* height2[8];
           void* sum;
         } transportinfo;
     } subwin;
     union {
        void* sym[11][2];
        struct {
          void*  ammotransfer[2];
          void*  research[2];
          void*  resourceinfo[2];
          void*  netcontrol[2];
          void*  solar[2];
          void*  ammoproduction[2];
          void*  wind[2];
          void*  powerplant[2];
          void*  buildinginfo[2];
          void*  miningstation[2];
          void*  transportinfo[2];
          void*  mineralresources[2];
        } a;
     } lasche;
   
     void* tabmark[2];
     void* container_window;
   } container;
   struct {
     void* bkgr;
     void* orgbkgr;
   } attack;
   void*        pfeil2[8];     // beispielsweise fuer das Mouse-Scrolling 
   void*        mousepointer;
   void*        fieldshape;
   void*        hex2octmask;
   void*        mapbackground;
   void*        mine[8]; // explosive mines
   struct {                  
               void*     nv8;
               void*     va8;
               void*     fog8;
               #ifndef HEXAGON
               void*     nv4[4];
               void*     va4[4];
               void*     fog4[4];
               void*     viereck[256];
               #endif
    } view;  
}; 







/*!
  \brief calculate the height difference between two levels of height

  Since floating and ground based are assumed to be the same effective height, a simple subtraction isn't sufficient.
 */
extern int getheightdelta ( int height1, int height2 );


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/// Structure field naming constants 
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


#define cminenum 4
extern const char*  cminentypen[cminenum] ;
extern const int cminestrength[cminenum]  ;
 #define cmantipersonnelmine 1  
 #define cmantitankmine 2  
 #define cmmooredmine 3  
 #define cmfloatmine 4  



enum { capeace, cawar, cawarannounce, capeaceproposal, canewsetwar1, canewsetwar2, canewpeaceproposal, capeace_with_shareview };
enum { visible_not, visible_ago, visible_now, visible_all };


  extern const char*  cwettertypen[];

extern const char* gameparametername[ gameparameternum ];
extern const int gameparameterdefault [ gameparameternum ];
enum { cgp_fahrspur, cgp_eis, cgp_movefrominvalidfields, cgp_building_material_factor, cgp_building_fuel_factor,
       cgp_forbid_building_construction, cgp_forbid_unitunit_construction, cgp_bi3_training, cgp_maxminesonfield,
       cgp_antipersonnelmine_lifetime, cgp_antitankmine_lifetime, cgp_mooredmine_lifetime, cgp_floatingmine_lifetime,
       cgp_buildingarmor, cgp_maxbuildingrepair, cgp_buildingrepairfactor, cgp_globalfuel, cgp_maxtrainingexperience,
       cgp_initialMapVisibility };



extern  const char*  choehenstufen[8] ;
 #define chtiefgetaucht 1  
 #define chgetaucht 2  
 #define chschwimmend 4  
 #define chfahrend 8  
 #define chtieffliegend 16  
 #define chfliegend 32  
 #define chhochfliegend 64  
 #define chsatellit 128  


#define cwaffentypennum 12
 extern const char*  cwaffentypen[cwaffentypennum] ; 
 #define cwcruisemissile 0
 #define cwcruisemissileb ( 1 << cwcruisemissile )
 #define cwminen 1  
 #define cwmineb ( 1 << cwminen   )
 #define cwbombn 2  
 #define cwbombb ( 1 << cwbombn  )
 #define cwairmissilen 3  
 #define cwairmissileb ( 1 << cwairmissilen  )
 #define cwgroundmissilen 4  
 #define cwgroundmissileb ( 1 << cwgroundmissilen  )
 #define cwtorpedon 5  
 #define cwtorpedob ( 1 << cwtorpedon  )
 #define cwmachinegunn 6  
 #define cwmachinegunb ( 1 << cwmachinegunn )
 #define cwcannonn 7  
 #define cwcannonb ( 1 << cwcannonn )
 #define cwweapon ( cwcruisemissileb | cwbombb | cwairmissileb | cwgroundmissileb | cwtorpedob | cwmachinegunb | cwcannonb )
 #define cwshootablen 11  
 #define cwshootableb ( 1 << cwshootablen  )
 #define cwammunitionn 9  
 #define cwammunitionb ( 1 << cwammunitionn )
 #define cwservicen 8  
 #define cwserviceb ( 1 << cwservicen )
 extern const int cwaffenproduktionskosten[cwaffentypennum][3];  /*  Angabe: Waffentyp; energy - Material - Sprit ; jeweils fuer 5er Pack */







extern const char*  cbodenarten[]  ;
  extern tterrainbits cbwater0 ;
  extern tterrainbits cbwater1 ;
  extern tterrainbits cbwater2 ;
  extern tterrainbits cbwater3 ;
  extern tterrainbits cbwater  ;
  extern tterrainbits cbstreet ;
  extern tterrainbits cbrailroad ;
  extern tterrainbits cbbuildingentry ;
  extern tterrainbits cbharbour ;
  extern tterrainbits cbrunway ;
  extern tterrainbits cbrunway ;
  extern tterrainbits cbpipeline ;
  extern tterrainbits cbpowerline;
  extern tterrainbits cbfahrspur ;
  extern tterrainbits cbfestland ;
  extern tterrainbits cbsnow1 ;
  extern tterrainbits cbsnow2 ;
  extern tterrainbits cbhillside ;
  extern tterrainbits cbsmallrocks ;
  extern tterrainbits cblargerocks ;


extern const char*  resourceNames[3];



extern  const char* cconnections[6];
 #define cconnection_destroy 1  
 #define cconnection_conquer 2  
 #define cconnection_lose 4  
 #define cconnection_seen 8
 #define cconnection_areaentered_anyunit 16
 #define cconnection_areaentered_specificunit 32
 //   conquered = You conquered sth.      
 //   lost      = an enemy conquered sth. from you


const int ceventtriggernum = 21;
extern const char* ceventtriggerconn[]; 
 #define ceventtrigger_and 1  
 #define ceventtrigger_or 2  
 #define ceventtrigger_not 4  
 #define ceventtrigger_klammerauf 8  
 #define ceventtrigger_2klammerauf 16  
 #define ceventtrigger_2klammerzu 32  
 #define ceventtrigger_klammerzu 64  
  /*  reihenfolgenpriorit�t: in der Reihenfolge von oben nach unten wird der TriggerCon ausgewertet
               AND   OR
               NOT
               (
               eigentliches event
               )
    */ 


#define ceventactionnum 21
extern const char* ceventactions[ceventactionnum]; // not bitmapped 
 enum { cemessage,   ceweatherchange, cenewtechnology, celosecampaign, cerunscript,     cenewtechnologyresearchable, 
        cemapchange, ceeraseevent,    cecampaignend,   cenextmap,      cereinforcement, ceweatherchangecomplete, 
        cenewvehicledeveloped, cepalettechange, cealliancechange,      cewindchange,    cenothing, 
        cegameparamchange, ceellipse, ceremoveellipse, cechangebuildingdamage };


extern const char*  ceventtrigger[]; 
 enum { ceventt_turn = 1 ,               ceventt_buildingconquered, ceventt_buildinglost,  ceventt_buildingdestroyed, ceventt_unitlost, 
        ceventt_technologyresearched,    ceventt_event,             ceventt_unitconquered, ceventt_unitdestroyed,     
        ceventt_allenemyunitsdestroyed,  ceventt_allunitslost,      ceventt_allenemybuildingsdestroyed, 
        ceventt_allbuildingslost,        ceventt_energytribute,     ceventt_materialtribute, ceventt_fueltribute, 
        ceventt_any_unit_enters_polygon, ceventt_specific_unit_enters_polygon, ceventt_building_seen, ceventt_irrelevant };


extern const char*  cmovemalitypes[cmovemalitypenum];


const int experienceDecreaseDamageBoundaryNum = 4;
extern const int experienceDecreaseDamageBoundaries[experienceDecreaseDamageBoundaryNum];


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/// Constants that specify the layout of ASC
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#define maxloadableunits 27  // Mehr vehicle d?rfen nicht in einen Transporter rein

#define guiiconsizex 49  
#define guiiconsizey 35  


#ifdef HEXAGON
 #define maxmalq 10  
 #define minmalq 10
 #define fieldxsize 48    /*  Breite eines terrainbildes  */ 
 #define fieldysize 48  
 #define fielddistx 64
 #define fielddisty 24
 #define fielddisthalfx 32

 //! the number of sides that a field has; is now fixed at 6;
 const int sidenum = 6;
#else
 #define maxmalq 12  
 #define minmalq 8
 #define fieldxsize 40    /*  Breite eines terrainbildes  */ 
 #define fieldysize 39  
 #define fielddirecpictsize 800
 #define fielddistx 40
 #define fielddisty 20
 #define fielddisthalfx 20
 #define sidenum 8
#endif

#define fieldsizex fieldxsize
#define fieldsizey fieldysize

  extern const int directionangle [ sidenum ];


#define fieldsize (fieldxsize * fieldysize + 4 )
#define unitsizex 30
#define unitsizey 30
#define tanksize (( unitsizex+1 ) * ( unitsizey+1 ) + 4 )
#define unitsize tanksize


#ifdef HAVE_LIMITS

 #ifdef max
  #undef max
 #endif
 #ifdef min
  #undef min
 #endif

 #define maxint numeric_limits<int>::max()
 #define minint numeric_limits<int>::min()
 
 #define maxfloat numeric_limits<float>::max()
 #define minfloat numeric_limits<float>::min()
#else

 #define maxint INT_MAX
 #define minint INT_MIN
 
 #define maxfloat FLT_MAX
 #define minfloat FLT_MIN
#endif



/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/// Constants that define the behaviour of units and buildings
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//! The movement decrease in percent of the total movemnt that is used for attacking; only used for units that can move after attacking
const int attackmovecost = 20;  

#define movement_cost_for_repaired_unit 24
#define movement_cost_for_repairing_unit 12
#define attack_after_repair 1       // Can the unit that is beeing repaired attack afterwards? 

#define mineputmovedecrease 8  
#define streetmovemalus 8  
#define railroadmovemalus 8  
#define searchforresorcesmovedecrease 8


#define fusstruppenplattfahrgewichtsfaktor 2  
#define mingebaeudeeroberungsbeschaedigung 80  
#define flugzeugtraegerrunwayverkuerzung 2  

#define autorepairdamagedecrease 10    // only for old units ; new one use autorepairrate

#define air_heightincmovedecrease 18  
#define air_heightdecmovedecrease 0
#define sub_heightincmovedecrease 12
#define sub_heightdecmovedecrease 12
#define helicopter_attack_after_ascent 1  // nach abheben angriff moeglich
#define helicopter_attack_after_descent 0  // nach landen angriff moeglich
#define helicopter_landing_move_cost 16   // zus�tzlich zu den Kosten fuer das Wechseln der Hoehenstufe 
#define weaponpackagesize 5

#define trainingexperienceincrease 2

#define brigde1buildcostincrease 12       // jeweils Basis 8; flaches Wasser
#define brigde2buildcostincrease 16       // jeweils Basis 8; mitteltiefes Wasser
#define brigde3buildcostincrease 36       // jeweils Basis 8; tiefes Wasser


#define lookintoenemytransports false  
#define lookintoenemybuildings false  

#define recyclingoutput 2    /*  Material div RecyclingOutput  */ 
#define destructoutput 5
#define nowindplanefuelusage 1      // herrscht kein Wind, braucht ein Flugzeug pro Runde soviel Sprit wie das fliegend dieser Anzahl fielder
  //   #define maxwindplainfuelusage 32   // beim nextturn: tank -= fuelconsumption * (maxwindplainfuelusage*nowindplainfuelusage + windspeed) / maxwindplainfuelusage     
#define maxwindspeed 128          // Wind der St�rke 256 legt pro Runde diese Strecke zur?ck: 128 entspricht 16 fieldern diagonal !


#define generatortruckefficiency 2  // fuer jede vehicle Power wird soviel Sprit gebraucht !

#define researchenergycost 512      // fuer 1000 researchpoints wird soviel energie benoetigt.
#define researchmaterialcost 200    //                                     material
#define researchcostdouble 10000    // bei soviel researchpoints verdoppeln sich die Kosten
#define minresearchcost 0.5
#define maxresearchcost 4
#define airplanemoveafterstart 12
#define airplanemoveafterlanding (2*minmalq - 1 )

#define mine_movemalus_increase 50   // percent

#define tfieldtemp2max 255
#define tfieldtemp2min 0


#define cnet_storeenergy        0x001           // es wird garantiert,  dass material immer das 2 und fuel das 4 fache von energy ist
#define cnet_storematerial      0x002
#define cnet_storefuel          0x004

#define cnet_moveenergyout      0x008
#define cnet_movematerialout    0x010
#define cnet_movefuelout        0x020

#define cnet_stopenergyinput    0x040
#define cnet_stopmaterialinput  0x080
#define cnet_stopfuelinput      0x100

#define cnet_stopenergyoutput   0x200
#define cnet_stopmaterialoutput 0x400
#define cnet_stopfueloutput     0x800


#define resource_fuel_factor 100         // die im boden liegenden Bodensch�tzen ergeben effektiv soviel mal mehr ( bei Bergwerkseffizienz 1024 )
#define resource_material_factor 100     // "

#define destruct_building_material_get 3 // beim Abreissen erh�lt man 1/3 des eingesetzten Materials zur?ck
#define destruct_building_fuel_usage 10  // beim Abreissen wird 10 * fuelconsumption Fuel fuelconsumptiont


#define dissectunitresearchpointsplus  2    // Beim dissectn einer vehicle wird der sovielte Teil der Researchpoints jeder unbekannten Technologie gutgeschrieben

#define dissectunitresearchpointsplus2 3    // Beim dissectn einer vehicle wird der sovielte Teil der Researchpoints jeder unbekannten Technologie gutgeschrieben.
  // fuer die Technologie existieren aber bereits von einem anderen sezierten vehicletype gutschriften.

//! The maximum number of fields a mining station can extract mineral resources from; Counted from its entry
const int maxminingrange = 10;

//! The weight of 1024 units of aa Resource 
extern const int resourceWeight[ resourceTypeNum ];

#define objectbuildmovecost 16  // vehicle->movement -= (8 + ( fld->movemalus[0] - 8 ) / ( objectbuildmovecost / 8 ) ) * kosten des obj


extern const int csolarkraftwerkleistung[];

//! The number of netcontrol actions ; see #cnetcontrol 
const int cnetcontrolnum  = 12;

//! The actions that can be used to control a ResourceNet
extern const char* cnetcontrol[cnetcontrolnum];

extern const char* cgeneralnetcontrol[];

#define unspecified_error 9999

#define greenbackgroundcol 156

#pragma pack()

#endif
