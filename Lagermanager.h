#pragma once
#include "Wareneingang.h"
#include "Artikel.h"
#include "Segment.h"

class Lagermanager
{
public:
	const static int ANZAHL_REGALE = 3;					// Konstante!
	const static int ANZAHL_SEGMENTE_PRO_REGAL = 4;
	const static int ANZAHL_FAECHER_PRO_SEGMENT = 5;

private:
	list<Wareneingang*>wareneingaenge;
	list<Artikel*>artikel;
	list<Segment*>segmente;

public:
	Lagermanager();
	~Lagermanager();
	string scanneKarton();
	bool pruefeBarcode(string);
	
	bool einlagern(Wareneingang*);
	void umlagern(int);
	Artikel* sucheArtikel(int);
	Segment* findeSegment(int);
	void setSegmente(Segment*);
	void setArtikel(Artikel* art) { artikel.push_front(art); }

};