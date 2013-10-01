#include <cstdlib>

#include "gtest/gtest.h"
#include "medir.h"
#include "problema1.h"

using namespace std;

TEST(problema1, PerformanceCasoGeneral) {
    medir(string("perf/problema1/caso-general.csv"),
          1000,
          20,
          [&] (int n) {
              costos c = crear_costos(n);
              costo k = 1;
              for(int i = 0; i < n; i++) {
                  for(int j = i + 1; j <= n; j++) {
                    c[i][j] = k;
                    k++;
                  }
              }
              return c;
          },
          [&] (int n, const costos& c) { problema1(n, c); }
          );
}

TEST(problema1, PerformanceInstanciasAleatorias) {
    medir(string("perf/problema1/instancias-aleatorias.csv"),
          1000,
          20,
          [&] (int n) {
              costos c = crear_costos(n);
              for(int i = 0; i < n; i++) {
                  for(int j = i + 1; j <= n; j++) {
                    c[i][j] = rand();
                  }
              }
              return c;
          },
          [&] (int n, const costos& c) { problema1(n, c); }
          );
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
