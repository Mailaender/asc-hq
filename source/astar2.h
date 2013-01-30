/*! \file astar2.h
    \brief Interface for the A* pathfinding algorithm
*/


#ifndef astar2H
 #define astar2H

 #include <vector>
 #include <tr1/unordered_map>
 #include <functional>
 #include "mapalgorithms.h"
 #include "gamemap.h"

 #include <boost/multi_index_container.hpp>
 #include <boost/multi_index/ordered_index.hpp>
 #include <boost/multi_index/hashed_index.hpp>
 #include <boost/multi_index/identity.hpp>
 #include <boost/multi_index/member.hpp>

 enum HexDirection { DirN, DirNE, DirSE, DirS, DirSW, DirNW, DirNone };


 //! A 2dimensional path finding algorithm, from Amit J. Patel
 class AStar {
    public:
       typedef vector<MapCoordinate> Path;

    protected:
       int MAXIMUM_PATH_LENGTH;
       GameMap* tempsMarked;
       Path *_path;
       Vehicle* _veh;
       GameMap* gamemap;


       //! returns the movement cost for the unit to travel from x1/y1 to x2/y2
       virtual int getMoveCost ( int x1, int y1, int x2, int y2, const Vehicle* vehicle );
    public:
       AStar ( GameMap* actmap, Vehicle* veh );

       //! A hexagonal Coordinate. This structure is used instead of MapCoordinate to reduce the amount of modifications to Amits path finding code.
       struct HexCoord{
           int m, n;
           HexCoord(): m(0), n(0) {}
           HexCoord( int m_, int n_ ): m(m_), n(n_) {}
           ~HexCoord() {}
       };

       struct Node {
           HexCoord h;        // location on the map, in hex coordinates
           int gval;        // g in A* represents how far we've already gone
           int hval;        // h in A* represents an estimate of how far is left
           Node(): h(0,0), gval(0), hval(0) {}
           bool operator< ( const Node& a ) const;
           bool operator> ( const Node& a ) const;
       };

       int dist( HexCoord a, HexCoord b );

       typedef std::vector<Node> Container;
	   std::greater<Node> comp;

       inline void get_first( Container& v, Node& n );


       Container visited;

       //! searches for a path from A to B and stores it in path
       void findPath( HexCoord A, HexCoord B, Path& path );

       //! searches for a path from the units current position to dest and stores it in path
       void findPath( Path& path, int x, int y );

       /** searches for all fields that are within the range of maxDist and marks them.
           On each field one bit for each level of height will be set.
           The Destructor removes all marks.
       */
       void findAllAccessibleFields ( int maxDist = maxint );  // all accessible fields will have a.temp set to 1

       //! returns the distance of the last found path, or -1 on any error
       int getDistance( );

       //! returns the number of turns that the unit will need to travel along the last found path
       int getTravelTime( );

       //! checks weather the field fld was among the visited fields during the last search
       bool fieldVisited ( int x, int y);
      
       virtual ~AStar ( );
 };


 //! finding a path for unit veh to position x, y on map actmap.
extern void findPath( GameMap* actmap, AStar::Path& path, Vehicle* veh, int x, int y );


//! A 3D path finding algorithm, based on the 2D algorithm by Amit J. Patel
class AStar3D {
       bool naivePathFinder(const MapCoordinate3D& a, const MapCoordinate3D& b);
    public:
       typedef float DistanceType;
       static const DistanceType longestPath = 1e9;
       //static const __m128i longestPathVector = _mm_set_epi32(1e9, 1e9, 1e9, 1e9);
       class OperationLimiter {
           public:
              virtual bool allowHeightChange() = 0;
              virtual bool allowMovement() = 0;
              virtual bool allowLeavingContainer() = 0;
              virtual bool allowDocking() = 0;
              virtual ~OperationLimiter() {};
       };


       class PathPoint: public MapCoordinate3D {
             PathPoint() {};
          public:
             PathPoint ( const MapCoordinate3D& mc, int dist_, int enterHeight_, bool hasAttacked_ ) : MapCoordinate3D(mc), dist(dist_), enterHeight(enterHeight_), hasAttacked(hasAttacked_) {};
             // PathPoint ( const MapCoordinate3D& mc ) : MapCoordinate3D(mc), dist(-1), enterHeight(-1), hasAttacked(false) {};
             int getRealHeight() { if ( getNumericalHeight() != -1 ) return getNumericalHeight(); else return enterHeight; };
             MapCoordinate3D getRealPos() { MapCoordinate3D p; p.setnum(x,y, getRealHeight()); return p; };
             int dist;
             int enterHeight;
             bool hasAttacked;
             void write( tnstream& stream ) const;
             void read( tnstream& stream );
             static PathPoint newFromStream( tnstream& stream );
       };

       typedef deque<PathPoint> Path;

       struct hash_h {
          size_t operator()(const MapCoordinate3D &h) const{
             return static_cast<size_t>(h.x) ^ (static_cast<size_t>(h.y) << 8) ^ (static_cast<size_t>(h.getNumericalHeight())  << 16);
          }
       };

       struct Node {
           Node* previous;
           MapCoordinate3D h;        // location on the map, in hex coordinates
           AStar3D::DistanceType gval;        // g in A* represents how far we've already gone
           AStar3D::DistanceType hval;        // h in A* represents an estimate of how far is left
           int enterHeight;
           bool canStop;
           bool hasAttacked;
           Node(DistanceType _gval=0, DistanceType _hval=0, int _enterHeight=-1,
                bool _canStop=false, bool _hasAttacked=false) :
              gval(_gval), hval(_hval), enterHeight(_enterHeight), canStop(_canStop),
              hasAttacked(_hasAttacked) {}
           bool operator< ( const Node& b ) const;
       };

    protected:
       OperationLimiter* operationLimiter;
       int MAXIMUM_PATH_LENGTH;
       GameMap* tempsMarked;
       Path *_path;
       Vehicle* veh;
       GameMap* actmap;
       float vehicleSpeedFactor[8];
       float maxVehicleSpeedFactor;
       bool markTemps;
       WindMovement* wind;

       virtual DistanceType getMoveCost ( const MapCoordinate3D& start, const MapCoordinate3D& dest, const Vehicle* vehicle, bool& hasAttacked );

       int* fieldAccess;

       DistanceType dist( const MapCoordinate3D& a, const MapCoordinate3D& b );
       DistanceType dist( const MapCoordinate3D& a, const vector<MapCoordinate3D>& b );

    public:

      typedef boost::multi_index_container <
          Node,
          boost::multi_index::indexed_by <
             boost::multi_index::ordered_non_unique<boost::multi_index::identity<Node> >,
             boost::multi_index::hashed_unique<boost::multi_index::member<Node, MapCoordinate3D, &Node::h>, hash_h>
          >
       > OpenContainer;

       typedef OpenContainer::nth_index<1>::type OpenContainerIndex;

       //! the reachable fields
       class VisitedContainer: protected deque<Node> {
             typedef tr1::unordered_map<MapCoordinate3D, DistanceType, hash_h> hMapType;
             hMapType hMap;
          public:
             typedef deque<Node> Parent;
             typedef Parent::iterator iterator;
             Node* add ( const Node& n) {
                push_back(n);
                hMap[n.h] = n.gval;
                return &back();
             };
             bool contains ( const MapCoordinate3D& pos ) {
                return hMap.find(pos) != hMap.end();
             }
             DistanceType gval( const MapCoordinate3D& pos ) {
                hMapType::iterator i = hMap.find(pos); 
                if (i == hMap.end()) return -1;
                else return i->second;
             };

             iterator begin() { return Parent::begin(); };
             iterator end() { return Parent::end(); };
      };
       VisitedContainer visited;
    protected:

       //! adds a node to the OpenContainer, or replaces one
       void addToOpen ( const Node& n, OpenContainer& open );

       bool initNode ( Node& newN,
                       Node* oldN_ptr,
                       int dir,
                       const vector<MapCoordinate3D>& B,
                       int newNumericalHeight=-2,
                       bool disableAttack=false,
                       bool keepEnterHeight=false);

    public:
       AStar3D ( GameMap* actmap, Vehicle* veh, bool markTemps_ = true, int maxDistance = maxint );


       //! the search can be restricted to certain operations
       void registerOperationLimiter( OperationLimiter* ol ) { operationLimiter = ol; };

       //! searches for a path from A to B and stores it in path
       void findPath( const MapCoordinate3D& A, const vector<MapCoordinate3D>& B, Path& path );

       //! searches for a path from the unit's current position to dest and stores it in path
       void findPath( Path& path, const MapCoordinate3D& dest );

       //! searches for a path from the units current position to one of the dest fields and stores it in path
       void findPath( Path& path, const vector<MapCoordinate3D>& dest );

       /** searches for all fields that are within the range of maxDist and marks them.
           On each field one bit for each level of height will be set.
           The Destructor removes all marks.
           \param path if non-null, all fields will be stored there
       */
       void findAllAccessibleFields ( vector<MapCoordinate3D>* path = NULL );

       //! returns the distance of the last found path, or -1 on any error
       int getDistance( );

       //! returns the number of turns that the unit will need to travel along the last found path
       int getTravelTime( );

       int& getFieldAccess ( int x, int y );
       int& getFieldAccess ( const MapCoordinate& mc );

       virtual ~AStar3D ( );
 };

#endif
