#include "pch.h"
#include <iostream>
#include<fstream>
#include<string>
#include<math.h>

using namespace std;

const double epsilon=pow(10, -6);



class Matrica {

private:
	int dim_n; //broj redaka
	int dim_m; //broj stupaca
	double** el;

	int transponirana; //ako se transponira postati ce 1 da se moze pravilno koristiti destruktor

public:
	Matrica();//defaultni konstruktor
	Matrica(const int&, const int&); //konstruktor koji postavlja na neke vrijednosti

	~Matrica(); //destruktor

	Matrica& operator= (const Matrica&); //mogli smo ovo i pomocu kopirnog konstruktora
	bool operator== (const Matrica&);

	int GetDimN();
	int GetDimM();
	int Zbroji(Matrica&, Matrica&);
	int Oduzmi(Matrica&, Matrica&);
	int Mnozi(Matrica&, Matrica&);
	void Transponiraj();

	void SetRowsAndColumns(int, int);//uz ovo imamo i konstruktor koji postavlja na neke vrijednosti, a ovo kad mijenjamo
	void SetRowsAndColumnsWithFile(string);
	void AllocateMemoryForElements();
	void DeallocateMemoryForElements();
	void ReadElementsFromFile(string);
	double GetElement(int, int); //jer su element privatni pa da ih mogu dohvatiti
	void SetElement(int, int, double);
	// void Print(); //postignuto pomocu preopterecenja operatora <<
	void PrintInFile(string);
	void MnoziSkalarom(double);
	void DijeliSkalarom(double);
	string LU(); //vraca ime foldera u koji smo spremili rjesenje
	string LUP(Matrica&);
	string SupstUnaprijed(Matrica&);
	string SupstUnatrag(Matrica&);
	Matrica& VratiRedak(int, Matrica&);
	void PostaviRedak(Matrica&, int); //na koje elemente i koji tocno redak
	Matrica& VratiStupac(int, Matrica&);
	int PositionOfMaxElInVector(int, int);

	friend ostream& operator << (ostream& s, Matrica& A);
	friend void operator +=(Matrica& A, Matrica& B);
	friend void operator -=(Matrica& A, Matrica& B);

};

Matrica::Matrica() //defaultni konstruktor
{
	dim_m = 1;
	dim_n = 1;

	transponirana = 0;

	AllocateMemoryForElements();

	el[0][0] = 0; //postavljamo sve elemente na nulu

}

Matrica::Matrica(const int& number1, const int& number2) //konstruktor koji postavlja dimenzije na neke vrijednosti
{
	dim_n = number1;
	dim_m = number2;

	transponirana = 0;

	AllocateMemoryForElements();

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			el[i][j] = 0; //postavljamo sve elemente na nulu
		}
	}
}

Matrica:: ~Matrica() //destruktor
{
	/*if (transponirana == 1)
	{
		for (int i = 0; i < dim_m; i++)
		{
			delete[] el[i];
		}

		delete[] el;
	}

	else
	{
		for (int i = 0; i < dim_n; i++)
		{
			delete[] el[i];
		}

		delete[] el;
	} */

}

double Matrica::GetElement(int i, int j)
{
	return el[i][j];
}

void Matrica::SetElement(int i, int j, double number)
{
	el[i][j] = number;
}

int Matrica::GetDimN()
{
	return dim_n;
}

int Matrica::GetDimM()
{
	return dim_m;
}

int Matrica::Zbroji(Matrica& A, Matrica& B)
{

	if (A.dim_n != B.dim_n || A.dim_n != B.dim_n)
	{
		cout << "Error" << endl;
		return -1;
	}


	dim_n = A.dim_n; //ili B.dim_n --> svejedno...
	dim_m = A.dim_m;

	el = new double*[dim_n];

	for (int i = 0; i < dim_n; i++)
		el[i] = new double[dim_m];

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			el[i][j] = A.el[i][j] + B.el[i][j];
		}
	}
}

int Matrica::Oduzmi(Matrica& A, Matrica& B)
{
	if (A.dim_n != B.dim_n || A.dim_n != B.dim_n)
		return -1;

	dim_n = A.dim_n; //ili B.dim_n --> svejedno...
	dim_m = A.dim_m;

	el = new double*[dim_n];

	for (int i = 0; i < dim_n; i++)
		el[i] = new double[dim_m];

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			el[i][j] = A.el[i][j] - B.el[i][j];
		}
	}
}

int Matrica::Mnozi(Matrica& A, Matrica& B)
{
	int equal;
	Matrica C;

	if (A.dim_m != B.dim_n)
	{
		cout << "Error! These matrices can not be multiplied!" << endl;
		return -1;
	}

	dim_n = A.dim_n; //bitno da bude bas A
	dim_m = B.dim_m; //bitno da bude bas B

	equal = A.dim_m; //ode moglo i B.dim_n

	el = new double*[dim_n];

	for (int i = 0; i < dim_n; i++)
		el[i] = new double[dim_m];

	for (int i = 0; i < dim_n; ++i)
		for (int j = 0; j < dim_m; ++j)
		{
			el[i][j] = 0; //postavit sve elemente na nulu
		}

	for (int i = 0; i < dim_n; i++)
		for (int j = 0; j < dim_m; j++)
			for (int k = 0; k < equal; k++)
			{
				el[i][j] = el[i][j] + A.el[i][k] * B.el[k][j];
			}
}

void Matrica::Transponiraj()
{
	Matrica B(dim_m, dim_n); //pomocna matrica koju cemo poslije samo prekopirat u izvornu,obrnili dimenzije
	double pom;
	B.transponirana = 1;

	for (int i = 0; i < dim_m; i++)
	{
		for (int j = 0; j < dim_n; j++)
		{
			B.el[i][j] = el[j][i];
		}
	}
	*this = B;
	transponirana = 1;
}

void Matrica::MnoziSkalarom(double scalar)
{
	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			el[i][j] = el[i][j] * scalar;
		}
	}
}

void Matrica::DijeliSkalarom(double scalar)
{
	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			el[i][j] = el[i][j] / scalar;
		}
	}
}

ostream& operator<< (ostream& s, Matrica& A)
{
	s << endl;

	s << "dim(" << A.dim_n << " x " << A.dim_m << ")" << endl;

	for (int i = 0; i < A.dim_m; i++)
	{
		s << "_____________";
	}

	s << endl << endl;
	for (int i = 0; i < A.dim_n; i++)
	{
		for (int j = 0; j < A.dim_m; j++)
		{
			s << A.el[i][j] << "		";
		}
		s << endl << endl;
	}

	for (int i = 0; i < A.dim_m; i++)
	{
		s << "_____________";
	}

	s << endl << endl;

	return s;
}

void operator +=(Matrica& A, Matrica& B) //napomena
{
	for (int i = 0; i < A.dim_n; i++)
	{
		for (int j = 0; j < A.dim_m; j++)
		{
			A.el[i][j] = A.el[i][j] + B.el[i][j];
		}
	}
}

void operator -=(Matrica& A, Matrica& B) //napomena
{
	for (int i = 0; i < A.dim_n; i++)
	{
		for (int j = 0; j < A.dim_m; j++)
		{
			A.el[i][j] = A.el[i][j] - B.el[i][j];
		}
	}
}

Matrica& Matrica:: operator= (const Matrica& B) // ovaj operator cilu jednu matricu izjednačit s drugom matricom, mogli i preko kopirnog kosntruktora
{
	DeallocateMemoryForElements();

	dim_n = B.dim_n;
	dim_m = B.dim_m;

	AllocateMemoryForElements();

	for (int i = 0; i < dim_n; i++)
		for (int j = 0; j < dim_m; j++)
		{
			el[i][j] = B.el[i][j];
		}

	return *this; // vraćamo *this zbog nadovezivanja
}

bool Matrica:: operator== (const Matrica& B) //matrice su jednake ako su jednakih dimenzija i jednakih elemenata
{

	if (dim_n != B.dim_n || dim_m != B.dim_m) //cim dimenzije nisu jednake to odmah znaci da nisu jednaki
	{
		return false;
	}

	for (int i = 0; i < dim_n; i++) //ako su dimenzije jednake mozda se razlikuju u nekom od brojeva
		for (int j = 0; j < dim_m; j++)
		{
			if (abs(el[i][j] - B.el[i][j]) > epsilon)
				return false;
		}
	return true;
}
void Matrica::SetRowsAndColumns(int n, int m)
{
	dim_n = n;
	dim_m = m;

	AllocateMemoryForElements();
}
void Matrica::SetRowsAndColumnsWithFile(string a)
{
	ifstream f; //ofstream je za pisanje
	double b;
	string line;
	int number_of_rows = 0; //broj redaka
	int number_of_elements = 0;
	int number_of_columns; //broj stupaca

	f.open(a);

	if (!f.is_open())
	{
		cout << "Error: file can not be open!" << endl;
	}

	while (!f.eof())
	{
		f >> b;

		number_of_elements++;
	}

	f.seekg(0, ios::beg); //da se vratimo na pocetak datoteke

	while (getline(f, line))
		number_of_rows++;

	number_of_columns = number_of_elements / number_of_rows;

	dim_n = number_of_rows;
	dim_m = number_of_columns;

	AllocateMemoryForElements();

	f.close();
}

void Matrica::AllocateMemoryForElements()
{
	el = new double*[dim_n];

	for (int i = 0; i < dim_n; i++)
		el[i] = new double[dim_m];

	/* el = (double **) malloc(dim_n * sizeof(double *));
	 for (int i = 0; i < dim_n; i++)
		 el[i] = (double *)malloc(dim_m * sizeof(double));*/
}

void Matrica::DeallocateMemoryForElements()
{
	if (transponirana == 1)
	{
		for (int i = 0; i < dim_m; i++)
		{
			delete[] el[i];
		}

		delete[] el;
	}

	else
	{
		for (int i = 0; i < dim_n; i++)
		{
			delete[] el[i];
		}

		delete[] el;
	}
}


/* void Matrica::Print() //nije bilo potrebno jer smo preopteretili operator <<
{
	cout << endl << endl;

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m ; j++)
		{
			cout << el[i][j] << "	" ; // ili *(*(el+i)+j)
		}

		cout << endl;
	}

	cout << endl;
}*/

void Matrica::PrintInFile(string a)
{
	ofstream f;

	f.open(a);

	if (!f.is_open())
	{
		cout << "Error: file can not be open!" << endl;
	}

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			f << el[i][j];// ili *(*(el+i)+j) 
			f << "	";
		}
		f << endl;
	}
}

void Matrica::ReadElementsFromFile(string a)
{
	ifstream f; //ofstream je za pisanje
	double b;
	string line;
	int i = 0, j = 0;

	f.open(a);

	if (!f.is_open())
	{
		cout << "Error: file can not be open!" << endl;
	}

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			f >> el[i][j];
		}
	}

	f.close();
}

string Matrica::LU()
{
	string a;
	cout << endl << "RADI SE SUPSTITUCIJA LU" << endl;
	cout << "Unesite ime datoteke u koju cete zapisati postupak ovog LU-a" << endl;
	cin >> a;
	a = a + ".txt";
	ofstream f(a); //ios::app da pise na kraj, a ne da je prepise s novim

	if (!f)
	{
		cout << "Error LU-can't open file! ";
		return "error_cant_open_file";
	}

	f << endl << "RADI LU nad matricom" << *this << endl;

	if (dim_n != dim_m)
	{
		f << "Error LU! Matrica nije kvadratna!" << endl;
		return "error_u_dimenziji";
	}

	for (int i = 0; i < dim_n - 1; i++)
	{
		f << endl << "=> Sljedeca iteracija" << endl << *this << endl;

		for (int j = i + 1; j < dim_n; j++)
		{
			f << "(dijelimo " << el[j][i] << " s pivotom: " << el[i][i] << " i dobijemo " << el[j][i] / el[i][i] << ")" << endl;

			el[j][i] = (el[j][i] / el[i][i]);

			for (int k = i + 1; k < dim_n; k++)
			{
				el[j][k] -= (el[j][i] * el[i][k]);
			}
		}
	}

	return a;
}

string Matrica::LUP(Matrica& b)
{	
	Matrica P(dim_n, dim_n);
	Matrica s1, s2;
	int brojac = 1;
	int R; // u kojem se retku nalazi pivot element

	string a;
	cout << endl << endl << endl << "RADI SE SUPSTITUCIJA LUP" << endl;
	cout << "Unesite ime datoteke u koju cete zapisati postupak ovog LUP-a" << endl;
	cin >> a;
	a = a + ".txt";
	ofstream f(a); //ios::app da pise na kraj, a ne da je prepise s novim

	if (!f)
	{
		cout << "Error LUP-can't open file! ";
		return "error";
	}

	f << endl << "RADI LUP nad matricom" << *this << endl;

	if (dim_n != dim_m)
	{
		f << "Error1 LUP! Matrica nije kvadratna!" << endl;
		return "error";
	}

	/* PERMUTACIJSKA MATRICA
	
	for (int i = 0; i < dim_n; i++)
	{
		P.el[i][i] = 1;
	} */

	for (int i = 0; i < dim_n; i++) //mogli staviti i dim_j
	{
			R = PositionOfMaxElInVector(i, i); //broj retka di je max el u stupcu; saljemo koji redak i koji stupac gledamo

			f << "-Odabran je pivot:" << el[R][i] << endl;

			//zamjeni retke u P matrici
			b.VratiRedak(i, s1); //koji redak i gdje ga spremam (u s1)
			b.VratiRedak(R, s2);
			b.PostaviRedak(s1, R);
			b.PostaviRedak(s2, i);

			//zamjeni stupce u A matrici
			VratiRedak(i, s1);
			VratiRedak(R, s2);
			PostaviRedak(s1, R);
			PostaviRedak(s2, i);

			if (abs(el[i][i]) < epsilon) //sad zaminila a moram prominit indexe
			{
				f << "Error LUP! Pivotni element" << el[R][i] << " je 0 (ili gotovo 0!) !" << endl;
				return "error";
			}

			f << endl << "Iteracija " << brojac++ << " : " <<endl << *this << endl;

			for (int j = i + 1; j < dim_n; j++)
			{
				f << "(dijelimo " << el[j][i] << " s pivotom: " << el[i][i] << " i dobijemo " << el[j][i] / el[i][i] << ")" << endl;

				if (el[i][i] == 0 || abs(el[i][i]) < epsilon)
				{
					f << "Error LUP! Ne moze se dijeliti s nula!" << endl;
					return "error";
				}
				
				el[j][i] /= el[i][i];

				for (int k = i + 1; k < dim_n; k++)
				{
					el[j][k] -= (el[j][i] * el[i][k]);
				}
		}

	}

	return a;

}

string Matrica::SupstUnaprijed(Matrica& b)
{
	Matrica L(dim_n, dim_n);
	int brojac = 1;
	string a;
	cout << endl << "RADI SE SUPSTITUCIJA UNAPRIJED" << endl;

	cout << "Unesite ime datoteke u koju cete zapisati postupak ove supstitucije unaprijed" << endl;
	cin >> a;
	a = a + ".txt";
	ofstream f(a); //ios::app da pise na kraj, a ne da je prepise s novim

	f << endl << "RADI SE SUPSTITUCIJA UNAPRIJED" << endl;

	if (!f)
	{
		cout << "Error SupstUnaprijed-can't open file! ";
		return "error";
	}


	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_n; j++)
		{
			L.el[i][i] = 1;

			if (i > j)
			{
				L.el[i][j] = el[i][j];
			}
		}
	}
	// L * y = b

	f << endl << "RADI SE SUPSTITUCIJA UNAPRIJED GDJE JE L:" << L << endl << "I GDJE JE b:" << endl << b << endl;

	f << "STVARANJE VEKTORA Y: " << endl;

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = i + 1; j < dim_n; j++)
		{
			
			b.el[j][0] -= (L.el[j][i] * b.el[i][0]); //b ce prijeci u y
			f << "ITERACIJA" << brojac++ << " : matrix y =  " << b << endl;
		}
	}

	f << "KONACNI Y GLASI:" << endl << b;

	return a;

}

string Matrica::SupstUnatrag(Matrica& b)
{
	int brojac = 1;
	string a;
	cout << endl << "RADI SE SUPSTITUCIJA UNATRAG" << endl;
	cout << "Unesite ime datoteke u koju cete zapisati postupak ove supstitucije unatrag" << endl;
	cin >> a;
	a = a + ".txt";
	ofstream f(a); //ios::app da pise na kraj, a ne da je prepise s novim

	if (!f)
	{
		cout << "Error SupstUnatrag-can't open file! ";
		return "error";
	}


	Matrica U(dim_n, dim_n);
	//pretpostavlja se da je napravljen rastav matrice na L\U matricu koja dijeli memorijski prostor

	//STVARANJE MATRICE U
	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_n; j++)
		{
			if (i <= j)
			{
				U.el[i][j] = el[i][j];
			}
		}
	}

	f << endl << "RADI SE SUPSTITUCIJA UNAPRIJED GDJE JE U:" << U << endl << "I GDJE JE b:" << endl << b << endl;


	for (int i = dim_n - 1; i >= 0; i--)
	{
		if (U.el[i][i] == 0 || abs(U.el[i][i])<epsilon)
		{
			f << "Error supstitucija unatrag! Element kojim se dijeli gotovo jednak nuli ili nula!" << endl;
			return "error";
		}

		b.el[i][0] /= U.el[i][i];

		for (int j = 0; j < i; j++)
		{
			b.el[j][0] -= (U.el[j][i] * b.el[i][0]); //b ce prijeci u x
			f << "ITERACIJA" << brojac++ << " : matrix x =  " << b << endl;
		}
	}

	f << "KONACNI X GLASI:" << endl << b;

	return a;

}

Matrica& Matrica::VratiRedak(int brojRetka, Matrica& B)
{
	Matrica Redak(1, dim_m);
	int k = 0;

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			if (i == brojRetka)
			{
				Redak.el[0][k] = el[i][j];
				k++;
			}
		}
	}

	B = Redak;
	return B;
}

Matrica& Matrica::VratiStupac(int brojStupca, Matrica& Vektor)
{
	Matrica Stupac(dim_n, 1);
	int k = 0;

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			if (j == brojStupca)
			{
				Stupac.el[k][0] = el[i][j];
				k++;
			}
		}
	}

	Vektor = Stupac;
	return Vektor;
}

void Matrica::PostaviRedak(Matrica& NoviRedak, int brojRetka)
{
	int k = 0;

	for (int i = 0; i < dim_n; i++)
	{
		for (int j = 0; j < dim_m; j++)
		{
			if (i == brojRetka)
			{
				el[i][j] = NoviRedak.el[0][k];
				k++;
			}
		}
	}

}

int Matrica::PositionOfMaxElInVector(int brojRetkaNaKojiStali, int brojStupca)
{
	Matrica A;
	VratiStupac(brojStupca, A); //stupac sprema u A koji je zapravo vektor

	double max = A.el[brojRetkaNaKojiStali][0]; //A zapravo vektor
	int position = brojRetkaNaKojiStali;
	cout << "redak na koji smo stali" << brojRetkaNaKojiStali << endl;

	for (int i = brojRetkaNaKojiStali; i < A.dim_n; i++)
	{
		if (abs(A.el[i][0]) > abs(max))
			{
				max = A.el[i][0];
				cout  << "max element glasi" << max << endl;
				position = i;
			}
	}

	return position; //vracamo u kojem se retku nalazi taj max el jer stupac znamo (jer setamo po stupcima gore)
}

int main()
{
	ofstream f;
	string filerj = "";

	f.open("ispis.txt"); //u ispis.txt je rjesenje

	if (!f.is_open())
	{
		cout << "Error: file can not be open!" << endl;
	}

	f << "** ZAD 1 ***"<< endl;

	f << "Kakva treba biti usporedba double varijabli kako bi uspoređivanje dalo ocekivane rezultate?";
	f << "Isprobajte operator == s elementima matrice kao necijelim brojevima, pomnozite i podijelite sa";
	f << "realnim brojem i usporedite s originalom. " << endl << endl;
	f << "Rjesenje:" << endl;
	f << "Usporedba: ne mozemo gledati samo sa obicnim == vec moramo gledati da je razlika dva broja manja od epsilon" << endl;
	Matrica A1;
	Matrica A2;
	string a1; //datoteka za citanje
	string a2; //datoteka2 za citanje

	a1 = "aprdat.txt";
	a2 = "arpdat2.txt";

	A1.SetRowsAndColumnsWithFile(a1);
	A1.ReadElementsFromFile(a1);

	A2.SetRowsAndColumnsWithFile(a2);
	A2.ReadElementsFromFile(a2);

	f << endl << "prva matrica glasi:" << endl<< "A1" << A1;
	f << endl << "druga matrica glasi:" << endl << "A2" << A2;

	if (A1 == A2)
	{
		f << "Iste su" << endl;
	}

	else
	{
		f << "Razlicite su" << endl;
	}

	A1.MnoziSkalarom(2);
	A2.DijeliSkalarom(2);

	f << "Nakon mnozenja skalarom prve i dijeljenja skalarom druge:" << endl;
	f << endl << "prva matrica glasi:" << endl << "A1" << A1;
	f << endl << "druga matrica glasi:" << endl << "A2" << A2;

	Matrica A3;
	Matrica b3;
	string a3 = "arpdat3.txt";
	string b_3 = "vektorb3.txt";

	A3.SetRowsAndColumnsWithFile(a3);
	A3.ReadElementsFromFile(a3);
	b3.SetRowsAndColumnsWithFile(b_3);
	b3.ReadElementsFromFile(b_3);

	f << "** ZAD 2 ***" << endl;
	f << "Odredite može li se  sustav riješiti LU odnosno LUP" << endl << endl;

	f << " Pocetna matrica" << endl << A3 << endl;
	
	f << " *** L U *** : " << endl << endl;
	cout << " *** L U *** : " << endl;
	filerj=A3.LU();
	f << "Radio se LU ciji postupak mozete pronaci u datoteci " << filerj << endl;
	f << "Dobivena je matrica L/U " << A3 << endl;
	filerj = A3.SupstUnaprijed(b3);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI Y GLASI:" << endl << b3;
	filerj = A3.SupstUnatrag(b3);
	f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
	if (filerj != "error")
		f << "KONACNI x glasi: " << b3;
	else
		f << "DOSLO JE DO POGRESKE!!" << endl;

	
	f << endl << " *** L U P ***: " << endl;
	cout << " *** L U P ***: " << endl;
	A3.ReadElementsFromFile(a3);
	b3.ReadElementsFromFile(b_3);
	filerj=A3.LUP(b3);
	f << "Radio se LUP ciji postupak mozete pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A3 << endl;	
	filerj=A3.SupstUnaprijed(b3);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI Y GLASI:" << endl << b3;
	filerj=A3.SupstUnatrag(b3);
	f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
	if (filerj != "error")
		f << "KONACNI x glasi: " << b3;
	else
		f << "DOSLO JE DO POGRESKE!!" << endl;
	

	Matrica A4;
	string a4 = "arpdat4.txt";
	double number;

	f << "** ZAD 3 ***" << endl;
	f << "Odredite moze li se  sustav riješiti LU odnosno LUP" << endl << endl;
	A4.SetRowsAndColumnsWithFile(a4);
	A4.ReadElementsFromFile(a4);

	Matrica b4(A4.GetDimN(), 1);

	cout << endl << endl << "Enter  " << b4.GetDimN() << "  elements for vector b" << endl;

	for (int i = 0; i < b4.GetDimN(); i++)
	{
		for (int j = 0; j < b4.GetDimM(); j++)
		{
			cin >> number;
			b4.SetElement(i, j, number);
		}
	}
	
	f << "Odabrani vektor b glasi:" << b4 << endl;
	
	Matrica b4_pom = b4;
	f << " L U : " << endl << endl;
	filerj=A4.LU();
	f << "Radio se LU ciji postupak mozete pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A4 << endl;
	filerj=A4.SupstUnaprijed(b4);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI y GLASI : " << b4;
	filerj=A4.SupstUnatrag(b4);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b4;
	}	
	else
		f << "DOSLO JE DO POGRESKE!!" << endl;


	f << " L U P : " << endl << endl;
	A4.ReadElementsFromFile(a4);
	filerj=A4.LUP(b4_pom);
	f << "Radio se LUP ciji postupak mozete pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A3 << endl;
	filerj=A4.SupstUnaprijed(b4_pom);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI y glasi: " << b4_pom;
	filerj=A4.SupstUnatrag(b4_pom);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b4_pom;
	}
		
	else
		f << "DOSLO JE DO POGRESKE!!" << endl;

	f << "** ZAD 4 ***" << endl;
	f << "Rijesiti pomocu LU odnosno LUP i obj razliku u rjesenju" << endl << endl;

	Matrica A5;
	string a5 = "arpdat5.txt";
	A5.SetRowsAndColumnsWithFile(a5);
	A5.ReadElementsFromFile(a5);

	Matrica b5(A4.GetDimN(), 1);
	string b_5 = "vektorb5.txt";
	b5.SetRowsAndColumnsWithFile(b_5);
	b5.ReadElementsFromFile(b_5);

	b4_pom = b5;
	f << "Pocetna matrica glasi:" << endl << A5;
	f << " L U : " << endl << endl;
	filerj=A5.LU();
	f << "Radilo se LU ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A5 << endl;
	filerj=A5.SupstUnaprijed(b5);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI Y glasi: " << b5;
	filerj=A5.SupstUnatrag(b5);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b5;
	}

	else
		f << "DOSLO JE DO POGRESKE!!" << endl;


	f << " L U P : " << endl << endl;
	A5.ReadElementsFromFile(a5);
	filerj=A5.LUP(b4_pom);
	f << "Radio se LUP postupak se moze pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A3 << endl;
	filerj=A5.SupstUnaprijed(b4_pom);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI Y glasi: " << b5;
	filerj=A5.SupstUnatrag(b4_pom);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b4_pom;
	}

	else
		f << "DOSLO JE DO POGRESKE!!" << endl;


	f << "** ZAD 5 ***" << endl;
	f << "Rijesiti pomocu LU odnosno LUP i obj razliku u rjesenju" << endl << endl;
	Matrica A6,b6;
	string a6 = "arpdat6.txt";
	string b_6 = "vektorb6.txt";
	A6.SetRowsAndColumnsWithFile(a6);
	A6.ReadElementsFromFile(a6);

	b6.SetRowsAndColumnsWithFile(b_6);
	b6.ReadElementsFromFile(b_6);

	f << " L U : " << endl << endl;
	filerj=A6.LU();
	f << "Radio se LU ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A6 << endl;
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	filerj=A6.SupstUnaprijed(b6);
	f << "KONACNI Y glasi: " << b6;
	filerj=A6.SupstUnatrag(b6);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b6;
	}

	else
		f << "DOSLO JE DO POGRESKE!!" << endl;


	f << " L U P : " << endl << endl;
	A6.ReadElementsFromFile(a6);
	b6.ReadElementsFromFile(b_6); //b_6 file, a b6 vektor
	filerj=A6.LUP(b6);
	f << "Radio se LUP ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A6 << endl;
	filerj=A6.SupstUnaprijed(b6);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI y: " << b6;
	filerj=A6.SupstUnatrag(b6);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b6;
	}

	else
		f << "DOSLO JE DO POGRESKE!!" << endl;


	f << "** ZAD 6 ***" << endl;
	f << "Rijesiti pomocu LU odnosno LUP i obj razliku u rjesenju" << endl << endl;
	 a6 = "6zadatak.txt";
	 b_6 = "6zadatakvektor.txt";
	A6.SetRowsAndColumnsWithFile(a6);
	A6.ReadElementsFromFile(a6);

	b6.SetRowsAndColumnsWithFile(b_6);
	b6.ReadElementsFromFile(b_6);

	f << " L U : " << endl << endl;
	filerj=A6.LU();
	f << "Matrica L/U " << A6 << endl;
	f << "Radio se LU ciji postupak se moze pronaci u datoteci " << filerj << endl;
	filerj=A6.SupstUnaprijed(b6);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI y: " << b6;
	filerj=A6.SupstUnatrag(b6);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b6;
	}

	else
		f << "DOSLO JE DO POGRESKE!" << endl;

	f << " L U P : " << endl << endl;
	A6.ReadElementsFromFile(a6);
	b6.ReadElementsFromFile(b_6); //b_6 file, a b6 vektor
	filerj=A6.LUP(b6);
	f << "Radio se LUP ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "Matrica L/U " << A6 << endl;
	filerj=A6.SupstUnaprijed(b6);
	f << "Radila se supstitucija unaprijed ciji postupak se moze pronaci u datoteci " << filerj << endl;
	f << "KONACNI y: " << b6;
	filerj=A5.SupstUnatrag(b6);
	if (filerj != "error")
	{
		f << "Radila se supstitucija unatrag ciji postupak se moze pronaci u datoteci " << filerj << endl;
		f << "KONACNI x glasi: " << b6;
	}

	else
		f << "DOSLO JE DO POGRESKE!" << endl;
	
}