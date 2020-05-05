#include <iostream>
#include <stdlib.h> //CARLOS: para usar abs
#include <ctype.h> //CARLOS: Para usar tolower
//CARLOS: Estas librerias son para el metodo ActualizarDirDeseada que propongo
#include <conio.h>
#include <chrono>

using namespace std;

class Ente{
	protected:
		Mapa casillasHabitables; //CARLOS: El mapa de casillas habitables contendra 1s (casillas no habitables) y 0s (casillas habitables)
		const Coordenadas coorIni;
		Coordenadas coorActuales;
	public:
			void InicializarCoor(Coordenadas coorIni);
			void MoverACoorIni();
			Coordenadas LeerCoorActuales();	
};

class Comecocos:public Ente{
	protected: //CARLOS: Se podria poner como private ya que ninguna clase va a heredar de esta. Asi demostramos que sabemos utilizar tanto public como private como protected
		char dirActual;
		char dirDeseada;
		int vidas; //Se podria utilizar short int y en vez de 32 bits se utilizarian 16. CARLOS: Por mi vale.
	public:
		void InicializarCasillasHabitables(Mapa mapa);
		void InicializarDir(char dirIni);
		void InicializarVidas(int vidasIni);
		int LeerVidas();
		void PerderVida();
		void ActualizarDirDeseada();
		void Moverse();
};

class Fantasma:public Ente{
	public:
		char direccion = 'w'; //Solo es utilizada por el metodo Deambular
		void InicializarCasillasHabitables(Mapa mapa);
		void Cazar(Coordenadas coorActualesComecocos);
		void Emboscar(Coordenadas coorActualesComecocos, char dirActualComecocos);
		void Deambular();
		void Huir();
}

class FantasmaRojo:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

class FantasmaRosa:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

class FantasmaNaranja:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

class FantasmaCian:public Fantasma{
	public:
		void Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos);
};

//Metodos de Ente

void Ente::InicializarCoor(Coordenadas c){
	coorIni = c;
}

void Ente::MoverACoorIni(){
	coorActuales=coorIni;
}

Coordenadas Ente::LeerCoorActuales(){
	return coorActuales;
}

//Metodos de Comecocos

void Comecocos::InicializarCasillasHabitables(Mapa mapa){
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < mapa.w; s++){
			if(mapa.m[s][r] == 1 || mapa.m[s][r] == 4) mapaDeCocos.m[s][r] = 1; //Solo meto los 1s porque se supone (si no me he equivocado al programar) que el mapa esta inicializado con 0s
		}
	}
}

void InicializarDir(char dirIni){
	dirActual = dirIni;
	dirDeseada = dirIni;
}

void Comecocos::InicializarVidas(int vidasIni){
	vidas = vidasIni;
}

int Comecocos::LeerVidas(){
	return vidas;
}

void Comecocos::PerderVida(){
	vidas = vidas - 1;
	return;
}

/*void Comecocos::ActualizarDirDeseada(){
	char input;
	bool flag;
	flag=false;
	while(flag==false){//Este chequeo no es necesario si al final hay botones en la interfaz de usuario
		cout<<"Direccion WASD: ";
		cin>>input;
		cout<<"\nDireccion "<<input<< " es ";
		if(input=='w' or input=='a' or input=='s' or input=='d' or input=='W' or input=='A' or input=='S' or input=='D'){
			cout<<"valida\n";
			dirDeseada=input;
			flag=true;
		}
		else
		{
		cout<<"no valida, vuelva a intentarlo\n";
		}
	}
}*/

void Comecocos::ActualizarDirDeseada(){
	auto start = chrono::steady_clock::now();
	while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < 0.2){
		if(kbhit()){ //Se ha pulsado una tecla
			char input = getch(); //Se recoge la tecla pulsada
			if(input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'W' || input == 'A' || input == 'S' || input == 'D'){ //Se comprueba si es valida
				dirDeseada = tolower(input); //Se pasa a minuscula y asi ya luego no nos tenemos que preocupar de contemplar ambos casos
			}
		}
	}
}

void Comecocos::Moverse(){
	
}

//Metodos de Fantasma

void Fantasma::InicializarCasillasHabitables(Mapa mapa){
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < mapa.w; s++){
			if(mapa.m[s][r] == 1) mapaDeCocos.m[s][r] = 1;
		}
	}
}

void Fantasma::Cazar(Coordenadas coorActualesComecocos){
	coorActuales = SiguientePosicion(coorActuales, coorActualesComecocos, casillasHabitables);
}

void Fantasma::Emboscar(Coordenadas coorActualesComecocos, char dirActualComecocos){
	Coordenadas objetivo = coorActualesComecocos; //El objetivo es la casilla justo detras de Pac-Man. Esta garantizado que esta casilla es habitable ya que Pac-Man acaba de estar en ella
	switch(dirActualComecocos){
		case 'w':
			objetivo.y++; //El origen de coordenadas esta arriba a la izquierda, asi que para elegir la casilla justo debajo de Pac-Man hay que incrementar y
			break;
		case 's':
			objetivo.y--;
			break;
		case 'a':
			objetivo.x++;
			break;
		case 'd':
			objetivo.x--;
	}
	casillasHabitables.Modificar(coorActualesComecocos, 1); //Se hace a la casilla donde esta Pac-Man no habitable para el fantasma
	coorActuales = SiguientePosicion(coorActuales, objetivo, casillasHabitables);
	casillasHabitables.Modificar(coorActualesComecocos, 0); //Se vuelve a marcar la casilla donde esta Pac-Man como habitable
}

void Fantasma::Deambular(){
	while(true){
		Coordenadas coorNuevas = coorActuales;
		switch(direccion){
			case 'w':
				coorNuevas.y++;
				break;
			case 's':
				coorNuevas.y--;
				break;
			case 'a':
				coorNuevas.x++;
				break;
			case 'd':
				coorNuevas.x--;
	 	}
		if(casillasHabitables(coorNuevas) == 0){ //Si las nuevas coordenadas son habitables, pasan a ser las coordenadas actuales y termina el bucle
			coorActuales = coorNuevas;
			break;
		}else{ //Si no lo son, se escoge aleatoriamente una nueva direccion
			int n = rand()%4;
			switch(n){
				case 0:
					direccion = 'w';
					break;
				case 1:
					direccion = 's';
					break;
				case 2:
					direccion = 'a';
					break;
				case 3:
					direccion = 'd';
			}
		}
	}
}

void Fantasma::Huir(){
	casillasHabitables.Modificar(coorActualesComecocos, 1); //Hay que hacer la casilla en la que esta Pac-Man no habitable, ya que la huida debe realizarse evitando a Pac-Man
	coorActuales = SiguientePosicion(coorActuales, coorIni, casillasHabitables);
	casillasHabitables.Modificar(coorActualesComecocos, 0); //Se vuelve a marcar la casilla donde esta Pac-Man como habitable
}

//Métodos de FantasmaRojo

void FantasmaRojo::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir();
	else Cazar(coorActualesComecocos);
}

//Métodos de FantasmaRosa

void FantasmaRosa::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir();
	else Emboscar(coorActualesComecocos, dirActualComecocos);
}

//Métodos de FantasmaNaranja

void FantasmaNaranja::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir();
	else{
		x = coorActualesComecocos.x - coorActuales.x;
		y = coorActualesComecocos.y - coorActuales.y;
		dist = x*x + y*y;
		if(dist < 100) Cazar(coorActualesComecocos);
		else Deambular();
	}
}

//Métodos de FantasmaCian

void FantasmaCian::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir();
	else{
		int n = rand()%3;
		switch(n){
			case 0: //Comportamiento de fantasmaRojo
				Cazar(coorActualesComecocos);
			case 1: //Comportamiento de fantasmaRosa
				Emboscar(coorActualesComecocos, dirActualComecocos);
			case 2: //Comportamiento de fantasmaNaranja
				x = coorActualesComecocos.x - coorActuales.x;
			y = coorActualesComecocos.y - coorActuales.y;
			dist = abs(x) + abs(y);
			if(dist < 100) Cazar(coorActualesComecocos);
			else Deambular();
		}
	}
}
