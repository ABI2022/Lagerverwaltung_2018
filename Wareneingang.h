#pragma once
#include "Karton.h"

class Wareneingang
{
private:
	int bestellnr;
	string datum;
	list<Karton*>kartons;

public:
	Wareneingang(int);
	~Wareneingang();
	void hinzufuegenKarton(Karton*);
	list<Karton*>& getKartons();
};