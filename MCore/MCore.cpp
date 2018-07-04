// MCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MCore.h"


// This is an example of an exported variable
MCORE_API int nMCore=0;

// This is an example of an exported function.
MCORE_API int fnMCore(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see MCore.h for the class definition
CMCore::CMCore()
{
    return;
}
