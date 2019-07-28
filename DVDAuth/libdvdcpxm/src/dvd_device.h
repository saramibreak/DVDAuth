#pragma once

#include <windows.h>

HANDLE dvddev_open (char *psz_target);
void   dvddev_close(HANDLE h_target);
