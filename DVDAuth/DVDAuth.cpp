#include "dvd_css.h"
#include "dvdcpxm.h"
#include "execScsiCmdforFileSystem.h"

CHAR logBufferA[DISC_RAW_READ_SIZE];
FILE* fpLog;

int main(int argc, char** argv)
{
	if (argc == 4) {
		fpLog = fopen(argv[3], "w");
		if (!fpLog) {
			fprintf(stderr, "Couldn't create %s\n", argv[3]);
			return 1;
		}
		if (!strncmp(argv[2], "css", 3)) {
			char szBuf[8] = { 0 };
			_snprintf(szBuf, 8, "\\\\.\\%c:", argv[1][0]);
			szBuf[7] = 0;
			DEVICE device = {};
			device.hDevice = CreateFile(szBuf, GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

			device.dwMaxTransferLength = 65536;
			device.dwTimeOutValue = 60;
			CDB::_READ12 cdb = {};
			cdb.OperationCode = SCSIOP_READ12;
			BYTE buf[2048] = {};
			VOB vob[256] = {};
			ReadDVDForFileSystem(&device, &cdb, buf, vob);
			CloseHandle(device.hDevice);

			memcpy(&css.vob, vob, sizeof(vob));
			dvdcss_init(argv[1]);
		}
		else if (!strncmp(argv[2], "cppm", 4) || !strncmp(argv[2], "cprm", 4)) {
			dvdcpxm_init(argv[1]);
		}
	}
	else {
		printf(
			"Usage: DVDAuth.exe <DriveLetter> <ProtectType> <OutFile>\n"
			"\tProtectType: css or cprm\n"
		);
		return 1;
	}
	return 0;
}
