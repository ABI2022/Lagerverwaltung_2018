#include "stdafx.h"
#include "Karton.h"


Karton::Karton(int kartonNr)
{
	this->kartonNr = kartonNr;
	fach = NULL;
	artikel = NULL;
}


Karton::~Karton()
{
}

void Karton::setFach(Fach* fach)
{
	this->fach = fach;
}

Artikel* Karton::getArtikel()
{
	return artikel;
}

void Karton::setArtikel(Artikel* art) {
	this->artikel = art;
}
