class Cocos{
	public:
		void InicializarMapaDeCocos(Mapa);
		void InicializarCocosRestantes(int);
		Mapa LeerMapaDeCocos(Coordenadas);
		int LeerCocosRestantes();
		void EliminarCoco(Coordenadas);
	private:
		Mapa mapaDeCocos;
		int cocosRestantes;
}

void Cocos::InicializarMapaDeCocos(Mapa mapa){
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < m.w; s++){
			if(mapa.m[s][r] == 2 || mapa.m[s][r] == 3) mapaDeCocos.m[s][r] = mapa.m[s][r];
		}
	}
}

void Cocos::InicializarCocosRestantes(int n){
	cocosRestantes = n;
}

int Cocos::LeerMapaDeCocos(Coordenadas c){
	return mapaDeCocos(c);
}

int Cocos::LeerCocosRestantes(){
	return cocosRestantes;
}

void Cocos::EliminarCoco(Coordenadas c){
	if(mapaDeCocos(c) != 0){
		mapaDeCocos.m[c.x][x.y] = 0;
		cocosRestantes--;
	}
}
