//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Nivel.h"

using namespace std;

Nivel SeleccionNivel(){
	/*Creacion del mapa
	Significado:
	- 0: casilla libre
	- 1: pared
	- 2: coco
	- 3: supercoco
	- 4: puerta del refugio (los fantasmas la atraviesan pero Pac-Man no)*/
	char semilla[31][28] = {
	  //00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//00
	    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},//01
		{1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},//02
		{1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1},//03
		{1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},//04
		{1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},//05
		{1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},//06
		{1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},//07
		{1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},//08
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},//09
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},//10
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//11	
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 4, 4, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//12
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//13
		{1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1},//14
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//15
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//16			
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//17
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//18
		{1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},//19
		{1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},//20
		{1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},//21	
		{1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1},//22
		{1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1},//23
		{1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},//24
		{1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},//25
		{1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},//26		
		{1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},//27
		{1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},//28
		{1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},//29
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//30
	};
	Mapa mapaClasico(semilla);
	
	//Se crean 3 niveles: uno facil, otro normal y otro dificil
	Nivel nivelFacil;
	nivelFacil.mapa = mapaClasico;
	nivelFacil.dirIniComecocos = 'd';
	nivelFacil.coorIniComecocos.x = 13; nivelFacil.coorIniComecocos.y = 23;
	nivelFacil.coorIniFantasmaRojo.x = 14; nivelFacil.coorIniFantasmaRojo.y = 11;
	nivelFacil.coorIniFantasmaRosa.x = 11; nivelFacil.coorIniFantasmaRosa.y = 13;
	nivelFacil.coorIniFantasmaNaranja.x = 13; nivelFacil.coorIniFantasmaNaranja.y = 15;
	nivelFacil.coorIniFantasmaCian.x = 16; nivelFacil.coorIniFantasmaCian.y = 13;
	nivelFacil.vidasIni = 3;
	nivelFacil.duracionHuida = 10; //En segundos
	nivelFacil.duracionPartida = 300; //En segundos
	nivelFacil.periodo = 500; //Milisegundos entre movimientos consecutivos
	
	//Los 3 niveles tienen el mismo mapa y las mismas posiciones iniciales
	Nivel nivelNormal = nivelFacil;
	Nivel nivelDificil = nivelFacil;
	
	//Los 3 niveles se diferencian en los siguientes parametros
	
	nivelFacil.vidasIni = 5;
	nivelFacil.duracionHuida = 60; //En segundos
	nivelFacil.duracionPartida = 4000; //En segundos
	nivelFacil.periodo = 1000; //Milisegundos entre movimientos consecutivos
	
	nivelNormal.vidasIni = 3;
	nivelNormal.duracionHuida = 15;
	nivelNormal.duracionPartida = 1000;
	nivelNormal.periodo = 500;
	
	nivelDificil.vidasIni = 1;
	nivelDificil.duracionHuida = 5;
	nivelDificil.duracionPartida = 250;
	nivelDificil.periodo = 250;
	
	//Seleccion del nivel
	cout << char(168) << "Dificultad?" << endl;
	cout << "- F" << char(160) << "cil -> pulsa 1" << endl;
	cout << "- Normal -> pulsa 2" << endl;
	cout << "- Dif" << char(161) << "cil -> pulsa 3" << endl << endl;
	char input;
	while(true){
		if(kbhit()){ //Se ha pulsado una tecla
			input = getch(); //Se recoge la tecla pulsada
			//Se comprueba si la tecla es valida                           
			if(input == '1' || input == '2' || input == '3') break;
		}
	}
	switch(input){
		case '1':
			return nivelFacil;
			break;
		case '2':
			return nivelNormal;
			break;
		case '3':
			return nivelDificil;
 	}
}
