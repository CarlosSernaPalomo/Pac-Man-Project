#include <list>
#include <algorithm>
#include <iostream>
#include "aStar.h"
#include "Partida.h"
#include "Coordenadas.h"
#include "Entes.h"
#include "Mapas.h"
using namespace std;
 
int main( int argc, char* argv[] ) {
	Partida partida;
	
	while (partida.continuar==true){
		
	partida.VisualizaMapa();
	partida.Mover();
	partida.Estado1();
	partida.SiguientePosicion(partida.Rojo);
	partida.Estado2();
	partida.ActualizaTurno();
	}
	
	
    return 0;
}
 
