#ifndef PROBLEMA3_H
#define PROBLEMA3_H

#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>

typedef unsigned nodo;
typedef unsigned costo_ruta;
typedef std::tuple<nodo, nodo, costo_ruta> ruta;

#define nodo1(e) get<0>(e)
#define nodo2(e) get<1>(e)
#define costo(e) get<2>(e)

std::vector<ruta> problema3(unsigned cant_nodos,
	                        unsigned cant_fabricas,
	                        const std::vector<ruta> &rutas);

#endif // PROBLEMA3_H
