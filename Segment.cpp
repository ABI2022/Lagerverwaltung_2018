#include "stdafx.h"
#include "Segment.h"
#include "Lagermanager.h"

// Aufgabe 1.2 --> Programmieren (Klasse + Algorithmus)
Segment::Segment(int regalnr, int segmentnr)
{
	this->regalnr = regalnr;
	this->segmentnr = segmentnr;
	artikel = NULL;

	// Fächer im Regalsegment erzeugen (Komposition)
	for (int i = 0; i < Lagermanager::ANZAHL_FAECHER_PRO_SEGMENT; i++)
		faecher.push_back(new Fach(i));
}

Segment::~Segment()
{
	if (artikel != NULL)
	{
		artikel->setSegment(NULL);	// Segmentinformation aus dem Artikel-Objekt löschen. 
	}

	for (Fach* f : faecher)			// "Fächer - Segment - Komposition" >> Alle Fächer in einem Segment werden mit gelöscht.
	{
		for (Karton* k : f->getKartons()) // Ein Fach beinhaltet mehrer Kartons.
			k->setFach(NULL);		// Fachinformationen aus den Karton-Objekten löschen.
	}

	while (!faecher.empty())		// Wiederhole, solange die Liste faecher nicht leer ist.
	{
		delete* (faecher.begin());  // new - delete >> Gibt den reservierten Speicher wieder frei. Löscht aber nicht den Listeneintrag!
	}
	faecher.clear();				// Löscht den Inhalt der Liste feacher
}

bool Segment::einlagern(Karton* karton)
{
	Fach* fachplatzFrei = nullptr;
	bool vorrat = false;

	// Erste freie Vorratsfach finden: 
	for (Fach* f : faecher)
	{
		// Erste Fach (Verkaufsfach) überspringen:
		if (f->getFachnr() != 0) 
		{
			// Ist Vorrat im Segment?
			// Wenn in dem Fach mind. 1 Karton liegt UND kein Vorrat (false) vorhanden ...
			if (!f->istLeer() && !vorrat)	
			{								// istLeer() >> true; wenn 1 Karton drin liegt >> false und !false der if-Block wird ausgeführt
											// istVoll() geht hier nicht, da das Fach ja auch halbvoll sein könnte

				vorrat = true;				// .. ändere Vorrat auf true 
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
		cout << "RegalNr: " << regalnr << " SegmentNr: " << segmentnr << " FachNr. " << fachplatzFrei->getFachnr() << " KartonNr. " << karton->getKartonNr() << endl; // Ausgabe nur zur Überprüfung
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
