#include "Identificator.h"

Identificator::Identificator(std::string N)
{
	Name = N;
	NextOne = nullptr;
}

Identificator::~Identificator() {}

std::string Identificator::GetName()
{
	return Name;
}

Identificator* Identificator::GetNext()
{
	return NextOne;
}

void Identificator::SetNext(Identificator* P)
{
	NextOne = P;
}