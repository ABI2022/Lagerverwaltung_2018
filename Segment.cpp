#include "stdafx.h"
#include "Segment.h"
#include "Lagermanager.h"

// Aufgabe 1.2 --> Programmieren (Klasse + Algorithmus)
Segment::Segment(int regalnr, int segmentnr)
{
	this->regalnr = regalnr;
	this->segmentnr = segmentnr;
	artikel = NULL;

	// F�cher im Regalsegment erzeugen (Komposition)
	for (int i = 0; i < Lagermanager::ANZAHL_FAECHER_PRO_SEGMENT; i++)
		faecher.push_back(new Fach(i));
}

Segment::~Segment()
{
	if (artikel != NULL)
	{
		artikel->setSegment(NULL);	// Segmentinformation aus dem Artikel-Objekt l�schen. 
	}

	for (Fach* f : faecher)			// "F�cher - Segment - Komposition" >> Alle F�cher in einem Segment werden mit gel�scht.
	{
		for (Karton* k : f->getKartons()) // Ein Fach beinhaltet mehrer Kartons.
			k->setFach(NULL);		// Fachinformationen aus den Karton-Objekten l�schen.
	}

	while (!faecher.empty())		// Wiederhole, solange die Liste faecher nicht leer ist.
	{
		delete* (faecher.begin());  // new - delete >> Gibt den reservierten Speicher wieder frei. L�scht aber nicht den Listeneintrag!
	}
	faecher.clear();				// L�scht den Inhalt der Liste feacher
}

bool Segment::einlagern(Karton* karton)
{
	Fach* fachplatzFrei = nullptr;
	bool vorrat = false;

	// Erste freie Vorratsfach finden: 
	for (Fach* f : faecher)
	{
		// Erste Fach (Verkaufsfach) �berspringen:
		if (f->getFachnr() != 0) 
		{
			// Ist Vorrat im Segment?
			// Wenn in dem Fach mind. 1 Karton liegt UND kein Vorrat (false) vorhanden ...
			if (!f->istLeer() && !vorrat)	
			{								// istLeer() >> true; wenn 1 Karton drin liegt >> false und !false der if-Block wird ausgef�hrt
											// istVoll() geht hier nicht, da das Fach ja auch halbvoll sein k�nnte

				vorrat = true;				// .. �ndere Vorrat auf true 
			}

			// Erste freie Vorratsfach merken:  
			if (!f->istVoll() && fachplatzFrei == nullptr)
			{
				fachplatzFrei = f; 
			}
		}
	}

	// Einlagern in das Verkaufsfach: 
	// Wenn kein Vorrat vorhanden UND Verkaufsfach ist nicht voll ist, ...
	if (!vorrat && !faecher.front()->istVoll()) // front() Zugriff auf das erste Element vs. beginn() setzt den Iterator an den Anfang der Liste
	{
		fachplatzFrei = faecher.front(); // ... dann merke dir das Verkaufsfach. 
	}

	// Einlagern in das freie Fach 
	if (fachplatzFrei != nullptr) {
		fachplatzFrei->hinzufuegenKarton(karton);
		cout << "RegalNr: " << regalnr << " SegmentNr: " << segmentnr << " FachNr. " << fachplatzFrei->getFachnr() << " KartonNr. " << karton->getKartonNr() << endl; // Ausgabe nur zur �berpr�fung
	}
	return fachplatzFrei != nullptr; // Wenn 0 != 0 dann false. Kein freier Platz gefunden.
}

Fach* Segment::getFach(int fachnr)
{
	for (auto cur : faecher)
	{
		if (cur->getFachnr() == fachnr) return cur;
	}
	return NULL;
}

void Segment::setArtikel(Artikel* artikel)
{
	this->artikel = artikel;
}

Artikel* Segment::getArtikel()
{
	return artikel;
}

int Segment::getSegmentNr() { return segmentnr; };
