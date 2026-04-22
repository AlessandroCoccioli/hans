#ifndef CARTA_H
#define CARTA_H

#include <iostream>
#include <string>
using namespace std;

class Carta{
private:
	int id;
	string razza;
	int valore;
	int uova;
	int medaglie;
public:
	Carta() : id(0), razza("vuota"), valore(0), uova(0), medaglie(0) {}
	
	Carta(int _id, string _razza, int _valore, int _uova, int _medaglie){
		id = _id;
		razza = _razza;
		valore = _valore;
		uova = _uova;
		medaglie = _medaglie;
	}
	
	string getRazza() const{ return razza; }
	int getValore() const{ return valore; }
	int getUova() const{ return uova; }
	int getMedaglie() const{ return medaglie; }
		
};

#endif