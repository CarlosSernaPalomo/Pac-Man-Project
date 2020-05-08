#ifndef ENTES_H
#define ENTES_H

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

class Comecocos:public Ente{
	protected:
		char dirIni;
		char dirActual;
		char dirDeseada;
		int vidas; //Se podria utilizar short int y en vez de 32 bits se utilizarian 16. CARLOS: Por mi vale.
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

class Fantasma:public Ente{
	public:
		char direccion = 'w'; //Solo es utilizada por el metodo Deambular
		void InicializarCasillasHabitables(Mapa mapa);
		Coordenadas SiguientePosicion(Coordenadas s, Coordenadas e, Mapa m); //Utiliza aStar
		void Cazar(Coordenadas coorActualesComecocos);
		void Emboscar(Coordenadas coorActualesComecocos, char dirActualComecocos);
		void Deambular();
		void Huir(Coordenadas coorActualesComecocos);
};

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
	coorActuales = c;
}

void Ente::MoverACoorIni(){
	coorActuales = coorIni;
}

Coordenadas Ente::LeerCoorActuales(){
	return coorActuales;
}

//Metodos de Comecocos

void Comecocos::InicializarCasillasHabitables(Mapa mapa){
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < mapa.w; s++){
			if(mapa.m[s][r] == 1 || mapa.m[s][r] == 4) casillasHabitables.m[s][r] = 1; //Solo meto los 1s porque se supone (si no me he equivocado al programar) que el mapa esta inicializado con 0s
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
	while(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < periodo){
		if(kbhit()){ //Se ha pulsado una tecla
			char input = getch(); //Se recoge la tecla pulsada
			if(input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'W' || input == 'A' || input == 'S' || input == 'D'){ //Se comprueba si es valida
				dirDeseada = tolower(input); //Se pasa a minuscula y asi ya luego no nos tenemos que preocupar de contemplar ambos casos
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
		if(dirDeseada == 'w') c1.y--; //El origen de coordenadas esta arriba a la izquierda, asi que para elegir la casilla justo encima de Pac-Man hay que decrementar y
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

//Metodos de Fantasma

void Fantasma::InicializarCasillasHabitables(Mapa mapa){
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < mapa.w; s++){
			if(mapa.m[s][r] == 1) casillasHabitables.m[s][r] = 1;
		}
	}
}

Coordenadas Fantasma::SiguientePosicion(Coordenadas s, Coordenadas e, Mapa m){ //s = punto partida, e = objetivo, m = mapa del fantasma
	aStar as;
	Coordenadas pos0,pos1,pos2;
	int k=0;
	if( as.search( s, e, m ) ) {
        list<Coordenadas> path;
        int c = as.path( path );
        //Bucle para mostrar por pantalla el camino del fantasma si fuera necesario
        /*for( int y = -1; y < 30; y++ ) {  
            for( int x = -1; x < 27; x++ ) {
                if( x < 0 || y < 0 || x > 25 || y > 28 || m( x, y ) == 1 )
                    cout << char(0xdb);
                else {
                    if( find( path.begin(), path.end(), Coordenadas( x, y ) )!= path.end() )
                        cout << "X";
                    else cout << " ";
                }
            }
            cout << "\n";
        }*/
        for( list<Coordenadas>::iterator i = path.begin(); i != path.end(); i++ ) {
        	if (k==0){
        		pos0.x=( *i ).x;
        		pos0.y=( *i ).y;
				k++;	
			}else if (k==1){
				pos1.x=( *i ).x;
        		pos1.y=( *i ).y;
				k++;
			}else if (k==2){
				pos2.x=( *i ).x;
        		pos2.y=( *i ).y;
				k++;
			}            
        }
    }    
    if (pos1==pos0)
    	return pos2;
    else return pos1;
};

void Fantasma::Cazar(Coordenadas coorActualesComecocos){
	coorActuales = SiguientePosicion(coorActuales, coorActualesComecocos, casillasHabitables);
}

void Fantasma::Emboscar(Coordenadas coorActualesComecocos, char dirActualComecocos){
	Coordenadas objetivo = coorActualesComecocos; //El objetivo es la casilla justo detras de Pac-Man. Esta garantizado que esta casilla es habitable ya que Pac-Man acaba de estar en ella
	if(dirActualComecocos == 'w') objetivo.y++;
	else if(dirActualComecocos == 's') objetivo.y--;
	else if(dirActualComecocos == 'a') objetivo.x++;
	else if(dirActualComecocos == 'd') objetivo.x--;
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

void Fantasma::Huir(Coordenadas coorActualesComecocos){
	casillasHabitables.Modificar(coorActualesComecocos, 1); //Hay que hacer la casilla en la que esta Pac-Man no habitable, ya que la huida debe realizarse evitando a Pac-Man
	coorActuales = SiguientePosicion(coorActuales, coorIni, casillasHabitables);
	casillasHabitables.Modificar(coorActualesComecocos, 0); //Se vuelve a marcar la casilla donde esta Pac-Man como habitable
}

//Métodos de FantasmaRojo

void FantasmaRojo::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir(coorActualesComecocos);
	else Cazar(coorActualesComecocos);
}

//Métodos de FantasmaRosa

void FantasmaRosa::Moverse(bool huida, Coordenadas coorActualesComecocos, char dirActualComecocos){
	if(huida) Huir(coorActualesComecocos);
	else Emboscar(coorActualesComecocos, dirActualComecocos);
}

//Métodos de FantasmaNaranja

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

//Métodos de FantasmaCian

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
