#pragma once
#include "Karton.h"
#include "Fach.h"
#include "Artikel.h"

class Segment
{
private:
	int regalnr;
	int segmentnr;
	list<Fach*> faecher;
	Artikel* artikel;

public:
	Segment(int,int);
	~Segment();
	bool einlagern(Karton*);
	Fach* getFach(int);
	void setArtikel(Artikel*);
	Artikel* getArtikel();
	int getSegmentNr();
	list<Fach*> getFaecher() { return faecher; }
};