#include <iostream>
#include "problema3.h"
using namespace std;

int main() {
	vector<ruta> rutas;
	while(true) {
	    // Leo la cantidad de tareas.
	    unsigned cantFabricas, cantClientes, cantRutas;
	    cin >> cantFabricas;
	    // Termino el ciclo si la lectura anterior fracasó.
	    if(cin.eof()) break;
	    cin >> cantClientes;
	    cin >> cantRutas;

	    // Leo los costos de preparacion de los trabajos.
	    unsigned v1, v2, costo;
	    for(unsigned i = 0; i < cantRutas; i++) {
	    	cin >> v1;
	    	cin >> v2;
	    	cin >> costo;
	    	rutas.push_back(ruta(v1,v2,costo));
	    }

	    // Ignoro el resto de la línea (numero 0 y comentarios posteriores.)
	    //¿Qué onda esto?
	    //string s;
	    //getline(cin, s);

	    // Resuelvo el problema
	    unsigned costoTotal=0;
		vector<ruta> solucion = problema3(cantClientes + cantFabricas, cantFabricas, rutas);
		for(unsigned i = 0; i < solucion.size(); i++) {
			costoTotal += costo(solucion[i]);
		}
	    // Imprimo
	    cout << costoTotal << " " << solucion.size();
	    for(unsigned i = 0; i < solucion.size(); ++i) {
	    	cout << " " << nodo1(solucion[i]) << " " << nodo2(solucion[i]);
	    }
	    cout << endl;
	}
	return 0;
}
