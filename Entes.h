#ifndef ENTES_H
#define ENTES_H

class Fantasma{
	public:
	Coordenadas Iniciales,Actuales;
	Fantasma();	
};

class Jugador{
	public:
	Coordenadas Iniciales,Actuales;
	Jugador();	
	void MoverArriba();
	void MoverIzquierda();
	void MoverAbajo();
	void MoverDerecha();
};

Fantasma::Fantasma(){
		Iniciales.x=14;
		Iniciales.y=14;
		Actuales.x=14;
		Actuales.y=14;
};

Jugador::Jugador(){
		Iniciales.x=14;
		Iniciales.y=17;
		Actuales.x=14;
		Actuales.y=17;
};

void Jugador::MoverArriba(){
	Actuales.y=Actuales.y-1;
};

void Jugador::MoverIzquierda(){
	Actuales.x=Actuales.x-1;
}

void Jugador::MoverAbajo(){
	Actuales.y=Actuales.y+1;
}

void Jugador::MoverDerecha(){
	Actuales.x=Actuales.x+1;
}


#endif
