#ifndef ENTE_H
#define ENTE_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "aStar.h"

using namespace std;

class Ente{
	protected:
		Mapa casillasHabitables; //CARLOS: El mapa de casillas habitables contendra 1s (casillas no habitables) y 0s (casillas habitables)
		Coordenadas coorIni;
		Coordenadas coorActuales;
	public:
		void InicializarCoor(Coordenadas coorIni);
		void MoverACoorIni();
		Coordenadas LeerCoorActuales();	
};

void Ente::InicializarCoor(Coordenadas c){
	coorIni = c;
	coorActuales = c;
}

void Ente::MoverACoorIni(){
	coorActuales = coorIni;
}

Coordenadas Ente::LeerCoorActuales(){
	return coorActuales;
}

#endif
