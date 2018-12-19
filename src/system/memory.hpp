#pragma once

#ifdef WIN32
#include <windows.h>
#include <psapi.h>
#endif

unsigned int getMemoryUsage() { //bytes

#ifdef WIN32
    PROCESS_MEMORY_COUNTERS_EX mem; 
    if (GetProcessMemoryInfo(GetCurrentProcess(),(PROCESS_MEMORY_COUNTERS*)&mem,sizeof(mem)))
        return mem.PrivateUsage;
#endif

    /*
         linux & android & apple? 
         Firstbober? , Dark?
    */

    return 0;
}