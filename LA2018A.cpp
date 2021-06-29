// LA2018A.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Lagermanager.h"
#include "Karton.h"



int main()
{
	Lagermanager la;

	Karton k0(11), k1(12), k2(13), k3(24), k4(25), k5(26), k6(27), k7(28); //Karton mit KartonNr 1. Zahl = Artikel; 2. Zahl = Kartonanzahl  .
	Segment seg31(3, 1);
	Segment seg32(3, 2);
	la.setSegmente(&seg31);
	la.setSegmente(&seg32);

	Artikel art1(1, "Handtuch Nr. 1", 10, &seg31); // Artikel kennt das Segment, in dem es eingelagert ist.
	Artikel art2(2, "Handtuch Nr. 2", 5, &seg32);
	seg31.setArtikel(&art1); // Segment kennt den Artikel
	seg32.setArtikel(&art2);
	la.setArtikel(&art1); // Das Lagermanagment kennt die Artikel, die es lagert.
	la.setArtikel(&art2);

	k0.setArtikel(&art1); // Karton kennt sein Artikel
	art1.setKartonliste(&k0); // Artikel kennt seinen Karton
	k1.setArtikel(&art1);
	art1.setKartonliste(&k1);
	k2.setArtikel(&art1);
	art1.setKartonliste(&k2);
	k3.setArtikel(&art2);
	art2.setKartonliste(&k3);
	k4.setArtikel(&art2);
	art2.setKartonliste(&k4);
	k5.setArtikel(&art2);
	k6.setArtikel(&art2);
	art2.setKartonliste(&k5);
	k7.setArtikel(&art2); 
	art2.setKartonliste(&k7);


	Wareneingang wa(123);
	wa.hinzufuegenKarton(&k0); // Erstes Element in der Liste (FIFO Prinzip)
	wa.hinzufuegenKarton(&k1);
	wa.hinzufuegenKarton(&k2); 
	wa.hinzufuegenKarton(&k3);
	wa.hinzufuegenKarton(&k4);
	wa.hinzufuegenKarton(&k5);
	wa.hinzufuegenKarton(&k6); 
	wa.hinzufuegenKarton(&k7);

	// Zur Überprüfung der Aufgabe 1.5
	cout << "Einlagern erfolgreich? "
		 << la.einlagern(&wa) // Zur Überprüfung der Aufgabe 1.2 siehe Funktion
		 << endl;


	// Zur Überprüfung der Aufgabe 1.6
	cout << "Ist Voll ? " << seg32.getFach(0)->istVoll() << endl; // Fach 0 wird überprüft, ob es voll ist
	seg32.getFach(0)->entnehmen(); // Karton 24 wird verkauft

	// Lagerbestand wird ausgegeben - Karton 24 fehlt und Fach 0 hat einen freien Platz
	for (int j = 0; j < seg32.getFaecher().size(); j++) { 
		for (Karton *k : seg32.getFach(j)->getKartons()) {
			cout << "KartonNr im Fach "<< j << ". "<<  k->getKartonNr() << endl;
		}
	}

	// Fach 0 wird überprüft => 0
	cout << "Vor dem Umlagern >> Ist das Verkaufsfach voll ? " << seg32.getFach(0)->istVoll() << endl;

	// Umlagern
	la.umlagern(2);

	// Fach 0 wird überprüft => 1
	cout << "Nach dem Umlagern >> Ist Voll ? " << seg32.getFach(0)->istVoll() << endl;

	// Lagerbestand wird ausgegeben - 
	for (int j = 0; j < seg32.getFaecher().size(); j++) {
		for (Karton *k : seg32.getFach(j)->getKartons()) {
			cout << "KartonNr im Fach " << j << ". " << k->getKartonNr() << endl;
		}
	}



	// Zur Überprüfung der Aufgabe 1.3
	//string barcode = "";
	//cout << la.scanneKarton() << endl;



	return 0;
}

