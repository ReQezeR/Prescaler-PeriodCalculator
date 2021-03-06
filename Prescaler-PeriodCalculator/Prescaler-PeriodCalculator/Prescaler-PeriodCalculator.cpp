// Prescaler-PeriodCalculator.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "PscPeriodCalc.h"
#include <iostream>

using namespace std;  

int main()
{
	string raw_number;
	Psc_Calculator *kalk;
	while (true)
	{
		cout << "Podaj kiedy ma nastapic przeladowanie: [wartosc] [jednostka]" << endl;
		getline(cin, raw_number);
		if (raw_number == "x" || raw_number == "z") { cout << "Koniec Programu" << endl; break; }
		else if (raw_number == "help" || raw_number == "Help" || raw_number == "HELP") 
		{ 
			cout << "Dostepne Wartosci:	1s - 50ns" << endl;
			cout << "Dostepne jednostki: [s], [ms], [mys], [ns]" << endl;
			getchar();
			system("cls");
			continue;
		}
		try
		{
			kalk = new Psc_Calculator(raw_number);
			cout << "f_reload(" << kalk->time_d << ") = " << kalk->overload << " Hz" << endl;
			getchar();
			system("cls");
			delete(kalk);
		}
		catch (string err) 
		{ 
			cout << err << endl;
			getchar();
			system("cls");
		}
	}

	getchar();
}