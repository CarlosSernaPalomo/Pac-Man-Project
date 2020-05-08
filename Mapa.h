#ifndef MAPAS_H
#define MAPAS_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Nodo.h"

using namespace std;

class Mapa {	
public:
	//Constructor por defecto (crea un mapa de 0s)
	Mapa();
	//Constructor a partir de semilla (crea un mapa a partir de un array bidimensional)
	Mapa(char semilla[31][28]);
	//Variables
	char m[28][31];
	int w, h;
	//Metodos
	int operator() (Coordenadas c);
	void Modificar(Coordenadas c, char valor);
	void Imprimir();
};

Mapa::Mapa(){
	w = 28;
	h = 31;
	for(int r = 0; r < h; r++) for(int s = 0; s < w; s++) m[s][r] = 0;
}

Mapa::Mapa(char semilla[31][28]) { 
	w = 28;
	h = 31;
	for(int r = 0; r < h; r++) for(int s = 0; s < w; s++) m[s][r] = semilla[r][s];
}

int Mapa::operator ()(Coordenadas c){
	return m[c.x][c.y];
}

void Mapa::Modificar(Coordenadas c, char valor){
	m[c.x][c.y] = valor;
}

void Mapa::Imprimir(){
Coordenadas posicionActual;
	for( int y = 0; y < h; y++ ) {
		for( int x = 0; x < w; x++ ) {
			if(m[x][y] == 0) //Pasillo
				cout << " ";
			else if(m[x][y] == 1) //Pared
				cout << char(0xdb);
			else if(m[x][y] == 2)	//Coco
				cout << char(250);
			else if(m[x][y] == 3) //Supercoco
				cout << "O";
			else if(m[x][y] == 4) //Puerta del refugio
				cout << char(176);
		}
		cout << endl;
	}
}

#endif
