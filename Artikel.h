#pragma once
class Segment;
class Karton;

class Artikel
{
private:
	int artikelnr;
	string bezeichnung;
	int anzahlImKarton;
	Segment*seg;
	list<Karton*> kartonliste;

public:
	Artikel(int anr, string bez, int aik,Segment* seg);
	~Artikel();
	void setSegment(Segment*);
	Segment* getSegment();
	int getArtikelnr();
	
	void  setKartonliste(Karton* k) {
		kartonliste.push_front(k);
	}

	list<Karton*> getKartonliste() { 
		return kartonliste; 
	}
};

