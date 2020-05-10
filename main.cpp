//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Bienvenida.h"
#include "SeleccionNivel.h"
#include "Partida.h"

using namespace std;

int main(){
	srand(time(NULL)); //Semilla para generar numeros aleatorios
	Bienvenida(); //Pantalla de bienvenida
	Nivel nivel = SeleccionNivel(); //Seleccion del nivel
	Partida partida(nivel); //Creacion de la partida
	partida.Jugar(); //Jugar
	return 0;
}
