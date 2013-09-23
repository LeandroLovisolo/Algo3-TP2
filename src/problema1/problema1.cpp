#include "problema1.h"

using namespace std;

costos crear_costos(unsigned n) {
	return vector<vector<costo>>(n, vector<costo>(n + 1, 0));
}

pair<costo, vector<trabajo>> problema1(unsigned n, costos c) {

    // Tabla de tamaño n * n+1, inicialmente llena con ceros.
    vector<vector<costo>> dp(n, vector<costo>(n + 1, 0));

    // Recorro las columnas de derecha a izquierda.
    for(int j = n - 1; j >= 0; j--) {

        // Recorro las filas de arriba a abajo.
        for(int i = 0; i < (int) n; i++) {

            if(i == 0 && j == 0) {
                dp[0][0] = dp[0][1] + c[0][1]; // Única transición posible.
                break;
            }

            if(i == j) break; // Estados inválidos.

            // Calculo el camino de menor costo desde la posición actual
            // hasta una posición terminal, evaluando las dos únicas
            // transiciones posibles desde la posición actual.
            dp[i][j] = min(dp[i][j + 1] + c[j][j + 1],
                           dp[j][j + 1] + c[i][j + 1]);
        }
    }

    // La coordenada (0, 0) en nuestra tabla contiene el costo del camino
    // mínimo entre la posición inicial hasta alguna posición terminal.
    costo costo_minimo = dp[0][0];

    // Cola de trabajos de una de las máquinas.
    vector<trabajo> trabajos;

    // Agregamos el primer trabajo a la máquina.
    trabajos.push_back(1);

    // Luego de agregar el primer trabajo a la máquina, recorremos la tabla
    // desde la posición (0, 1), avanzando por los caminos de menor costo
    // hasta llegar a una posición terminal.
    int i = 0, j = 1;

    // Ciclamos hasta haber agregado el n-ésimo trabajo.
    while(j < (int) n) {

        // Avanzamos desde [i][j] hasta [i][j + 1].
        if(dp[i][j] == dp[i][j + 1] + c[j][j + 1]) {
            if(trabajos.back() == (trabajo) j) trabajos.push_back(j + 1);
            j++;
        } 

        // Avanzamos desde [i][j] hasta [j][j + 1].
        else {
            if(trabajos.back() == (trabajo) i) trabajos.push_back(j + 1);
            i = j;
            j++;
        }
    }

    return make_pair(costo_minimo, trabajos);
}