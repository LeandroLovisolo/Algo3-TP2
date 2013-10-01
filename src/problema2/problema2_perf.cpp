#include <cstdlib>

#include "gtest/gtest.h"
#include "medir.h"
#include "problema2.h"

using namespace std;

TEST(problema2, PerformanceCasoGeneral) {
    medir(string("perf/problema2/caso-general.csv"),
          1000,
          20,
          [&] (int n) {
              vector<enlace> enlaces;

              for(int i = 1; i < n; i++)
                  enlaces.push_back(enlace(0, i, 1));

              return problema2a(n, enlaces);
          },
          [&] (int n, const vector<enlace>& enlaces) { problema2b(n, enlaces); }
          );
}

TEST(problema2, PerformanceInstanciasAleatorias) {
    medir(string("perf/problema2/instancias-aleatorias.csv"),
          1000,
          20,
          [&] (int n) {
              vector<enlace> enlaces;

              for(int i = 1; i < n; i++) {
                  nodo nodo1, nodo2;

                  while(true) {
                      // Elijo dos nodos al azar
                      nodo1 = rand() % n;
                      nodo2 = rand() % n;

                      // Me aseguro que no exista un enlace entre ambos nodos
                      bool ya_existe = false;
                      for(size_t j = 0; j < enlaces.size(); j++) {
                          if((nodo1(enlaces[j]) == nodo1 && nodo2(enlaces[j]) == nodo2) ||
                             (nodo1(enlaces[j]) == nodo2 && nodo2(enlaces[j]) == nodo1)) {
                              ya_existe = true;
                              break;
                          }
                      }
                      if(!ya_existe) break;
                  }

                  enlaces.push_back(enlace(nodo1, nodo2, rand()));
              }

              return problema2a(n, enlaces);
          },
          [&] (int n, const vector<enlace>& enlaces) { problema2b(n, enlaces); }
          );
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
