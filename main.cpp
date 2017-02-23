#include <cstdlib>
#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include "PolynomialArithmeticRedux.h"
using namespace std;



template<class T>
polyArith<T>::polyArith(string input, string output) {

	fstream inFile(input);
	ofstream outFile(output);
	string line;
	int exp;
	int coef;
	int maxExp = 0;
	map<int, int>pMap;
	outFile << "Polynomial Calculator" << endl << endl;
	outFile << "Polynomials as they appear in the file: " << endl;
	while (getline(inFile, line)) {

		bool firstPoly = true;
		istringstream in(line);
		while (in >> coef) {
			in >> exp;
			if (exp > maxExp) {
				maxExp = exp;
			}
			pMap[exp] += coef;

			//Printing input data in its raw form
			if (firstPoly&&exp != 0) {
				firstPoly = false;
				outFile << coef << "X^" << exp;
			}

			else if (firstPoly&&exp == 0) {
				firstPoly = false;
				outFile << coef;
			}

			else if (exp != 0) {
				if (coef < 0)
					outFile << coef << "x^" << exp;

				if (coef > 0)
					outFile << "+" << coef << "x^" << exp;
			}

			else if (exp == 0) {
				if (coef < 0)
					outFile << coef;

				if (coef > 0)
					outFile << "+" << coef;
			}
		}
		outFile << endl;
		polyVector.push_back(pMap);
		pMap.clear();
	}

	outFile << endl << "Polynomials in canonical form: " << endl;
	print(polyVector, outFile);
	sum(outFile);
	difference(outFile);
	product(outFile);


}

template <typename Iter>
Iter next(Iter iter)
{
	return ++iter;
}

template<class T>
void polyArith<T>::sum(ofstream &outFile) {

	vector<map<int, int>>polySum;
	//calculate sum and store into polySum
	for (int i = 0; i < polyVector.size(); i += 2) {
		map<int, int>pSum;
		pSum = polyVector[i];


		for (map<int, int>::iterator it1 = polyVector[i + 1].begin(); it1 != polyVector[i + 1].end(); it1++) {

			pSum[it1->first] += it1->second;

		}

		polySum.push_back(pSum);
	}

	outFile << endl << "The sum of each pair of polynomials is:" << endl;
	print(polySum, outFile);
}

template<class T>
void polyArith<T>::difference(ofstream &outFile) {

	vector<map<int, int>>polyDif;
	for (int i = 0; i < polyVector.size(); i += 2) {
		map<int, int>pDif;
		pDif = polyVector[i];


		for (map<int, int>::iterator it1 = polyVector[i + 1].begin(); it1 != polyVector[i + 1].end(); it1++) {

			pDif[it1->first] -= it1->second;

		}

		polyDif.push_back(pDif);
	}

	outFile << endl << "The difference of each pair of polynomials is:" << endl;
	print(polyDif, outFile);
}

template<class T>
void polyArith<T>::product(ofstream &outFile) {
	vector<map<int, int>>polyProduct;
	int tempCoef;
	int tempExp;

	for (int i = 0; i < polyVector.size(); i += 2) {
		map<int, int>pProd;
		for (auto it = polyVector[i].begin(); it != polyVector[i].end(); it++) {
			for (auto it2 = polyVector[i + 1].begin(); it2 != polyVector[i + 1].end(); it2++) {
				tempExp = it->first + it2->first;
				tempCoef = it->second*it2->second;

				pProd[tempExp] += tempCoef;
			}
		}
		polyProduct.push_back(pProd);
	}//for
	outFile << endl << "The product of each pair of polynomials is:" << endl;
	print(polyProduct, outFile);
}

template<class T>
void polyArith<T>::print(vector<map<int, int>>poly, ofstream &outFile) {

	for (int i = 0; i < poly.size(); i++) {
		for (auto it = poly[i].rbegin(); it != poly[i].rend(); it++) {


			if (it->first == 0) {

				if (::next(it) == poly[i].rend()) {
					outFile << it->second;
				}
				else if (::next(it)->second < 0)
					outFile << it->second;
				else
					outFile << it->second << "+";
			}

			else {
				if (::next(it) == poly[i].rend()) {
					outFile << it->second << "X^" << it->first;
				}
				else if (::next(it)->second < 0)
					outFile << it->second << "X^" << it->first;
				else
					outFile << it->second << "X^" << it->first << "+";
			}
		}
		outFile << endl;
	}
}

int main() {

	polyArith<int>p("input.txt", "output.txt");

}