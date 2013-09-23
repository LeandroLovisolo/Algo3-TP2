#include <iostream>

#include "problema1.h"

using namespace std;

int main() {
    while(true) {

        // Leo la cantidad de trabajos.
        unsigned n;
        cin >> n;

        // Ignoro el resto de la línea.
        string s;
        getline(cin, s);

        if(n == 0) break;

        // Leo la tabla de costos de preparación.
        costos c = crear_costos(n);
        for(int i = 0; i < (int) n; i++) {
            for(int j = i + 1; j <= (int) n; j++) {
                unsigned c_ij;
                cin >> c_ij;
                c[i][j] = c_ij;
            }
        }

        // Ignoro el resto de la línea.
        getline(cin, s);        

        // Resuelvo
        pair<costo, vector<trabajo>> res = problema1(n, c);

        // Imprimo costo hallado y cantidad de trabajos de una máquina.
        cout << res.first << " " << res.second.size();

        // Imprimo los trabajos de esa máquina.
        for(size_t i = 0; i < res.second.size(); i++)
            cout << " " << res.second[i];
        cout << endl;
    }

    return 0;
}