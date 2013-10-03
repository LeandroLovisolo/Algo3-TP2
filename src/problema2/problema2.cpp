#include <algorithm>
#include <queue>

#include "problema2.h"

using namespace std;

pair<nodo, vector<enlace>> problema2(unsigned cant_nodos, vector<enlace> enlaces) {
    vector<enlace> arbol_generador_minimo = problema2a(cant_nodos, enlaces);
    nodo maestro                          = problema2b(cant_nodos, arbol_generador_minimo);
    return make_pair(maestro, arbol_generador_minimo);
}

///////////////////////////////////////////////////////////////////////////////
// Problema 2a                                                               //
///////////////////////////////////////////////////////////////////////////////

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

vector<enlace> problema2a(unsigned cant_nodos, vector<enlace> enlaces) {
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

///////////////////////////////////////////////////////////////////////////////
// Problema 2b                                                               //
///////////////////////////////////////////////////////////////////////////////

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

bool camino_entre_nodos_rec(vector<nodo_lista_adyacencia> &nodos, vector<nodo> &camino, nodo actual, nodo final) {
    nodos[actual].visitado = true;
    
    // Si donde estoy es el que buscaba, lo agrego y devuelvo true
    if(actual == final) {
        camino.push_back(actual);
        return true; 
    }

    // Si donde estoy no es el que busco y no tiene adyacentes, no encontré solución, false
    if(nodos[actual].adyacentes.size() == 0) {
        return false;
    }

    // Si tiene adyacentes, los checkeo
    else {
        for(size_t i = 0; i < nodos[actual].adyacentes.size(); i++) {
            nodo adyacente = nodos[actual].adyacentes[i];
            if(!nodos[adyacente].visitado) {
                if(camino_entre_nodos_rec(nodos, camino, adyacente, final)) {
                    camino.push_back(actual);
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


nodo problema2b(unsigned cant_nodos, vector<enlace> enlaces) {
    // Caso borde
    if(cant_nodos == 1) return 0;

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