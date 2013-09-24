#include <algorithm>
#include <queue>
#include "problema2.h"

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

pair<unsigned, vector<enlace>> problema2(unsigned nodos, vector<enlace> enlaces) {
    vector<enlace> camino_minimo;
    DisjointSet disjoint_set(nodos);

    sort(enlaces.begin(),
         enlaces.end(),
         [] (enlace e, enlace f) { return costo(e) < costo(f); });

    for(unsigned i = 0; i < enlaces.size(); i++) {
        unsigned set1 = disjoint_set.find(nodo1(enlaces[i]));
        unsigned set2 = disjoint_set.find(nodo2(enlaces[i]));
        if(set1 != set2){
            disjoint_set.make_union(set1, set2);
            camino_minimo.push_back(enlaces[i]);
        }        
    }

    // Pendiente
    unsigned nodo_maestro = 0;

    return make_pair(nodo_maestro, camino_minimo);
}

struct nodo{
	vector<unsigned> adyacentes;
	unsigned distancia;
	bool visitado = false;
};

vector<unsigned> bfs(unsigned nodos, vector<enlace> enlaces, unsigned inicial) {
	vector<nodo> V;
	vector<unsigned> distancias;
	V.resize(nodos);
	distancias.resize(nodos);

	for (unsigned i = 0; i < enlaces.size(); ++i) {
		V[nodo1(enlaces[i])].adyacentes.push_back(nodo2(enlaces[i]));
		V[nodo2(enlaces[i])].adyacentes.push_back(nodo1(enlaces[i]));
	}

	queue<unsigned> cola;
	cola.push(inicial);
	V[inicial].distancia = 0;

	while (!cola.empty()) {
		unsigned n = cola.front();
		V[n].visitado = true;
		cola.pop();
		for (unsigned i = 0; i < V[n].adyacentes.size(); ++i) {
			if (V[V[n].adyacentes[i]].visitado != true) {
				V[V[n].adyacentes[i]].distancia = V[n].distancia + 1;
				cola.push(V[n].adyacentes[i]);
			}
		}
	}

	for (unsigned i = 0; i < nodos; ++i) distancias[i] = V[i].distancia;

	return distancias;
}