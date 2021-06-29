#pragma once

class IOPortAccess
{
public:
	IOPortAccess();
	~IOPortAccess();
	bool openDriver();
	void closeDriver();
	void writePort(int,int);
	int readPort(int);
};