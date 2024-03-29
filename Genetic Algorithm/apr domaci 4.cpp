#include "pch.h"
#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<ctime>

#define e pow(10,6);

using namespace std;

int velpop = 10000;
int brojbitova = 8; //za svaku koord ista preciznost
double vj_mut = 0.1;
int dg = -5;
int gg = 5;

// ___________ klasa tocka___________
class Tocka
{
public:

	int dim;
	double* koord;

	Tocka();
	Tocka(int);
};

Tocka::Tocka()
{
	dim = 1;
	koord = new double[dim];
}


Tocka::Tocka(int broj)
{
	dim = broj;
	koord = new double[broj];
}

class FunkcijaCilja
{
protected:
	virtual double PostaviVrijednost(Tocka);
	double vrijednost;
	int brevaluacija;

public:
	//Jedinka xx;
	int dimfun;
	FunkcijaCilja();
	virtual void PostaviDim(int);

	void Genetski();
};


FunkcijaCilja::FunkcijaCilja() //defaultni konstruktor
{
	brevaluacija = 0;
	vrijednost = 0;
	dimfun = 2;
}

double FunkcijaCilja::PostaviVrijednost(Tocka x)
{
	vrijednost = 0;

	return vrijednost;
}

void FunkcijaCilja::PostaviDim(int br)
{
	dimfun = br;
}

//funkcija 1
class Funkcija1 : public FunkcijaCilja //Funkcija1 nasljeđuje klasu FunkcijuCilja
{
public:
	int dimfun;
	double PostaviVrijednost(Tocka x) override;
};

//Funkcija1::Funkcija1()
//{
//	dimfun = 2;
//}

double Funkcija1::PostaviVrijednost(Tocka x)
{
	vrijednost = 100 * pow((x.koord[1] - x.koord[0] * x.koord[0]), 2) + pow((1 - x.koord[0]), 2);

	brevaluacija++;

	return vrijednost;
}

//____________funkcija 2______________

class Funkcija2 : public FunkcijaCilja //Funkcija2 nasljeđuje klasu FunkcijuCilja
{
public:
	double PostaviVrijednost(Tocka)  override;
	int dimfun = 2;
};

double Funkcija2::PostaviVrijednost(Tocka x)
{

	vrijednost = 0;

	for (int i = 0; i < x.dim; i++)
	{
		vrijednost = vrijednost + pow((x.koord[i] - i), 2);
	}

	brevaluacija++;

	return vrijednost;
}

//____________funkcija 3______________

class Funkcija3 : public FunkcijaCilja //Funkcija3 nasljeđuje klasu FunkcijuCilja
{
public:
	double PostaviVrijednost(Tocka)  override;
	int dimfun = 2;
};

double Funkcija3::PostaviVrijednost(Tocka x)
{
	double kvadrsuma = 0;

	for (int i = 0; i < x.dim; i++)
		kvadrsuma = kvadrsuma + pow(x.koord[i], 2);

	double vr1 = pow(sin(sqrt(kvadrsuma)), 2) - 0.5;
	double vr2 = pow(1 + (0.001 * kvadrsuma), 2);

	vrijednost = 0.5 + (vr1 / vr2);

	brevaluacija++;

	return vrijednost;
}

//____________funkcija 4______________

class Funkcija4 : public FunkcijaCilja //Funkcija4 nasljeđuje klasu FunkcijuCilja
{
public:
	int dimfun = 2;
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija4::PostaviVrijednost(Tocka x)
{
	double kvadrsuma = 0;

	for (int i = 0; i < x.dim; i++)
		kvadrsuma = kvadrsuma + pow(x.koord[i], 2);

	double vr1 = pow(kvadrsuma, 0.25);
	double unutarsinusa = 50 * pow(kvadrsuma, 0.1);
	double vr2 = 1 + pow(sin(unutarsinusa), 2);

	vrijednost = vr1 * vr2;

	brevaluacija++;

	return vrijednost;
}

//____________funkcija 5______________
class Funkcija5 : public FunkcijaCilja
{
public:
	int dimfun = 1;
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija5::PostaviVrijednost(Tocka x)
{
	vrijednost = pow(x.koord[0], 2);

	brevaluacija++;

	return vrijednost;
}

//____________funkcija 6______________
class Funkcija6 : public FunkcijaCilja
{
public:
	int dimfun = 1;
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija6::PostaviVrijednost(Tocka x)
{
	vrijednost = pow((x.koord[0] - 4), 2) + 4 * pow((x.koord[1] - 2), 2);

	brevaluacija++;

	return vrijednost;
}


class Jedinka //svaka koordinata je jedna jedinka
{
public:
	//realno
	double stvarna_vrijednost;

	//binarno
	int* bin; //za svaku koord svoj binarni kod
	double vrijednost;

	//dobrota
	double dobrota;

	Jedinka();
	Jedinka(int);
};

Jedinka::Jedinka()
{
	vrijednost = 0;
	bin = new int[brojbitova];
}

Jedinka::Jedinka(int br)
{
	vrijednost = 0;
	bin = new int[br];
}

void FunkcijaCilja::Genetski()
{
	ofstream f;
	double rj;
	int provjera = 1;
	int rj2;

	f.open("rjj.txt"); //u rjj.txt je rjesenje

	if (!f.is_open())
	{
		cout << "Error: file can not be open!" << endl;
	}

	Tocka* x;
	x = new Tocka[velpop];

	for (int i = 0; i < velpop; i++)
		x->dim = dimfun;

	//el = new double*[dim_n];

	//for (int i = 0; i < dim_n; i++)
	//	el[i] = new double[dim_m];

	Jedinka** populacija; //imamo niz jedinki, onoliko koliko je velika populacija... ali trebamo populacija koliko je dimenzija
	populacija = new Jedinka*[dimfun]; //koliko imamo populacija(a imamo ih koliko ima dimenzija)
	for (int i = 0; i < dimfun; i++)
		populacija[i] = new Jedinka[velpop]; //koliko je velika svaka populacija (a velika je kolika je zadana velicina populacije)

	//populacija[k][j] //govorimo o k-toj populaciji (za k-tu dimeniju),a j oznacava na kojoj smo jedinci populacije !!!!!

	for (int k = 0; k < dimfun; k++) //za svaku dimenziju stvori 5 jedinki
	{
		f << "_______________________________________________" << endl;
		f << "************* IZVODI SE ZA " << k << ". KOORDINATU TOCKE *************" << endl << endl;

		//stvori populaciju
		f << "STVARANJE POPULACIJE OD " << velpop << " JEDINKI" << endl;
		for (int j = 0; j < velpop; j++)
		{
			for (int i = 0; i < brojbitova; i++)
			{
				populacija[k][j].bin[i] = rand() % 2;
				f << populacija[k][j].bin[i];
			}
			f << endl;
		}

		f << endl;

		///izracunaj koliko iznosi binarna vrijednost (b)
		f << "NJIHOVA BINARNA VRIJEDNOST IZNOSI:" << endl;
		for (int j = 0; j < velpop; j++)
			populacija[k][j].vrijednost = 0;

		for (int j = 0; j < velpop; j++)
		{
			for (int i = 0; i < brojbitova; i++)
			{
				populacija[k][j].vrijednost = populacija[k][j].vrijednost + (populacija[k][j].bin[i] * pow(2, brojbitova - 1 - i));
			}
			f << populacija[k][j].vrijednost << " " << endl;
		}

		f << endl;

		//izracunaj stvarnu vrijednost jedinke
		f << "NJIHOVA STVARNA VRIJEDNOST IZNOSI:" << endl;
		for (int j = 0; j < velpop; j++)
			populacija[k][j].stvarna_vrijednost = 0;

		for (int j = 0; j < velpop; j++)
			populacija[k][j].stvarna_vrijednost = dg + ((populacija[k][j].vrijednost * (gg - dg)) / (pow(2, brojbitova) - 1));

		for (int j = 0; j < velpop; j++)
		{
			x[j].koord[k] = populacija[k][j].stvarna_vrijednost; //imamo velpop(j) tocaka i svakoj smo dali stvarne vrijednosti za svaku koord
			f << populacija[k][j].stvarna_vrijednost << endl;
		}

		f << endl;

	}

	f << "_________________________________________________________________" << endl;

	//evaluiraj populaciju (pridruži dobrotu)
	f << "NJIHOVA DOBROTA(za svaku kombinaciju koordinata jedinki) IZNOSI:" << endl;
	for (int j = 0; j < velpop; j++)
	{
		populacija[0][j].dobrota = PostaviVrijednost(x[j]);
		f << populacija[0][j].dobrota << endl; //s obzirom da vrijednost ovisi o kombinacij i biti ce ista, pohranjivat cemo je samo u populaciju koja je generirana za prvu dimenziju, tj nalazi se u prvoj populaciji
	}

	do {
		//f << endl << "IZABIREMO SLJEDECE JEDINKE: " << endl;
		int slucbr[3];
		int provjera = 0;
		int i = 0, j = 0;

		for (i = 0; i < 3; i++)
			slucbr[i] = rand() % velpop;

		while (provjera == 0)
		{
			provjera = 1; //pretpostavimo da nema istih

			for (i = 0; i < 2; i++)
			{
				for (j = i + 1; j < 3; j++)
				{
					if (slucbr[i] == slucbr[j])
					{
						provjera = 0;  //ako ima makar jedna ista 
					}
				}
			}

			if (provjera == 0) //ako ima istih ponovno generiraj sve brojeve
			{
				for (i = 0; i < 3; i++)
				{
					slucbr[i] = rand() % velpop;
				}
			}
		}

		//for (i = 0; i < 3; i++)
			//f << slucbr[i] << " ";

		//f << endl;


		//for (int k = 0; k < dimfun; k++)
		//{
		//	f << endl << "Njihove binarne vrijednosti za koord " << k << " su" << endl;
		//	for (int i = 0; i < 3; i++)
		//	{
		//		for (int j = 0; j < brojbitova; j++)
		//		{
		//			f << populacija[k][slucbr[i]].bin[j]; //k-ta populacija, i-ta jedinka i j-ti bit jedinke
		//		}
		//		f << "  ";
		//	}

		//	f << endl;
		//}

		//f << endl << "Njihove dobrote su: " << endl;
		//for (int i = 0; i < 3; i++)
		//{
		//	f << populacija[0][slucbr[i]].dobrota << "	";
		//}

		//f << endl << endl << "Izbacujemo najlošiju, tj onu koja ima najecu dobrotu i krizamo preostale dvije!" << endl << "Dobivenu stavljamo na mjesto izbacene." << endl;

		double max = populacija[0][slucbr[0]].dobrota;
		int worst = 0;

		for (int i = 0; i < 3; i++)
		{
			if (populacija[0][slucbr[i]].dobrota > max)
			{
				max = populacija[0][slucbr[i]].dobrota;
				worst = i;
			}

		}
		//f << "--> NAJLOSIJA (od ove tri) je jedinka " << slucbr[worst] << " cija dobrota iznosi " << max;

		//krizanje
		//f << endl << "Krizanje ce se obaviti pomocu tocke prekida koja ce biti na sredini bitova." << endl;
		int tockaprekida = (brojbitova / 2) - 1; //-1 zbog toga sto se prekid radi tocno nakon tog bita koji se dobije; a zelimo da se radi nakon onog prije sredine da bi bilo na sredini

		//f << "Tocka prekida je " << tockaprekida + 1 << endl; //+1 jer je kao 0. zapravo 1.

	//int* randombin;
	//randombin = new int[brojbitova];

	////stvori treci niz binarnih velicina
	//for (int i = 0; i < brojbitova; i++)
	//{
	//	randombin[i] = rand() % 2;
	//}

		int temp;
		//da zapamtimo zadnju od te dvije bolje
		for (int k = 0; k < dimfun; k++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == worst)
					continue;

				temp = i;
			}
		}
		int temp2;

		for (int k = 0; k < dimfun; k++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == worst || i == temp)
					continue;

				for (int j = 0; j <= tockaprekida; j++)
				{
					temp2 = j;
					populacija[k][slucbr[worst]].bin[j] = populacija[k][slucbr[i]].bin[j]; //k-ta populacija, i-ta jedinka i j-ti bit jedinke
				}
			}
		}

		for (int k = 0; k < dimfun; k++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == worst || i == temp2)
					continue;

				for (int j = tockaprekida + 1; j < brojbitova; j++)
				{
					temp2 = j;
					populacija[k][slucbr[worst]].bin[j] = populacija[k][slucbr[i]].bin[j]; //k-ta populacija, i-ta jedinka i j-ti bit jedinke
				}
			}
		}

	/*	f << endl;
		f << endl << "NOVI BINARNI PRIKAZ NAJLOŠIJE JEDINKE (NAKON KRIŽANJA) JE:" << endl;*/
		for (int k = 0; k < dimfun; k++)
		{
			populacija[k][slucbr[worst]].vrijednost = 0; //postavimo joj vrijednost na 0 da možeo dolje izracunati novu
		}

		//f << endl;


		//mutacija
		//hoce li se dogoditi mutacija
		double mut;
		mut = rand() % 100;
		mut = mut / 100;
		/*f << "mutacija: " << mut << endl;*/

		if (mut < vj_mut)
		{
			/*f << endl << "RADI SE MUTACIJA NAD NAJLOŠIJOM JEDINKOM" << endl;*/
			int rand_bit;
			rand_bit = rand() % brojbitova;

			for (int k = 0; k < dimfun; k++)
			{
				if (populacija[k][slucbr[worst]].bin[rand_bit] == 0)
					populacija[k][slucbr[worst]].bin[rand_bit] = 1;

				else
					populacija[k][slucbr[worst]].bin[rand_bit] = 0;
			}

			//f << endl << "NOVI BINARNI PRIKAZ NAJLOŠIJE JEDINKE (NAKON MUTACIJE) JE:" << endl;
			for (int k = 0; k < dimfun; k++)
			{
				//f << "za koord " << k << ":	";
				//for (int j = 0; j < brojbitova; j++)
				//{
				//	f << populacija[k][slucbr[worst]].bin[j]; //k-ta populacija, i-ta jedinka i j-ti bit jedinke
				//}
				//f << endl;

				populacija[k][slucbr[worst]].vrijednost = 0; //postavimo joj vrijednost na 0 da možeo dolje izracunati novu
			}

			//f << endl;

		}

		//f << endl << "NOVA BINARNA VRIJEDNOST NAJLOŠIJE JEDINKE IZNOSI" << endl;
		for (int k = 0; k < dimfun; k++)
		{
			for (int i = 0; i < brojbitova; i++)
			{
				populacija[k][slucbr[worst]].vrijednost = populacija[k][slucbr[worst]].vrijednost + (populacija[k][slucbr[worst]].bin[i] * pow(2, brojbitova - 1 - i));
			}
			//f << "za koord " << k << ": " << populacija[k][slucbr[worst]].vrijednost << " " << endl;
		}

		//f << endl << "NOVA STVARNA VRIJEDNOST NAJLOŠIJE JEDINKE IZNOSI" << endl;
		//izracunaj stvarnu vrijednost jedinke
		for (int k = 0; k < dimfun; k++)
		{
			populacija[k][slucbr[worst]].stvarna_vrijednost = 0;

			populacija[k][slucbr[worst]].stvarna_vrijednost = dg + ((populacija[k][slucbr[worst]].vrijednost * (gg - dg)) / (pow(2, brojbitova) - 1));

			x[j].koord[k] = populacija[k][slucbr[worst]].stvarna_vrijednost; //imamo velpop(j) tocaka i svakoj smo dali stvarne vrijednosti za svaku koord
			//f << populacija[k][slucbr[worst]].stvarna_vrijednost << endl;
		}

		//f << endl;


		//f << "_________________________________________________________________" << endl;

		//evaluiraj populaciju (pridruži dobrotu)
		//f << "NJENA NOVA DOBROTA IZNOSI:" << endl;
		populacija[0][slucbr[worst]].dobrota = PostaviVrijednost(x[j]);
		//f << populacija[0][slucbr[worst]].dobrota << endl; //s obzirom da vrijednost ovisi o kombinacij i biti ce ista, pohranjivat cemo je samo u populaciju koja je generirana za prvu dimenziju, tj nalazi se u prvoj populaciji

		rj = populacija[0][0].dobrota;

		for (int i = 0; i < velpop; i++)
		{
			if (populacija[0][i].dobrota < rj)
			{
				rj = populacija[0][i].dobrota;
				rj2 = i;
			}
		}
			
		//rj = rj / velpop;

		if (rj< 0.000001)
		{
			break;
		}

	} while (brevaluacija < 300000); 

	cout << "Vrijednost funkcije cilja u minimumu je " << rj << endl;

	f << endl << endl << "*** _______________________________________________________________________________________________________________ ***" << endl << endl;
		
	if(rj > 0.000001)
		cout << "Rjesenje nije provedeno do kraja" << endl;
	cout << "RJESENJE JE" << endl;

	//double* rj;
	//rj = new double[dimfun];
	//for (int k = 0; k < dimfun; k++)
	//	rj[k] = 0;
	//
	//for (int k = 0; k < dimfun; k++)
	//	for (int i = 0; i < velpop; i++)
	//		rj[k] += populacija[k][i].stvarna_vrijednost;
	//
	//for (int k = 0; k < dimfun; k++)
	//rj[k] = rj[k] / velpop;
	//for (int k = 0; k < dimfun; k++)
	//	f << rj[k] << endl;
	//
	f << "Rjesenje je:" << endl;
	for (int k = 0; k < dimfun; k++)
	{
		f << populacija[k][rj2].stvarna_vrijednost << endl;
		cout << populacija[k][rj2].stvarna_vrijednost << endl;
	}

}


int main()
{
	srand(time(NULL));

	//Funkcija1 f1;
	//f1.PostaviDim(2);
	//f1.Genetski();

	//Funkcija2 f2;
	//f2.PostaviDim(1);
	//f2.Genetski();

	Funkcija3 f3;
	f3.PostaviDim(2);
	f3.Genetski();

	/*Funkcija4 f4;
	f4.PostaviDim(2);
	f4.Genetski();*/

	//Funkcija5 f5;
	//f5.PostaviDim(1);
	//f5.Genetski();

	//Funkcija6 f6;
	//f6.PostaviDim(2);
	//f6.Genetski();

}