#include <iostream>

#include "problema3.h"

using namespace std;

int main() {
    while(true) {
    
        // Leo la cantidad de fábricas.
        unsigned f;
        cin >> f;

        if(f == 0) break;

        // Leo la cantidad de clientes.
        unsigned c;
        cin >> c;

        // Leo la cantidad de rutas.
        unsigned r;
        cin >> r;

        // Ignoro el resto de la línea.
        string s;
        getline(cin, s);

        // Leo las rutas.
        vector<ruta> rutas;
        for(unsigned i = 0; i < r; i++) {
            unsigned a, b, c;
            cin >> a; // Leo nodo 1.
            cin >> b; // Leo nodo 2.
            cin >> c; // Leo costo de la ruta.
            rutas.push_back(ruta(a, b, c));

            // Ignoro el resto de la línea.
            getline(cin, s);            
        }

        // Resuelvo.
        vector<ruta> res = problema3(c + f, f, rutas);

        // Computo el costo total de la solución.
        unsigned costo_total = 0;
        for(unsigned i = 0; i < res.size(); i++) {
            costo_total += costo(res[i]);
        }

        // Imprimo costo total y cantidad de rutas.
        cout << costo_total << " " << res.size();

        // Imprimo las rutas utilizadas.
        for(unsigned i = 0; i < res.size(); i++) {
            cout << " " << nodo1(res[i]) << " " << nodo2(res[i]);
        }
        cout << endl;
    }

    return 0;
}