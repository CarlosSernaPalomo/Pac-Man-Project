#ifndef COORDENADAS_H
#define COORDENADAS_H

//Librerias
#include "librerias.h"

using namespace std;

class Coordenadas {
public:
	Coordenadas(int a, int b);
	bool operator ==(const Coordenadas& o);
	Coordenadas operator +(const Coordenadas& o);
	int x, y;
};

Coordenadas::Coordenadas(int a = 0, int b = 0){
	x = a; y = b;
}

bool Coordenadas::operator ==(const Coordenadas& o){
	return o.x == x && o.y == y;
}

Coordenadas Coordenadas::operator +(const Coordenadas& o){
	return Coordenadas(o.x + x, o.y + y);
}

#endif
