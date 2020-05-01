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


class Mapa {	
public:
	//Constructor por defecto (crea un mapa de 0s)
	Mapa(){
		w = 28;
		h = 31;
        for( int r = 0; r < h; r++ )
            for( int s = 0; s < w; s++ )
                m[s][r] = '0';
    }
    //Constructor a partir de semilla (crea un mapa a partir de un array bidimensional)
    Mapa(char semilla[31][28]) { 
        w = 28;
		h = 31;
        for( int r = 0; r < h; r++ )
            for( int s = 0; s < w; s++ )
                m[s][r] = semilla[r][s];
    }
    char m[28][31];
    int operator() (Coordenadas c) { return m[c.x][c.y]; }
    int w, h;
	void Modificar(Coordenadas, char);
};
