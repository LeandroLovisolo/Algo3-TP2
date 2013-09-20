#include "problema1.h"
#include <iostream>
using namespace std;

//Ti -> tarea a decidir dónde poner
//TM1 -> tarea actual en la máquina 1
//TM2 -> tarea actual en la máquina 2
int cost(int Ti, int TM1, int TM2, int cantTareas, 
		vector<vector<int> > &arrayMemoizacion,
		vector<vector<int> > &tablaCostos, vector<int> &tareasM1) {
 	//Si me paso de la cantidad de tareas, el resultado es 0
	if(Ti == cantTareas) {
		return 0;
	}
	//Si no, me fijo si ya computé este resultado (MEMOIZACION)
	else if(arrayMemoizacion[TM1][TM2] != -1) {
		return arrayMemoizacion[TM1][TM2];
	}
	//Si no lo tengo computado, hago la llamada recursiva
	else {
		cout <<  "Hago una it" << endl;
		int costoPonerTiM1 = cost(Ti + 1, Ti, TM2, cantTareas, arrayMemoizacion, tablaCostos, tareasM1) + tablaCostos[Ti-1][TM1];
		int costoPonerTiM2 = cost(Ti + 1, TM1, Ti, cantTareas, arrayMemoizacion, tablaCostos, tareasM1) + tablaCostos[Ti-1][TM2];
		arrayMemoizacion[TM1][TM2] = min(costoPonerTiM1,costoPonerTiM2);
		//Agrego las tareas de la máquina 1
		if(costoPonerTiM1 <= costoPonerTiM2) {
			tareasM1.push_back(Ti);
		}
		return arrayMemoizacion[TM1][TM2];
	}
}

pair<int, vector<int> > problema1(int cantTareas, vector<vector<int> > tablaCostos) {
  vector<vector<int> >  arrayMemoizacion;
  vector<int> tareasM1;
  tareasM1.reserve(cantTareas);
  //Creo el arreglo de 3 dimensiones para guardar los resultados ya computados
  cantTareas++;
  arrayMemoizacion.resize(cantTareas);
    for (int j = 0; j < cantTareas; ++j) {
      arrayMemoizacion[j].assign(cantTareas, -1);
  }

  //Lamar a cost y ver como recorrer la tabla armada para conseguir las tareas de una máquina
  int costo = cost(1,0,0,cantTareas,arrayMemoizacion,tablaCostos,tareasM1);
  //El return es cualquier bolazo, ni si quiera puede funcionar
  return make_pair(costo, tareasM1);
}