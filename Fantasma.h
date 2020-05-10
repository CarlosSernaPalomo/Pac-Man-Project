#ifndef FANTASMA_H
#define FANTASMA_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Ente.h"

using namespace std;

class Fantasma:public Ente{
	protected:
		char direccion = 'w'; //Solo es utilizada por el metodo Deambular
		bool tocaHuir = true;
	public:
		void InicializarCasillasHabitables(Mapa mapa);
		Coordenadas SiguientePosicion(Coordenadas s, Coordenadas e, Mapa m); //Utiliza aStar
		void Cazar(Coordenadas coorActualesComecocos);
		void Emboscar(Coordenadas coorActualesComecocos, char dirActualComecocos);
		void Deambular();
		void Huir(Coordenadas coorActualesComecocos);
};

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
	//El objetivo es tambien la casilla donde esta Pac-Man, pero acercandose a Pac-Man por delante
	Coordenadas objetivo = coorActualesComecocos;
	if(dirActualComecocos == 'w') objetivo.y--;
	else if(dirActualComecocos == 's') objetivo.y++;
	else if(dirActualComecocos == 'a') objetivo.x--;
	else if(dirActualComecocos == 'd') objetivo.x++;
	//Se hace a la casilla justo detras de Pac-Man no habitable para el fantasma. Esto se hace para asegurar que el fantasma se acerque por delante
	Coordenadas detras = coorActualesComecocos;
	if(dirActualComecocos == 'w') detras.y++;
	else if(dirActualComecocos == 's') detras.y--;
	else if(dirActualComecocos == 'a') detras.x++;
	else if(dirActualComecocos == 'd') detras.x--;
	casillasHabitables.Modificar(detras, 1);
	coorActuales = SiguientePosicion(coorActuales, objetivo, casillasHabitables);
	//Se vuelve a marcar la casilla detras de Pac-Man como habitable
	casillasHabitables.Modificar(detras, 0);
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
	//Los fantasmas reducen su velocidad a la mitad cuando huyen
	if(tocaHuir){
		//Hay que hacer la casilla en la que esta Pac-Man no habitable, ya que la huida debe realizarse evitando a Pac-Man
		casillasHabitables.Modificar(coorActualesComecocos, 1);
		coorActuales = SiguientePosicion(coorActuales, coorIni, casillasHabitables);
		//Se vuelve a marcar la casilla donde esta Pac-Man como habitable
		casillasHabitables.Modificar(coorActualesComecocos, 0);
		tocaHuir = false;
	}else tocaHuir = true;
}

#endif
