#ifndef COORDENADAS_H
#define COORDENADAS_H

#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

class Coordenadas {
public:
    Coordenadas( int a = 0, int b = 0 ) { x = a; y = b; } 
    bool operator ==( const Coordenadas& o ) { return o.x == x && o.y == y; }
    Coordenadas operator +( const Coordenadas& o ) { return Coordenadas( o.x + x, o.y + y ); }
    int x, y;
};


#endif
