#include "problema3.h"

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

vector<ruta> problema3(unsigned cant_nodos,
                       unsigned cant_fabricas,
                       const vector<ruta> &rutas_) {
    // Creo un vector de rutas.
    vector<ruta> rutas;

    // Conecto las fábricas a un nodo fantasma con rutas de costo 0.
    for(unsigned i = 0; i < cant_fabricas; i++) rutas.push_back(ruta(i, cant_nodos, 0));
    
    // Agrego las rutas verdaderas al nuevo vector de rutas.
    rutas.insert(rutas.end(), rutas_.begin(), rutas_.end());

    // Inicio de algoritmo de Kruskal.
    DisjointSet disjoint_set(cant_nodos + 1);

    sort(rutas.begin(),
         rutas.end(),
         [] (ruta e, ruta f) { return costo(e) < costo(f); });

    vector<ruta> arbol_generador_minimo;

    for(unsigned i = 0; i < rutas.size(); i++) {
        unsigned set1 = disjoint_set.find(nodo1(rutas[i]));
        unsigned set2 = disjoint_set.find(nodo2(rutas[i]));
        if(set1 != set2){
            disjoint_set.make_union(set1, set2);
            arbol_generador_minimo.push_back(rutas[i]);
        }        
    }
    // Fin de algoritmo de Kruskal.

    // Devuelvo una copia del árbol generador mínimo al que le quito
    // las rutas que conectan las fábricas al nodo fantasma.
    return vector<ruta>(arbol_generador_minimo.begin() + cant_fabricas,
                        arbol_generador_minimo.end());
}