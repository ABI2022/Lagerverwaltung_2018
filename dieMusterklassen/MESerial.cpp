#include "StdAfx.h"
#include "MESerial.h"

MESerial::MESerial(string iportName, int ibaudrate, int idataBits, int istopBits, int iparity)
{
	portName = iportName;
	baudrate = ibaudrate;
	dataBits = idataBits;
	stopBits = istopBits;
	parity = iparity;
	handle = INVALID_HANDLE_VALUE;
	lastsate = 0;
}

MESerial::~MESerial()
{
}

bool MESerial::openPort()
{
	return true; // nur für die Überprüfung der Aufgabe 1.4
}
//	char szPort[15];
//	wsprintf (szPort, "\\\\.\\%s", portName.c_str());
//	
//	/*
//	!!! Wichtig !!!:
//	Zeichensatz einstellen unter Projekteigenschaften
//		=> 2 Varianten
//		   1.) Unicode-Zeichensatz (Standard/ CreateFileW wird genutzt)
//		   2.) Multi-Byte-Zeichensatz (CreateFileA wird genutzt)
//		   --> Variante 1 geht nicht <--
//	*/
//
//	handle =	CreateFile(szPort,
//				GENERIC_READ | GENERIC_WRITE,
//				0,
//				NULL,
//				OPEN_EXISTING,
//				FILE_ATTRIBUTE_NORMAL,
//				NULL);
//
//	if (handle == INVALID_HANDLE_VALUE)
//	{
//		handle = NULL;
//		return false;
//	}
//
//	DCB dcb;
//	ZeroMemory (&dcb, sizeof(dcb));
//	dcb.DCBlength = sizeof(DCB);
//
//	if (!GetCommState (handle, &dcb))
//	{
//		closePort();
//		return false;
//	}
//
//	dcb.BaudRate = baudrate;
//	dcb.ByteSize = (BYTE)dataBits;
//	dcb.StopBits = (BYTE)stopBits;
//	//dcb.ByteSize = (dataBits)? 8:7;
//	dcb.Parity   = (BYTE)parity;
//	//dcb.fParity = (Parity!=0)? TRUE:FALSE;
//	dcb.fParity = (dcb.Parity != NOPARITY);
//	dcb.fBinary      	= TRUE;
//	dcb.fOutxCtsFlow 	= FALSE;
//	dcb.fOutxDsrFlow 	= FALSE;
//	dcb.fDtrControl	= DTR_CONTROL_ENABLE;
//	dcb.fRtsControl	= RTS_CONTROL_ENABLE;
//	dcb.fDsrSensitivity= FALSE;
//	dcb.fAbortOnError	= FALSE;
//
//	if (!SetCommState(handle, &dcb))
//	{
//		closePort();
//		return false;
//	}
//
//	return true;
//}

// Schnittstelle schließen
bool MESerial::closePort()
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(handle);
		handle   = INVALID_HANDLE_VALUE;
		return false;
	}
	return true; 
}

// Setzt die DTR-Leitung auf high (mode = true) oder low (mode = false)
bool MESerial::SetDTR (bool mode)
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		if (mode == true)
			EscapeCommFunction(handle, SETDTR);// setzen
		else
			EscapeCommFunction(handle, CLRDTR);// Loeschen

		return false;
	}
	else
	{
		return true;
	}
}

// Setzt die RTS-Leitung auf high (mode = true) oder low (mode = false)
bool MESerial::SetRTS (bool mode)
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		if (mode == true)
			EscapeCommFunction(handle, SETRTS);// setzen
		else
			EscapeCommFunction(handle, CLRRTS);// Loeschen

		return false;
	}
	else
	{
		return true;
	}
}

bool MESerial::SetTXD (bool mode)
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		if(mode==ON) 
		{   
			EscapeCommFunction(handle, SETBREAK);  // setzen 
		} 
		else 
		{ 
			EscapeCommFunction(handle, CLRBREAK);  // Loeschen     
		}
		return false;
	}
	else
	{
		return true; 
	}
}

bool MESerial::SetAll (bool mode)
{
	SetRTS(mode); 
    SetDTR(mode);
	SetTXD(mode);  
	return false;
}

// Modem-Statusinformationen ermitteln (hier CTS)
bool MESerial::GetCTS()
{
  GetCommModemStatus(handle, &COMStatus);
  if(COMStatus & MS_CTS_ON) 
    { 
        return true; 
    } 
   return false;
}

// Modem-Statusinformationen ermitteln (hier DSR)
bool MESerial::GetDSR()
{
    GetCommModemStatus(handle, &COMStatus);   
    if(COMStatus & MS_DSR_ON) 
    { 
        return true; 
    } 
    return false; 
}

bool MESerial::GetRI()
{
	GetCommModemStatus(handle, &COMStatus);   
    if(COMStatus & MS_RING_ON) 
    { 
        return true; 
    } 
    return false; 
}

bool MESerial::GetDCD()
{
	GetCommModemStatus(handle, &COMStatus);   
    if(COMStatus & MS_RLSD_ON) 
    { 
        return true; 
    } 
    return false; 
}

int MESerial::read()
{
	if (handle == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	else
	{
		if(ComGetReadCount()==0)return lastsate;
		DWORD dwRead = 0;
		char chRead;
		if(!ReadFile(handle, &chRead, 1, &dwRead, NULL))return -1;
		lastsate = chRead;
		return chRead;
	}
}

// Daten empfangen (Empfangspuffer leeren)
// buffer: Zeiger auf Puffer, welcher die Daten übernehmen soll
// bufSize: Größe des Puffers
// Ergebnis: Anzahl Datenbytes, die tatsächlich in den Puffer geschrieben wurden
int MESerial::read(char *buffer)
{
	if (handle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	else
	{
		DWORD bytesRead = 0;
		while(ComGetReadCount() ==0);
		int bufSize = ComGetReadCount();
		if(!ReadFile(handle, buffer, bufSize, &bytesRead, NULL))return -1;
			return bytesRead;
	}
}

// Text empfangen bis LF(Linefeed) empfangen
// Ergebnis: Eingelesener Text
string MESerial::readLine()
{
	const int LF = 0x0A;
	int ch;
	string result = "";
	if (handle != INVALID_HANDLE_VALUE)
	{
		ch = read();
		while (ch != LF){
			result += char(ch);
			ch = read();
		}
	}
	return result;
	//string test = "x";
	//test += "BARCODE";
	//test += '\n';
	//cout << test << endl;

	//	return test;
}
//	Ein Zeichen senden
//	zeichen	: Ist das Zeichen das gesendet werden soll.
void MESerial::write(int zeichen)
{
	DWORD bytesWritten = 0;
	if (handle != INVALID_HANDLE_VALUE)
		WriteFile(handle,&zeichen,1,&bytesWritten,0);
}

// Daten übertragen
// buffer: Zeiger auf zu übertragende Daten
// bytesToWrite: Umfang der zu übertragenden Daten
void MESerial::write(const char *buffer,int bytesToWrite)
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		DWORD bytesWritten;
		WriteFile(handle, buffer, bytesToWrite, &bytesWritten, 0);
	}
}

// Text übertragen
// text: Zu sendender Text
void MESerial::write(string text)
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		DWORD bytesWritten;
		WriteFile(handle, text.c_str(), text.length(), &bytesWritten, NULL);
	}
}

void MESerial::wait(int milli_sek)
{
	clock_t start;
	start = clock();
	while( clock() < start + milli_sek);
}

//	Gibt die Anzahl der Bytes(Zeichen) die im Lesepuffer der Schnittstelle sind zurück

int MESerial::ComGetReadCount()
{
	COMSTAT sComStat;
	DWORD dwErrorFlags = 0;

	if(!ClearCommError(handle, &dwErrorFlags, &sComStat))return 0;
	return sComStat.cbInQue;
}

//	Gibt die Anzahl der Bytes(Zeichen), die im Schreibpuffer der Schnittstelle sind zurück
int MESerial::ComGetWriteCount()
{
	COMSTAT sComStat;
	DWORD dwErrorFlags = 0;
	if(!ClearCommError(handle, &dwErrorFlags, &sComStat))return 0;
	return sComStat.cbOutQue;
}

string MESerial::GetName()
{
	return portName;
}
