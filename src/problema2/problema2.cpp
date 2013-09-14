#include "problema2.h"
using namespace std;
unsigned int *parent;
unsigned int *ranking;

/*
Matriz::Matriz(vector<enlace> v, unsigned servidores)
		: _matriz(servidores * servidores, 0) {
	_servidores = servidores;
	_enlaces = v.size();
	for (int i = 0; i < _enlaces; ++i) {
		set(v[i]._srv1,v[i]._srv2,v[i]._costo);
	}

}

void Matriz::set(unsigned fila, unsigned columna, unsigned valor) {
	_matriz[_servidores * fila + columna] = valor;
	_matriz[_servidores * columna + fila] = valor;
}

unsigned Matriz::get(unsigned fila, unsigned columna) {
	return _matriz[_servidores * fila + columna];
}
*/
bool comparador (const enlace& e1, const enlace& e2) { return e1.costo() < e2.costo(); }

unsigned int findSet(unsigned int x){
	unsigned int actual = x;
	while(actual != parent[actual]) {
		actual = parent[actual];
	}
	//Path compression, esto le da O(1)
	parent[x] = actual;

    return actual;
}

void unionSet(int x,int y){
    unsigned int setX = findSet(x);
    unsigned int setY = findSet(y);
    if(ranking[setX] > ranking[setY]){
        parent[setY] = setX;
    }else{
        parent[setX] = setX;
    }
    if(ranking[setX] == ranking[setY]){
        ++ranking[setY];
    }
}

void problema2(unsigned int nodos, vector<enlace> &aristas) {
	//Esto debería crearlo en el main mientras recibo los datos
	parent = new unsigned int[nodos];
	ranking = new unsigned int[nodos];
	for(unsigned int i = 0; i < nodos; i++) {
		parent[i] = i;
		ranking[i] = 0;
	}
	//Ordeno las aristas
	sort(aristas.begin(),aristas.end(),comparador);

	unsigned int costo = 0;
	for(unsigned int i=0; i < aristas.size(); i++) {
		unsigned int set1 = findSet(aristas[i]._srv1);
		unsigned int set2 = findSet(aristas[i]._srv2);
		if(set1 != set2){
            unionSet(set1 , set2);
            costo += aristas[i].costo();
        }        
	}
	//Falta calcular el problema 2 también y ver que devuelve problema2
}
