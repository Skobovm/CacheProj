// CacheProj.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "SalesTaxFinder.h"
#include <string>

using namespace std;

// Comment out below line if you do not want the command window to stay up
#define SPIN_AT_END

void Test1()
{
	SalesTaxFinder finder(2);

	finder.fast_rate_lookup("one");
	finder.fast_rate_lookup("two");
	finder.fast_rate_lookup("three");
	finder.fast_rate_lookup("two"); // Cache should kick in here
}

int main()
{
	LogEvent("Start Main");

	Test1();

	LogEvent("End Main");

#ifdef SPIN_AT_END
	while (1) 
	{
		// Spin to see log
	}
#endif

    return 0;
}

