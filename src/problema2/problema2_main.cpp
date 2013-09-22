#include <iostream>
#include "problema2.h"

using namespace std;

int main() {
	while(true) {
		vector<enlace> enlaces;
	    // Leo la cantidad de tareas.
	    unsigned cantServidores, cantEnlaces;
	    cin >> cantServidores;
	    // Termino el ciclo si la lectura anterior fracasó.
	    if(cin.eof()) break;
	    cin >> cantEnlaces;
	    // Leo los costos de preparacion de los trabajos.
	    unsigned v1, v2, costo;
	    for(unsigned i = 0; i < cantEnlaces; i++) {
	    	cin >> v1;
	    	cin >> v2;
	    	cin >> costo;
	    	enlaces.push_back(enlace(v1,v2,costo));
	    }

	    // Ignoro el resto de la línea (numero 0 y comentarios posteriores.)
	    //¿Qué onda esto?
	    //string s;
	    //getline(cin, s);

	    // Resuelvo el problema
	    unsigned costoTotal=0;
		pair<unsigned, vector<enlace> > solucion = problema2(cantServidores, enlaces);
		for(unsigned i = 0; i < solucion.second.size(); i++) {
			costoTotal += costo(solucion.second[i]);
		}
	    // Imprimo
	    cout << costoTotal << " " << solucion.first << " " << solucion.second.size();
	    for(unsigned i = 0; i < solucion.second.size(); ++i) {
	    	cout << " " << nodo1(solucion.second[i]) << " " << nodo2(solucion.second[i]);
	    }
	    cout << endl;
	}
    return 0;
}
