#include <iostream>

#include "gtest/gtest.h"
#include "problema2.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Funciones definidas en problema2.cpp. No se exportan en problema2.h
// para que no aparezcan en el apéndice del informe.
vector<unsigned> bfs(unsigned cant_nodos,
	                 vector<enlace> enlaces,
	                 nodo inicial);

vector<nodo> camino_entre_nodos(unsigned cant_nodos,
	                            vector<enlace> enlaces, 
	                            nodo inicial,
	                            nodo final);
///////////////////////////////////////////////////////////////////////////////

TEST(problema2, UnSoloNodo) {
	pair<nodo, vector<enlace>> res = problema2(1, vector<enlace>());

	EXPECT_EQ(0, res.first);
	EXPECT_EQ(0, res.second.size());
}

TEST(problema2, DosNodos) {
	vector<enlace> enlaces;
	enlaces.push_back(enlace(0, 1, 1));

	pair<nodo, vector<enlace>> res = problema2(2, enlaces);

	EXPECT_TRUE(res.first == 0 || res.first == 1);
	EXPECT_EQ(enlaces, res.second);
}

TEST(problema2, CasoGeneral) {
	// Ejemplo sacado de Introduction to Algorithms, por T. Cormen, pág. 632.
	vector<enlace> enlaces;
	enlaces.push_back(enlace(0, 1, 4));
	enlaces.push_back(enlace(1, 2, 8));
	enlaces.push_back(enlace(2, 3, 7));
	enlaces.push_back(enlace(3, 4, 9));
	enlaces.push_back(enlace(4, 5, 10));
	enlaces.push_back(enlace(5, 6, 2));
	enlaces.push_back(enlace(6, 7, 1));
	enlaces.push_back(enlace(0, 7, 8));	
	enlaces.push_back(enlace(7, 8, 7));
	enlaces.push_back(enlace(1, 7, 11));
	enlaces.push_back(enlace(2, 8, 2));
	enlaces.push_back(enlace(2, 5, 4));
	enlaces.push_back(enlace(3, 5, 14));
	enlaces.push_back(enlace(6, 8, 6));

	pair<nodo, vector<enlace>> res = problema2(9, enlaces);

	unsigned costo_total = 0;
	for(size_t i = 0; i < res.second.size(); i++) {
		costo_total += costo(res.second[i]);
	}
	
	EXPECT_EQ(37, costo_total);
	EXPECT_TRUE(res.first == 2 || res.first == 5);
}

TEST(problema2, BFS) {
	vector<enlace> enlaces;
	enlaces.push_back(enlace(0, 1, 4));
	enlaces.push_back(enlace(0, 2, 4));

	vector<unsigned> solucion = bfs(3, enlaces, 0);

	EXPECT_EQ(0, solucion[0]);
	EXPECT_EQ(1, solucion[1]);
	EXPECT_EQ(1, solucion[2]);
}

TEST(problema2, CaminoEntrePuntos) {
	vector<enlace> enlaces;
	enlaces.push_back(enlace(0,1,1));
	enlaces.push_back(enlace(0,2,1));
	enlaces.push_back(enlace(1,3,1));
	enlaces.push_back(enlace(1,4,1));
	enlaces.push_back(enlace(2,5,1));
	enlaces.push_back(enlace(2,6,1));

	vector<nodo> solucion = camino_entre_nodos(7, enlaces, 0, 6);

	EXPECT_EQ(6, solucion[0]);
	EXPECT_EQ(2, solucion[1]);
	EXPECT_EQ(0, solucion[2]);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
