#include "problema1.h"
#include <iostream>
using namespace std;

//Ti -> tarea a decidir dónde poner
//TM1 -> tarea actual en la máquina 1
//TM2 -> tarea actual en la máquina 2
int cost(int Ti, int TM1, int TM2, int cantTareas, 
		vector<vector<vector<int> > > &arrayMemoizacion,
		vector<vector<int> > &tablaCostos) {
 	//Si me paso de la cantidad de tareas, el resultado es 0
 	cout << "Tarea a poner: " << Ti << endl;
	if(Ti == cantTareas) {
		cout << "Llego al final, devuelvo 0" << endl;
		return 0;
	}
	//Si no, me fijo si ya computé este resultado (MEMOIZACION)
	else if(arrayMemoizacion[Ti][TM1][TM2] != -1) {
		cout << "Ya compute este resultado ["<< Ti <<"]["<< TM1 <<"]["<<TM2<<"], es = " << arrayMemoizacion[Ti][TM1][TM2] << endl;
		return arrayMemoizacion[Ti][TM1][TM2];
	}
	//Si no lo tengo computado, hago la llamada recursiva
	else {
		cout << "No compute este resultado, poner " << Ti <<" dado M1 = "<< TM1 <<" y M2 = "<<TM2<<"" << endl;
		int costoPonerTiM1 = cost(Ti + 1, Ti, TM2, cantTareas, arrayMemoizacion, tablaCostos) + tablaCostos[Ti-1][TM1];
		int costoPonerTiM2 = cost(Ti + 1, TM1, Ti, cantTareas, arrayMemoizacion, tablaCostos) + tablaCostos[Ti-1][TM2];
		arrayMemoizacion[Ti][TM1][TM2] = min(costoPonerTiM1,costoPonerTiM2);
		if(costoPonerTiM1 <= costoPonerTiM2) {
			cout << "Elijo poner la tarea " << Ti << " en la M1" << endl;
		}
		else {
			cout << "Elijo poner la tarea " << Ti << " en la M2" << endl;	
		}
		return arrayMemoizacion[Ti][TM1][TM2];
	}
}

pair<int, vector<int> > problema1(int cantTareas, vector<vector<int> > tablaCostos) {
  vector<vector<vector<int> > > arrayMemoizacion;
  //Creo el arreglo de 3 dimensiones para guardar los resultados ya computados
  cantTareas++;
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