#ifndef PROBLEMA2_H
#define PROBLEMA2_H

#include <vector>
#include <utility>
#include <tuple>

typedef std::tuple<unsigned, unsigned, unsigned> enlace;

#define nodo1(e) get<0>(e)
#define nodo2(e) get<1>(e)
#define costo(e) get<2>(e)

std::pair<unsigned, std::vector<enlace>> problema2(unsigned nodos, std::vector<enlace> &aristas);

#endif // PROBLEMA2_H

