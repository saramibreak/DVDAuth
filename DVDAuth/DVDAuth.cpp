﻿#include "dvd_css.h"
#include "dvdcpxm.h"
#include "execScsiCmdforFileSystem.h"

CHAR logBufferA[DISC_RAW_READ_SIZE];
FILE* fpLog;

VOID OutputLastErrorNumAndString(
	LPCTSTR pszFuncName,
	LONG lLineNum
) {
#ifdef _WIN32
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	// http://blog.livedoor.jp/afsoft/archives/52230222.html
	OutputErrorString("[F:%s][L:%lu] GetLastError: %lu, %s\n",
		pszFuncName, lLineNum, GetLastError(), (LPCTSTR)lpMsgBuf);

	LocalFree(lpMsgBuf);
#else
	OutputErrorString("[F:%s][L:%lu] GetLastError: %lu, %s\n",
		pszFuncName, lLineNum, GetLastError(), strerror(GetLastError()));
#endif
}

int main(int argc, char** argv)
{
	if (argc == 4) {
		fpLog = fopen(argv[3], "w");
		if (!fpLog) {
			fprintf(stderr, "Couldn't create %s\n", argv[3]);
			return 1;
		}
		if (!strncmp(argv[2], "css", 3)) {
			DEVICE device = {};
#ifdef _WIN32
			char szBuf[8] = { 0 };
			_snprintf(szBuf, 8, "\\\\.\\%c:", argv[1][0]);
			szBuf[7] = 0;
			device.hDevice = CreateFile(szBuf, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
#elif __linux__
			device.hDevice = open(argv[1], O_RDONLY | O_NONBLOCK, 0777);
#elif __MACH__
			device.hDevice = GetSCSITaskInterface(argv[1]);
#endif
#if defined (_WIN32) || defined (__linux__)
			if (device.hDevice == INVALID_HANDLE_VALUE) {
#elif __MACH__
			if (device.hDevice == NULL) {
#endif
				OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
				return 1;
			}

			device.dwMaxTransferLength = 65536;
			LPBYTE lpBuf = NULL;
			if (NULL == (lpBuf = (LPBYTE)calloc(
				device.dwMaxTransferLength, sizeof(BYTE)))) {
				OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
#if defined (_WIN32) || defined (__linux__)
				CloseHandle(device.hDevice);
#elif __MACH__
				CloseHandleTask(device.hDevice);
#endif
			}
			else {
				device.dwTimeOutValue = 60;
				CDB::_READ12 cdb = {};
				cdb.OperationCode = SCSIOP_READ12;
				VOB vob[256] = {};

				ReadDVDForFileSystem(&device, &cdb, lpBuf, vob);
				free(lpBuf);
#if defined (_WIN32) || defined (__linux__)
				CloseHandle(device.hDevice);
#elif __MACH__
				CloseHandleTask(device.hDevice);
				usleep(5000000);
#endif
				memcpy(&css.vob, vob, sizeof(vob));
				int ret = dvd_init(argv[1], argv[2]);
				if (ret == -1) {
					OutputErrorString("Failed dvd_init\n");
					return 1;
				}
			}
		}
		else if (!strncmp(argv[2], "cppm", 4) || !strncmp(argv[2], "cprm", 4)) {
#ifdef __MACH__
			usleep(5000000);
#endif
			int ret = dvd_init(argv[1], argv[2]);
			if (ret == -1) {
				OutputErrorString("Failed dvd_init\n");
				return 1;
			}
#ifdef __MACH__
			if (!strncmp(argv[2], "cprm", 4)) {
				usleep(50000000);
			}
#endif
		}
		fclose(fpLog);
	}
	else {
		printf(
			"Usage: DVDAuth.exe <DriveLetter> <ProtectType> <OutFile>\n"
			"\tProtectType: css or cppm or cprm\n"
		);
		return 1;
	}
	return 0;
}
