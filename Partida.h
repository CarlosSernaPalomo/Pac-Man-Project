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
		
		void Partida(Nivel nivel);
		Nivel LeerNivel(); //Por si se desea consultar el nivel desde fuera del objeto, aunque en principio no es necesario
		bool LeerVictoria(); //Puede que no sea necesario
		void ActualizarVictoria();
		void ActualizarEnCurso();
		void ActualizarHuida();
		void Comer();
		void Jugar();
		
		
	private:
		
		Nivel nivel;
		bool enCurso = true;
		bool victoria = false;
		bool huida = false;
		auto tComienzoHuida = chrono::steady_clock::now();
		auto tComienzoPartida = chrono::steady_clock::now();
		
};

void Partida::Partida(Nivel nivel){
		
		//Almacenamiento del nivel	
		this->nivel = nivel;
		
		//Inicializacion del objeto cocos
		cocos.InicializarNivelDeCocos(nivel.distribCocos);
		cocos.InicializarCocosRestantes(nivel.numCocos);
		
		//Inicializacion del objeto supercocos
		supercocos.InicializarNivelDeCocos(nivel.distribSupercocos);
		supercocos.InicializarCocosRestantes(nivel.numSupercocos);
		
		//Inicializacion del objeto comecocos
		comecocos.InicializarCasillasHabitables(nivel.paredes, nivel.coorPuerta);
		comecocos.InicializarCoor(nivel.coorIniComecocos);
		comecocos.InicializarDir(nivel.dirIniComecocos);
		comecocos.InicializarVidas(nivel.vidasIni);
		
		//Inicializacion del objeto fantasmaRojo
		fantasmaRojo.InicializarCasillasHabitables(nivel.paredes);
		fantasmaRojo.InicializarCoor(nivel.coorIniFantasmaRojo);
		
		//Inicializacion del objeto fantasmaRosa
		fantasmaRosa.InicializarCasillasHabitables(nivel.paredes);
		fantasmaRosa.InicializarCoor(nivel.coorIniFantasmaRosa);
		
		//Inicializacion del objeto fantasmaNaranja
		fantasmaNaranja.InicializarCasillasHabitables(nivel.paredes);
		fantasmaNaranja.InicializarCoor(nivel.coorIniFantasmaNaranja);
		
		//Inicializacion del objeto fantasmaCian
		fantasmaCian.InicializarCasillasHabitables(nivel.paredes);
		fantasmaCian.InicializarCoor(nivel.coorIniFantasmaCian);
		
}

Nivel Partida::LeerNivel(){
	return nivel;
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
	if(chrono::steady_clock::now() - tComienzoPartida > LeerNivel().duracionPartida
	|| comecocos.LeerVidas() == 0
	|| victoria)
	{
		enCurso = false;
	}
}

void Partida::ActualizarHuida(){
	if(chrono::steady_clock::now() - tComienzoHuida > LeerNivel().duracionHuida){
		huida = false;
	}
}

void Partida::Comer(){
	
	//Se comprueba si el comecocos se ha comido un coco
	if(cocos.LeerMapaDeCocos(comecocos.LeerCoorActuales){
		//El metodo EliminarCoco sobrescribe con false la casilla correspondiente del mapaDeCocos y decrementa en uno los cocosRestantes
		cocos.EliminarCoco(comecocos.LeerCoorActuales);
	}
	
	//Se comprueba si el comecocos se ha comido un supercoco
	if(supercocos.LeerMapaDeCocos(comecocos.LeerCoorActuales){
		supercocos.EliminarCoco(comecocos.LeerCoorActuales);
		//Si se ha comido un supercoco, ademas de llamar a EliminarCoco hay que activar la huida
		huida = true;
		tComienzoHuida = chrono::steady_clock::now();
	}
	
	//Si los fantasmas estan huyendo, el comecocos se los puede comer
	if(huyendo){
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
			comecocos.MoverACoorIni();
			comecocos.PerderVida();
		}
	
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
				- Para el fantasmaRojo el objetivo seran las coordenadas de Pac-Man.
				- El fantasmaRosa hay que ver como lo hacemos pero quiza lo mas sencillo seria que sus coordenadas deseadas fueran
				  la casilla que Pac-Man tiene justo en frente, siendo Pac-Man para este fantasma una casilla no habitable.
				- Respecto al fantasmaNaranja, si Pac-Man esta cerca (a menos de diez casillas en distancia de Manhattan) el objetivo seran
				  las coordenadas de Pac-Man; si no, se mueve en una direccion aleatoria hasta toparse con un muro y asi sucesivamente.
				- El fantasmaCian utilizara aleatoriamente una de las tres estrategias anteriores.
			Si estan huyendo, el objetivo de todos ellos es entrar en el refugio.*/
		
		//Se comprueba si alguien se ha comido algo y se ejecutan las acciones correspondientes
		Comer();
		
		//Se comprueba la condicion de victoria
		ActualizarVictoria();
		
		//Se comprueban las condiciones de finalizacion de la partida
		ActualizarEnCurso();
		
		//Se comprueba si ha finalizado la huida en caso de que este activada
		ActualizarHuida();
		
		//Actualizar interfaz grafica
		//LoQueSea();
		
	} //Fin del bucle
	
	if(victoria){
		//HacemosAlgo();
	}else{
		//HacemosOtraCosa();
	}
	
}

