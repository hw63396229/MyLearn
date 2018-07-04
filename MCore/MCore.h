// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MCORE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MCORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MCORE_EXPORTS
#define MCORE_API __declspec(dllexport)
#else
#define MCORE_API __declspec(dllimport)
#endif

// This class is exported from the MCore.dll
class MCORE_API CMCore {
public:
	CMCore(void);
	// TODO: add your methods here.
};

extern MCORE_API int nMCore;

MCORE_API int fnMCore(void);
