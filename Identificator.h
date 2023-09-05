#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>

using namespace System;

class Identificator
{
public:
	Identificator(std::string N);
	~Identificator();
	std::string GetName();
	Identificator* GetNext();
	void SetNext(Identificator* P);

private:
	std::string Name;
	Identificator* NextOne;
};
