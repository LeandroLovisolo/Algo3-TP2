#include <iostream>

#include "problema2.h"

using namespace std;

int main() {
    while(true) {

        // Leo la cantidad de servidores.
        unsigned n;
        cin >> n;

        if(n == 0) break;

        // Ignoro el resto de la línea.
        string s;
        getline(cin, s);

        // Leo la cantidad de enlaces.
        unsigned m;
        cin >> m;

        // Ignoro el resto de la línea.
        getline(cin, s);

        // Leo los enlaces
        vector<enlace> enlaces;
        for(unsigned i = 0; i < m; i++) {
            unsigned a, b, c;
            cin >> a; // Leo nodo 1.
            cin >> b; // Leo nodo 2.
            cin >> c; // Leo costo del enlace.
            enlaces.push_back(enlace(a, b, c));

            // Ignoro el resto de la línea.
            getline(cin, s);        
        }

        // Resuelvo.
        pair<nodo, vector<enlace>> res = problema2(n, enlaces);

        // Computo el costo total de la solución.
        unsigned costo_total = 0;
        for(size_t i = 0; i < res.second.size(); i++) {
            costo_total += costo(res.second[i]);
        }

        // Imprimo costo total, nodo master y cantidad de enlaces.
        cout << costo_total << " " << res.first << " " << res.second.size();

        // Imprimo los enlaces utilizados.
        for(size_t i = 0; i < res.second.size(); i++) {
            cout << " " << nodo1(res.second[i]) << " " << nodo2(res.second[i]);
        }
        cout << endl;
    }

    return 0;
}