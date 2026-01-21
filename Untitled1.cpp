 //challenge 1 de the huddle, realizar un generador de laberintos aleatorios los cuales sean totalmente resolubles y se autocompleten
 
 //modulos:
 #include <iostream>
 #include <cstdlib>
 #include <stdlib.h>
 #include <ctime>
 #include <cmath>
 #include <vector>
 #include <queue>
 
 using namespace std;


 //funcion para mostrar laberinto:
void mostrar_laberinto(int** laberinto, int filas, int columnas) {
	cout<<"\n\n";
	for (int i=0; i<filas; i++) {
		for (int j=0; j<columnas; j++) {
			//cout<<laberinto[i][j]<<" ";	
			if (laberinto[i][j] == 10) {
				cout<<"##";
			} else if (laberinto[i][j] == 2) {
				cout<<" *";
			} else if (laberinto[i][j] == 1) {
				cout<<"  ";
			} else if (laberinto[i][j] == 3) {
				cout<<" ~"; //agua
			} else if (laberinto[i][j] == 4) {
				cout<<"::"; //piedras
			}
		};
		cout<<"\n";
	};
};
 
 
 //crear structura de tipo nodo para A star:
 typedef struct Node {
 	int fila;
 	int columna;
 	int g;
 	int h; 
 	int f;
	Node* padre;
 } Node;
 
//funcion para crear un nuevo Node:
Node* crearNode(int fila, int columna, int g, int h, int f) {
	Node* nuevoNode = new Node;
	nuevoNode->fila = fila;
	nuevoNode->columna = columna;
	nuevoNode->g = g;
	nuevoNode->h = h;
	nuevoNode->f = f;
	nuevoNode->padre = NULL;
	
	return nuevoNode;
}

 
//con el fin de que la cola de prioridad vaya de menor a mayor y no de mayor a menor:
struct CompararNodes {
	bool operator()(const Node* a, const Node* b) const {
		return a->f > b->f;
	}
};

 //Posibles funciones heuristicas para A star:
 int heuristica_manhattan(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin) {
 	int distancia_manhattan = abs(fila_fin - fila_inicio) + abs(columna_fin - columna_inicio);
 	return distancia_manhattan;
 };
 int heuristica_euclidiana(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin) {
 	int distancia_euclidiana = sqrt((fila_inicio - fila_fin)*(fila_inicio - fila_fin) + (columna_inicio - columna_fin)*(columna_inicio - columna_fin));
 	return distancia_euclidiana;
 };
 
 
 
 // Validar que pueda usar para mi analisis la celda:
 bool validar_escarbar(int **laberinto, int filas, int columnas, int fila, int columna) {
 	if (fila > 0 && fila < (filas - 1) && columna > 0 && columna < (columnas - 1)) {	
	 	if (laberinto[fila][columna] == 10) {
	 		return true;	
		} else {
			return false;
		};		
	} else {
		return false;
	};
 };
 
 
 
 // Generar los caminos dentro del laberinto con DFS y Backtracking:
 void abrir_camino(int** laberinto,bool** visitados, int fila, int columna, int filas, int columnas, int fila_fin, int columna_fin) {
 	
	// marcar la fila donde estoy como libre y aparte marcar como visitado
	laberinto[fila][columna] = 1;
	visitados[fila][columna] = true;
	
	// DIRECCIONES:	
	int fila_pos[4] = {2, -2, 0, 0};
	int columna_pos[4] = {0, 0, 2, -2};
	int direcciones[4] = {0, 1, 2, 3};
	
	// hacer shuffle manual a direcciones
	for (int i = 3; i > 0; i--) {
	    int j = rand() % (i + 1);   
	    int temp = direcciones[i];
	    direcciones[i] = direcciones[j];
	    direcciones[j] = temp;
	}
	
	//recorrer las posibles direcciones luego de shuffle:
	for (int mov=0; mov<4; mov++) {
		
		int movimiento = direcciones[mov];
		int nueva_fila = fila + fila_pos[movimiento];
		int nueva_columna = columna + columna_pos[movimiento];
		bool respuesta = validar_escarbar(laberinto, filas, columnas, nueva_fila, nueva_columna);
		
		if (respuesta && !visitados[nueva_fila][nueva_columna]) {
			laberinto[(nueva_fila + fila) / 2][(nueva_columna + columna) / 2] = 1;
			visitados[nueva_fila][nueva_columna] = true;
			abrir_camino(laberinto, visitados, nueva_fila, nueva_columna, filas, columnas, fila_fin, columna_fin);	
		};	
	};
 };
 
 
 void agregar_optimizar_obstaculos(int **laberinto, int filas, int columnas) {
 	
 	int posibilidad, obstaculo, pos_quitar;
 	
 	for (int i=0; i<filas; i++) {
 		for (int j=0; j<columnas; j++) {
 			
 			if (laberinto[i][j] == 10) {	
 				if (i > 0 && i < (filas - 1) && j > 0 && j < (columnas - 1)) {
 					pos_quitar = rand() % 10;
	 				
	 				if (pos_quitar < 2) {
	 					laberinto[i][j] = 1;
					}
				};
				continue;
 			};
 			
 			posibilidad = rand() % 10;
 				
 			if (posibilidad > 1) {
 				continue;
 			};
 			
 			obstaculo = rand() % 10;		
			 
			if (obstaculo > 5) {
				laberinto[i][j] = 3;
			} else {
				laberinto[i][j] = 4;
			}
		};
	};
 }
 
 
 
//funcion que resuelve el laberinto con un algoritmo de busqueda por anchura BFS A*
void Resolver_laberinto_Astar(int** laberinto, int fila_inicio, int columna_inicio, int fila_fin, int columna_fin, int filas, int columnas) {
	
	//Declarar la lista abierta:
	priority_queue<Node*, vector<Node*>, CompararNodes> open_list;
	
	//Declarar la lista cerrada:
	bool** cerrado = new bool*[filas];
	for (int i=0; i<filas; i++) {
		cerrado[i] = new bool[columnas];
		for (int j=0; j<columnas; j++) {
			cerrado[i][j] = false;	
		};	
	};
	
	//guardar la mejor g para poder optimizar A*:
	int** mejor_g = new int*[filas];
	for (int i=0; i<filas; i++) {
		mejor_g[i] = new int[columnas];
		for(int j=0; j<columnas; j++) {
			mejor_g[i][j] = 9999;
		}
	}
	
	mejor_g[fila_inicio][columna_inicio] = 0;
	
	//posibles direcciones del algoritmo:
	int df[4] = {1, -1, 0, 0};
	int dc[4] = {0, 0, 1, -1};
	
	int g = 0;
	int h = heuristica_manhattan(fila_inicio, columna_inicio, fila_fin, columna_fin);
	int f = g + h;

	//crear nodo inicial de A*:
	Node* nodo_inicial= crearNode(fila_inicio, columna_inicio, g, h, f);
	open_list.push(nodo_inicial);
	Node* objetivo = NULL;
	
	//empezar a recorrer el laberinto para encontrar camino:
	while (!open_list.empty()) {
		Node* menor_nodo = open_list.top();
		open_list.pop();
		
		if (menor_nodo->fila == fila_fin && menor_nodo->columna == columna_fin){
			objetivo = menor_nodo;
			break;
		}
		if (cerrado[menor_nodo->fila][menor_nodo->columna]) {
			continue;
		}
		
		cerrado[menor_nodo->fila][menor_nodo->columna] = true;
		
		for (int dir=0; dir<4; dir++) {
			
			int nf = menor_nodo->fila + df[dir];
			int nc = menor_nodo->columna + dc[dir];
			
			if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && !(laberinto[nf][nc] == 10) && !cerrado[nf][nc])  {
				
				int g_n = menor_nodo->g + laberinto[nf][nc];
				
				if (g_n < mejor_g[nf][nc]) {
					mejor_g[nf][nc] = g_n;
					
					int h_n = heuristica_manhattan(nf, nc, fila_fin, columna_fin);
					int f_n = g_n + h_n;
					
					Node* hijo = crearNode(nf, nc, g_n, h_n, f_n);
					hijo->padre = menor_nodo;	
					open_list.push(hijo);
				};
			};
		};		
	};
	
	
	if (objetivo == NULL) {
		cout<< "\nno existe camino. \n";
		return;
	};

	
	Node* recorrer = objetivo;
	while (recorrer != NULL) {
		system("CLS");
		laberinto[recorrer->fila][recorrer->columna] = 2;
		recorrer = recorrer->padre;
		mostrar_laberinto(laberinto, filas, columnas);
		_sleep(120);
	};
	
	cout<<"\nCamino encontrado. \n";


	//limpiar memoria de cerrado:
    for (int i = 0; i < filas; i++) {
        delete[] cerrado[i];
	};
    delete[] cerrado;
    
    
    //limpiar memoria de mejor_g:
    for (int i = 0; i < filas; i++) {
    	delete[] mejor_g[i];
	};
	delete[] mejor_g;
}


 
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

