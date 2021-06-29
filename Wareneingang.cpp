#include "stdafx.h"
#include "Wareneingang.h"


Wareneingang::Wareneingang(int bestellnr)
{
	this->bestellnr = bestellnr;
	this->datum = "31.02.2018";
}

Wareneingang::~Wareneingang()
{
}

list<Karton*>&  Wareneingang::getKartons()
{
	return kartons;
}

void Wareneingang::hinzufuegenKarton(Karton* k) {
	kartons.push_back(k); // First In Frist Out 
}