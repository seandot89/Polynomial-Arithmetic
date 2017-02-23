#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <map>



using namespace std;

#ifndef  PolyArith___REALLY_____LONG
#define PolyArith___REALLY_____LONG

template<class T>
class polyArith {
private:
	vector<map<int, int>>polyVector;
public:
	polyArith(string input, string output);
	void sum(ofstream &outFile);
	void difference(ofstream &outFile);
	void product(ofstream &outFile);
	void print(vector<map<int, int>>polyProduct, ofstream &outFile);
};

#endif