#include "gtest/gtest.h"
#include "problema3.h"

using namespace std;

TEST(problema3, TestGenerico) {

	unsigned cantFabricas = 2;
	unsigned nodos = 7;
	vector<ruta> rutas;
	//Grafo de: http://en.wikipedia.org/wiki/Kruskal%27s_algorithm
	//A = 0, B = 2, C = 1, D = 3, E = 4, F = 5 G = 6
	//A y C son fábricas
	rutas.push_back(ruta(0,3,5));
	rutas.push_back(ruta(0,2,7));
	rutas.push_back(ruta(2,1,8));
	rutas.push_back(ruta(2,4,7));
	rutas.push_back(ruta(1,4,5));
	rutas.push_back(ruta(4,6,9));
	rutas.push_back(ruta(4,5,8));
	rutas.push_back(ruta(5,6,11));
	rutas.push_back(ruta(5,3,6));
	rutas.push_back(ruta(3,4,15));
	rutas.push_back(ruta(3,2,9));
    vector<ruta> solucion = problema3(nodos, cantFabricas, rutas);
    unsigned costoTotal = 0;
    for (unsigned i = 0; i < solucion.size(); ++i) {
    	costoTotal += costo(solucion[i]);
    	//Imprime caminos de la solución
    	//cout << nodo1(solucion[i]) << " <--> " << nodo2(solucion[i]) << " C: " << costo(solucion[i]) << endl;
    }
    EXPECT_EQ(32, costoTotal);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
