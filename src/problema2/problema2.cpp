#include <algorithm>
#include <queue>
#include "problema2.h"
#include <iostream>

using namespace std;

class DisjointSet {
public:
    DisjointSet(unsigned sets);
    void make_union(unsigned x, unsigned y);
    unsigned find(unsigned x);

private:
    std::vector<unsigned> parent;
    std::vector<unsigned> ranking;
};

DisjointSet::DisjointSet(unsigned sets)
        : parent(sets), ranking(sets) {
    for(unsigned i = 0; i < sets; i++) {
        parent[i] = i;
        ranking[i] = 0;
    }
}

void DisjointSet::make_union(unsigned x, unsigned y) {
    unsigned set_x = find(x);
    unsigned set_y = find(y);
    if(ranking[set_x] > ranking[set_y]) {
        parent[set_y] = set_x;
    } else {
        parent[set_x] = set_y;
    }
    if(ranking[set_x] == ranking[set_y]) {
        ranking[set_y]++;
    }
}

unsigned DisjointSet::find(unsigned x) {
    if(x != parent[x]) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

vector<enlace> kruskal(unsigned cant_nodos, vector<enlace> enlaces) {
    vector<enlace> arbol_generador_minimo;
    DisjointSet disjoint_set(cant_nodos);

    sort(enlaces.begin(),
         enlaces.end(),
         [] (enlace e, enlace f) { return costo(e) < costo(f); });

    for(unsigned i = 0; i < enlaces.size(); i++) {
        unsigned set1 = disjoint_set.find(nodo1(enlaces[i]));
        unsigned set2 = disjoint_set.find(nodo2(enlaces[i]));
        if(set1 != set2){
            disjoint_set.make_union(set1, set2);
            arbol_generador_minimo.push_back(enlaces[i]);
        }        
    }

    return arbol_generador_minimo;
}

nodo nodo_mas_distante(vector<unsigned> distancias) {
	nodo mas_distante;
	unsigned distancia_maxima = 0;
	for(nodo n = 0; n < distancias.size(); n++) {
		if(distancias[n] > distancia_maxima) {
			distancia_maxima = distancias[n];
			mas_distante = n;
		}
	}
	return mas_distante;
}

nodo centro_del_arbol(unsigned cant_nodos, vector<enlace> enlaces) {
	// Busco un extremo de un camino máximo dentro del árbol.
	vector<unsigned> distancias = bfs(cant_nodos, enlaces, nodo1(enlaces[0]));
	nodo inicial = nodo_mas_distante(distancias);

	// Busco el otro extremo del camino máximo dentro del árbol.
	distancias = bfs(cant_nodos, enlaces, inicial);
	nodo final = nodo_mas_distante(distancias);

	// Obtengo el camino máximo.
	vector<nodo> camino = camino_entre_nodos(cant_nodos, enlaces, inicial, final);

	// Devuelvo el punto medio del camino.
	return camino[camino.size() / 2];
}

pair<nodo, vector<enlace>> problema2(unsigned cant_nodos, vector<enlace> enlaces) {
	// Caso borde
	if(cant_nodos == 1) {
		return make_pair(0, enlaces);
	}

	vector<enlace> arbol_generador_minimo = kruskal(cant_nodos, enlaces);
	nodo maestro = centro_del_arbol(cant_nodos, arbol_generador_minimo);

    return make_pair(maestro, arbol_generador_minimo);
}

struct nodo_lista_adyacencia {
	vector<nodo> adyacentes;
	unsigned distancia;
	bool visitado = false;
};

vector<nodo_lista_adyacencia> crear_lista_adyacencia(unsigned cant_nodos, vector<enlace> enlaces){
	vector<nodo_lista_adyacencia> nodos(cant_nodos);
	for(size_t i = 0; i < enlaces.size(); i++) {
		nodos[nodo1(enlaces[i])].adyacentes.push_back(nodo2(enlaces[i]));
		nodos[nodo2(enlaces[i])].adyacentes.push_back(nodo1(enlaces[i]));
	}
	return nodos;
}

vector<unsigned> bfs(unsigned cant_nodos, vector<enlace> enlaces, nodo inicial) {
	vector<nodo_lista_adyacencia> nodos = crear_lista_adyacencia(cant_nodos, enlaces);
	nodos[inicial].distancia = 0;

	queue<nodo> cola;
	cola.push(inicial);

	while(!cola.empty()) {
		nodo n = cola.front();
		nodos[n].visitado = true;
		cola.pop();
		for(size_t i = 0; i < nodos[n].adyacentes.size(); i++) {
			nodo adyacente = nodos[n].adyacentes[i];
			if(nodos[adyacente].visitado != true) {
				nodos[adyacente].distancia = nodos[n].distancia + 1;
				cola.push(adyacente);
			}
		}
	}

	vector<unsigned> distancias(cant_nodos);
	for(nodo n = 0; n < cant_nodos; n++){
		distancias[n] = nodos[n].distancia;
	}

	return distancias;
}

bool camino_entre_nodos_rec(vector<nodo_lista_adyacencia> &nodos, vector<unsigned> &camino, nodo inicial, nodo final) {
    // Si donde estoy es el que buscaba, lo agrego y devuelvo true
    if(inicial == final) {
        nodos[inicial].visitado = true;
        camino.push_back(inicial);
        return true; 
    }

    // Si donde estoy no es el que busco y no tiene adyacentes, no encontré solución, false
    if(nodos[inicial].adyacentes.size() == 0) {
        nodos[inicial].visitado = true;
        return false;
    }

    // Si tiene adyacentes, los checkeo
    else {
        nodos[inicial].visitado = true;
        for(size_t i = 0; i < nodos[inicial].adyacentes.size(); i++) {
        	nodo adyacente = nodos[inicial].adyacentes[i];
            if(!nodos[adyacente].visitado) {
                if(camino_entre_nodos_rec(nodos, camino, adyacente, final)) {
                    camino.push_back(inicial);
                    return true;
                }
            }
        }
        return false;
    }
}

vector<nodo> camino_entre_nodos(unsigned cant_nodos, vector<enlace> enlaces, nodo inicial, nodo final) {
    vector<nodo_lista_adyacencia> nodos = crear_lista_adyacencia(cant_nodos, enlaces);

    vector<nodo> camino;
    camino.reserve(cant_nodos);

    camino_entre_nodos_rec(nodos, camino, inicial, final);
    return camino;
}
