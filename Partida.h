#ifndef PARTIDA_H
#define PARTIDA_H

#include "Entes.h"

class Partida{
	public:
	Mapa Mapafantasmas;
	MapaJugador MapaJugador;
	int vidas,cocos,supercocos,turnos,puntos;
	bool huida,continuar;
	Fantasma Rojo;
	Jugador Jugador;
	
	Partida();
	void ActualizaTurno();
	void Mover();
	void VisualizaMapa ();
	void ComerCoco();
	void ComerSupercoco();
	void SiguientePosicion(Fantasma&);
	void Estado1();
	void Estado2();
};

Partida::Partida(){
		Mapafantasmas;
		MapaJugador;
		vidas=3;
		cocos=242;
		supercocos=4;
		turnos=999;	
		puntos=0;
		huida=false;
		continuar=true;
		Rojo;
		Jugador;		
}

void Partida::ActualizaTurno(){
	turnos--;
	if (turnos==0||cocos==0||vidas==0) continuar=false;
}

void Partida::Mover(){
	char input;
	bool flag;
	flag=false;
	while(flag==false){//Este chequeo no es necesario si al final hay botones en la interfaz de usuario
		cout<<"Direccion WASD: ";
		cin>>input;
		//cout<<"\nDireccion "<<input<< " es ";
		if(input=='w' or input=='a' or input=='s' or input=='d' or input=='W' or input=='A' or input=='S' or input=='D'){
			//cout<<"valida\n";
			flag=true;
		}
		else
		{
		//cout<<"no valida, vuelva a intentarlo\n";
		}
	}
		
	if (input=='w'){
		Jugador.MoverArriba();	
		if (MapaJugador(Jugador.Actuales)==1){
			Jugador.MoverAbajo();
			Mover();
			} 
	}
	
	if (input=='a'){
		Jugador.MoverIzquierda();
		cout<<Jugador.Actuales.x<<endl;
		if (MapaJugador(Jugador.Actuales)==1){
			Jugador.MoverDerecha();
			Mover();
			} 
	}
	
	if (input=='s'){
		Jugador.MoverAbajo();
		if (MapaJugador(Jugador.Actuales)==1||MapaJugador(Jugador.Actuales)==4){
			Jugador.MoverArriba();
			Mover();
			} 
	}
	
	if (input=='d'){
		Jugador.MoverDerecha();
		if (MapaJugador(Jugador.Actuales)==1){
			Jugador.MoverIzquierda();
			Mover();
			} 
	}
}

void Partida::VisualizaMapa (){
	Coordenadas poscionActual;
	for( int y = 0; y < 31; y++ ) {
        for( int x = 0; x < 28; x++ ) {
			poscionActual.x=x;poscionActual.y=y;
			if(Jugador.Actuales.x==x&&Jugador.Actuales.y==y)	//Jugador
				cout << "C";
			else if(Rojo.Actuales.x==x&&Rojo.Actuales.y==y)	//Fantasma
				cout << "F";	
            else if(MapaJugador(poscionActual) == 0)	//Pasillo
                cout << " ";
            else if(MapaJugador(poscionActual) == 1)	//Pared
                cout << char(0xdb);
            else if(MapaJugador(poscionActual) == 2)	//Coco
                cout << ".";
			else if(MapaJugador(poscionActual) == 3)	//Supercoco
				cout << "X";
			else if(MapaJugador(poscionActual) == 4)	//Puerta
				cout << "-";
    	}
		cout << "\n";	
	}
}

void Partida::ComerCoco(){
	cocos--;
	puntos=puntos+100;
	MapaJugador.PonerPasillo(Jugador.Actuales);
}

void Partida::ComerSupercoco(){
	supercocos--;
	puntos=puntos+1000;
	huida=true;
	MapaJugador.PonerPasillo(Jugador.Actuales);
}

void Partida::SiguientePosicion (Fantasma& f){
	aStar as;
	Coordenadas s,e;
	s=f.Actuales;
	Mapa m=Mapafantasmas;
	if (huida==true){
		e=f.Iniciales;
		m.PonerPasillo(Jugador.Actuales);
	}
	else e=Jugador.Actuales;
		
	Coordenadas pos0,pos1,pos2,test;
	int k=0;
	if( as.search( s, e, m ) ) {
        list<Coordenadas> path;
        int c = as.path( path );        
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
    if (pos1==pos0) f.Actuales=pos2;
	else f.Actuales=pos1;
};	

void Partida::Estado1(){//Antes movimiento fantasmas
	if (MapaJugador(Jugador.Actuales)==2) ComerCoco();
	if (MapaJugador(Jugador.Actuales)==3) ComerSupercoco();
	if (Jugador.Actuales==Rojo.Actuales){
		Rojo.Actuales=Rojo.Iniciales;
		Jugador.Actuales=Jugador.Iniciales;
		vidas--;
	}
}

void Partida::Estado2(){//Despues movimiento fantasmas
	if (Rojo.Actuales==Jugador.Actuales){
		Rojo.Actuales=Rojo.Iniciales;
		Jugador.Actuales=Jugador.Iniciales;
		vidas--;
	}
}

#endif
