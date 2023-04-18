/*
PROJECT: QUADTREE
AUTHOR: ALEXANDER SEBASTIÁN GÓMEZ DEL CARPIO
DATE: 04/30/2022

[EN]
In this code we can see an implementation of a "Quadtree" with the intention of implementing it in a heat map, according to the density of points
in a sector, consider that the divisions are a parameter to know how many levels our Quad tree will have.

[ES]
En el presente código podemos ver un implementación de una "Quadtree" con la intención de implementarlo en un mapa de calor, según la densidad de puntos 
en un sector, considerar que las divisiones son un parámetro para saber cuántos niveles tendrá nuestro árbol Quad.
*/



#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

struct Node {			//Node structure = quadrant
	Node* quad[4] = {nullptr, nullptr, nullptr, nullptr};		//Quadtree: The node has 4 children
	float begin[2] = {0,0};			//Start up coordinates
	float end[2] = {0,0};			//End coordinates
	int num=0;						//Number of points
	int nivel = 0;					//Node level
	Node(){}
	Node(float b[2], float e[2],int n){			//Initialization
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
	int deep;		//Depth of the tree
	QuadTree(float b[2],float e[2], int d){
		root = new Node(b,e,0);
		deep = d;
		init(root, deep);		//Funtion to initaliaze a tree with its right depth
	}
	~QuadTree(){}
	void init(Node* ptr,int d = 1) {
		if (d == 1) {	//If we reached the depth limit that we wanted
			return;
		}

		//Variables to initialize the 4 node children, we split the space in four.  
		float bt[2] = { ptr->begin[0],ptr->begin[1] };
		float et[2] = { ptr->end[0],ptr->end[1] };
		float bt2[2] = { ptr->begin[0],ptr->begin[1] };
		float et2[2] = { ptr->end[0],ptr->end[1] };
		float difX = abs(ptr->begin[0] - ptr->end[0]);
		float difY = abs(ptr->begin[1] - ptr->end[1]);

		//For every children we will find out where its quadrant begins and where it ends
		//First children
		et[0] = et[0] - (difX / 2);
		et[1] = et[1] + (difY / 2);
		ptr->quad[0] = new Node(bt, et,ptr->nivel+1);
		et[0] = et2[0];
		et[1] = et2[1];

		//Second children
		bt[0] = bt[0] + (difX / 2);
		et[1] = et[1] + (difY / 2);
		ptr->quad[1] = new Node(bt, et, ptr->nivel + 1);
		bt[0] = bt2[0];
		et[1] = et2[1];

		//Third children
		bt[1] = et[1] + (difY / 2);
		et[0] = bt[0] + (difX / 2);
		ptr->quad[2] = new Node(bt, et, ptr->nivel + 1);
		bt[1] = bt2[1];
		et[0] = et2[0];

		//Fourth children
		bt[0] = et[0] - (difX / 2);
		bt[1] = et[1] + (difY / 2);
		ptr->quad[3] = new Node(bt, et, ptr->nivel + 1);
		bt[0] = bt2[0];
		bt[1] = bt2[1];
		
		//We initialize the children of each child node
		init(ptr->quad[0], d - 1);
		init(ptr->quad[1], d - 1);
		init(ptr->quad[2], d - 1);
		init(ptr->quad[3], d - 1);
	}

	void add2(Node* ptr, float x, float y) {  //We search which quadrant will be getting the new point, then we divide it

		ptr->num += 1;		//We increase a point
		if (!ptr->quad[0]) {			//If it is leaf node
			return;
		}
		//We see which region of the four ones it belongs to
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

	void add(float x, float y) { //Calls a recursive function
		add2(root, x, y);
	}
};

void DFS(Node* ptr) {			//We print the tree with no null values
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
	QuadTree myQuad(begin,end,4);	//EXAMPLE
	myQuad.add(10,774);
	myQuad.add(10,554);
	myQuad.add(15,20);
	myQuad.add(20,25);
	myQuad.add(490,520);
	myQuad.add(540,400);
	myQuad.add(900,900);
	cout << "Todos los nodos que no aparecen tienen 0 puntos\n";  //All the nodes that are not appearing have 0 points
	DFS(myQuad.root);
	return 0;
}
