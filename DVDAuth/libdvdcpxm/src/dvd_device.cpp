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
#elif __linux__
	int h_target;
	h_target = open(psz_target, O_RDONLY | O_NONBLOCK, 0777);
#elif __MACH__
	char* unmountCmd;
	const char* cmd = "sudo /usr/sbin/diskutil unmountDisk";
	const char* devNull = "> /dev/null";
	size_t cmdLen = strlen(cmd) + strlen(psz_target) + strlen(devNull) + 3;
	if ((unmountCmd = (char*)malloc(cmdLen)) == NULL) {
		fprintf(stderr, "Failed: malloc\n");
		return -1;
	}
	snprintf(unmountCmd, cmdLen, "%s %s %s", cmd, psz_target, devNull);
	printf("unmountCmd: %s\n", unmountCmd);

	if (system(unmountCmd) != 0) {
		free(unmountCmd);
		fprintf(stderr, "Failed: system\n");
		return -1;
	}
	free(unmountCmd);

	int h_target;
	h_target = open(psz_target, O_RDONLY);
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

