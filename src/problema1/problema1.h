#ifndef PROBLEMA1_H
#define PROBLEMA1_H

#include <utility>
#include <vector>

using std::pair;
using std::vector;

typedef unsigned trabajo;
typedef unsigned costo;
typedef vector<vector<costo>> costos;

// Genera una tabla de costos para n problemas, inicializada en 0.
costos crear_costos(unsigned n);

pair<costo, vector<trabajo>> problema1(unsigned n, costos c);

#endif