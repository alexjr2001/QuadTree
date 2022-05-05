/*
PROYECTO: QUADTREE
AUTOR: ALEXANDER SEBASTIÁN GÓMEZ DEL CARPIO
FECHA: 30/04/2022
[ES]
En el presente código podemos ver un implementación de una "Quadtree" con la intención de implementarlo en un mapa de calor, según la densidad de puntos 
en un sector, considerar que las divisiones son un parámetro para saber cuántos niveles tendrá nuestro árbol Quad.
*/



#include <iostream>
#include<vector>
#include<cmath>
#include<math.h>
using namespace std;

struct Node {			//Estructura nodo = cuadrante
	Node* quad[4] = {nullptr, nullptr, nullptr, nullptr};		//Quadtree: El nodo tiene 4 sub hijos
	float begin[2] = {0,0};			//Coordenadas de inicio
	float end[2] = {0,0};			//Coordenadas de fin
	int num=0;						//Número de puntos
	int nivel = 0;					//Nivel de nodo
	Node(){}
	Node(float b[2], float e[2],int n){			//Inicializamos
		begin[0] = b[0];
		begin[1] = b[1];
		end[0] = e[0];
		end[1] = e[1];
		nivel = n;
	}
	~Node(){}
};

struct QuadTree {
	Node* root;
	int deep;		//Profundidad
	QuadTree(float b[2],float e[2], int d){
		root = new Node(b,e,0);
		deep = d;
		init(root, deep);		//Función para inicializar el árbol con su profundidad correcta
	}
	~QuadTree(){}
	void init(Node* ptr,int d = 1) {
		if (d == 1) {	//Si ya se llegó al límite de profundidad que queremos
			return;
		}

		//Variables para inicializar los 4 hijos nodos
		float bt[2] = { ptr->begin[0],ptr->begin[1] };
		float et[2] = { ptr->end[0],ptr->end[1] };
		float bt2[2] = { ptr->begin[0],ptr->begin[1] };
		float et2[2] = { ptr->end[0],ptr->end[1] };
		float difX = abs(ptr->begin[0] - ptr->end[0]);
		float difY = abs(ptr->begin[1] - ptr->end[1]);


		//Primer hijo
		et[0] = et[0] - (difX / 2);
		et[1] = et[1] + (difY / 2);
		ptr->quad[0] = new Node(bt, et,ptr->nivel+1);
		et[0] = et2[0];
		et[1] = et2[1];

		//Segundo hijo
		bt[0] = bt[0] + (difX / 2);
		et[1] = et[1] + (difY / 2);
		ptr->quad[1] = new Node(bt, et, ptr->nivel + 1);
		bt[0] = bt2[0];
		et[1] = et2[1];

		//Tercer hijo
		bt[1] = et[1] + (difY / 2);
		et[0] = bt[0] + (difX / 2);
		ptr->quad[2] = new Node(bt, et, ptr->nivel + 1);
		bt[1] = bt2[1];
		et[0] = et2[0];

		//Cuarto hijo
		bt[0] = et[0] - (difX / 2);
		bt[1] = et[1] + (difY / 2);
		ptr->quad[3] = new Node(bt, et, ptr->nivel + 1);
		bt[0] = bt2[0];
		bt[1] = bt2[1];
		
		//Inicializamos los hijos de cada nodo hijo
		init(ptr->quad[0], d - 1);
		init(ptr->quad[1], d - 1);
		init(ptr->quad[2], d - 1);
		init(ptr->quad[3], d - 1);
	}

	void add2(Node* ptr, float x, float y) {

		ptr->num += 1;		//Aumentamos un punto
		if (!ptr->quad[0]) {			//Si es nodo hoja
			return;
		}
		//Vemos a que régión de las cuatro pertenece
		if (ptr->quad[0]->end[0] > x) {
			if(ptr->quad[0]->end[1] < y){
				add2(ptr->quad[0], x, y);
			}
			else {
				add2(ptr->quad[2],x,y);
			}
		}
		else { 
			if (ptr->quad[0]->end[1] < y) {
				add2(ptr->quad[1], x, y);
			}
			else {
				add2(ptr->quad[3], x, y);
			}
		}
	}

	void add(float x, float y) { //Llama a function recursiva
		add2(root, x, y);
	}
};

void DFS(Node* ptr) {			//Impresion de árbol con valores no nulos
	if (!ptr) {
		return;
	}
	if (ptr->num != 0) {
		cout << endl << "Nodo nivel " << ptr->nivel << " Cantidad " << ptr->num << " puntos Inicio: " << ptr->begin[0] << " - " << ptr->begin[1] << " Final: " << ptr->end[0] << " - " << ptr->end[1];
	}
	DFS(ptr->quad[0]);
	DFS(ptr->quad[1]);
	DFS(ptr->quad[2]);
	DFS(ptr->quad[3]);
}

int main() {
	float begin[2] = {0,1000};
	float end[2] = {1000,0};
	QuadTree myQuad(begin,end,4);
	myQuad.add(10,774);
	myQuad.add(10,554);
	myQuad.add(15,20);
	myQuad.add(20,25);
	myQuad.add(490,520);
	myQuad.add(540,400);
	myQuad.add(900,900);
	cout << "Todos los nodos que no aparecen tienen 0 puntos\n";
	DFS(myQuad.root);
	return 0;
}
