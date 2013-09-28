#include <iostream>
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

//Según el enunciado, primero van las fábricas y luego los clientes
//Tener la cantidad de fábricas me ayuda a saber que fábricas son en el DisjointSet
vector<ruta> problema3(unsigned nodos, unsigned cantFabricas, vector<ruta> rutas) {
    vector<ruta> camino_minimo;
    for (unsigned i = 0; i < cantFabricas; ++i) {
        //Uno cada fábrica con el nuevo nodo fantasma
        //Asumo que el costo de pavimentación es > 0 siempre
        rutas.push_back(ruta(i, nodos, 0));
    }
    DisjointSet disjoint_set(nodos+1);

    sort(rutas.begin(),
         rutas.end(),
         [] (ruta e, ruta f) { return costo(e) < costo(f); });

    for(unsigned i = 0; i < rutas.size(); i++) {
        unsigned set1 = disjoint_set.find(nodo1(rutas[i]));
        unsigned set2 = disjoint_set.find(nodo2(rutas[i]));
        if(set1 != set2){
            disjoint_set.make_union(set1, set2);
            camino_minimo.push_back(rutas[i]);
        }        
    }

    vector<ruta> res;
    res.reserve(camino_minimo.size() - cantFabricas);
    for (unsigned i = cantFabricas; i < camino_minimo.size(); ++i) {
        res.push_back(ruta(nodo1(camino_minimo[i]), nodo2(camino_minimo[i]), costo(camino_minimo[i])));
    }
    return res;
}