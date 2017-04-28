Description:

This small project implements a cache for finding sales taxes at various addresses. For simplicity's sake, a few assumptions were made:
1. Sales tax rate is returned as a float
2. Address is represented as a string

Compilation:
This project was created with VS2015 and will build with MSBuild. Additionally, compilation was tested with CLANG, and that works as well. 

Usage:
In order to use the cache, create a SalesTaxFinder with the max number of elements that it can hold. Then make calls to fast_rate_lookup