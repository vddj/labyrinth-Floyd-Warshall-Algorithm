#ifndef _FUNCIJE_H_
#define _FUNCIJE_H_
#include<iostream>
using namespace std;

unsigned char* stvori_graf(unsigned char*, int);
void ispis_glavnog_menija(int&, int&, int&, int&, int&, int&);

class Lavirint {
	int n = 0, m = 0;
	int ulx, uly, izx, izy;
	int dimenzija;
	unsigned char* niz;
	unsigned char* matrica_dostiznosti = nullptr;
	short int* d, * t;
	int broj_cvorova;
	void dodaj_granu(int, int, int, int);
	void napravi_marticu_dostiznosti();
	void nadji_izlaz();
	void path(int, int);
public:
	Lavirint(int, int, int, int, int, int);
	void dodavanje_grana();
	friend void nadji_resenje(Lavirint&);
	friend ostream& operator<< (ostream&, Lavirint&);
	friend void Varsalov_algoritam(Lavirint&);
	friend void floyd(Lavirint&);
	bool operator[] (int);
	bool operator() (int);
	~Lavirint();

	void sossss() {
		for (int i = 0; i < n * m; i++) {
			for (int j = 0; j < n * m; j++) {
				if (i == j) cout << 0;
				else {
					int ii = i, jj = j;
					if (i < j) { ii = j; jj = i; }
					int b, c;
					b = ii * (ii - 1) / 2 + jj;
					c = b - 8 * (b >> 3);
					bool p = *(niz + (b >> 3))& (1 << (7 - c));
					cout << p;
				}
			}
			cout << endl;
		}
	}

	void ispisidost() {
		for (int i = 0; i < n * m; i++) {
			for (int j = 0; j < n * m; j++) {
				if (i == j) cout << 0;
				else {
					int ii = i, jj = j;
					if (i < j) { ii = j; jj = i; }
					int b, c;
					b = ii * (ii - 1) / 2 + jj;
					c = b - 8 * (b >> 3);
					bool p = *(matrica_dostiznosti + (b >> 3)) & (1 << (7 - c));
					cout << p;
				}
			}
			cout << endl;
		}
	}

	void ispisiflojda() {
		/*for (int i = 0; i < n * m; i++) {
			for (int j = 0; j < n * m; j++) cout << t[i*m+j];
			cout << endl;
			}*/
		}
};


#endif
