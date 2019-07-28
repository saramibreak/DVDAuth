#include <string.h>

#include "dvd_command.h"

HANDLE h_dvd;
SCSI_PASS_THROUGH_DIRECT sptd;
uint8_t *sptd_buf = NULL;

void ioctl_Init(int i_type, int i_size)
{
	if (sptd_buf)
		free(sptd_buf);
	sptd_buf = (uint8_t *)malloc(i_size);
	memset(&sptd, 0, sizeof(SCSI_PASS_THROUGH_DIRECT));
	sptd.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
	sptd.DataBuffer = sptd_buf;
	sptd.DataTransferLength = i_size;
	memset(sptd.DataBuffer, 0, sptd.DataTransferLength);
	switch(i_type)
	{
	case GPCMD_SEND_KEY:
		sptd.DataIn = SCSI_IOCTL_DATA_OUT;
		break;
	case GPCMD_READ_DISC_STRUCTURE:
	case GPCMD_REPORT_KEY:
		sptd.DataIn = SCSI_IOCTL_DATA_IN;
		break;
	}
	sptd.Cdb[0] = i_type;
	sptd.Cdb[8] = (uint8_t)(sptd.DataTransferLength >> 8) & 0xff;
	sptd.Cdb[9] = (uint8_t)(sptd.DataTransferLength >> 0) & 0xff;
	sptd.CdbLength = 12;
	sptd.TimeOutValue = 2;
}

int ioctl_Send(int *p_bytes)
{
	return DeviceIoControl(h_dvd, IOCTL_SCSI_PASS_THROUGH_DIRECT, &sptd, sizeof(sptd), &sptd, sizeof(sptd), (uint32_t*)p_bytes, NULL) ? 0 : -1;
}

int ioctl_ReadPhysical(int i_layer, PDVD_PHYSICAL_DESCRIPTOR p_physical)
{
	int i_bytes;
	int i_ret;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, 2048);
	sptd.Cdb[6] = i_layer;
	sptd.Cdb[7] = DVD_STRUCT_PHYSICAL;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
	{
		memcpy(p_physical, &sptd_buf[4], sizeof(DVD_PHYSICAL_DESCRIPTOR));
		B2N_32(p_physical->StartPhysicalSectorOfDataArea);
		B2N_32(p_physical->EndPhysicalSectorOfDataArea);
		B2N_32(p_physical->EndPhysicalSectorOfLayer0);
	}
	return i_ret;
}

int ioctl_ReadCopyright(int i_layer, PDVD_COPYRIGHT_DESCRIPTOR p_copyright)
{
	int i_bytes;
	int i_ret;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, 8);
	sptd.Cdb[6] = i_layer;
	sptd.Cdb[7] = DVD_STRUCT_COPYRIGHT;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
		memcpy(p_copyright, &sptd_buf[4], sizeof(DVD_COPYRIGHT_DESCRIPTOR));
	return i_ret;
}

int ioctl_ReadDiscKey(int *p_agid, uint8_t *p_key)
{
	int i_bytes;
	int i_ret;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, DVD_DISCKEY_SIZE + 4);
	sptd.Cdb[7]  = DVD_STRUCT_DISCKEY;
	sptd.Cdb[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
		memcpy(p_key, sptd_buf + 4, DVD_DISCKEY_SIZE);
	return i_ret;
}

int ioctl_ReadTitleKey(int *p_agid, int i_pos, uint8_t *p_key)
{
	uint8_t buf[DVD_TITLE_KEY_LENGTH];
	DWORD i_bytes;
	int i_ret;
	PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_TITLE_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdTitleKey;
	key->KeyFlags   = 0;
	key->Parameters.TitleOffset.QuadPart = (int64_t)i_pos * 2048;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
		memcpy(p_key, key->KeyData, DVD_KEY_SIZE);
	return i_ret;
}

int ioctl_ReportAgidCssCppm(int *p_protection, int *p_agid)
{
	int i_bytes;
	int i_ret;
	ioctl_Init(GPCMD_REPORT_KEY, 8);
	sptd.Cdb[10] = DVD_REPORT_AGID_CSSCPPM | (*p_agid << 6);
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0 && *(uint16_t*)&sptd_buf[0] == 0x0600)
	{
		*p_protection = DvdProtCSSCPPM;
		*p_agid = sptd_buf[7] >> 6;
		return 0;
	}
	return -1;
}

int ioctl_ReportAgidCprm(int *p_protection, int *p_agid)
{
	int i_bytes;
	int i_ret;
	ioctl_Init(GPCMD_REPORT_KEY, 8);
	sptd.Cdb[10] = DVD_REPORT_AGID_CPRM | (*p_agid << 6);
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0 && *(uint16_t*)&sptd_buf[0] == 0x0600)
	{
		*p_protection = DvdProtCPRM;
		*p_agid = sptd_buf[7] >> 6;
		return 0;
	}
	return -1;
}

int ioctl_ReportChallenge(int *p_agid, uint8_t *p_challenge)
{
	uint8_t buf[DVD_CHALLENGE_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	int i_ret;
	key =  (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_CHALLENGE_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdChallengeKey;
	key->KeyFlags   = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
		memcpy(p_challenge, key->KeyData, DVD_CHALLENGE_SIZE);
	return i_ret;
}

int ioctl_ReportASF(int *p_remove_me, int *p_asf)
{
	uint8_t buf[DVD_ASF_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	int i_ret;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_ASF_LENGTH;
	key->KeyType    = DvdAsf;
	key->KeyFlags   = 0;
	((PDVD_ASF)key->KeyData)->SuccessFlag = *p_asf;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
		*p_asf = ((PDVD_ASF)key->KeyData)->SuccessFlag;
	return i_ret;
}

int ioctl_ReportKey1(int *p_agid, uint8_t *p_key)
{
	uint8_t buf[DVD_BUS_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	int i_ret;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_BUS_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdBusKey1;
	key->KeyFlags   = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL ) ? 0 : -1;
	if (i_ret == 0)
		memcpy(p_key, key->KeyData, DVD_KEY_SIZE);
	return i_ret;
}

int ioctl_InvalidateAgid(int *p_agid)
{
	DWORD i_bytes;
	int i_ret;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_END_SESSION, p_agid, sizeof(*p_agid), NULL, 0, &i_bytes, NULL ) ? 0 : -1;
	return i_ret;
}

int ioctl_SendChallenge(int *p_agid, uint8_t *p_challenge)
{
	uint8_t buf[DVD_CHALLENGE_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	int i_ret;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_CHALLENGE_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdChallengeKey;
	key->KeyFlags   = 0;
	memcpy(key->KeyData, p_challenge, DVD_CHALLENGE_SIZE);
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_SEND_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	return i_ret;
}

int ioctl_SendKey2(int *p_agid, uint8_t *p_key)
{
	uint8_t buf[DVD_BUS_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	int i_ret;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_BUS_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdBusKey2;
	key->KeyFlags   = 0;
	memcpy(key->KeyData, p_key, DVD_KEY_SIZE);
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_SEND_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	return i_ret;
}

int ioctl_ReportRPC(int *p_type, int *p_mask, int *p_scheme)
{
	uint8_t buf[DVD_RPC_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	int i_ret;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_RPC_KEY_LENGTH;
	key->KeyType    = DvdGetRpcKey;
	key->KeyFlags   = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL);
	if (i_ret == 0)
	{
		*p_type = ((PDVD_RPC_KEY)key->KeyData)->TypeCode;
		*p_mask = ((PDVD_RPC_KEY)key->KeyData)->RegionMask;
		*p_scheme = ((PDVD_RPC_KEY)key->KeyData)->RpcScheme;
	}
	return i_ret;
}
