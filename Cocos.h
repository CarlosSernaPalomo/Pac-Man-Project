class Cocos{
	public:
		void InicializarCocos(Mapa, int);
		Mapa LeerMapaDeCocos(Coordenadas);
		int LeerCocosRestantes();
		void EliminarCoco(Coordenadas);
	private:
		Mapa mapaDeCocos;
		int cocosRestantes;
}

void Cocos::InicializarCocos(Mapa mapa, int n){
	
	for(int r = 0; r < mapa.h; r++){
		for(int s = 0; s < m.w; s++){
			if(mapa.m[s][r] == 2) mapaDeCocos.m[s][r] = 1;
		}
	}
	
	cocosRestantes = n;
	
}
