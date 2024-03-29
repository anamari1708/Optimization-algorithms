#include "pch.h"
#include <iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
#include<cstdlib>
#include<ctime>
 
using namespace std;

const double e = pow(10, -6);

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

//____________funkcija cilja______________
class FunkcijaCilja 
{
protected:
	virtual double PostaviVrijednost(Tocka);

   //da bi se moglo koristit u klasama koje je nasljeđuju
	int broj_poziva;	
	double vrijednost;

public:
	Tocka l, r;
	Tocka x;

	FunkcijaCilja();
	void UvecajBrojPoziva();
	int GetBrojPoziva();
	double GetVrijednost();
	int unimodalni(double , Tocka , Tocka& , Tocka& , int);
	double virtual Zlatni_rez(Tocka, Tocka, int);
	void virtual PoNelderuiMeadu(Tocka, int);
	Tocka KoordinatnoTrazenje(Tocka);
	Tocka HookeJeeves(Tocka);
	Tocka Istrazi(Tocka, Tocka);

};

double FunkcijaCilja::PostaviVrijednost(Tocka x)
{
	vrijednost = 0;

	return vrijednost;
}

FunkcijaCilja::FunkcijaCilja() //defaultni konstruktor
{
	broj_poziva = 0;
	vrijednost = 0;
}

int FunkcijaCilja::GetBrojPoziva()
{
	return broj_poziva;
}

void FunkcijaCilja::UvecajBrojPoziva()
{
	broj_poziva++;
}

double FunkcijaCilja::GetVrijednost()
{
	return vrijednost;
}

//____________funkcija 1______________

class Funkcija1 : public FunkcijaCilja //Funkcija1 nasljeđuje klasu FunkcijuCilja
{
	public:
		double PostaviVrijednost(Tocka x)  override;
};

double Funkcija1::PostaviVrijednost(Tocka x)
{
	vrijednost = 100 * pow((x.koord[1] - x.koord[0]* x.koord[0]), 2) + pow((1 - x.koord[0]),2);

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 2______________

class Funkcija2 : public FunkcijaCilja //Funkcija2 nasljeđuje klasu FunkcijuCilja
{
public:
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija2::PostaviVrijednost(Tocka x)
{
	
	vrijednost = pow((x.koord[0] -4), 2) + 4* pow((x.koord[1] -2), 2);
	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 3______________

class Funkcija3 : public FunkcijaCilja //Funkcija3 nasljeđuje klasu FunkcijuCilja
{
public:
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija3::PostaviVrijednost(Tocka x)
{
	vrijednost = 0;

	for (int i = 0; i < x.dim; i++)
	{
		vrijednost = vrijednost + pow((x.koord[i] - i), 2);
	}

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 4______________

class Funkcija4 : public FunkcijaCilja //Funkcija4 nasljeđuje klasu FunkcijuCilja
{
public:
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija4::PostaviVrijednost(Tocka x)
{
	vrijednost = abs((x.koord[0] - x.koord[1])*(x.koord[0] + x.koord[1])) + sqrt(pow(x.koord[0], 2) + pow(x.koord[1], 2));

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 5______________

class Funkcija5 : public FunkcijaCilja //Funkcija5 nasljeđuje klasu FunkcijuCilja
{
public:
	double PostaviVrijednost(Tocka)  override;
};

double Funkcija5::PostaviVrijednost(Tocka x)
{
	double vr1, vr2;
	double zbrojkvadrat=0;
	
	for (int i = 0; i < x.dim; i++)
	{
		zbrojkvadrat = zbrojkvadrat + pow((x.koord[i]), 2);
	}

	vr1 = pow(sin(sqrt(zbrojkvadrat)), 2) - 0, 5;
	vr2 = pow((1 + 0.001*zbrojkvadrat),2);

	vrijednost = 0.5 + (vr1 / vr2);

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 6 (moja probna) ______________

class Funkcija6 : public FunkcijaCilja 
{
public:

	double PostaviVrijednost(Tocka) override;
	//double Zlatni_rez(double a, double b);
};

double Funkcija6::PostaviVrijednost(Tocka x) 
{
	vrijednost = pow((x.koord[0] - 4), 2);

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 7 (moja probna2) ______________

class Funkcija7 : public FunkcijaCilja
{
public:

	double PostaviVrijednost(Tocka) override;
	//double Zlatni_rez(double a, double b);
};

double Funkcija7::PostaviVrijednost(Tocka x)
{
	vrijednost = pow((x.koord[0]), 2) + pow((x.koord[1]), 2) + pow((x.koord[2]), 2);

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 8 za zadatak 1 ______________

class Funkcija8 : public FunkcijaCilja
{
public:

	double PostaviVrijednost(Tocka) override;
	//double Zlatni_rez(double a, double b);
};

double Funkcija8::PostaviVrijednost(Tocka x)
{
	vrijednost = pow((x.koord[0]-3),2);

	UvecajBrojPoziva();

	return vrijednost;
}

//____________funkcija 9 za zprobu HookJeeves-a ______________

class Funkcija9 : public FunkcijaCilja
{
public:

	double PostaviVrijednost(Tocka) override;
};

double Funkcija9::PostaviVrijednost(Tocka x)
{
	vrijednost = pow(x.koord[0], 2) + 4 * pow(x.koord[1], 2);

	UvecajBrojPoziva();

	return vrijednost;
}



// __________________________________ nasljedene unimodalni i zlatni rez__________________________________________

int FunkcijaCilja::unimodalni(double h, Tocka tocka, Tocka& l, Tocka& r, int index)
{
	int prosli_broj_poziva = broj_poziva;
	Tocka m(1);

	cout << "---- UNIMODALNI ----" << endl << endl;
	l.koord[0] = tocka.koord[0];
	l.koord[1] = tocka.koord[1];

	m.koord[0] = tocka.koord[0];
	m.koord[1] = tocka.koord[1];

	r.koord[0] = tocka.koord[0];
	r.koord[1] = tocka.koord[1];

	
	l.koord[index] = tocka.koord[index] - h;
	m.koord[index] = tocka.koord[index];
	r.koord[index] = tocka.koord[index] + h;

	
	double fl, fr, fm;
	unsigned int step = 1;
	
	fl = PostaviVrijednost(l);
	fm = PostaviVrijednost(m);
	fr = PostaviVrijednost(r);

	if (fm < fr && fm < fl)
	{
		//cout << " fm < fr && fm < fl ! " << endl;
		return -1;
	}
		

   else if (fm > fr)
	{
		do
		{
			l.koord[index] = m.koord[index];
			m.koord[index] = r.koord[index];
			fm = fr;
			r.koord[index] = tocka.koord[index] + h * (step *= 2);
			fr = PostaviVrijednost(r);
		} while (fm > fr);
	}
	else
	{
		do
		{
			r.koord[index] = m.koord[index];
			m.koord[index] = l.koord[index];
			fm = fl;
			l.koord[index] = tocka.koord[index] - h * (step *= 2);
			fl = PostaviVrijednost(l);
		} while (fm > fl);
	}

	cout << "- Unimodalni interval - :" << endl;
	cout << l.koord[index] << " " << " do " << r.koord[index] << endl;

	//cout << endl << "Broj poziva je " << broj_poziva - prosli_broj_poziva;


	return 0;
}

double FunkcijaCilja::Zlatni_rez(Tocka a, Tocka b, int index)
{
	int prosli_broj_poziva = broj_poziva;
	cout << endl << endl << "----Zlatni rez----" << endl << endl;


	Tocka c(1);
	Tocka d(1);
	double fc, fd;
	double k = 0.5*(sqrt(5) - 1);
	
	c.koord[0] = a.koord[0];
	c.koord[1] = a.koord[1];
	d.koord[0] = a.koord[0];
	d.koord[1] = a.koord[1];

	c.koord[index] = b.koord[index] - k * (b.koord[index] - a.koord[index]);
	d.koord[index] = a.koord[index] + k * (b.koord[index] - a.koord[index]);
	fc = PostaviVrijednost(c);
	fd = PostaviVrijednost(d);

	//cout << "TOCKA a JE: " << a.koord[index] << endl << "TOCKA c JE: " << c.koord[index] << endl << "TOCKA d je:" << d.koord[index] << endl << "TOCKA b je: " << b.koord[0] << endl;
	cout << endl << endl;

	while ( abs(b.koord[index] - a.koord[index]) > e)
	{
		if (fc < fd)
		{
			b.koord[index] = d.koord[index];
			d.koord[index] = c.koord[index];
			c.koord[index] = b.koord[index] - k * (b.koord[index] - a.koord[index]);
			fd = fc;
			fc = PostaviVrijednost(c);
		}

		else
		{
			a.koord[index] = c.koord[index];
			c.koord[index] = d.koord[index];
			d.koord[index] = a.koord[index] + k * (b.koord[index] - a.koord[index]);
			fc = fd;
			fd = PostaviVrijednost(d);
		}

		//cout << "TOCKA a JE: " << a.koord[index] << endl << "TOCKA c JE: " << c.koord[index] << endl << "TOCKA d je:" << d.koord[index] << endl << "TOCKA b je: " << b.koord[0] << endl;
		//cout << "Vrijednost fc je:" << fc << endl;
		//cout << "Vrijednost fd je:" << fd << endl;
		cout << endl << endl;
	}


	cout << "interval je od: " << a.koord[index] << " do " << b.koord[index] << endl;

	cout << endl << endl << "Broj poziva je " << broj_poziva - prosli_broj_poziva << endl;

	return (a.koord[index] + b.koord[index]) / 2; // sredinu intervala
}

Tocka FunkcijaCilja:: KoordinatnoTrazenje(Tocka x0)
{
	int stari_broj_poziva = broj_poziva;

	cout << endl <<  "--- KOORDINATNO TRAZENJE ---" << endl;

	cout << "Pocetna tocka: " << endl;//ispis
	for (int i = 0; i < x0.dim; i++)
	{
		cout << "Tocka T" << i + 1 << ":" << endl;

		cout << x0.koord[i] << " " << endl;
	}

	Tocka x = x0;
	Tocka xs(x0.dim);
	bool UvjetZaustavljanja=false;
	double h= 1;
	int iter = 0;
	while ( iter < 1000/*!UvjetZaustavljanja*/)
	{
		iter++;
		UvjetZaustavljanja = true;

		for (int i = 0; i < x0.dim; i++) //kopiraj x u xs
		{
			xs.koord[i] = x.koord[i];
		}

		for (int i = 0; i < x0.dim; i++)
		{
			unimodalni(h, x, l, r, i);
			double novaVrijednost = Zlatni_rez(l,r,i);
			double staraVrijednost = xs.koord[i];
			x.koord[i] = novaVrijednost;
			double razlika = abs(novaVrijednost - staraVrijednost);

			if (razlika > e)
			{
				UvjetZaustavljanja = false;
			}
		}

		cout << endl<< endl << "Minimum je u tocki :" << endl;

		for (int i = 0; i < x0.dim; i++)
		{
			cout << "Tocka T" << i + 1 << ":" << endl;

				cout << x.koord[i] << " " << endl;
		}

	
	}

	cout << endl << "Broj poziva nakon Koordinatnog pretrazivanja: " << broj_poziva - stari_broj_poziva << endl;
	return x;

}


void FunkcijaCilja::PoNelderuiMeadu(Tocka x0, int t) //simplex
{
	int prosli_broj_poziva = broj_poziva;
	
	cout <<endl << "_______________________________________________________" << endl;
	cout << "*****		Po Nelderu i Meadu	(simplex)	*****" << endl;

	cout << "KORAK: " << t << endl;
	int n, j;
	n = x0.dim;
	vector<Tocka> d;
	vector<Tocka> simplex;
	Tocka centroidpom(n);
	double sigma = 0.5;
	double gama = 2;
	double beta = 0.5;
	double alfa = 1;
	double UvjetZaustavljanja;
	Tocka xr(n); //tocka refleksije
	Tocka xe(n); //tocka ekspanzije
	Tocka xk(n); //tocka kontrakcije

	double a1, a2;

	//a1 = (t / (n*sqrt(2)))*(sqrt(n + 1) + (n - 1));
	//a2 = (t / (n*sqrt(2)))*(sqrt(n + 1) - (1));

	int i = 0;
	int k = 0;
	

	//IZRACUN SIMPLEXA (za pomak t=1)
		simplex.push_back(x0);
		for(i=0;i<n;i++)
		{
			Tocka temp;
			for (j = 0; j < n; j++)
			{		
				if (i == j)
					temp.koord[j] = x0.koord[j] + 1;
				else
					temp.koord[j] = x0.koord[j];
			}
			simplex.push_back(temp);
		
		}	
	
	do
	{
		Tocka xh, xl;
		xh = simplex[0]; //tocka s najvecom(najgorom) vrijednoscu funkcije cilja
		xl = simplex[0]; //tocka s najmanjom(najboljom) vrijednoscu funkcije cilja
		double max = PostaviVrijednost(simplex[0]);
		double min = PostaviVrijednost(simplex[0]);
		int worsTindex = 0;
		int bestIndex = 0;

		//PRONALAZAK NAJBOLJE I NAJGORE TOCKE U SIMPLEXU
		for (i = 0; i < n + 1; i++)
		{
			if (PostaviVrijednost(simplex[i]) > max)
			{
				max = PostaviVrijednost(simplex[i]);
				xh.dim = simplex[i].dim;
				xh.koord = simplex[i].koord;
				worsTindex = i;
			}

			if (PostaviVrijednost(simplex[i]) < min)
			{
				min = PostaviVrijednost(simplex[i]);
				xl.dim = simplex[i].dim;
				xl.koord = simplex[i].koord;
				bestIndex = i;
			}
		}
		cout << endl << "Tocke simplexa:" << endl;

		for (i = 0; i < n + 1; i++)
		{
			cout << endl << "Tocka T" << i + 1 << ":" << endl;
			for (j = 0; j < n; j++)
				cout << simplex[i].koord[j] << " " << endl;
		}

		cout << endl;
			
		//IZRACUN CENTROIDA
		Tocka centroid(n);
		for (i = 0; i < n; i++)
			centroid.koord[i] = 0;

		for (i = 0; i < n + 1; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i != worsTindex)
				{
					centroid.koord[j] += simplex[i].koord[j];
				}

			}
		}

		for (j = 0; j < n; j++)
		{
			centroid.koord[j] /= n;
		}

		cout << "Tocka centorida glasi:" << endl;
		for (j = 0; j < n; j++)
		{
			cout << centroid.koord[j] << " " << endl;
		}
		UvjetZaustavljanja = 0;
		//IZRACUN UVJETA ZAUSTAVLJANJA
		for (i = 0; i < n+1; i++)
		{
			UvjetZaustavljanja += pow((PostaviVrijednost(simplex[i]) - PostaviVrijednost(centroid)), 2);
		}
		UvjetZaustavljanja = UvjetZaustavljanja / n;
		UvjetZaustavljanja = sqrt(UvjetZaustavljanja);

		//IZRACUN TOCKE REFLEKSIJE
		for (i = 0; i < n; i++) //refleksija
			xr.koord[i] = (1 + alfa)*centroid.koord[i] - (alfa*xh.koord[i]);
		
		cout << endl << "Tocka refleksije xr:" << endl;
		for (i = 0; i < n; i++)
		{
			cout << "T" << i + 1 << ":" << xr.koord[i] << endl;
		}


		cout << endl << "Tocke simplexa:" << endl;

		for (i = 0; i < n + 1; i++)
		{
			cout << endl << "Tocka T" << i + 1 << ":" << endl;
			for (j = 0; j < n; j++)
				cout << simplex[i].koord[j] << " " << endl;
		}

		cout << endl;
			

		if (PostaviVrijednost(xr) < PostaviVrijednost(xl))
		{
			//IZRACUN TOCKE EKSPANZIJE xe
			for (i = 0; i < n; i++) //ekspanzija
				xe.koord[i] = (1 - gama)*centroid.koord[i] + (gama * xr.koord[i]);

			cout << endl << "Tocka ekspanzije xe:" << endl;
			for (i = 0; i < n; i++)
			{
				cout << "T" << i + 1 << ":" << xe.koord[i] << endl;
			}

			if (PostaviVrijednost(xe) < PostaviVrijednost(xl))
				for (i = 0; i < n; i++)
					simplex[worsTindex].koord[i] = xe.koord[i];

			else
				for (i = 0; i < n; i++)
					simplex[worsTindex].koord[i] = xr.koord[i];

		}
		
		else
		{
			bool provjera = true;
			//IZRACUN TOCKE KONTRAKCIJE
			for (j = 0; j < n + 1; j++)
			{
				if (j == worsTindex)
					continue;

				if (PostaviVrijednost(xr) < PostaviVrijednost(simplex[j]))
				{
					provjera = false;
					//break;
				}
			}

			if (provjera == true)
			{
				Tocka xh = simplex[worsTindex];
				double fxh = PostaviVrijednost(xh);
				if (PostaviVrijednost(xr) > fxh)
				{
					for (i = 0; i < n; i++)
						simplex[worsTindex].koord[i] = xr.koord[i];
					fxh = PostaviVrijednost(xr);
				}

				for (i = 0; i < n; i++) //kontrakcija
					xk.koord[i] = (1 - beta)*centroid.koord[i] + (beta*xh.koord[i]);

				cout << endl << "Tocka kontrakcije xk:" << endl;
				for (i = 0; i < n; i++)
				{
					cout << "T" << i + 1 << ":" << xk.koord[i] << endl;
				}

				double fxk = PostaviVrijednost(xk);

				if (fxk < fxh)
					for (i = 0; i < n; i++)
						simplex[worsTindex].koord[i] = xk.koord[i];

				else //pomakni sve tocke prema xl
				{
					for (int i = 0; i < n + 1; i++)
					{
						if (i != bestIndex)
						{
							for (j = 0; j < n; j++)
								simplex[i].koord[j] = sigma * (simplex[i].koord[j] + simplex[bestIndex].koord[j]);
						}
					}
				}
			}


			else
				for (i = 0; i < n; i++)
					simplex[worsTindex].koord[i] = xr.koord[i];
		}

		//da se ispise posljednji centroid
		for (i = 0; i < n; i++)
			centroid.koord[i] = 0;

		for (i = 0; i < n + 1; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i != worsTindex)
				{
					centroid.koord[j] += simplex[i].koord[j];
				}
			}
		}

		for (j = 0; j < n; j++)
		{
			centroid.koord[j] /= n;
		}
		centroidpom = centroid;


	} while (abs(UvjetZaustavljanja) > e);


	cout << endl << endl << "Centroid (minimum) glasi:" << endl;
	for (j = 0; j < n; j++)
	{
		cout << centroidpom.koord[j] << " " << endl;
	}

	
	cout << endl << endl << "Broj poziva je " << broj_poziva - prosli_broj_poziva << endl;
	
}

Tocka FunkcijaCilja:: HookeJeeves(Tocka x0)
{
	int i;
	int n = x0.dim;
	Tocka xP(x0.dim);
	Tocka xB(x0.dim);
	Tocka Dx;

	cout << endl <<"_____________________________________________________" << endl;
	cout << "*****		   Hooke-Jeeves		   *****" << endl;
	cout << endl << endl << "Pocetna tocka pretrazivanja:" << endl;
	cout << endl << "--> Tocka x0:" << endl; //ispis pocetne tocke
	for (i = 0; i < n; i++)
	{
		cout << "T" << i + 1 << ":  " << x0.koord[i] << endl;
	}

	cout << "______________________________________" << endl;

	for (i = 0; i < n; i++)
	{
		xP.koord[i] = x0.koord[i];
	}
	
	for (i = 0; i < n; i++)
	{
		xP.koord[i] = x0.koord[i];
	} 
	
	cout << endl << "Tocka xB:" << endl;

	for (i = 0; i < n; i++)
	{
		cout << "T" << i + 1 << ":  " << xB.koord[i] << endl;
	}

	cout << endl << "Tocka xP:" << endl;
	for (i = 0; i < n; i++)
	{
		cout << "T" << i + 1 << ":  " << xP.koord[i] << endl;
	}

	for (i = 0; i < n; i++)
		Dx.koord[i] = 0.5;// pomaci za isti iznos ne znace ise stvari pa se i on definira kao vektor ???
	
	do
	{
		Tocka xN;
		for (i = 0; i < n; i++)
			xN.koord[i] = Istrazi(xP, Dx).koord[i];   // definiran je potprogram

		cout << "__________________________" << endl;
		cout << endl << "Tocka xB:" << endl;
		for (i = 0; i < n; i++)
		{
			cout << "T" << i + 1 << ":  " << xB.koord[i] << endl;
		}
		cout << endl << "Tocka xP:" << endl;
		for (i = 0; i < n; i++)
		{
			cout << "T" << i + 1 << ":  " << xP.koord[i] << endl;
		}
		cout << endl << "Tocka xN:" << endl;
		for (i = 0; i < n; i++)
		{
			cout << "T" << i + 1 << ":  " << xN.koord[i] << endl;
		}
		
		if(PostaviVrijednost(xN) < PostaviVrijednost(xB))  // prihvacamo baznu tocku
		{
			for (i = 0; i < n; i++)
			{
				xP.koord[i] = 2 * xN.koord[i] - xB.koord[i];  // definiramo novu tocku pretrazivanja
				xB.koord[i] = xN.koord[i];
			}				
		}
		else
		{
			for (i = 0; i < n; i++)
				Dx.koord[i] = Dx.koord[i]/2;

			for (i = 0; i < n; i++)
			{
				xP.koord[i] = xB.koord[i]; // vracamo se na zadnju baznu tocku
				
			}			       
		}
	} while (abs(Dx.koord[0]) > e);

			return xB;
}

Tocka FunkcijaCilja:: Istrazi(Tocka xP, Tocka Dx)
 {
	Tocka x;
	int i, n;
	n = xP.dim;
	for (i = 0; i < n; i++)
		x.koord[i] = xP.koord[i];

	for (i = 0; i < n; i++) {
		x.koord[i] = x.koord[i] + Dx.koord[i];  // povecamo za Dx

		if (PostaviVrijednost(x) > PostaviVrijednost(xP)) // ne valja pozitivni pomak
			x.koord[i] = x.koord[i] - 2 * Dx.koord[i];  // smanjimo za Dx

		if (PostaviVrijednost(x) > PostaviVrijednost(xP))  // ne valja ni negativni
			x.koord[i] = x.koord[i] + Dx.koord[i];  // vratimo na staro

		for (int j = 0; j < n; j++)
			xP.koord[j] = x.koord[j];
	}
	 return x;
 }


int main()
{
	//za probu 
	//Funkcija6 f6;
	//Funkcija7 f7;
	//Tocka tt(3);
	//tt.koord[0]=0;
	//tt.koord[1]=2;
	//tt.koord[2]=3;
	//Tocka t1(1);
	//Tocka t2(1);
	//t2.koord[0] = 0;
	//t1.koord[0] = 0;

	//cout << endl << "Tocka tt:" << endl;
	//for (int i = 0; i < 3; i++)
	//{
	//	cout << "T" << i + 1 << ":  " <<tt.koord[i] << endl;
	//}

	/*f6.unimodalni(1, t1 , f6.l, f6.r,0); //0 za koordinatu(index) tocke
	f6.Zlatni_rez(f6.l, f6.r, 0);
	f6.KoordinatnoTrazenje(t1);
	f6.PoNelderuiMeadu(t1,1); //1 za korak
	f6.HookeJeeves(t1);*/

	//Funkcija9 f9;
	//Tocka t9(2);
	////t9.koord[0] = 7;
	//t9.koord[1] = 3;
	//f9.HookeJeeves(t9);

	//_________________________________________________________________________________________________________________________________

	//ZADATAK 1
	
	/*Funkcija8 f8;
	Tocka t8(1);
	t8.koord[0] = 10;*/
	//
	//f8.unimodalni(1, t8, f8.l, f8.r,0);
	//f8.Zlatni_rez(f8.l, f8.r,0);
	//f8.KoordinatnoTrazenje(t8);
	//f8.PoNelderuiMeadu(t8,1); // 1 za korak
	//f8.HookeJeeves(t8); 
	
	//_________________________________________________________________________________________________________________________________

	//ZADATAK 2

	Funkcija1 f2;
	Tocka t2(2);
	Tocka trj(2);
	t2.koord[0] = -1.9;
	t2.koord[1] = 2;
	//f2.PoNelderuiMeadu(t2,1);
	trj=f2.HookeJeeves(t2);
	//f2.KoordinatnoTrazenje(t2);


	//_________________________________________________________________________________________________________________________________

	//ZADATAK 3
	//
	//Funkcija4 f4;
	//Tocka t4(2);

	//t4.koord[0] = 5;
	//t4.koord[1] = 5;

	//f4.KoordinatnoTrazenje(t4);
	//f4.PoNelderuiMeadu(t4,1);
	/*f4.HookeJeeves(t4);*/

	//_________________________________________________________________________________________________________________________________

	//ZADATAK 4 
	
	/*Funkcija1 f1;
	Tocka t1(2);
	cout << "Tocka 1" << endl;
	t1.koord[0] = 0.5;
	t1.koord[1] = 0.5;
	f1.PoNelderuiMeadu(t1,1);*/
	//f1.PoNelderuiMeadu(t1, 7);
	//f1.PoNelderuiMeadu(t1, 17);

	/*
	cout << "Tocka 2" << endl;
	Tocka t11(2);
	t11.koord[0] = 20;
	t11.koord[1] = 20;
	f1.PoNelderuiMeadu(t11, 1);
	f1.PoNelderuiMeadu(t11, 7);
	f1.PoNelderuiMeadu(t11, 17);*/
	
	//_________________________________________________________________________________________________________________________________

	//ZADATAK 5
	/*Funkcija6 f6;
	Tocka t6(2);
	int x;
	srand(time(NULL));
	cout << "Generirani su brojevi:" << endl;
	x = rand() % (50 - (-50) + 1) - 50;
	cout << x << "		";
	t6.koord[0] = x;
	x = rand() % (50 - (-50) + 1) - 50;
	cout << x;
	t6.koord[1] = x;
	f6.PoNelderuiMeadu(t6);
*/
		
}

