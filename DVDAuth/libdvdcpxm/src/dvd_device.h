#pragma once

#ifdef _WIN32
#include <windows.h>
HANDLE dvddev_open(char* psz_target);
void   dvddev_close(HANDLE h_target);
#else
int dvddev_open(char* psz_target);
void   dvddev_close(int h_target);
#endif
