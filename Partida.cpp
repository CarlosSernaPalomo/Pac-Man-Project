#include <chrono>

using namespace std;

class Partida{
	
	public:
		
		Cocos cocos;
		Cocos supercocos;
		Comecocos comecocos;
		FantasmaRojo fantasmaRojo;
		FantasmaRosa fantasmaRosa;
		FantasmaNaranja fantasmaNaranja;
		FantasmaCian fantasmaCian;
		
		void Partida(Mapa mapa);
		Mapa LeerMapa(); //Por si se desea consultar el mapa desde fuera del objeto, aunque en principio no es necesario
		bool LeerVictoria(); //Puede que no sea necesario
		void ActualizarVictoria();
		void ActualizarEnCurso();
		void ActualizarHuida();
		void Comer();
		void Jugar();
		
		
	private:
		
		Mapa mapa;
		bool enCurso = true;
		bool victoria = false;
		bool huida = false;
		auto tComienzoHuida = chrono::steady_clock::now();
		auto tComienzoPartida = chrono::steady_clock::now();
		
};

void Partida::Partida(Mapa mapa){
		
		//Almacenamiento del mapa	
		this->mapa = mapa;
		
		//Inicializacion del objeto cocos
		cocos.InicializarMapaDeCocos(mapa.distribCocos);
		cocos.InicializarCocosRestantes(mapa.numCocos);
		
		//Inicializacion del objeto supercocos
		supercocos.InicializarMapaDeCocos(mapa.distribSupercocos);
		supercocos.InicializarCocosRestantes(mapa.numSupercocos);
		
		//Inicializacion del objeto comecocos
		comecocos.InicializarCasillasHabitables(mapa.paredes, mapa.coorPuerta);
		comecocos.InicializarCoor(mapa.coorIniComecocos);
		comecocos.InicializarDir(mapa.dirIniComecocos);
		comecocos.InicializarVidas(mapa.vidasIni);
		
		//Inicializacion del objeto fantasmaRojo
		fantasmaRojo.InicializarCasillasHabitables(mapa.paredes);
		fantasmaRojo.InicializarCoor(mapa.coorIniFantasmaRojo);
		
		//Inicializacion del objeto fantasmaRosa
		fantasmaRosa.InicializarCasillasHabitables(mapa.paredes);
		fantasmaRosa.InicializarCoor(mapa.coorIniFantasmaRosa);
		
		//Inicializacion del objeto fantasmaNaranja
		fantasmaNaranja.InicializarCasillasHabitables(mapa.paredes);
		fantasmaNaranja.InicializarCoor(mapa.coorIniFantasmaNaranja);
		
		//Inicializacion del objeto fantasmaCian
		fantasmaCian.InicializarCasillasHabitables(mapa.paredes);
		fantasmaCian.InicializarCoor(mapa.coorIniFantasmaCian);
		
}

Mapa Partida::LeerMapa(){
	return mapa;
}

bool Partida::LeerVictoria(){
	return victoria;
}

void Partida::ActualizarVictoria(){
	if(cocos.LeerCocosRestantes() + supercocos.LeerCocosRestantes() == 0){
		victoria = true;
	}
}

bool Partida::LeerEnCurso(){
	return enCurso;
}

void Partida::ActualizarEnCurso(){
	if(chrono::steady_clock::now() - tComienzoPartida > LeerMapa().duracionPartida || comecocos.LeerVidas() == 0 || victoria){
		enCurso = false;
	}
}

void Partida::ActualizarHuida(){
	if(chrono::steady_clock::now() - tComienzoHuida > LeerMapa().duracionHuida){
		huida = false;
	}
}

void Partida::Comer(){
	
}

void Partida::Jugar(){
	
	while(enCurso){
		
		//Movimiento del jugador
		comecocos.ActualizarDirDeseada(); //Aqui se espera un tiempo y, si se pulsa una tecla, se actualiza la direccion deseada
		comecocos.Moverse(); //Aqui se comprueba si es posible moverse en la direccion deseada y, si es posible, se hace; si no, se mantiene la direccion actual
		
		/*Movimiento de los fantasmas:
		el metodo Moverse determina primero el objetivo, luego llama al algoritmo A*
		(que determina el camino optimo hasta las coordenadas deseadas y, sabiendo el camino,
		determina a que casilla se tiene que mover el fantasma) y finalmente mueve el fantasma*/
		fantasmaRojo.Moverse(huida, comecocos.LeerCoorActuales); //
		fantasmaRojo.Moverse(huida, comecocos.LeerCoorActuales); //
		fantasmaRojo.Moverse(huida, comecocos.LeerCoorActuales); //
		fantasmaRojo.Moverse(huida, comecocos.LeerCoorActuales); //
		/*Sobre el objetivo de cada fantasma:
			Si no estan huyendo:
				Para el fantasmaRojo el objetivo seran las coordenadas de Pac-Man.
				El fantasmaRosa hay que ver como lo hacemos pero quiza lo mas sencillo seria que sus coordenadas deseadas fueran la casilla que Pac-Man tiene justo en frente, siendo Pac-Man para este fantasma una casilla no habitable.
				Respecto al fantasmaNaranja, si Pac-Man esta cerca (a menos de diez casillas en distancia de Manhattan) el objetivo seran las coordenadas de Pac-Man; si no, se mueve en una direccion aleatoria hasta toparse con un muro y asi sucesivamente.
				El fantasmaCian utilizara aleatoriamente una de las tres estrategias anteriores.
			Si estan huyendo, el objetivo de todos ellos es entrar en el refugio.*/
		
		//Se comprueba si alguien se ha comido algo y se ejecutan las acciones correspondientes
		Comer();
		
		//Se comprueba la condicion de victoria
		ActualizarVictoria();
		
		//Se comprueban las condiciones de finalizacion de la partida
		ActualizarEnCurso();
		
		//Actualizar interfaz grafica
		//LoQueSea();
		
	} //Fin del bucle
	
	if(victoria){
		//HacemosAlgo();
	}else{
		//HacemosOtraCosa();
	}
	
}

