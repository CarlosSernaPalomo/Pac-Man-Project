#ifndef FANTASMANARANJA_H
#define FANTASMANARANJA_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Fantasma.h"

using namespace std;

class FantasmaNaranja:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

void FantasmaNaranja::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir(coorActualesComecocos);
	else{
		int x = coorActualesComecocos.x - coorActuales.x;
		int y = coorActualesComecocos.y - coorActuales.y;
		int dist = x*x + y*y;
		if(dist < 100) Cazar(coorActualesComecocos);
		else Deambular();
	}
}

#endif
