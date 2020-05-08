#ifndef FANTASMAROSA_H
#define FANTASMAROSA_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Fantasma.h"

using namespace std;

class FantasmaRosa:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

void FantasmaRosa::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir(coorActualesComecocos);
	else Emboscar(coorActualesComecocos, dirActualComecocos);
}

#endif
