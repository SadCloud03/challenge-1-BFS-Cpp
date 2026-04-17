 //challenge 1 de the huddle, realizar un generador de laberintos aleatorios los cuales sean totalmente resolubles y se autocompleten
 
 //modulos:
 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 #include "funciones.h"
 
 using namespace std;


 
int main(){	
	
	//declaracion de variables que necesito
	char desicion;
	int **laberinto;
	int filas, columnas, fila_entrada = 1, columna_entrada = 1, fila_salida, columna_salida;
	bool **visitados;
	
	
	//preguntar al usuario si quiere personalizar el tamano del laberinto:
	cout<<"Generador de laverintos" << "\n\n" << "Desea personalizar el tamano del laberinto?:(s/n) ";
	cin>>desicion;
	if (desicion == 's') {
		system("CLS");
		cout<<"\n\nCuantas filas quieres que tenga el laberinto?: ";
		cin>>filas;	
		cout<<"\n\nCuantas columnas quieres que tenga el laberinto?: ";
		cin>>columnas;
	} else {
		filas = 11;
		columnas = 11;
	};
	
	
	//asignar la salida con los valores recibidos:
	fila_salida = filas - 2;
	columna_salida = columnas - 2;
	
	
	//Generar nueva semilla para los laberintos:
	srand(time(NULL));
	
	//Reservar la memoria para el laverinto y generarlo con solamente paredes
	laberinto = new int*[filas];
	for (int i=0; i<filas; i++) {
		laberinto[i] = new int[columnas];
		for (int j=0; j<columnas; j++) {
			laberinto[i][j] = 10;
		}
	};
	
 	//Reservar la memoria para almacenar las casillas ya visitadas
 	visitados = new bool*[filas];
 	for (int i=0; i<filas; i++){
 		visitados[i] = new bool[columnas];
 		for (int j=0; j<columnas; j++){
 			visitados[i][j] = false;
		 }
	};
	
	
	
	//Generar los caminos y obstaculos extras en el laberinto:
	abrir_camino(laberinto, visitados, fila_entrada, columna_entrada, filas, columnas, fila_salida, columna_salida);
	agregar_optimizar_obstaculos(laberinto, filas, columnas);
	
	//mostrar el laberinto:
	mostrar_laberinto(laberinto, filas, columnas);
	
	//resolver laberinto:
	Resolver_laberinto_Astar(laberinto, fila_entrada, columna_entrada, fila_salida, columna_salida, filas, columnas);
	
	
	
	//liberar espacio en la memoria:
	for (int i=0; i<filas; i++) {
		delete[] laberinto[i];		
	}
	delete[] laberinto;

	return 0;
}

