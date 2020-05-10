//Librerias
#include "librerias.h"

using namespace std;

void Bienvenida(){
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //Para impresion en color
	SetConsoleTextAttribute(color, 14); //Amarillo
	cout << "                                                      .         .                                                  " << endl;
	cout << "8 888888888o      .8.           ,o888888o.           ,8.       ,8.                   .8.          b.             8 " << endl;
	cout << "8 8888    `88.   .888.         8888     `88.        ,888.     ,888.                 .888.         888o.          8 " << endl;
	cout << "8 8888     `88  :88888.     ,8 8888       `8.      .`8888.   .`8888.               :88888.        Y88888o.       8 " << endl;
	cout << "8 8888     ,88 . `88888.    88 8888               ,8.`8888. ,8.`8888.             . `88888.       .`Y888888o.    8 " << endl;
	cout << "8 8888.   ,88'.8. `88888.   88 8888              ,8'8.`8888,8^8.`8888.           .8. `88888.      8o. `Y888888o. 8 " << endl;
	cout << "8 888888888P'.8`8. `88888.  88 8888             ,8' `8.`8888' `8.`8888.         .8`8. `88888.     8`Y8o. `Y88888o8 " << endl;
	cout << "8 8888      .8' `8. `88888. 88 8888            ,8'   `8.`88'   `8.`8888.       .8' `8. `88888.    8   `Y8o. `Y8888 " << endl;
	cout << "8 8888     .8'   `8. `88888.`8 8888       .8' ,8'     `8.`'     `8.`8888.     .8'   `8. `88888.   8      `Y8o. `Y8 " << endl;
	cout << "8 8888    .888888888. `88888.  8888     ,88' ,8'       `8        `8.`8888.   .888888888. `88888.  8         `Y8o.` " << endl;
	cout << "8 8888   .8'       `8. `88888.  `8888888P'  ,8'         `         `8.`8888. .8'       `8. `88888. 8            `Yo " << endl;
	SetConsoleTextAttribute(color, 15); //Blanco
	cout << endl << "PULSA CUALQUIER TECLA PARA JUGAR" << endl << endl;
	while(!kbhit());
}
