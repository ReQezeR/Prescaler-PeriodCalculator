#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h> 
#include <time.h> 

class Psc_Calculator
{
public:
	std::string time_s;
	double time_d;
	int prescaler = 0;
	int period = 0;
	double overload = 0.0000000;

	Psc_Calculator(std::string t1);
	~Psc_Calculator() {}
	double f_reload(double t);
	double convert_time(std::string t1);
	void specify_parameters(int a, int b, int overload);
	void overload_time(int a, int b);

};
