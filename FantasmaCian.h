#ifndef FANTASMACIAN_H
#define FANTASMACIAN_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Fantasma.h"

using namespace std;

class FantasmaCian:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

void FantasmaCian::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir(coorActualesComecocos);
	else{
		int n = rand()%3;
		switch(n){
			case 0: //Comportamiento de fantasmaRojo
				Cazar(coorActualesComecocos);
				break;
			case 1: //Comportamiento de fantasmaRosa
				Emboscar(coorActualesComecocos, dirActualComecocos);
				break;
			case 2: //Comportamiento de fantasmaNaranja
				int x = coorActualesComecocos.x - coorActuales.x;
				int y = coorActualesComecocos.y - coorActuales.y;
				int dist = x*x + y*y;
				if(dist < 100) Cazar(coorActualesComecocos);
				else Deambular();
		}
	}
}

#endif
