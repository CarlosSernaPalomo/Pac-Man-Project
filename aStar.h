#ifndef ASTAR_H
#define ASTAR_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Mapa.h"

using namespace std;

class aStar {
public:
	//Constructor
	aStar();
	//Metodos
	int calcDist(Coordenadas& p);
	bool isValid(Coordenadas& p);
	bool existPoint(Coordenadas& p, int cost);
	bool fillOpen(Nodo& n);
	bool search(Coordenadas& s, Coordenadas& e, Mapa& mp);
	int path(list<Coordenadas>& path);
	//Variables
	Mapa m;
	Coordenadas end, start;
	Coordenadas neighbours[8];
	list<Nodo> open;
	list<Nodo> closed;
};

aStar::aStar(){
    neighbours[0] = Coordenadas(  0, -1 ); neighbours[1] = Coordenadas( -1,  0 );
    neighbours[2] = Coordenadas(  0,  1 ); neighbours[3] = Coordenadas(  1,  0 );
}

int aStar::calcDist(Coordenadas& p){
    int x = end.x - p.x, y = end.y - p.y;
    return( x * x + y * y );
}

bool aStar::isValid(Coordenadas& p) {
    return ( p.x >-1 && p.y > -1 && p.x < m.w && p.y < m.h );
}

bool aStar::existPoint(Coordenadas& p, int cost){
    list<Nodo>::iterator i;
    i = find( closed.begin(), closed.end(), p );
    if( i != closed.end() ) {
        if( ( *i ).cost + ( *i ).dist < cost ) return true;
        else { closed.erase( i ); return false; }
    }
    i = std::find( open.begin(), open.end(), p );
    if( i != open.end() ) {
        if( ( *i ).cost + ( *i ).dist < cost ) return true;
        else { open.erase( i ); return false; }
    }
    return false;
}

bool aStar::fillOpen(Nodo& n){
    int stepCost, nc, dist;
    Coordenadas neighbour;
    for( int x = 0; x < 8; x++ ) {
        stepCost = x < 4 ? 1 : 1;
        neighbour = n.pos + neighbours[x];
        if( neighbour == end ) return true;

        if( isValid( neighbour ) && m( neighbour ) != 1 ) {
            nc = stepCost + n.cost;
            dist = calcDist( neighbour );
            if( !existPoint( neighbour, nc + dist ) ) {
                Nodo m;
                m.cost = nc; m.dist = dist;
                m.pos = neighbour; 
                m.parent = n.pos;
                open.push_back( m );
            }
        }
    }
    return false;
}

bool aStar::search(Coordenadas& s, Coordenadas& e, Mapa& mp){
    Nodo n; end = e; start = s; m = mp;
    n.cost = 0; n.pos = s; n.parent = 0; n.dist = calcDist( s ); 
    open.push_back( n );
    while( !open.empty() ) {
        Nodo n = open.front();
        open.pop_front();
        closed.push_back( n );
        if( fillOpen( n ) ) return true;
    }
    return false;
}

int aStar::path(list<Coordenadas>& path){
    path.push_front( end );
    int cost = 1 + closed.back().cost; 
    path.push_front( closed.back().pos );
    Coordenadas parent = closed.back().parent;
    for( list<Nodo>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++ ) {
        if( ( *i ).pos == parent && !( ( *i ).pos == start ) ) {
            path.push_front( ( *i ).pos );
            parent = ( *i ).parent;
        }
    }
    path.push_front( start );
    return cost;
}

#endif
