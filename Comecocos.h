#ifndef COMECOCOS_H
#define COMECOCOS_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Ente.h"

using namespace std;

class Comecocos:public Ente{
	private:
		char dirIni;
		char dirActual;
		char dirDeseada;
		int vidas;
		int periodo;
	public:
		void InicializarCasillasHabitables(Mapa mapa);
		void InicializarDir(char dir);
		void InicializarVidas(int vidasIni);
		void InicializarPeriodo(int p);
		int LeerVidas();
		void QuitarVida();
		char LeerDirActual();
		void ActualizarDirDeseada();
		void ResetearDir();
		void Moverse();
};

void Comecocos::InicializarCasillasHabitables(Mapa mapa){
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < mapa.w; s++){
			if(mapa.m[s][r] == 1 || mapa.m[s][r] == 4) casillasHabitables.m[s][r] = 1;
		}
	}
}

void Comecocos::InicializarDir(char dir){
	dirIni = dir;
	dirActual = dir;
	dirDeseada = dir;
}

void Comecocos::InicializarVidas(int vidasIni){
	vidas = vidasIni;
}

void Comecocos::InicializarPeriodo(int p){
	periodo = p;
}

int Comecocos::LeerVidas(){
	return vidas;
}

void Comecocos::QuitarVida(){
	vidas = vidas - 1;
	return;
}

char Comecocos::LeerDirActual(){
	return dirActual;
}

void Comecocos::ActualizarDirDeseada(){
	auto start = chrono::steady_clock::now();
	while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < periodo){
		if(kbhit()){ //Se ha pulsado una tecla
			char input = getch(); //Se recoge la tecla pulsada
			//Se comprueba si la tecla es valida
			if(input == 'w' || input == 'W'
			|| input == 'a' || input == 'A'
			|| input == 's' || input == 'S'
			|| input == 'd' || input == 'D'){
				dirDeseada = tolower(input); //Se pasa a minuscula y asi ya no hay que preocuparse de contemplar ambos casos
			}
		}
	}
}

void Comecocos::ResetearDir(){
	dirActual = dirIni;
	dirDeseada = dirIni;
}

void Comecocos::Moverse(){
	
	//Se comprueba si se puede cambiar la direccion actual conforme a la deseada y si es asi se cambia
	if(dirActual != dirDeseada){
		Coordenadas c1 = coorActuales;
		//El origen de coordenadas esta arriba a la izquierda, asi que para elegir la casilla justo encima de Pac-Man hay que decrementar y, y viceversa
		if(dirDeseada == 'w') c1.y--;
		else if(dirDeseada == 's') c1.y++;
		else if(dirDeseada == 'a') c1.x--;
		else if(dirDeseada == 'd') c1.x++;
		if(casillasHabitables(c1) == 0) dirActual = dirDeseada;
	}
	
	//Se comprueba si Pac-Man puede continuar moviendose o si se ha topado con un muro
	Coordenadas c2 = coorActuales;
	if(dirActual == 'w') c2.y--;
	else if(dirActual == 's') c2.y++;
	else if(dirActual == 'a') c2.x--;
	else if(dirActual == 'd') c2.x++;
	if(casillasHabitables(c2) == 0) coorActuales = c2;
}

#endif
