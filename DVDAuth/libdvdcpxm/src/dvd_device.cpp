#include "dvd_device.h"

HANDLE dvddev_open(char *psz_target)
{
	HANDLE h_target;
	h_target = CreateFile(psz_target, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
	if (h_target == INVALID_HANDLE_VALUE)
		h_target = CreateFile(psz_target, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
	return h_target;
}

void dvddev_close(HANDLE h_target)
{
	CloseHandle(h_target);
}

