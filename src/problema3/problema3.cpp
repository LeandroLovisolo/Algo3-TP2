#include <iostream>
#include "problema3.h"

using namespace std;

class DisjointSet {
public:
    DisjointSet(unsigned sets, unsigned cantFabricas);
    void make_union(unsigned x, unsigned y);
    pair<unsigned, unsigned> find(unsigned x);

private:
    std::vector<unsigned> parent;
    //Fabrica tiene, si es fábrica al inicio o si está conectada con alguna fábrica luego
    std::vector<unsigned> ranking;
    std::vector<unsigned> fabrica;
};

DisjointSet::DisjointSet(unsigned sets, unsigned cantFabricas)
        : parent(sets), ranking(sets), fabrica(sets) {
    //Las fábricas se encuentran en los primeros valores del arreglo
    for(unsigned i = 0; i < cantFabricas; i++) {
        parent[i] = i;
        ranking[i] = 0;
        //Se pone a si mismo como fábrica
        fabrica[i] = i;
    }
    for(unsigned i = cantFabricas; i < sets; i++) {
        parent[i] = i;
        ranking[i] = 0;
        //No es fábrica, infinito
        fabrica[i] = inf;
    }
}

void DisjointSet::make_union(unsigned x, unsigned y) {
    pair<unsigned, unsigned> set_x = find(x);
    pair<unsigned, unsigned> set_y = find(y);
    if(ranking[set_x.first] > ranking[set_y.first]) {
        parent[set_y.first] = set_x.first;
    } else {
        parent[set_x.first] = set_y.first;
    }
    if(ranking[set_x.first] == ranking[set_y.first]) {
        ranking[set_y.first]++;
    }
    //Asigno la fábrica al nodo padre para unir los sets con una fábrica
    //En el caso de que no esten unidas por una fábrica, ambas quedan con inf
    if(set_x.second != inf) {
    	fabrica[set_y.first] = set_x.second;
    }
    else {
    	fabrica[set_x.first] = set_y.second;	
    }
}

pair<unsigned, unsigned> DisjointSet::find(unsigned x) {
    if(x != parent[x]) {
    	pair<unsigned, unsigned> _parent = find(parent[x]);
        parent[x] = _parent.first;
        //Asigno la misma fábrica para path compression
        fabrica[x] = _parent.second;
    }
    return make_pair(parent[x], fabrica[x]);
}

/*
La idea es la siguiente:
-Buscar subconjuntos de árboles mínimos los cuales sólo compartan una fábrica
-Comparten una única fábrica ya que, conectar una fábrica a un arbol tiene menor
costo que conectar > 1 fábricas y solo se necesita 1.

-Se tendrá siempre el subconjunto de clientes con la fábrica de menor costo de pavimentación ya que Kruskal toma
las aristas de menor a mayor, siendo siempre la primera conexión con una fábrica, la menor en cada subconjunto.
-No se unen subconjuntos que ya tengan fábricas ya que es un gasto innecesario (ambos subconjuntos ya estan) unidos
a una fábrica que es un requisito y tinen camiones de costo mínimo entre ellos.
-Debido a que Kruscal obtiene los AGM, no permitiendo la unión de subconjuntos con mismas fábricas crea subconjuntos
de AGM, es decir subconjuntos con caminos mínimos entre sí.
*/

//Según el enunciado, primero van las fábricas y luego los clientes
//Tener la cantidad de fábricas me ayuda a saber que fábricas son en el DisjointSet
vector<ruta> problema3(unsigned nodos, unsigned cantFabricas, vector<ruta> rutas) {
    vector<ruta> camino_minimo;
    DisjointSet disjoint_set(nodos, cantFabricas);

    sort(rutas.begin(),
         rutas.end(),
         [] (ruta e, ruta f) { return costo(e) < costo(f); });

    for(unsigned i = 0; i < rutas.size(); i++) {
        pair<unsigned, unsigned> set1 = disjoint_set.find(nodo1(rutas[i]));
        pair<unsigned, unsigned> set2 = disjoint_set.find(nodo2(rutas[i]));
        //Uno los sets que no tengan ya una fábrica, es decir, que ambos
        //no tengan como fábrica algo diferente de infinito.
        if((set1.first != set2.first) && 
        	!(set1.second != inf && set2.second != inf)){
            	disjoint_set.make_union(set1.first, set2.first);
            	camino_minimo.push_back(rutas[i]);
        }        
    }

    return camino_minimo;
}