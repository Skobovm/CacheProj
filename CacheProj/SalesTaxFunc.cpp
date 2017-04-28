#pragma weak sales_tax_lookup
#include <string>

// NOTE: This function is declared as weak, meaning any other
//		 function with the same name will be linked over this one.
//		 If you have your own function to test with, just add
//		 it to the project, and it should build, and override
//		 this one. Some compilers do not support weak, so if that
//		 is the case, just modify this one.
float sales_tax_lookup(std::string address)
{
	return 0.0;
}