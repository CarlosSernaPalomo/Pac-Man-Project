#include <ctime>

class Partida{
	public:
		
		Cocos cocos;
		Supercocos supercocos;
		Comecocos comecocos;
		FantasmaRojo fantasmaRojo;
		FantasmaRosa fantasmaRosa;
		FantasmaCian fantasmaCian;
		FantasmaNaranja fantasmaNaranja;
		
		void Partida(Mapa mapa);
		void ~Partida();
		Mapa LeerMapa(); //Este metodo en principio creo que no va a hacer falta (como tampoco va a hacer falta incorporar el objeto mapa al objeto partida, ya que se usa al construir la partida y nunca mas, pero creo que no esta de mas que la partida contenga el mapa)
		bool LeerEnCurso();
		void ActualizarEnCurso();
		bool LeerVictoria();
		void ActualizarVictoria();
		bool LeerHuida();
		void ActivarHuida();
		void Desactivar Huida();
		void Jugar();
		
	private:
		Mapa mapa;
		bool enCurso;
		bool victoria;
		bool huida;
		time_t cronoHuida;
};

void Partida::Partida(Mapa mapa){
		this->mapa = mapa;
		cocos 
}
