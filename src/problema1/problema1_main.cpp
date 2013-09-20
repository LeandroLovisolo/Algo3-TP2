#include <iostream>
#include "problema1.h"


using namespace std;
int main() {
	while(true) {
        vector<vector<int> > tablaCostos;

        // Leo la cantidad de tareas.
        int cantTareas;
        cin >> cantTareas;

        // Termino el ciclo si la lectura anterior fracasó.
        if(cin.eof()) break;

        // Leo los costos de preparacion de los trabajos.
        for(int i = 0; i < cantTareas; i++) {
        	for (int j = 0; j <= i; ++j) {
        		int costo;
            	cin >> costo;
            	tablaCostos[i].push_back(costo);
        	}
        }

        // Ignoro el resto de la línea (numero 0 y comentarios posteriores.)
        string s;
        getline(cin, s);

        // Resuelvo el problema
        pair<int, vector<int> > solucion = problema1(cantTareas, tablaCostos);

        // Imprimo
        cout << get<0>(solucion);
 

	}
}
