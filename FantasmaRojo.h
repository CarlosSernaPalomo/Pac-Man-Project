#ifndef FANTASMAROJO_H
#define FANTASMAROJO_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Fantasma.h"

using namespace std;

class FantasmaRojo:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

void FantasmaRojo::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir(coorActualesComecocos);
	else Cazar(coorActualesComecocos);
}

#endif
