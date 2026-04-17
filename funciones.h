#ifndef FUNCIONES_H
#define FUNCIONES_H

 typedef struct Node {
 	int fila;
 	int columna;
 	int g;
 	int h; 
 	int f;
	Node* padre;
 } Node;

Node* crearNode(int fila, int columna, int g, int h, int f);

struct CompararNodes {
    bool operator()(const Node* a, const Node* b) const;
};

void mostrar_laberinto(int** laberinto, int filas, int columnas);

int heuristica_manhattan(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin);

int heuristica_euclidiana(int fila_inicio, int columna_inicio, int fila_fin, int columna_fin);

bool validar_escarbar(int **laberinto, int filas, int columnas, int fila, int columna);

void abrir_camino(int** laberinto, bool** visitados, int fila, int columna, int filas, int columnas, int fila_fin, int columna_fin);

void agregar_optimizar_obstaculos(int** laberinto, int filas, int columnas);

void Resolver_laberinto_Astar(int** laberinto, int fila_inicio, int columna_inicio, int fila_fin, int columna_fin, int filas, int columnas);


#endif
