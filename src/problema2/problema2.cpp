#include "problema2.h"
using namespace std;
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

Set::Set(unsigned int costo) {
    _costo = costo;
    _parent = this;
}

unsigned int Set::costo() {
	return _costo;
}

Set *Set::getRoot() {
    Set *search = 0;
    while(_parent != search) {
        search = _parent->_parent;
    }
    //La siguiente linea se llama "path compression"
    //Aplana aún mas el set, poniendole la raiz que encuentra como padre
    _parent = search;
    //-------------------------------------------
    return search;
}

//Pre condición, las dos raices no son iguales
void Set::unionSet(Set &otherSet) {
    //Quiero unir dos sets, los sets se unen por su nodo raiz
    //Si uno este al nodo raiz o el que me pasan, depende de cuál es su ranking
    //El ranking incrementa al unirse uno

    Set *otherSetRoot = otherSet.getRoot(); //Consigo el ranking del otro
    Set *thisSetRoot = getRoot(); //Consigo el ranking de este
    if(otherSetRoot->_rank < thisSetRoot->_rank) {
        thisSetRoot->_parent = otherSetRoot; //Pongo como padre al otro set
        otherSetRoot->_rank++; //Incremento el rango
    }
    else {
        otherSetRoot->_parent = thisSetRoot;
        thisSetRoot->_rank++;
    }
}

void problema2(vector<Set> &aristas) {
	//Sort aristas por _costo
	//Tomo aritas 0 como mi conjunto inicial
	unsigned int costo = aristas[0].costo();
	for(unsigned int i=1;i<aristas.size();i++) {
		//Ver si comparten el mismo conjunto, si no comparten, la agrego
		if(aristas[0].getRoot() != aristas[i].getRoot()) {
			aristas[0].unionSet(aristas[i]);
			costo += aristas[i].costo();
		}
	}
	//Falta calcular el problema 2 también y ver que devuelve problema2
}
