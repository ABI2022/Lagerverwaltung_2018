#include "stdafx.h"
#include "Fach.h"

Fach::Fach(int fachnr)
{
	this->fachnr = fachnr;
}

Fach::~Fach()
{
}

bool Fach::istLeer()
{
	return kartons.empty(); // liefert TRUE, wenn das Fach leer ist
}

bool Fach::istVoll()
{
	return KAPAZITAET == static_cast<int>(kartons.size()); // Beachte: Ist das Fach mit einem Karton belegt, wird false zur�ck gegeben!
}

int Fach::getFachnr()
{
	return fachnr;
}

list<Karton*>&  Fach::getKartons()
{
	return kartons;
}

void Fach::hinzufuegenKarton(Karton* karton)
{
	if(!istVoll())kartons.push_back(karton);
}

Karton * Fach::entnehmen()
{
	Karton * tmp = NULL;
	// Der erste Karton im Fach wird genommen und
	for (Karton * k : kartons) {
		tmp = k; break;
	}
	// ... aus der Liste gel�scht und ...
	kartons.pop_front();
	// zur�ckgegeben.
	return tmp;
}