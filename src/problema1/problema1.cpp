#include "problema1.h"
using namespace std;

//Ti -> tarea a decidir dónde poner
//TM1 -> tarea actual en la máquina 1
//TM2 -> tarea actual en la máquina 2
int cost(int Ti, int TM1, int TM2, int cantTareas, 
		vector<vector<vector<int> > > &arrayMemoizacion,
		vector<vector<int> > &tablaCostos) {
 	//Si me paso de la cantidad de tareas, el resultado es 0
	if(Ti > cantTareas) {
		return 0;
	}
	//Si no, me fijo si ya computé este resultado (MEMOIZACION)
	else if(arrayMemoizacion[Ti][TM1][TM2] != 1) {
		return arrayMemoizacion[Ti][TM1][TM2];
	}
	//Si no lo tengo computado, hago la llamada recursiva
	else {
		arrayMemoizacion[Ti][TM1][TM2] = 
		min(cost(Ti + 1, Ti, TM2, cantTareas, arrayMemoizacion, tablaCostos) + tablaCostos[TM1][Ti], 
			cost(Ti + 1, TM1, Ti, cantTareas, arrayMemoizacion, tablaCostos) + tablaCostos[TM2][Ti]);
		return arrayMemoizacion[Ti][TM1][TM2];
	}
}

pair<int, vector<int> > problema1(int cantTareas, vector<vector<int> > tablaCostos) {
  vector<vector<vector<int> > > arrayMemoizacion;
  //Creo el arreglo de 3 dimensiones para guardar los resultados ya computados
  cantTareas+=2;
  arrayMemoizacion.resize(cantTareas);
  for (int i = 0; i < cantTareas; ++i) {
    arrayMemoizacion[i].resize(cantTareas);
    for (int j = 0; j < cantTareas; ++j)
      arrayMemoizacion[i][j].assign(cantTareas, -1);
  }

  //Lamar a cost y ver como recorrer la tabla armada para conseguir las tareas de una máquina
  int costo = cost(1,0,0,cantTareas,arrayMemoizacion,tablaCostos);
  //El return es cualquier bolazo, ni si quiera puede funcionar
  vector<int> v(1,1);
  return make_pair(costo, v);
}