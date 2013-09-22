#ifndef PROBLEMA3_H
#define PROBLEMA3_H
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>

typedef std::tuple<unsigned, unsigned, unsigned> ruta;

#define nodo1(e) get<0>(e)
#define nodo2(e) get<1>(e)
#define costo(e) get<2>(e)
#define inf 1000000000

std::vector<ruta> problema3(unsigned nodos, unsigned cantFabricas, std::vector<ruta> rutas);

#endif // PROBLEMA3_H
