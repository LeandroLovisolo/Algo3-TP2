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

std::pair<nodo, std::vector<enlace>> problema2(unsigned cant_nodos,
                                               std::vector<enlace> enlaces);

std::vector<enlace> problema2a(unsigned cant_nodos, std::vector<enlace> enlaces);

nodo problema2b(unsigned cant_nodos, std::vector<enlace> enlaces);

#endif // PROBLEMA2_H