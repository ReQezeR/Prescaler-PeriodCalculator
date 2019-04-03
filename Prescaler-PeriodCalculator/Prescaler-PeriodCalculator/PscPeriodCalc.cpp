#include "pch.h"
#include "PscPeriodCalc.h"
#include <string>
#include <iostream>
#include <regex>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

Psc_Calculator::Psc_Calculator(string t1)
{
	this->time_s = t1;
	this->time_d = convert_time(t1);
	this->overload = f_reload(this->time_d);
	specify_parameters(this->prescaler, this->period, this->overload);

}


double Psc_Calculator::f_reload(double t)
{
	double result = 0.000;
	result = 1.0000 / t;
	return result;
}


double Psc_Calculator::convert_time(string t1)
{
	string err1 = "too small value!";
	string err2 = "too large value!";

	this->time_s = t1;
	string err = "Wrong value!";
	double double_result = 0.0;
	std::regex w1("([0-9]+)\\s([a-zA-Z]+)*");
	std::smatch result;

	if (regex_search(t1, result, w1))
	{
		double_result = stoi(result[1]);
		//cout << "[ " << result[1] << " ] | [ " << result[2] << " ] " << endl;
		if (result[2] == "s") { if (double_result >1) throw err2; }

		if (result[2] == "ms") { double_result = double_result * pow(10, -3); }
		else if (result[2] == "mys") { double_result = double_result * pow(10, -6); }
		else if (result[2] == "ns")
		{
			if (double_result >= 50)
			{
				double_result = double_result * pow(10, -9);
			}
			else throw err1;
		}
	}
	else
	{
		for (int i = 0; i < t1.length(); i++) { if (t1[i] > '9' || t1[i] < '0') throw err; }
		double_result = std::stoi(t1);
	}

	this->time_d = double_result;
	return double_result;
}


void Psc_Calculator::specify_parameters(int prescaler, int period, int overload)
{
	string err1 = "too small value!";

	if (overload >=1)
	{
		int result = 0;
		int product = 84000000 / overload;
		if (product <= 0) { throw err1; }
		cout << "Product: " << product << endl;

		if (product < 65535 && product >10000) { prescaler = rand() % product + 1; }
		else if (product <= 10000 && product > 0) { prescaler = product; cout << "Prescaler = " << product << endl; }

		period = (84000000 / ((prescaler + 1)*(int)overload)) - 1;

		while (true)
		{
			if (period < 65535 && period>0 && result == product) { break; }
			else
			{
				if (product <= 10000)
				{
					if (prescaler > 1)
					{
						prescaler -= 1;
					}
				}
				else
				{
					if (product < 65535) { prescaler = rand() % (int)product + 1; }
					else prescaler = rand() % 65533 + 1;

					period = (84000000 / ((prescaler + 1)*(int)overload)) - 1;
				}
				period = (84000000 / ((prescaler + 1)*(int)overload)) - 1;
			}
			result = (prescaler + 1)*(period + 1);
		}
		cout << "[#]  Prescaler: " << prescaler << ", Period: " << period << endl;

		this->prescaler = prescaler;
		this->period = period;
	}
	else cout << "Wrong value of overload!" << endl;
}


void Psc_Calculator::overload_time(int a, int b)
{
	double result = 84000000.000;
	cout << a << " , " << b << endl;
	result = result / ((a + 1)*(b + 1));
	result = 1 / result;
	printf("Overload in: %f", result);
}