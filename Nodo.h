#ifndef NODO_H
#define NODO_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Coordenadas.h"

using namespace std;

class Nodo {
public:
    bool operator ==(const Nodo& o);
    bool operator ==(const Coordenadas& o);
    bool operator <(const Nodo& o);
    Coordenadas pos, parent;
    int dist, cost;
};

bool Nodo::operator ==(const Nodo& o){
	return pos == o.pos;
}

bool Nodo::operator ==(const Coordenadas& o){
	return pos == o;
}

bool Nodo::operator <(const Nodo& o){
	return dist + cost < o.dist + o.cost;
}

#endif
