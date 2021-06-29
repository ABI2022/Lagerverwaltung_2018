#include "stdafx.h"
#include "Artikel.h"


Artikel::Artikel(int anr, string bez, int aik, Segment* seg)
{
	artikelnr = anr;
	bezeichnung = bez;
	anzahlImKarton = aik;
	this->seg = seg;
}


Artikel::~Artikel()
{
}

void Artikel::setSegment(Segment* seg)
{
	this->seg = seg;
}

Segment* Artikel::getSegment()
{
	return seg;
}

int Artikel::getArtikelnr()
{
	return artikelnr;
}
