#include"funkcije.h"
#include<iostream>
using namespace std;

int max(int a, int b) {
	return (a > b) ? a : b;
}
int min(int a, int b) {
	return (a < b) ? a : b;
}
int index(int i, int k) {
	return max(i, k) * (max(i, k) - 1) / 2 + min(i, k);
}

void Lavirint::path(int i, int j) {
	if (i == j) { cout << i + 1; return; }
	else {
		path(i, t[i * m + j]);
		cout << j + 1;
	}
}

void ispis_glavnog_menija(int& a, int& b, int& ulx, int& uly, int& izx, int& izy)
{
	cout << "________________________________________________" << endl;
	cout << "| 1-dodavanje grana 2-uklanjanje grane 3-ispis  |" << endl;
	cout << "|     4-nadji put 0-izlazak iz programa         |" << endl;
	cout << "|_______________________________________________|" << endl;
	cout << " Na pocetku, unesite dimenzije lavirinta: ";
	//cin >> a; cin >> b;
	a = 3; b = 5;
	//cout << "Koordinate ulaza: "; cin >> ulx; cin >> uly; 
	//cout << "Koordinate izlaza: "; cin >> izx; cin >> izy;
	cout << "_________________________________________________" << endl;
	ulx = uly = 0; izx = 1; izy = 0;
}

unsigned char* stvori_graf(unsigned char* niz, int dim) {
	niz = new unsigned char[dim];
	for (int i = 0; i < dim; i++) niz[i] = 0;
	return niz;
}

void Lavirint::dodaj_granu(int x1, int y1, int x2, int y2){
	int i = x1 * m + y1;
	int j = x2 * m + y2;
	if (i < j) { int pom = i; i = j; j = pom; }
	unsigned short int b, c;
	b = i * (i - 1) / 2 + j;
	c = b - 8 * (b >> 3);
	*(niz + (b >> 3)) |= (1 << (7 - c));
}

void Lavirint::napravi_marticu_dostiznosti(){
	for (int i = 0; i < dimenzija; i++)
	matrica_dostiznosti[i] = niz[i];
}

void Varsalov_algoritam(Lavirint& lav) {
	for (int k = 0; k < lav.broj_cvorova; k++)
		for (int i = 0; i < lav.broj_cvorova; i++) 
			for (int j = 0; j < lav.broj_cvorova; j++) {
				if (!lav(index(i, j)) && lav(index(i, k)) && lav(index(k, j))) {
					if (i != j) {
						int b = index(i, j);
						int c = b - 8 * (b >> 3);
						*(lav.matrica_dostiznosti + (b >> 3)) |= (1 << (7 - c));
					}
				}
			}
}

void Lavirint::nadji_izlaz() {
	int i = izx * m + izy;
	int j = ulx * m + uly;
	if (i < j) { int pom = i; i = j; j = pom; }
	unsigned short int b, c;
	b = i * (i - 1) / 2 + j;
	c = b - 8 * (b >> 3);
	bool pom = *(matrica_dostiznosti + (b >> 3))& (1 << (7 - c));
	if (pom) {
		cout << "Ima resenja";
		floyd(*this);
		path(i, j);
	}
	else cout << "nema resenja";
	cout << endl;
}

Lavirint::Lavirint(int _a, int _b, int _ulx, int _uly, int _izx, int _izy){
	n = _a; m = _b;
	dimenzija = ((n * n * m * m / 2 - n * m) >> 3) + 3;
	broj_cvorova = m * n;
	niz = new unsigned char[dimenzija];
	matrica_dostiznosti = new unsigned char[dimenzija];
	ulx = _ulx, uly = _uly, izx = _izx, izy = _izy;
	for (int i = 0; i < dimenzija; i++) niz[i] = 0;
}

void Lavirint::dodavanje_grana(){
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	while (1) {
		cout << "Unesite koordinate prvog cvora: ";
		cin >> x1; cin >> y1;
		if (x1 >= n || y1 >= m) break;
		cout << "Unesite koordinate drugog cvora: ";
		cin >> x2; cin >> y2;
		if (x1 != x2 && y1 != y2) break;
		dodaj_granu(x1, y1, x2, y2);
	}
}

void nadji_resenje(Lavirint& lav){
	lav.napravi_marticu_dostiznosti();
	Varsalov_algoritam(lav);
	lav.nadji_izlaz();
}

bool Lavirint::operator[](int indeks) {
	int c;
	c = indeks - 8 * (indeks >> 3);
	return *(niz + (indeks >> 3)) & (1 << (7 - c));
}

bool Lavirint::operator()(int indeks) {
	int c;
	c = indeks - 8 * (indeks >> 3);
	return *(matrica_dostiznosti + (indeks >> 3)) & (1 << (7 - c));
}

Lavirint::~Lavirint() {
	delete[] niz;
	delete[] matrica_dostiznosti;
	delete[] d;
	delete[] t;
}

ostream& operator<< (ostream& os, Lavirint& lav) {
	int izlaz = lav.izx * lav.m + lav.izy;
	int ulaz = lav.ulx * lav.m + lav.uly;
	for (int i = 0; i < lav.m; i++) {
		if (i == izlaz) cout << " i";
		else if (i == ulaz) cout << " u";
		else os << " _";
	}
	os << endl;
	int b;
	for (int i = 0; i < lav.n * lav.m; i++) {
		if (i % lav.m == 0) {
			if (i == izlaz) cout << 'i';
			else if (i == ulaz && i != 0) cout << 'u';
			else os << "|";
		}
		if (i >= (lav.n - 1) * lav.m) {
			if (i == izlaz) cout << "i";
			else if (i == ulaz) cout << "u";
			else os << "_";
		}
		else {
			b = (i + lav.m) * (i + lav.m - 1) / 2 + i;
			if (!lav[b]) os << "_";
			else os << " ";
		}
		if (i % lav.m == lav.m-1) {
			if (i == izlaz) cout << 'i';
			else if (i == ulaz) cout << 'u';
			else os << "|";
		}
		else {
			b = i * (i + 3) / 2;
			if (!lav[b]) os << "|";
			else os << " ";
		}
		if (i % lav.m == lav.m - 1) os << endl;
	}
	return os;
}

void floyd(Lavirint& lav) {
	int dim = lav.broj_cvorova * lav.broj_cvorova;
	lav.d = new short int[dim];
	lav.t = new short int[dim];
	for (int i = 0; i < lav.broj_cvorova; i++) {
		for (int j = 0; j < lav.broj_cvorova; j++) {
			int cvor = i * lav.broj_cvorova + j;
			if (i == j) {
				lav.d[cvor] = 0; lav.t[cvor] = 0;
			}
			else {
				lav.t[cvor] = i +1;
				if (lav[index(i, j)]) {
					lav.d[cvor] = 0xFFFF;
					lav.t[cvor] = 0;
				}
				else lav.d[cvor] = 1;
			}
		}
	}

	for (int k = 0; k < lav.broj_cvorova; k++)
		for (int i = 0; i < lav.broj_cvorova; i++)
			for (int j = 0; j < lav.broj_cvorova; j++)
				if (lav.d[i * lav.m + j] > lav.d[i * lav.m + k] + lav.d[k * lav.m + j]) {
					lav.t[i * lav.m + j] = lav.t[k * lav.m + j];
					lav.d[i * lav.m + j] = lav.d[i * lav.m + k] + lav.d[k * lav.m + j];
				}
}