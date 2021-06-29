#include "stdafx.h"
#include "Lagermanager.h"
#include "dieMusterklassen\MESerial.h"


Lagermanager::Lagermanager()
{

}


Lagermanager::~Lagermanager()
{
}

bool Lagermanager::pruefeBarcode(string code)
{
	if (code == "BARCODE") return true;
	else return false;
}

void Lagermanager::umlagern(int artikelnr)  // 1 II
{

	// Aufgabe 1.6 --> Programmieren Methode (Algorithmus)
	// Nach ausf�hren der Methode stimmt der Ansatz, die �ltesten Kartons stehen hinten, nicht mehr (lt. Musterl�sung auch nicht :-) )

	// Wo lagert der Artikel?
	Segment* suchSegment = findeSegment(artikelnr); 
	if (suchSegment == NULL) return;				

	Fach* tmpFach = NULL;								 
	Fach* zielFach = suchSegment->getFach(0);			 

	// Umlagern nur, wenn Verkaufsfach nicht voll
	if (!zielFach->istVoll())							 
	{
		// Alle Vorratsf�cher durchlaufen
		for (int i = 1; i < ANZAHL_FAECHER_PRO_SEGMENT; i++) 
		{
			// Je Fach Kartons nacheinander entnehmen (solange das Fach nicht leer ist)
			// und Katon im Verkaufsfach einlagern (solange dieses nicht voll ist)
			tmpFach = suchSegment->getFach(i);				
			while (!tmpFach->istLeer())						
			{
				zielFach->hinzufuegenKarton(tmpFach->entnehmen()); 
				// lt. L�sung --> setFach <== beidseitige Beziehung, d.h. es h�tte auch �ber hinzufuegen erfolgen k�nnen
				if (zielFach->istVoll()) return;				
			}
		}
	}
	
}

Artikel * Lagermanager::sucheArtikel(int artikelnr)
{
	Artikel* suche = NULL;

	for (auto i : artikel)
		if (artikelnr == i->getArtikelnr()) {
			suche = i;
			return suche;
		}

	return suche;
}

Segment* Lagermanager::findeSegment(int artikelnr)
{
	Segment* suche = NULL;

	for (Segment* i : segmente)
	{
		if (artikelnr == i->getArtikel()->getArtikelnr()) 
		{
			suche = i; // schade f�r die Stunde suchen ;)
			return suche;
		}
	}

	return suche;
}

bool Lagermanager::einlagern(Wareneingang* we)
{
	// Aufgabe 1.5 --> Struktogramm
	Artikel* tmpArtikel = NULL;
	Segment* tmpSegment = NULL;
	bool erfolgreicheEinlagerung = true;

	for (Karton* k : we->getKartons())
	{
		tmpArtikel = k->getArtikel();			// Zwischenspeichern des Artikel 
		tmpSegment = tmpArtikel->getSegment();	// Zwischenspeichenr des Segments
		if (!tmpSegment->einlagern(k))			// Wenn Karton nicht erfolgreich im Segment eingelagert wurde,
		{
			erfolgreicheEinlagerung = false;	// ... Einlagerung fehlgeschlagen!
		}
		// Zur �berpr�fung der Aufgabe 1.2 
		// Teste in der main() mit zuvielen Kartons f�r ein Segment.
	}
	return erfolgreicheEinlagerung;
}

string Lagermanager::scanneKarton()
{
	// Aufgabe 1.3 --> Protokoll
	MESerial* conn = new MESerial("COM1", 9600, 8, ONESTOPBIT, NOPARITY);
	string etikett = "NULL"; // NULL geht nicht! Warum?
	char rc;

	if (conn->openPort())
	{
		conn->SetRTS(ON);
		conn->write((char)0x02 + "READ" + '\n');  // <STX>READ<LF>
		//string test = "" + (char)0x02;
		//test += "READ";
		//test += '\n';
		//		cout << test << endl;
		do
		{
			etikett = conn->readLine();
			etikett = etikett.substr(1, etikett.length() - 2); // STX entfernen <STX>Barcode<LF>

			if (pruefeBarcode(etikett))
				// ACK = 0x06
				rc = (char)0x06;
			else
				// NAK = 0x15
				rc = (char)0x15;
			conn->write(rc);

		} while (rc != 0x06);
		conn->SetRTS(OFF);
		conn->closePort();
	}
	delete conn;
	return etikett;
}

void Lagermanager::setSegmente(Segment* seg) {
	segmente.push_front(seg);
}
