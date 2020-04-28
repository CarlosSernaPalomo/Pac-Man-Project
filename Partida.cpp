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

bool Partida::Jugar(){
	
	while(enCurso){
		
		
		
	}
	
	if(victoria){
		lo que sea;
	}else{
		lo que sea;
	}
	
}



