/***************************************************************************
                          vehicle.h  -  description
                             -------------------
    begin                : Fri Sep 29 2000
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

#ifndef vehicleH
 #define vehicleH

 #include "typen.h"
 #include "vehicletype.h"
 #include "containerbase.h"
 #include "ascstring.h"

 #pragma pack(1)

 class Vehicle : public ContainerBase {
    //! a vehicle must not be created without a type or map
    Vehicle (  );

    //! cloning of vehicles is not allowed too
    Vehicle ( const Vehicle& v );

    //! is  the vehicle currently viewing the map? if yes, the view has to be removed on destruction
    bool viewOnMap;

    /** remaining movement for this turn.
        Note that the usable movement can be less due to lack of fuel.
        Use #getmovement to optain the usable movement
    */
    int  _movement;

    //! the amount of energy that the unit has spent this turn
    int   energyUsed;

    void init ( void );

    ResourceMatrix repairEfficiency;

    bool generatoractive;

    bool movementLeft() const;

    Vehicle ( const Vehicletype* t, pmap actmap, int player, int networkID  );

   protected:
     bool isBuilding() const { return false; };

   public:

    Vehicle ( const Vehicletype* t, pmap actmap, int player );


    const Vehicletype* typ;
    int          ammo[16];
    int          weapstrength[16];
    int          experience;

    //! did the unit already attack this turn
    bool         attacked;

    //! the the unit and all cargo to #attacked = true
    void setAttacked();

    //! the current level of height ( BITMAPPED ! )
    int          height;

    //! the direction in which the unit is facing
    char         direction;

    //! the position on the map
    int          xpos, ypos;

    //! the resources that the unit is carrying
    Resources    tank;

    //! if events are triggered by this unit (if it is lost for example), this will set connection != 0
    int          connection;

    //! the generation of the vehicletype (also called 'class', as in 'salmon class')
    char         klasse;
    word         armor;

    /** a unique identification of the unit that is used everywhere in ASC
       (and not only the network protocols where is was first used, hence the name)
    */
    int          networkid;
    ASCString    name;

    //! The class that manages the reaction fire which causes a unit to attack approaching enemies even if it is not the unit's turn
    class  ReactionFire {
         friend class Vehicle;

         Vehicle* unit;
       public:
         ReactionFire ( Vehicle* _unit ) : unit ( _unit ) {};
         enum Status { off, init1a, init2, ready, init1b };

         //! for each player that can still be attacked one bit is set
         int enemiesAttackable;
         Status getStatus() const { return status;};

         //! enables the reaction fire or returns an error code ( result < 0 = -errorNr ) 
         int enable();
         void disable();

         //! hook that is called when a turn ends
         void endTurn ( void );

         bool canMove() const;
       private:
         Status status;

    } reactionfire;

    AiParameter* aiparam[8];

    //! can the unit move from its current position (does not check neighbouring fields)
    bool canMove ( void ) const;

    //! returns the movement points the unit has left for this turn. CheckFuel should almost always be true.
    int getMovement ( bool checkFuel = true ) const ;

    /** sets a new distance that the unit can move
        \param cargoDivisor : the cargo of this unit gets 1/cargodivisor the change that this unit is getting; if 0 the cargo is not touched
    */
    void setMovement ( int newmove, int cargoDivisor = 2 );

    //! did the unit move this turn
    bool hasMoved ( void ) const;

    //! the maximum distance that the unit can drive in a single turn on the current level of height
    int maxMovement ( void );

    /** reduces the movement by the given amount. Negative values are possible.
        Don't use something like "setmovement ( getmovement() - amount )", because getmovement may return a lower amount due to lack of fuel. */
    void decreaseMovement ( int movement );

    //! resets a units movement. This is called at the beginning of each turn.
    void resetMovement( void );

    //! changes a units height and adjusts the movement so that the percentage of used movepoints remains constant
    void setNewHeight( int height );

    //! add the objects like tracks or broken ice
    void spawnMoveObjects( const MapCoordinate& start, const MapCoordinate& dest );

    int putResource ( int amount, int resourcetype, int queryonly, int scope = 1 );
    int getResource ( int amount, int resourcetype, int queryonly, int scope = 1 );


    //! weight of unit including cargo, fuel and material
    int weight( void ) const;

    //! returns the units name or, if it does not exist, the unit type's name or description
    const ASCString&    getName() const;


  protected:
    /** should not be called except from freeweight
        \param what: 0=cargo ; 1=material/fuel
    */
    int searchstackforfreeweight( pvehicle eht, int what );

    //! returns the maximum amount of the resource 'resourcetype' that the unit can carry
    int getMaxResourceStorageForWeight ( int resourcetype );

    const ResourceMatrix& getRepairEfficiency ( void ) { return repairEfficiency; };

    virtual void postRepair ( int oldDamage );


  public:

    /** returns the free weight that can be used for cargo or for resources
        \param what: 0=cargo ; 1=resources
    */
    int freeweight ( int what = 0 );

    //! Returns the size of a unit. A size is equal to the weight of the unit without any cargo or carried resources.
    int size ( void );

    //! hook that is called when a turn ends
    void endTurn( void );

    //! hook that is called the next round begins ( active player switching from player8 to player1 )
    void endRound ( void );

    //! constructs a vehicle at the given position.
    void constructvehicle ( pvehicletype tnk, int x, int y );

    //! checks whether the unit can construct a vehicle of the given type at the given position.
    bool vehicleconstructable ( pvehicletype tnk, int x, int y );

    //! displays the unit at position x/y on the screen
    void putimage ( int x, int y );

    //! sets the unit (and its cargo) the a new position (the unit will not be chained to a field)
    void setnewposition ( int x, int y );
    void setnewposition ( const MapCoordinate& mc );

    void setup_classparams_after_generation ( void );

    /** converts the unit so it is owned by 'player'. Note that the player is passed
        as parameter (values [0..8]), and not his color (which would be the values
        [0,8,16,..,64] )
    */
    void convert ( int player );

    //! sets the status of the unit's energy generator
    void setGeneratorStatus( bool status );
    bool getGeneratorStatus () const { return generatoractive; };

    //! callback that is called after the unit has attacked
    void postAttack();

    /** adds the units view to the map. The view must then be evaluated by functions like #evaluateviewcalculation ( pmap, int)
        \sa viewcalculation.cpp */
    void addview ( void );

    /** removes the units view to the map. The view must then be evaluated by functions like #evaluateviewcalculation ( pmap, int)
        \sa viewcalculation.cpp */
    void removeview ( void );

    /** returns true if the units view is currently added to the maps global visibility.
        \sa viewcalculation.cpp */
    bool isViewing ( ) const { return viewOnMap; };
    const SingleWeapon *getWeapon( unsigned weaponNum );

    /** checks whether the unit can construct a building of the given type.
        This method does not check if there is enough space around the unit to place
        the building */
    bool buildingconstructable ( pbuildingtype bld );

    /** searches for mineral resources.
        \returns > 0 on success ; < 0 on failure (error number is returned => message.txt )
    */
    int searchForMineralResources( void );

    bool searchForMineralResourcesAvailable();

    //! returns the units position
    MapCoordinate3D getPosition ( ) const;

    //! returns the units position; if  inside building then Height is -1
    MapCoordinate3D getPosition3D ( ) const;

    /** can the unit repair anything? This does not necessarily mean that the unit can repair
        other units, because a service weapon is additionally needed for that. It may be the
        case that the unit can only repair itself.
    */
    bool canRepair( const ContainerBase* item );

    /** fills a unit with all resources it can carry and sets it class to "to be determined on map load".
        This function should only be called in the mapeditor !
    */
    void fillMagically( void );


    /** generates a new unit, loads its parameters from the stream (where they have been
        previously written with #write) and returns this new unit.
    */
    static Vehicle* newFromStream ( pmap gamemap, tnstream& stream );

    /** replaces the parameters of the unit by the ones form the stream. The VehicleType on
        the stream and the current one must be the same!
    */
    void read ( tnstream& stream );

    void write ( tnstream& stream, bool includeLoadedUnits = true );
  private:
    void readData ( tnstream& stream );
  public:

    //! For the AI: calculating the ValueType if the unit was on the height uheight
    int getValueType ( int uheight ) { return log2(uheight); };

    //! For the AI: calculating the ValueType
    int getValueType ( ) { return log2(height); };


    //! to be used with EXTREME caution, and only in the mapeditor !!
    void transform ( const pvehicletype type );

    /** returns the method for changing the height in the specified direction, or none if there is none.
        \param dir  +1 is up;  -1 is down
        \param height if != 0:  assume this level of height instead of the actual one
    */
    const Vehicletype::HeightChangeMethod* getHeightChange( int dir, int height = 0 ) const;

    //! Is the unit able to shoot ?
    bool weapexist ( void );
    ~Vehicle ( );
};

 #pragma pack()

#endif



