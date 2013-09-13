#include "problema2.h"

using namespace std;

Matriz::Matriz(vector<enlace> v, unsigned servidores)
		: _matriz(servidores * servidores, 0) {
	_servidores = servidores;
	_enlaces = v.size();
	for (int i = 0; i < _enlaces; ++i) {
		set(v[i]._srv1,v[i]._srv2,v[i]._costo);
	}

}

void Matriz::set(unsigned fila, unsigned columna, unsigned valor) {
	_matriz[_servidores * fila + columna] = valor;
	_matriz[_servidores * columna + fila] = valor;
}

unsigned Matriz::get(unsigned fila, unsigned columna) {
	return _matriz[_servidores * fila + columna];
}

