#ifndef PROBLEMA2_H
#define PROBLEMA2_H

#include <vector>

struct enlace {
	unsigned _srv1;
    unsigned _srv2;
    unsigned _costo;
    enlace(unsigned srv1, unsigned srv2, unsigned costo){
    	_srv1 = srv1;
    	_srv2 = srv2;
    	_costo = costo;
    }
};

class Matriz{
	public:
		Matriz(vector<enlace> v, unsigned servidores);
        void set(unsigned fila, unsigned columna, unsigned valor);
        unsigned get(unsigned fila, unsigned columna);

	private:
		unsigned _servidores;
    	unsigned _enlaces;
        vector<unsigned> _matriz;
};

#endif // PROBLEMA2_H

