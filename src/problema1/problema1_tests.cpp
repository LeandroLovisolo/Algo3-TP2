#include <cmath>
#include <climits>
#include <cstdlib>

#include "gtest/gtest.h"
#include "problema1.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Las funciones a continuación fueron extraídas de
// http://stackoverflow.com/questions/9252680/generating-the-power-set-of-a-list.

// Returns which bits are on in the integer a                                                                                                                                                                                              
vector<int> get_on_locations(int a) {
  vector<int> result;
  int place = 0;
  while (a != 0) {
    if (a & 1) {
      result.push_back(place);
    }
    ++place;
    a >>= 1;
  }
  return result;
}

template<typename T>
vector<vector<T> > power_set(const vector<T>& set) {
    vector<vector<T> > result;
    int numPowerSets = static_cast<int>(pow(2.0, static_cast<double>(set.size())));
    for (size_t i = 0; i < numPowerSets; ++i) {
          vector<int> onLocations = get_on_locations(i);
          vector<T> subSet;
          for (size_t j = 0; j < onLocations.size(); ++j) {
              subSet.push_back(set.at(onLocations.at(j)));
          }
      result.push_back(subSet);
    }
    return result;
}
///////////////////////////////////////////////////////////////////////////////

// Calcula el costo de una solución devuelta por el algoritmo.
costo costo_solucion(unsigned n, costos c, vector<trabajo> maquina) {
    vector<trabajo> maquina2;

    // Obtengo los trabajos de la otra máquina.
    for(trabajo i = 1; i <= n; i++) {
    	bool esta_presente = false;
    	for(size_t j = 0; j < maquina.size(); j++) {
    		if(maquina[j] == i) {
    			esta_presente = true;
    			break;
    		}
    	}
    	if(!esta_presente) maquina2.push_back(i);
    }

    // Agrego el trabajo vacío a ambas máquinas.
    maquina.insert(maquina.begin(), 0);
    maquina2.insert(maquina2.begin(), 0);

    // Sumo los costos.
    costo total = 0;
    for(size_t i = 1; i < maquina.size(); i++) total += c[maquina[i - 1]][maquina[i]];
    for(size_t i = 1; i < maquina2.size(); i++) total += c[maquina2[i - 1]][maquina2[i]];

    return total;
}

// Calcula por fuerza bruta el costo de la solución óptima.
costo solucion_fuerza_bruta(unsigned n, costos c) {
	
	// Genero todo el espacio de soluciones posibles.
	vector<trabajo> trabajos;
	for(trabajo i = 1; i <= n; i++) trabajos.push_back(i);
	vector<vector<trabajo>> soluciones = power_set(trabajos);

	// Busco la solución de menor costo.
	costo mejor_costo = INT_MAX;
	for(size_t i = 0; i < soluciones.size(); i++) {
		mejor_costo = min(mejor_costo, costo_solucion(n, c, soluciones[i]));
	}

	return mejor_costo;
}

TEST(problema1, UnSoloTrabajo) {
	unsigned n = 1;

	costos c = crear_costos(n);
    c[0][1] = 1;

    pair<costo, vector<trabajo>> res = problema1(n, c);

    EXPECT_EQ(1, res.first);
    EXPECT_EQ(res.first, costo_solucion(n, c, res.second));
}

TEST(problema1, CasoGeneral) {
    unsigned n = 4;

    costos c = crear_costos(n);
    c[0][1] = 1;
    c[0][2] = 2;
    c[0][3] = 3;
    c[0][4] = 4;
    c[1][2] = 5;
    c[1][3] = 6;
    c[1][4] = 7;
    c[2][3] = 8;
    c[2][4] = 9;
    c[3][4] = 10;

    pair<costo, vector<trabajo>> res = problema1(n, c);

    EXPECT_EQ(18, res.first);
    EXPECT_EQ(res.first, costo_solucion(n, c, res.second));
}

TEST(problema1, CompararConMetodoFuerzaBruta) {
	// Me aseguro de generar siempre los mismos casos.
	srand(80085);

	for(unsigned n = 1; n <= 10; n++) {
		// Genero la tabla de costos.
		costos c = crear_costos(n);
		for(int i = 0; i < (int) n; i++)
			for(int j = i + 1; j <= (int) n; j++)
				c[i][j] = rand() % 10; // Costos chicos para evitar overflow.

		pair<costo, vector<trabajo>> res = problema1(n, c);

    	EXPECT_EQ(res.first, solucion_fuerza_bruta(n, c));
		EXPECT_EQ(res.first, costo_solucion(n, c, res.second));
	}
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
