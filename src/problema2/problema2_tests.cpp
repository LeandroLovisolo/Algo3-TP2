#include <iostream>

#include "gtest/gtest.h"
#include "problema2.h"

using namespace std;

TEST(problema2, DevuelveArbolGeneradorMinimo) {
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

	pair<unsigned, vector<enlace>> res = problema2(9, enlaces);

	unsigned costo_total = 0;
	for(size_t i = 0; i < res.second.size(); i++) {
		costo_total += costo(res.second[i]);
	}

	EXPECT_EQ(37, costo_total);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}