class Mapa{//Para que compile
	int i;
};

class Ente{
	protected://Las hago protected
		bool* casillasHabitables;//Se podría hacer de int para no complicarse o justificar el bool con que pesa 8 bits frente a los 32 del int
		const pair<int,int> coorIni;
		pair<int,int> coorActuales;
	public:
			void Moverse();
			void MoverACoorIni();
			pair<int,int> LeerCoorActuales();	
};

class Comecocos:public Ente{
	protected:
		char dirActual;
		char dirDeseada;
		int vidas;//Se podría utilizar short int y en vez de 32 bits se utilizarían 16
	public:
		void InicializarComecocos(Mapa mapa);
		int LeerVidas();
		void QuitarVida();
		void ActualizarDirDeseada();
		void ComerCoco();
		void ComerSupercoco();
		void ComerFantasma();
		void Comer();
};

class Fantasma:public Ente{
	protected:
		pair<int,int> coorDeseadas;
	public:
		pair<int,int> LeerCoorDeseadas();
		void Comer();
		void Perseguir();
		void CortarElPaso();
		void Deambular();
		void Huir();
		void AEstrella();
		void EditarCasillasHabitalbes(bool input);//No se que se pretende pasar como argumento
};

class FantasmaRojo:public Fantasma{
	public:
		void InicializarFantasmaRojo(Mapa mapa);
		void ActualizarCoorDeseadas();
};

class FantasmaRosa:public Fantasma{
	public:
		void InicializarFantasmaRosa(Mapa mapa);
		void ActualizarCoorDeseadas();
};

class FantasmaNaranja:public Fantasma{
	public:
		void InicializarFantasmaNaranja(Mapa mapa);
		void ActualizarCoorDeseadas();
};

class FantasmaCian:public Fantasma{
	public:
		void InicializarFantasmaCian(Mapa mapa);
		void ActualizarCoorDeseadas();
};

//Metodos de Ente
pair<int,int> Ente::LeerCoorActuales(){
	return coorActuales;
}

//Métodos de Comecocos
int Comecocos::LeerVidas(){
	return vidas;
}

void Comecocos::QuitarVida(){
	vidas=vidas-1;
	return;
}

void Comecocos::ActualizarDirDeseada(){
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
}

//Métodos de Fantasma
pair<int,int> Fantasma::LeerCoorDeseadas(){
	return coorDeseadas;
}

//Métodos de FantasmaRojo
//Métodos de FantasmaRosa
//Métodos de FantasmaNaranja
//Métodos de FantasmaCian

