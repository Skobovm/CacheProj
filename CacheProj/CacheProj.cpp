// CacheProj.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "SalesTaxFinder.h"

#define SPIN_AT_END

int main()
{
	LogEvent("Start Main");

	// TODO: tests and such go here

	LogEvent("End Main");

#ifdef SPIN_AT_END
	while (1) 
	{
		// Spin to see log
	}
#endif

    return 0;
}

