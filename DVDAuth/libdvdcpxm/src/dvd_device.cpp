#include "dvd_device.h"

#ifdef _WIN32
HANDLE dvddev_open(char *psz_target)
#else
int dvddev_open(char* psz_target)
#endif
{
#ifdef _WIN32
	HANDLE h_target;
	h_target = CreateFile(psz_target, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
	if (h_target == INVALID_HANDLE_VALUE)
		h_target = CreateFile(psz_target, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
#else
	int h_target;
	h_target = open(psz_target, O_RDONLY | O_NONBLOCK, 0777);
#endif
	return h_target;
}

#ifdef _WIN32
void dvddev_close(HANDLE h_target)
#else
void dvddev_close(int h_target)
#endif
{
	CloseHandle(h_target);
}

