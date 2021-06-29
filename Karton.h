#pragma once
class Fach;
class Artikel;

class Karton
{
private:
	Fach* fach;
	Artikel* artikel;
	int kartonNr;

public:
	Karton(int);
	~Karton();
	
	void setFach(Fach*);
	Artikel* getArtikel();
	void setArtikel(Artikel*);

	int getKartonNr() { return kartonNr; };
};