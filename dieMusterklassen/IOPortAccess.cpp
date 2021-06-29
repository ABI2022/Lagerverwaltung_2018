#include "StdAfx.h"
#include "IOPortAccess.h"


IOPortAccess::IOPortAccess()
{
}

IOPortAccess::~IOPortAccess()
{
}

bool IOPortAccess::openDriver()
{
	return false;
}

void IOPortAccess::closeDriver()
{

}

void IOPortAccess::writePort(int port,int value)
{

}
int IOPortAccess::readPort(int port)
{
	return 23;
}