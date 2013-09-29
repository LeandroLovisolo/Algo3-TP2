#ifndef PROBLEMA2_H
#define PROBLEMA2_H

#include <vector>
#include <utility>
#include <tuple>

typedef unsigned nodo;
typedef unsigned costo_enlace;
typedef std::tuple<nodo, nodo, costo_enlace> enlace;

#define nodo1(e) get<0>(e)
#define nodo2(e) get<1>(e)
#define costo(e) get<2>(e)

std::pair<nodo, std::vector<enlace>>
problema2(unsigned cant_nodos, std::vector<enlace> enlaces);

std::vector<unsigned> bfs(unsigned cant_nodos, std::vector<enlace> enlaces, nodo inicial);

std::vector<nodo> camino_entre_nodos(unsigned cant_nodos, std::vector<enlace> enlaces, nodo inicial, nodo final);

#endif // PROBLEMA2_H

