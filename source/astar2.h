#ifndef astar2_h_included
 #define astar2_h_included

 #include <vector>

/*! \file astar2.h
    finding a path with the A* algorithm
*/


class AStar {
    public:
       typedef vector<MapCoordinate> Path;
       pmap tempsMarked;
       Path *_path;
       pvehicle _veh;
       pmap _actmap;


    protected:
       virtual int getMoveCost ( int x1, int y1, int x2, int y2, const pvehicle vehicle );
    public:


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
           bool operator< ( const Node& a );
       };
       int dist( HexCoord a, HexCoord b );

       typedef std::vector<Node> Container;
       greater<Node> comp;

       inline void get_first( Container& v, Node& n );


       Container visited;

       void findPath( pmap actmap, HexCoord A, HexCoord B, Path& path, pvehicle veh );
       void findPath( pmap actmap, Path& path, pvehicle veh, int x, int y );
       void findAllAccessibleFields ( pmap actmap, pvehicle veh );  // all accessible fields will have a.temp set to 1
       int getDistance( );
       int getTravelTime( );
       bool fieldVisited ( int x, int y);
       AStar ( void );
       virtual ~AStar ( );
 };

//bool operator< ( const AStar::Node& a, const AStar::Node& b );

 //! finding a path for unit veh to position x, y on map actmap.
extern void findPath( pmap actmap, AStar::Path& path, pvehicle veh, int x, int y );

#endif
