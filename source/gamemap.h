/*! \file gamemap.h
    \brief Definition of THE central asc class: tmap 
*/

/***************************************************************************
                          gamemap.h  -  description
                             -------------------
    begin                : Tue Feb 17 2001
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


#ifndef gamemapH
 #define gamemapH

 #include <vector>

 #include "typen.h"
 #include "baseaiinterface.h"
 #include "vehicle.h"
 #include "buildings.h"
 #include "basestrm.h"
 #include "time.h"
 #include "messages.h"
 #include "gameeventsystem.h"
 #include "research.h"
 #include "password.h"
 #include "weatherarea.h"
 
 class WeatherSystem;

//! The number of game paramters that can be specified for each map.
const int gameparameternum = 29;

//! The names of the game paramter. \sa gameparameterdefault
extern const char* gameparametername[ gameparameternum ];

extern const int gameparameterdefault [ gameparameternum ];

extern const int gameParameterLowerLimit [ gameparameternum ];
extern const int gameParameterUpperLimit [ gameparameternum ];
extern const bool gameParameterChangeableByEvent [ gameparameternum ];

enum GameParameter { cgp_fahrspur,
       cgp_eis,
       cgp_movefrominvalidfields,
       cgp_building_material_factor,
       cgp_building_fuel_factor,
       cgp_forbid_building_construction,
       cgp_forbid_unitunit_construction,
       cgp_bi3_training,
       cgp_maxminesonfield,
       cgp_antipersonnelmine_lifetime,
       cgp_antitankmine_lifetime,
       cgp_mooredmine_lifetime,
       cgp_floatingmine_lifetime,
       cgp_buildingarmor,
       cgp_maxbuildingrepair,
       cgp_buildingrepairfactor,
       cgp_globalfuel,
       cgp_maxtrainingexperience,
       cgp_initialMapVisibility,
       cgp_attackPower,
       cgp_jammingAmplifier,
       cgp_jammingSlope,
       cgp_superVisorCanSaveMap,
       cgp_objectsDestroyedByTerrain,
       cgp_trainingIncrement,
       cgp_experienceDivisorAttack,
       cgp_disableDirectView,
       cgp_disableUnitTransfer,
       cgp_experienceDivisorDefense };


//! an instance of an object type (#tobjecttype) on the map
class Object {
    public:
       pobjecttype typ;
       int damage;
       int dir;
       int time;
       // int dummy[4];
       Object ( void );
       Object ( pobjecttype t );
       void display ( Surface& surface, SPoint pos, int weather = 0 ) const;
       void setdir ( int dir );
       int  getdir ( void );
};

#define cminenum 4
extern const char* MineNames[cminenum] ;
extern const int MineBasePunch[cminenum]  ;

enum MineTypes { cmantipersonnelmine = 1 , cmantitankmine, cmmooredmine, cmfloatmine  };


class Mine {
   public:
      MineTypes type;

      //! the effective punch of the mine
      int strength;

      //! the turnnumber in which the mine was placed
      int time;

      //! the player who placed the mine; range 0 .. 7      
      int player;

      //! can the mine attack this unit
      bool attacksunit ( const Vehicle* veh );
};


class LoadNextMap {
       public:
          int id;
          LoadNextMap( int ID ) : id(ID) {};
};          



//! a single field of the map
class  tfield {
    pmap gamemap;
    void init();
  protected:
    tfield (  );
    friend class tmap;
  public:
    tfield ( pmap gamemap_ );
    void operator= ( const tfield& f );

    void setMap ( pmap gamemap_ ) { gamemap = gamemap_; };

    //! the terraintype (#pwterraintype) of the field
    TerrainType::Weather* typ;

    //! mineral resources on this field (should be changed to #ResourcesType sometime...)
    char         fuel, material;

    //! can this field be seen be the player. Variable is bitmapped; two bits for each player. These two bits can have the states defined in ::VisibilityStates
    Uint16       visible;

    //! in the old octagonal version of ASC it was possible to rotate the terraintype; this is not used in the hexagonal version any more
    char         direction;

    //! units standing on this object will get a bonus to their view
    int          viewbonus;


    //@{ 
    //! Various algorithms need to store some information in the fields they process. These variables are used for this.
    union  {
      struct {
        char         temp;
        char         temp2;
      }a;
      Uint16 tempw;
    };
    int          temp3;
    int          temp4;
    //@}

    Vehicle*     vehicle;
    Building*    building;

    struct Resourceview {
      Resourceview ( void );
      char    visible;      // BM
      char    fuelvisible[8];
      char    materialvisible[8];
    };

    //! the mineral resources that were seen by a player on this field; since the actual amount may have decreased since the player looked, this value is not identical to the fuel and material fields.
    Resourceview*  resourceview;

    typedef list<Mine> MineContainer;
    MineContainer mines;

    //! returns the nth mine. This function should only be used by legacy code; new code should store an iterator instead of an index
    Mine& getMine ( int n );


    typedef vector< ::Object> ObjectContainer;
    ObjectContainer objects;

    /** add an object to the field
         \param obj The object type
         \param dir The direction of the object type; -1 to use default direction
         \param force Put the object there even if it cannot normally be placed on this terrain
    **/
    void addobject ( pobjecttype obj, int dir = -1, bool force = false );

    //! removes all objects of the given type from the field
    void removeobject ( pobjecttype obj, bool force = false );

    //! sorts the objects. Since objects can be on different levels of height, the lower one must be displayed first
    void sortobjects ( void );

    //! checks if there are objects from the given type on the field and returns them
    pobject checkforobject ( pobjecttype o );


    //! the terraintype properties. They determine which units can move over the field. This variable is recalculated from the terraintype and objects each time something on the field changes (#setparams)
    TerrainBits  bdt;

    //! are any events connected to this field
    int connection;


    //! deletes everything placed on the field
    void deleteeverything ( void );

    //! recalculates the terrain properties, movemalus etc from the terraintype and the objects,
    void setparams ( void );

    //! the defense bonus that unit get when they are attacked
    int getdefensebonus ( void );

    //! the attack bonus that unit get when they are attacking
    int getattackbonus  ( void );

    //! the weather that is on this field
    int getweather ( void );
    void setweather( int weather );

    //! the radar jamming that is on this field
    int getjamming ( void );
    int getmovemalus ( const Vehicle* veh );
    int getmovemalus ( int type );

    //! can any of the mines on this field attack this unit
    int mineattacks ( const Vehicle* veh );

    //! the player who placed the mines on this field.
    int mineowner ( void );

    //! mines may have a limited lifetime. This methods removes all mines whose maxmimum lifetime is exeeded
    void checkminetime ( int time );

    //! checks if the unit is standing on this field. Since units are being cloned for some checks, this method should be used instead of comparing the pointers to the unit
    bool unitHere ( const Vehicle* veh );

    //! returns a pointer to the #ContainerBase of the field or NULL if there is none
    ContainerBase* getContainer() { if ( vehicle ) return vehicle; else return building; };

    //! put a mine of type typ for player col (0..7) and a punch of strength on the field. Strength is an absolute value (unlike the basestrength of a mine or the punch of the mine-weapon, which are just factors)
    bool  putmine ( int col, int typ, int strength );

    /** removes a mine
         \param num The position of the mine; if num is -1, the last mine is removed)
    **/
    void  removemine ( int num ); 

    //! some variables for the viewcalculation algorithm. see #viewcalculation.cpp for details
    struct View {
      int view;
      int jamming;
      char mine, satellite, sonar, direct;
    } view[8];

   /** The visibility status for all players is stored in a bitmapped variable. This functions changes the status in this variable for a single player
      \param valtoset the value that is going to be written into the visibility variable
      \param actplayer the player for which the view is changed
   */
   void setVisibility ( VisibilityStates valtoset, int actplayer ) {
       int newval = (valtoset ^ 3) << ( 2 * actplayer );
       int oneval = 3 << ( 2 * actplayer );

       visible |= oneval;
       visible ^= newval;
   };

    int getx();
    int gety();

    ~tfield();
  private:
    TerrainType::MoveMalus __movemalus;
};






//! The map. THE central structure of ASC, which holds everything not globally available together
class tmap {
      void operator= ( const tmap& map );
   public:
      //! the size of the map
      int          xsize, ysize;

      //! the coordinate of the map that is displayed on upper left corner of the screen
      int          xpos, ypos;

      //! the array of fields
      pfield       field;

      //! the codeword for accessing a map in a campaign
      char         codeword[11]; 

      //! the title of the map
      ASCString    maptitle;


      struct Campaign {
          //! an identification for identifying a map in the chain of maps that make up a campaign
          int         id;

          //! the id of the previous map in the campaign. This is only used as a fallback mechanism if the event based chaining fails. It will probably be discared sooner or later
          int         prevmap;   

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
      GameTime    time;

      struct Weather {
         Weather():fog(0),windSpeed(0),windDirection(0){};
         //! the idea of fog is to reduce the visibility, but this is currently not used
         int fog;

         int windSpeed;
         int windDirection;
      } weather;

      WeatherSystem* weatherSystem;
      /** how are Resources handled on this map
             0= "ASC mode": complex system with mineral resources etc
             1= "BI mode": simpler system like in Battle Isle
      **/
      int _resourcemode;

      //! the diplomatic status between the players
      char         alliances[8][8];


      //! the different players in ASC. There may be 8 players (0..7) and neutral units (8)
      class Player {
            friend class tmap;
            int player;
         public:
            //! does the player exist at all
            bool         exist();

            //! did the player exist when the turn started? Required for checking if a player has been terminated
            bool existanceAtBeginOfTurn;

            typedef list<Vehicle*> VehicleList;
            //! a list of all units
            VehicleList  vehicleList;

            typedef list<Building*> BuildingList;
            //! a list of all units
            BuildingList  buildingList;

            //! the status of the scientific research
            Research    research;

            //! if the player is run by an AI, this is the pointer to it
            BaseAI*      ai;

            //! the status of the player: 0=human ; 1=AI ; 2=off
            enum tplayerstat { human, computer, off } stat;

            //! the name of the player that is used if the player is human
            ASCString       humanname;

            //! the name of the player that is used if the player is the AI
            ASCString       computername;

            //! returns the name of the player depending on the status
            const ASCString& getName( );

            //! the Password required for playing this player
            Password passwordcrc;

            class Dissection {
               public:
                  pvehicletype  fzt;
                  const Technology*   tech;
                  int           orgpoints;
                  int           points;
                  int           num;
            };

            //! the list of dissected units
            typedef list<Dissection> DissectionContainer;
            DissectionContainer dissections;

            bool __dissectionsToLoad;

            //! the list of messages that haven't been read by the player yet
            MessagePntrContainer  unreadmessage;
            bool __loadunreadmessage;

            //! the list of messages that already have been read by the player yet
            MessagePntrContainer  oldmessage;
            bool __loadoldmessage;

            //! the list of messages that have been sent yet
            MessagePntrContainer  sentmessage;
            bool __loadsentmessage;

            //! if ASC should check all events for fullfilled triggers, this variable will be set to true. This does not mean that there really ARE events that are ready to be executed
            int queuedEvents;

            //! the version of ASC that this player has used to make his last turn 
            int ASCversion;

            struct PlayTime {
              int turn;
              time_t date;
            };
            typedef list<PlayTime> PlayTimeContainer;

            //! The time this player ended his turns. This is very informative in email games with > 2 players to find out who is delaying the game.
            PlayTimeContainer playTime;

            MapCoordinate cursorPos;

            int getColor();
            
      } player[9];

      typedef map<int, Vehicle*> VehicleLookupCache;
      VehicleLookupCache vehicleLookupCache; 

      int eventID;

      typedef PointerList<Event*> Events;
      Events events;

      vector<GameTime> eventTimes;

      /*
      //! a container for events that were executed during previous maps of the campaign
      peventstore  oldevents;

      //! the list of events that haven't been triggered yet.
      pevent       firsteventtocome;

      //! the list of events that already have been triggered.
      pevent       firsteventpassed;
      */

      // required for loading the old map file format; no usage outside the loading routine
      // bool loadeventstore,loadeventstocome,loadeventpassed;

      int eventpassed ( int saveas, int action, int mapid );
      int eventpassed ( int id, int mapid );

      int          unitnetworkid;
      char         levelfinished;
      pnetwork     network;
      // int          alliance_names_not_used_any_more[8];

      //! only to be used by units and buildings. To speed up map destruction, the view won't be recalculated. No signals will be send when units & buildings are destroyed, either 
      bool __mapDestruction;

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
            tribute.paid[b][a].energy is the amount of energy that player b has already extracted from player a's net
            a is source player, b is destination player
       **/
      class ResourceTribute {
        public:
           Resources avail[8][8];
           Resources paid[8][8];

           //! for the messages that are send each turn it is necessary to record how much of the transfer happend during the last turn
           Resources payStatusLastTurn[8][8];
           bool empty ( );
           void read ( tnstream& stream );
           void write ( tnstream& stream );
      } tribute;

      //! the list of messages that were written this turn and are waiting to be processed at the end of the turn
      MessagePntrContainer  unsentmessage;
      bool __loadunsentmessage;

      //! these are the messages themselfs. A #pmessagelist only stores pointers to message body which are archived here
      MessageContainer messages;
      bool __loadmessages;

      //! each message has an identification number (which is incremented with each message) for referencing it in files. The id of the last message is stored here
      int           messageid;

      //! temporary variables for loading the map
      bool ___loadJournal, ___loadNewJournal, ___loadtitle;

      void allocateFields ( int x, int y );

      ASCString     gameJournal;
      ASCString     newJournal;
      Password      supervisorpasswordcrc;

      char          alliances_at_beginofturn[8];

      class  Shareview {
         public:
            Shareview ( void );
            Shareview ( const Shareview* org );
            bool mode[8][8];
            int recalculateview;
            void read ( tnstream& stream );
            void write( tnstream& stream );
       };
       // mode[1][6] = visible_all    =>  Spieler 1 gibt Spieler 6 die view frei

      Shareview*    shareview;

      //! if a player has won a singleplayer map, but wants to continue playing without any enemies, this will be set to 1
      int           continueplaying;

      class ReplayInfo {
      public:
          ReplayInfo ( void );

          pmemorystreambuf guidata[8];
          pmemorystreambuf map[8];
          pmemorystream    actmemstream;

          //! if stopRecordingActions > 0 then no actions will be recorded. \see LockReplayRecording
          int stopRecordingActions;
          void read ( tnstream& stream );
          void write ( tnstream& stream );
          ~ReplayInfo ( );
        };


      ReplayInfo*  replayinfo;

      //! a helper variable to store some information during the loading process. No usage outside.
      bool          __loadreplayinfo;


      //! the player which is currently viewing the map. During replays, for example, this will be different from the player that moves units
      int           playerView;
      GameTime     lastjournalchange;

      //! in BI resource mode ( see #_resourcemode , #isResourceGlobal ) , this is where the globally available resources are stored. Note that not all resources are globally available.
      Resources     bi_resource[8];

      struct PreferredFilenames {
        ASCString mapname[8];
        ASCString savegame[8];
      } preferredFileNames;

      //! for tutorial missions it is possible to highlight elements of the interface with an ellipse using the event system.
      EllipseOnScreen* ellipse;

      //! the ID of the graphic set
      int           graphicset;
      int           gameparameter_num;
      int*          game_parameter;

      int           mineralResourcesDisplayed;

      class ArchivalInformation {
         public:
            ArchivalInformation() : modifytime ( 0 ) {};
            ASCString author;
            ASCString description;
            ASCString tags;
            ASCString requirements;
            time_t modifytime;
      } archivalInformation;

      //! specifies which vehicle types can be constructed by construction units
      class UnitProduction {
         public:
            typedef vector<int> IDsAllowed;
            bool check ( int id );
            IDsAllowed idsAllowed;
      } unitProduction;

      tmap ( void );

      Vehicle* getUnit ( int x, int y, int nwid );
      Vehicle* getUnit ( int nwid );
      ContainerBase* getContainer ( int nwid );
      int  getgameparameter ( GameParameter num );
      void setgameparameter ( GameParameter num, int value );
      void cleartemps( int b = -1, int value = 0 );
      bool isResourceGlobal ( int resource );
      void setupResources ( void );
      const ASCString& getPlayerName ( int playernum );
      pfield getField ( int x, int y );
      pfield getField ( const MapCoordinate& pos );
      void startGame ( );

      //! called after a player ends his turn
      void endTurn();

      //! called between endTurn() of player 7 and the next turn of player 0
      void endRound();


      //! called when a new round starts (after switching from player 7 to player 0 )
      SigC::Signal0<void> newRound;



      //! changes to the next player and calls endRound() if necessary. \Returns false if there are no players left
      bool nextPlayer();

      VisibilityStates getInitialMapVisibility( int player );

      //! resizes the map. Positive numbers enlarge the map in that direction
      int  resize( int top, int bottom, int left, int right );

      bool compareResources( tmap* replaymap, int player, ASCString* log = NULL );

      void calculateAllObjects ( void );

      void read ( tnstream& stream );
      void write ( tnstream& stream );

      Surface getOverviewMap();

      pterraintype getterraintype_byid ( int id );
      pobjecttype getobjecttype_byid ( int id );
      pvehicletype getvehicletype_byid ( int id );
      pbuildingtype getbuildingtype_byid ( int id );
      const Technology* gettechnology_byid ( int id );

      pterraintype getterraintype_bypos ( int pos );
      pobjecttype getobjecttype_bypos ( int pos );
      pvehicletype getvehicletype_bypos ( int pos );
      pbuildingtype getbuildingtype_bypos ( int pos );
      const Technology* gettechnology_bypos ( int pos );

      int getTerrainTypeNum ( );
      int getObjectTypeNum ( );
      int getVehicleTypeNum ( );
      int getBuildingTypeNum ( );
      int getTechnologyNum ( );

      ~tmap();

      //! just a helper variable for loading the map; no function outside;
      bool loadOldEvents;
   private:
      Vehicle* getUnit ( Vehicle* eht, int nwid );
};

typedef tmap::Player Player;



#endif

