#include<iostream>
#include"funkcije.h"
using namespace std;

int main() {
	int a, b, ulx, uly, izx, izy;
	ispis_glavnog_menija(a, b, ulx, uly, izx, izy);
	Lavirint lavirint(a, b, ulx, uly, izx, izy);
	int poz_ulaza = ulx * b + uly;
	int poz_izlaza = izx * b + izy;
	while (1) {
		int izbor;
		cout << "Unesite broj: ";
		cin >> izbor;
		switch (izbor) {
		case 1:
			lavirint.dodavanje_grana(); break;
		case 2:
			//uklanjanje grane;
			lavirint.sossss();
			cout << endl;
			lavirint.ispisidost();
			cout << endl; 
			lavirint.ispisiflojda();
			cout << endl;
			break;
		case 3:
			cout << lavirint; break;
		case 4: 
			nadji_resenje(lavirint);
			break;
		case 0:
			exit(10);
		}
	}
	return 0;
}