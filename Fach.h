#pragma once
class Karton;

class Fach
{
private:
	int fachnr;
	list<Karton*> kartons;

public:
	const static int KAPAZITAET = 2;
	
public:
	Fach(int);
	~Fach();

	bool istLeer();
	bool istVoll();
	int getFachnr();
	list<Karton*>& getKartons();
	void hinzufuegenKarton(Karton*);
	Karton* entnehmen();
};