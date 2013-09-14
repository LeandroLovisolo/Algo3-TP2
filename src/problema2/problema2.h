#ifndef PROBLEMA2_H
#define PROBLEMA2_H

#include <vector>
using namespace std;
//Implementación de disjoint set
class Set {
private:
    Set *_parent;
    unsigned int _rank; //Para mantener los sets bien planos (menos complejidad)
    unsigned int _costo;
public:
    Set(unsigned int costo);
    Set *getRoot();
    unsigned int costo();
    //Ok, no se puede poner union como nombre de función en C++, hermoso
    void unionSet(Set &otherSet);
};

void problema2(vector<Set> &aristas);

/*
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
*/

#endif // PROBLEMA2_H

