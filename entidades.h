//CARLOS: Estas librerias son para el metodo ActualizarDirDeseada que propongo
#include <conio.h>
#include <chrono>
using namespace std;

class Mapa{//Para que compile
	int i;
};

class Ente{
	protected://Las hago protected
		bool** casillasHabitables;//Se podría hacer de int para no complicarse o justificar el bool con que pesa 8 bits frente a los 32 del int. CARLOS: Creo que es una buena justificacion.
		const pair<int,int> coorIni;
		pair<int,int> coorActuales;
	public:
			void InicializarCoor(pair<int,int> coorIni);
			void MoverACoorIni();
			pair<int,int> LeerCoorActuales();	
};

class Comecocos:public Ente{
	protected: //CARLOS: Yo lo pondria como private ya que ninguna clase va a heredar de esta
		char dirActual;
		char dirDeseada;
		int vidas;//Se podría utilizar short int y en vez de 32 bits se utilizarían 16. CARLOS: Por mi vale.
	public:
		void InicializarCasillasHabitables(bool** paredes, pair<int,int> coorPuerta);
		void InicializarDir(char dirIniComecocos);
		void InicializarVidas(int vidasIni);
		int LeerVidas();
		void PerderVida();
		void ActualizarDirDeseada();
		void Moverse();
};

class Fantasma:public Ente{
	public:
		void InicializarCasillasHabitables(bool** paredes);
		void ActualizarCasillasHabitables(pair<int,int> coorActualesComecocos);
		void Moverse(bool huida, pair<int,int> coorActualesComecocos);
		void Perseguir(pair<int,int> coorActualesComecocos);
		void CortarElPaso(pair<int,int> coorActualesComecocos);
		void Deambular();
		void Huir();
		void AEstrella();
}

class FantasmaRojo:public Fantasma{
	public:
		void Moverse(bool huida, pair<int,int> coorActualesComecocos);
};

class FantasmaRosa:public Fantasma{
	public:
		void Moverse(bool huida, pair<int,int> coorActualesComecocos);
};

class FantasmaNaranja:public Fantasma{
	public:
		void Moverse(bool huida, pair<int,int> coorActualesComecocos);
};

class FantasmaCian:public Fantasma{
	public:
		void Moverse(bool huida, pair<int,int> coorActualesComecocos);
};

//Metodos de Ente
void Ente::InicializarCoor(pair<int,int> coorIni){
	this->coorIni=coorIni;
}

void Ente::MoverACoorIni(){
	coorActuales=coorIni;
}

pair<int,int> Ente::LeerCoorActuales(){
	return coorActuales;
}

//Métodos de Comecocos
void Comecocos::InicializarCasillasHabitables(bool** paredes, pair<int,int> coorPuerta){
	casillasHabitables = !paredes; //CARLOS: He supuesto que en la variable paredes los 1s van a ser las paredes y que en la variable casillasHabitables los 1s van a ser las casillas habitables, aunque no tiene por que ser asi	
	castillasHabitables(coorPuerta) = 0; //CARLOS: No se ahora mismo cual es la manera correcta de acceder a los elementos de casillasHabitables
}

void Comecocos::InicializarVidas(int vidasIni){
	
}

int Comecocos::LeerVidas(){
	return vidas;
}

void Comecocos::PerderVida(){
	vidas=vidas-1;
	return;
}

/*void Comecocos::ActualizarDirDeseada(){
	char input;
	bool flag;
	flag=false;
	while(flag==false){//Este chequeo no es necesario si al final hay botones en la interfaz de usuario
		cout<<"Direccion WASD: ";
		cin>>input;
		cout<<"\nDireccion "<<input<< " es ";
		if(input=='w' or input=='a' or input=='s' or input=='d' or input=='W' or input=='A' or input=='S' or input=='D'){
			cout<<"valida\n";
			dirDeseada=input;
			flag=true;
		}
		else
		{
		cout<<"no valida, vuelva a intentarlo\n";
		}
	}
}*/

//CARLOS: Propongo el siguiente metodo para leer el teclado. Creo que es mas realista ya que es "en tiempo real", no hay que esperar a que se pulse una tecla ni a que esta sea valida
void Comecocos::ActualizarDirDeseada(){
	auto start = chrono::steady_clock::now();
	while(chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < 1){
		if(kbhit()){ //Se ha pulsado una tecla
			char input = getch(); //Se recoge la tecla pulsada
			if(input == 'w' || input == 'a' || input == 's' || input == 'd' || input == 'W' || input == 'A' || input == 'S' || input == 'D'){ //Se comprueba si es valida
				dirDeseada = input;
			}
		}
	}
}

//Métodos de Fantasma
void Fantasma::InicializarCasillasHabitables(bool** paredes){
	casillasHabitables = !paredes;
}

//CARLOS: El siguiente metodo se utiliza para hacer la casilla donde esta Pac-Man no habitable o habitable segun corresponda
void Fantasma::ActualizarCasillasHabitables(pair<int,int> coorActualesComecocos, bool valor){
	casillasHabitables(coorActualesComecocos) = valor; //CARLOS: De nuevo, no se cual es la forma correcta de acceder a los elementos de casillasHabitables
}

//CARLOS: Faltan Perseguir, CortarElPaso, Deambular, Huir, AEstrella

//Métodos de FantasmaRojo
//Métodos de FantasmaRosa
//Métodos de FantasmaNaranja
//Métodos de FantasmaCian

