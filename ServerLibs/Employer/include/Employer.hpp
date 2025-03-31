#ifndef _LIBRARY_EMPLOYER_H_
#define _LIBRARY_EMPLOYER_H_

#if defined (_WIN32) || defined (_WIN64)

    #define MYLIB_EXPORT __declspec(dllexport)
    #define MYLIB_IMPORT __declspec(dllimport)

#else
    #define MYLIB_EXPORT __attribute__((visibility("default")))
    #define MYLIB_IMPORT __attribute__((visibility("default")))
    #define MYLIB_HIDDEN __attribute__((visibility("hidden")))
#endif

//list of possible package types
enum MYLIB_EXPORT Packet_Employer{
	P_ChatMessege_E,
	P_Closed_E
};

//the function of defining and executing instructions corresponding to this package
MYLIB_EXPORT bool ProcessPacket(int, Packet_Employer, int, SOCKET*);

#endif /* _LIBRARY_EMPLOYER_H_ */