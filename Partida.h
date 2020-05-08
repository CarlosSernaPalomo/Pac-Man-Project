#ifndef PARTIDA_H
#define PARTIDA_H

//Librerias
#include "librerias.h"

//Archivos de cabecera
#include "Nivel.h"
#include "Comecocos.h"
#include "FantasmaRojo.h"
#include "FantasmaRosa.h"
#include "FantasmaNaranja.h"
#include "FantasmaCian.h"

using namespace std;

class Partida{
	public:
		Partida(Nivel nivel);
		void ActualizarVictoria();
		void ActualizarEnCurso();
		void ActualizarHuida();
		void Comer();
		void Imprimir();
		void Jugar();
	private:
		Mapa mapa;
		Comecocos comecocos;
		FantasmaRojo fantasmaRojo;
		FantasmaRosa fantasmaRosa;
		FantasmaNaranja fantasmaNaranja;
		FantasmaCian fantasmaCian;
		int cocosRestantes = 0;
		bool enCurso = true;
		bool victoria = false;
		bool huida = false;
		chrono::steady_clock::time_point tComienzoHuida = chrono::steady_clock::now();
		chrono::steady_clock::time_point tComienzoPartida = chrono::steady_clock::now();
		int duracionPartida;
		int duracionHuida;
};

Partida::Partida(Nivel nivel){
	
	mapa = nivel.mapa;
	
	duracionPartida = nivel.duracionPartida;
	
	duracionHuida = nivel.duracionHuida;
	
	//cocosRestantes
	for(int r = 0; r < mapa.h; r++) for(int s = 0; s < mapa.w; s++)
		if(mapa.m[s][r] == 2 || mapa.m[s][r] == 3) cocosRestantes++;
	
	//comecocos
	comecocos.InicializarCasillasHabitables(nivel.mapa);
	comecocos.InicializarCoor(nivel.coorIniComecocos);
	comecocos.InicializarDir(nivel.dirIniComecocos);
	comecocos.InicializarVidas(nivel.vidasIni);
	comecocos.InicializarPeriodo(nivel.periodo);
	
	//fantasmaRojo
	fantasmaRojo.InicializarCasillasHabitables(nivel.mapa);
	fantasmaRojo.InicializarCoor(nivel.coorIniFantasmaRojo);
	
	//fantasmaRosa
	fantasmaRosa.InicializarCasillasHabitables(nivel.mapa);
	fantasmaRosa.InicializarCoor(nivel.coorIniFantasmaRosa);
	
	//fantasmaNaranja
	fantasmaNaranja.InicializarCasillasHabitables(nivel.mapa);
	fantasmaNaranja.InicializarCoor(nivel.coorIniFantasmaNaranja);
	
	//fantasmaCian
	fantasmaCian.InicializarCasillasHabitables(nivel.mapa);
	fantasmaCian.InicializarCoor(nivel.coorIniFantasmaCian);
	
}

void Partida::ActualizarVictoria(){
	if(cocosRestantes == 0){
		victoria = true;
	}
}

void Partida::ActualizarEnCurso(){
	if(chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - tComienzoPartida).count() > duracionPartida
	|| comecocos.LeerVidas() == 0
	|| victoria)
	{
		enCurso = false;
	}
}

void Partida::ActualizarHuida(){
	if(chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - tComienzoHuida).count() > duracionHuida){
		huida = false;
	}
}

void Partida::Comer(){
	
	//Se comprueba si el comecocos se ha comido un coco
	if(mapa(comecocos.LeerCoorActuales()) == 2){
		mapa.Modificar(comecocos.LeerCoorActuales(), 0);
		cocosRestantes--;
	}
	
	//Se comprueba si el comecocos se ha comido un supercoco
	else if(mapa(comecocos.LeerCoorActuales()) == 3){
		mapa.Modificar(comecocos.LeerCoorActuales(), 0);
		cocosRestantes--;
		//Si se ha comido un supercoco, ademas de eliminarlo hay que activar la huida
		huida = true;
		tComienzoHuida = chrono::steady_clock::now();
	}
	
	//Si los fantasmas estan huyendo, el comecocos se los puede comer
	if(huida){
		if(comecocos.LeerCoorActuales() == fantasmaRojo.LeerCoorActuales()){
			fantasmaRojo.MoverACoorIni();
		}else if(comecocos.LeerCoorActuales() == fantasmaRosa.LeerCoorActuales()){
			fantasmaRosa.MoverACoorIni();
		}else if(comecocos.LeerCoorActuales() == fantasmaNaranja.LeerCoorActuales()){
			fantasmaNaranja.MoverACoorIni();
		}else if(comecocos.LeerCoorActuales() == fantasmaCian.LeerCoorActuales()){
			fantasmaCian.MoverACoorIni();
		}
		
	//Si los fantasmas no estan huyendo, se pueden comer al comecocos
	}else{
		if(comecocos.LeerCoorActuales() == fantasmaRojo.LeerCoorActuales()
		|| comecocos.LeerCoorActuales() == fantasmaRosa.LeerCoorActuales()
		|| comecocos.LeerCoorActuales() == fantasmaNaranja.LeerCoorActuales()
		|| comecocos.LeerCoorActuales() == fantasmaCian.LeerCoorActuales())
		{
			comecocos.QuitarVida();
			comecocos.MoverACoorIni();
			comecocos.ResetearDir();
		}
	}
	
}

void Partida::Imprimir(){
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //Para impresion en color
	SetConsoleTextAttribute(color, 15);
	cout << "VIDAS: " << comecocos.LeerVidas() << "        " << "PUNTOS: " << endl;
	cout << "Tiempo restante: " << duracionPartida - chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - tComienzoPartida).count();
	cout << endl << endl;
	Coordenadas c;
	for(int y = 0; y < mapa.h; y++) {
		for(int x = 0; x < mapa.w; x++){
			c.x = x; c.y = y;
			if(c == comecocos.LeerCoorActuales()){ //comecocos
				SetConsoleTextAttribute(color, 14);
				cout << "C";
			}else if(c == fantasmaRojo.LeerCoorActuales()){ //fantasmaRojo
				if(huida){
					SetConsoleTextAttribute(color, 9);
					cout << "M";
				}else{
					SetConsoleTextAttribute(color, 12);
					cout << "M";
				}
			}else if(c == fantasmaRosa.LeerCoorActuales()){ //fantasmaRosa
				if(huida){
					SetConsoleTextAttribute(color, 9);
					cout << "M";
				}else{
					SetConsoleTextAttribute(color, 13);
					cout << "M";
				}
			}else if(c == fantasmaNaranja.LeerCoorActuales()){ //fantasmaNaranja
				if(huida){
					SetConsoleTextAttribute(color, 9);
					cout << "M";
				}else{
					SetConsoleTextAttribute(color, 6);
					cout << "M";
				}
			}else if(c == fantasmaCian.LeerCoorActuales()){ //fantasmaCian
				if(huida){
					SetConsoleTextAttribute(color, 9);
					cout << "M";
				}else{
					SetConsoleTextAttribute(color, 11);
					cout << "M";
				}
			}else if(mapa(c) == 0){ //Pasillo
				SetConsoleTextAttribute(color, 0);
				cout << " ";
			}else if(mapa(c) == 1){ //Pared
				SetConsoleTextAttribute(color, 9);
				cout << char(0xdb);
			}else if(mapa(c) == 2){ //Coco
				SetConsoleTextAttribute(color, 14);
				cout << char(250);
			}else if(mapa(c) == 3){ //Supercoco
				SetConsoleTextAttribute(color, 14);
				cout << "O";
			}else if(mapa(c) == 4){ //Puerta del refugio
				SetConsoleTextAttribute(color, 9);
				cout << char(176);
			}
		}
		cout << endl;	
	}
	cout << endl << endl;
	SetConsoleTextAttribute(color, 15);
}

void Partida::Jugar(){
	
	cout << char(173) << "Comienza la partida!" << endl << endl;
	
	while(enCurso){
		
		//Movimiento del jugador
		comecocos.ActualizarDirDeseada(); //Aqui se espera un tiempo y, si se pulsa una tecla, se actualiza la direccion deseada
		comecocos.Moverse(); //Aqui se comprueba si es posible moverse en la direccion deseada y, si es posible, se hace; si no, se mantiene la direccion actual
		
		/*Movimiento de los fantasmas:
		El metodo Moverse determina primero el objetivo, luego llama a un metodo SiguientePosicion
		(que determina, utilizando A*, el camino optimo hasta el objetivo y, sabiendo el camino,
		determina a que casilla se tiene que mover el fantasma) y finalmente mueve el fantasma*/
		fantasmaRojo.Moverse(huida, comecocos.LeerCoorActuales(), comecocos.LeerDirActual());
		fantasmaRosa.Moverse(huida, comecocos.LeerCoorActuales(), comecocos.LeerDirActual());
		fantasmaNaranja.Moverse(huida, comecocos.LeerCoorActuales(), comecocos.LeerDirActual());
		fantasmaCian.Moverse(huida, comecocos.LeerCoorActuales(), comecocos.LeerDirActual());
		/*Objetivo de cada fantasma:
			Si estan huyendo, el objetivo de todos ellos es entrar en el refugio.
			Si no estan huyendo:
				- Para el fantasmaRojo, el objetivo son las coordenadas de Pac-Man.
				- Para el fantasmaRosa, el objetivo es la casilla justo detras de Pac-Man.
				- Respecto al fantasmaNaranja, si Pac-Man esta cerca (a menos de diez casillas en distancia de Manhattan) el objetivo seran
				  las coordenadas de Pac-Man; si no, se mueve aleatoriamente.
				- El fantasmaCian utilizara aleatoriamente una de las tres estrategias anteriores.*/
		
		//Se comprueba si algun ente se ha comido algo y se ejecutan las acciones correspondientes
		Comer();
		
		//Se comprueba la condicion de victoria
		ActualizarVictoria();
		
		//Se comprueban las condiciones de finalizacion de la partida
		ActualizarEnCurso();
		
		//Se comprueba si ha finalizado la huida en caso de que este activada
		ActualizarHuida();
		
		//Se actualiza la interfaz grafica
		Imprimir();
		
	} //Fin del bucle
	
	if(victoria){
		cout << char(173) << "HAS GANADO!" << endl;
		//Se calcula la puntuacion obtenida y se muestra
	}else{
		cout << char(173) << "HAS PERDIDO!" << endl;
		if(comecocos.LeerVidas() == 0) cout << "Te quedaste sin vidas." << endl;
		else cout << "Te quedaste sin tiempo." << endl;
	}
	cout << endl << char(173) << "Gracias por jugar!" << endl;
	
}

#endif
