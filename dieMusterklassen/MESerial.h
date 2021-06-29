#pragma once
#include "stdafx.h"
#include "string"

#define ON  true 
#define OFF false

using namespace std;

class MESerial
{
	// Parameter für die Erstellung eines Objektes --> "COM1",9600,8,ONESTOPBIT,NOPARITY
	private:
		// Der Port-Name (COM1, COM2)
		string portName;
		// Die Datenübertragungsrate
		int baudrate;
		// Die Anzahl der Datenbits (5 .. 8)
		int dataBits;
		// Der Anzahl der Stoppbits (ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS)
		int stopBits;
		// Festlegung der Parität (EVENPARITY, NOPARITY, ODDPARITY,SPACEPARITY,MARKPARITY)
		int parity;

		char lastsate;

		// Handle für den Com-Port
		HANDLE handle;
		
		//Word zum Speichern des Status 
		DWORD COMStatus;
	
	public:
		MESerial(string portName, int baudrate, int dataBits, int stopBits, int parity);
		~MESerial();

		bool openPort();
		bool closePort();

		bool SetDTR (bool mode);
		bool SetRTS (bool mode);	
		bool SetTXD (bool mode);
		bool SetAll (bool mode);

		bool GetCTS();
		bool GetDSR();
		bool GetRI();
		bool GetDCD();

		int read();
		int read(char *buffer);
		string readLine();
		
		void write(int zeichen);
		void write(const char *buffer,int bytesToWrite);
		void write(string s);
		
		void wait(int milli_sek);	//Warteschleife mit einer Verzögerung von "milli_sek" ms
		int ComGetWriteCount();		// Anzahl der Zeichen, die im Schreibpuffer stehen
		int ComGetReadCount();		// Anzahl der Zeichen, die im Empfangspuffer stehen

		string GetName();
};