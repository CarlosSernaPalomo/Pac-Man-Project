#ifndef NIVEL_H
#define NIVEL_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Mapa.h"

using namespace std;

class Nivel{
	
	public:
		Mapa mapa;
		char dirIniComecocos;
		Coordenadas coorIniComecocos;
		Coordenadas coorIniFantasmaRojo;
		Coordenadas coorIniFantasmaRosa;
		Coordenadas coorIniFantasmaNaranja;
		Coordenadas coorIniFantasmaCian;
		int vidasIni;
		int duracionPartida;
		int duracionHuida;
		int periodo;
};

#endif
