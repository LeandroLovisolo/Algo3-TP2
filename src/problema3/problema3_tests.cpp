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

TEST(problema3, CasoDosClientesUnaFabrica) {
	/*Representa el caso trivial en el cuál se eligen 
	los dos únicos caminos para coenctarse con una fábrica*/
	unsigned cantFabricas = 1;
	unsigned nodos = 3;
	vector<ruta> rutas1;
	// 1 <--> 0, 0 <--> 2 (fábrica en el medio de los 2 clientes)
	rutas1.push_back(ruta(1,0,5));
	rutas1.push_back(ruta(0,2,7));
	vector<ruta> solucion1 = problema3(nodos, cantFabricas, rutas1);
    unsigned costoTotal = 0;
    for (unsigned i = 0; i < solucion1.size(); ++i) {
    	costoTotal += costo(solucion1[i]);
    }
    EXPECT_EQ(12, costoTotal);
    vector<ruta> rutas2;
	// 0 <--> 1, 1 <--> 2 (fábrica en una punta)
	rutas2.push_back(ruta(0,1,5));
	rutas2.push_back(ruta(1,2,7));
	costoTotal = 0;
	vector<ruta> solucion2 = problema3(nodos, cantFabricas, rutas2);
	for (unsigned i = 0; i < solucion2.size(); ++i) {
    	costoTotal += costo(solucion2[i]);
    }
    EXPECT_EQ(12, costoTotal);

}

TEST(problema3, CasoDosFabricasUnCliente) {
	/*Representa el caso trivial en el cuál se elige un único camino para
	conectar con una de las 2 fábrica*/
	unsigned cantFabricas = 2;
	unsigned nodos = 3;
	vector<ruta> rutas1;
	// 0 <--> 2, 1 <--> 2 (cliente en el medio de 2 fábricas)
	rutas1.push_back(ruta(0,2,5));
	rutas1.push_back(ruta(1,2,7));
	vector<ruta> solucion1 = problema3(nodos, cantFabricas, rutas1);
    unsigned costoTotal = 0;
    for (unsigned i = 0; i < solucion1.size(); ++i) {
    	costoTotal += costo(solucion1[i]);
    }
    EXPECT_EQ(5, costoTotal);
    vector<ruta> rutas2;

	// 0 <--> 1, 1 <--> 2 (2 fábricas en una punta)
	rutas2.push_back(ruta(0,1,5));
	rutas2.push_back(ruta(1,2,7));
	costoTotal = 0;
	vector<ruta> solucion2 = problema3(nodos, cantFabricas, rutas2);
	for (unsigned i = 0; i < solucion2.size(); ++i) {
    	costoTotal += costo(solucion2[i]);
    }
    EXPECT_EQ(7, costoTotal);
}

TEST(problema3, CasoDosSubconjuntos) {
	/*
	Representa el caso trivial en el cuál se consiguen 2 subconjuntos, cada uno
	de un cliente con su fábrica. (Prueba que no se unen subconjuntos con una fábrica)
	*/
	unsigned cantFabricas = 2;
	unsigned nodos = 4;
	vector<ruta> rutas1;
	//El grafo es un cuadrado, con los 2 nodos superiores como fábricas
	// 0 <--> 2, 0 <--> 1, 1 <--> 3, 2 <--> 3
	rutas1.push_back(ruta(0,2,4));
	rutas1.push_back(ruta(0,1,1));
	rutas1.push_back(ruta(1,3,5));
	rutas1.push_back(ruta(2,3,7));
	vector<ruta> solucion1 = problema3(nodos, cantFabricas, rutas1);
    unsigned costoTotal = 0;
    for (unsigned i = 0; i < solucion1.size(); ++i) {
    	costoTotal += costo(solucion1[i]);
    }
    EXPECT_EQ(9, costoTotal);

}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
