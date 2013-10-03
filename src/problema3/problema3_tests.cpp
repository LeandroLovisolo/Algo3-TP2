#include "gtest/gtest.h"
#include "problema3.h"

using namespace std;

TEST(problema3, CasoGeneral) {
	unsigned cant_fabricas = 2;
	unsigned cant_nodos = 7;

	//Grafo de: http://en.wikipedia.org/wiki/Kruskal%27s_algorithm
	//A = 0, B = 2, C = 1, D = 3, E = 4, F = 5 G = 6
	//A y C son fábricas
	vector<ruta> rutas;
	rutas.push_back(ruta(0, 3, 5));
	rutas.push_back(ruta(0, 2, 7));
	rutas.push_back(ruta(2, 1, 8));
	rutas.push_back(ruta(2, 4, 7));
	rutas.push_back(ruta(1, 4, 5));
	rutas.push_back(ruta(4, 6, 9));
	rutas.push_back(ruta(4, 5, 8));
	rutas.push_back(ruta(5, 6, 11));
	rutas.push_back(ruta(5, 3, 6));
	rutas.push_back(ruta(3, 4, 15));
	rutas.push_back(ruta(3, 2, 9));

    vector<ruta> solucion = problema3(cant_nodos, cant_fabricas, rutas);

    costo_ruta costo_total = 0;
    for(unsigned i = 0; i < solucion.size(); i++) {
    	costo_total += costo(solucion[i]);
    }

    EXPECT_EQ(32, costo_total);
}

// Representa el caso trivial en el cuál se eligen 
// los dos únicos caminos para coenctarse con una fábrica.
TEST(problema3, UnaFabricaDosClientes) {
	unsigned cant_fabricas = 1;
	unsigned cant_nodos = 3;

	// 1 <--> 0, 0 <--> 2 (fábrica en el medio de los 2 clientes)
	vector<ruta> rutas1;
	rutas1.push_back(ruta(1, 0, 5));
	rutas1.push_back(ruta(0, 2, 7));

	vector<ruta> solucion1 = problema3(cant_nodos, cant_fabricas, rutas1);

    costo_ruta costo_total = 0;
    for(unsigned i = 0; i < solucion1.size(); i++) {
    	costo_total += costo(solucion1[i]);
    }

    EXPECT_EQ(12, costo_total);

	// 0 <--> 1, 1 <--> 2 (fábrica en una punta)
    vector<ruta> rutas2;
	rutas2.push_back(ruta(0, 1, 5));
	rutas2.push_back(ruta(1, 2, 7));

	vector<ruta> solucion2 = problema3(cant_nodos, cant_fabricas, rutas2);

	costo_total = 0;
	for(unsigned i = 0; i < solucion2.size(); i++) {
    	costo_total += costo(solucion2[i]);
    }

    EXPECT_EQ(12, costo_total);
}

// Representa el caso trivial en el cuál se elige un único
// camino para conectar con una de las 2 fábricas.
TEST(problema3, DosFabricasUnCliente) {
	unsigned cant_fabricas = 2;
	unsigned cant_nodos = 3;

	// 0 <--> 2, 1 <--> 2 (cliente en el medio de 2 fábricas)
	vector<ruta> rutas1;
	rutas1.push_back(ruta(0, 2, 5));
	rutas1.push_back(ruta(1, 2, 7));

	vector<ruta> solucion1 = problema3(cant_nodos, cant_fabricas, rutas1);

    costo_ruta costo_total = 0;
    for(unsigned i = 0; i < solucion1.size(); i++) {
    	costo_total += costo(solucion1[i]);
    }

    EXPECT_EQ(5, costo_total);
    
	// 0 <--> 1, 1 <--> 2 (2 fábricas en una punta)
    vector<ruta> rutas2;
	rutas2.push_back(ruta(0, 1, 5));
	rutas2.push_back(ruta(1, 2, 7));

	vector<ruta> solucion2 = problema3(cant_nodos, cant_fabricas, rutas2);

	costo_total = 0;
	for(unsigned i = 0; i < solucion2.size(); i++) {
    	costo_total += costo(solucion2[i]);
    }

    EXPECT_EQ(7, costo_total);
}

// Representa el caso trivial en el cuál se consiguen 2 subconjuntos,
// cada uno de un cliente con su fábrica. (Prueba que no se unen
// subconjuntos con una fábrica.)
TEST(problema3, DosGrafosDisjuntos) {
	unsigned cant_fabricas = 2;
	unsigned cant_nodos = 4;

	// El grafo es un cuadrado, con los 2 nodos superiores como fábricas
	// 0 <--> 2, 0 <--> 1, 1 <--> 3, 2 <--> 3
	vector<ruta> rutas;
	rutas.push_back(ruta(0, 2, 4));
	rutas.push_back(ruta(0, 1, 1));
	rutas.push_back(ruta(1, 3, 5));
	rutas.push_back(ruta(2, 3, 7));

	vector<ruta> solucion = problema3(cant_nodos, cant_fabricas, rutas);
    
    costo_ruta costo_total = 0;
    for(unsigned i = 0; i < solucion.size(); i++) {
    	costo_total += costo(solucion[i]);
    }

    EXPECT_EQ(9, costo_total);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}