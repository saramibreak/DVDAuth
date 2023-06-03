#include <string.h>

#include "dvd_command.h"

#ifdef _WIN32
HANDLE h_dvd;
SCSI_PASS_THROUGH_DIRECT sptd;
#else
int h_dvd;
SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER swb;
uint8_t* cmd = NULL;
#endif
uint8_t *sptd_buf = NULL;

extern VOID OutputLastErrorNumAndString(LPCTSTR pszFuncName, LONG lLineNum);

void ioctl_Init(int i_type, int i_size)
{
	if (sptd_buf)
		free(sptd_buf);
	sptd_buf = (uint8_t *)malloc(i_size);
#ifdef _WIN32
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
#elif __linux__
	memset(&swb, 0, sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER));
	swb.io_hdr.interface_id = 'S';
	switch (i_type)
	{
	case GPCMD_SEND_KEY:
		swb.io_hdr.dxfer_direction = SG_DXFER_TO_DEV;
		break;
	case GPCMD_READ_DISC_STRUCTURE:
	case GPCMD_REPORT_KEY:
		swb.io_hdr.dxfer_direction = SG_DXFER_FROM_DEV;
		break;
	}
	swb.io_hdr.cmd_len = 12;
	swb.io_hdr.mx_sb_len = sizeof(swb.Dummy);
	swb.io_hdr.dxfer_len = i_size;
	swb.io_hdr.dxferp = sptd_buf;
	memset(swb.io_hdr.dxferp, 0, swb.io_hdr.dxfer_len);
	if (cmd)
		free(cmd);
	cmd = (uint8_t*)malloc(swb.io_hdr.cmd_len);
	swb.io_hdr.cmdp = cmd;
	memset(swb.io_hdr.cmdp, 0, swb.io_hdr.cmd_len);
	swb.io_hdr.cmdp[0] = i_type;
	swb.io_hdr.cmdp[8] = (uint8_t)(swb.io_hdr.dxfer_len >> 8) & 0xff;
	swb.io_hdr.cmdp[9] = (uint8_t)(swb.io_hdr.dxfer_len >> 0) & 0xff;
	swb.io_hdr.sbp = swb.Dummy;
	swb.io_hdr.timeout = 2;
#endif
}

int ioctl_Send(int *p_bytes)
{
#ifdef _WIN32
	return DeviceIoControl(h_dvd, IOCTL_SCSI_PASS_THROUGH_DIRECT, &sptd, sizeof(sptd), &sptd, sizeof(sptd), (LPDWORD)p_bytes, NULL) ? 0 : -1;
#elif __linux__
	return DeviceIoControl(h_dvd, IOCTL_SCSI_PASS_THROUGH_DIRECT, &swb, sizeof(swb), &swb, sizeof(swb), (unsigned long*)p_bytes, NULL) ? 0 : -1;
#else
	return -1;
#endif
}

int ioctl_ReadPhysical(int i_layer, PDVD_PHYSICAL_DESCRIPTOR p_physical)
{
	int i_ret;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, 2048);
#ifdef _WIN32
	int i_bytes;
	sptd.Cdb[6] = i_layer;
	sptd.Cdb[7] = DVD_STRUCT_PHYSICAL;
	i_ret = ioctl_Send(&i_bytes);
#elif __linux__
	int i_bytes;
	swb.io_hdr.cmdp[6] = i_layer;
	swb.io_hdr.cmdp[7] = DVD_STRUCT_PHYSICAL;
	i_ret = ioctl_Send(&i_bytes);
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_read_structure_t, DVDPhysicalFormatInfo,
                   kDVDStructureFormatPhysicalFormatInfo );

    dvd.layer = i_layer;

    i_ret = ioctl( h_dvd, DKIOCDVDREADSTRUCTURE, &dvd );
	memcpy(sptd_buf, dvd.buffer, sizeof(dvd.bufferLength));
#endif
	if (i_ret == 0)
	{
		memcpy(p_physical, &sptd_buf[4], sizeof(DVD_PHYSICAL_DESCRIPTOR));
		B2N_32(p_physical->StartPhysicalSectorOfDataArea);
		B2N_32(p_physical->EndPhysicalSectorOfDataArea);
		B2N_32(p_physical->EndPhysicalSectorOfLayer0);
	}
	else
	{
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	}
	return i_ret;
}

int ioctl_ReadCopyright(int i_layer, PDVD_COPYRIGHT_DESCRIPTOR p_copyright)
{
	int i_ret;
#ifdef _WIN32
	int i_bytes;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, 8);
	sptd.Cdb[6] = i_layer;
	sptd.Cdb[7] = DVD_STRUCT_COPYRIGHT;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
		memcpy(p_copyright, &sptd_buf[4], sizeof(DVD_COPYRIGHT_DESCRIPTOR));
#elif __linux__
	int i_bytes;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, 8);
	swb.io_hdr.cmdp[6] = i_layer;
	swb.io_hdr.cmdp[7] = DVD_STRUCT_COPYRIGHT;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
		memcpy(p_copyright, &sptd_buf[4], sizeof(DVD_COPYRIGHT_DESCRIPTOR));
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_read_structure_t, DVDCopyrightInfo,
                   kDVDStructureFormatCopyrightInfo );

    dvd.layer = i_layer;

    i_ret = ioctl( h_dvd, DKIOCDVDREADSTRUCTURE, &dvd );

	if (i_ret == 0)
		p_copyright->CopyrightProtectionType = dvdbs.copyrightProtectionSystemType;
#endif
	else
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	return i_ret;
}

int ioctl_ReadDiscKey(int *p_agid, uint8_t *p_key)
{
	int i_ret;
#ifdef _WIN32
#if 1
	uint8_t buf[DVD_DISC_KEY_LENGTH];
	DWORD i_bytes;
	PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength = DVD_DISC_KEY_LENGTH;
	key->SessionId = *p_agid;
	key->KeyType = DvdDiskKey;
	key->KeyFlags = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
		memcpy(p_key, key->KeyData, DVD_DISCKEY_SIZE);
#else
	int i_bytes;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, DVD_DISCKEY_SIZE + 4);
	sptd.Cdb[7] = DVD_STRUCT_DISCKEY;
	sptd.Cdb[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
		memcpy(p_key, sptd_buf + 4, DVD_DISCKEY_SIZE);
#endif
#elif __linux__
	int i_bytes;
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, DVD_DISCKEY_SIZE + 4);
	swb.io_hdr.cmdp[7] = DVD_STRUCT_DISCKEY;
	swb.io_hdr.cmdp[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0)
		memcpy(p_key, sptd_buf + 4, DVD_DISCKEY_SIZE);
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_read_structure_t, DVDDiscKeyInfo,
                   kDVDStructureFormatDiscKeyInfo );

    dvd.grantID = *p_agid;

    i_ret = ioctl( h_dvd, DKIOCDVDREADSTRUCTURE, &dvd );

	if (i_ret == 0)
	    memcpy( p_key, dvdbs.discKeyStructures, DVD_DISCKEY_SIZE );
#endif
	else
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	return i_ret;
}

int ioctl_ReadTitleKey(int *p_agid, int i_pos, uint8_t *p_key)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_TITLE_KEY_LENGTH];
	DWORD i_bytes;
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
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_LU_SEND_TITLE_KEY;
	ai.lstk.agid = *p_agid;
	ai.lstk.lba = i_pos;
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
	if (i_ret == 0)
		memcpy(p_key, ai.lstk.title_key, DVD_KEY_SIZE);
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDTitleKeyInfo,
                   kDVDKeyFormatTitleKey );

    dvd.address = i_pos;
    dvd.grantID = *p_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0)
	    memcpy( p_key, dvdbs.titleKeyValue, DVD_KEY_SIZE );
#endif
	else
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	return i_ret;
}

int ioctl_ReportAgidCssCppm(int *p_protection, int *p_agid)
{
	int i_ret;
#ifdef _WIN32
	int i_bytes;
	ioctl_Init(GPCMD_REPORT_KEY, 8);
	sptd.Cdb[10] = DVD_REPORT_AGID_CSSCPPM | (*p_agid << 6);
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0 && *(uint16_t*)&sptd_buf[0] == 0x0600)
	{
		*p_protection = DvdProtCSSCPPM;
		*p_agid = sptd_buf[7] >> 6;
		return 0;
	}
#elif __linux__
	int i_bytes;
	ioctl_Init(GPCMD_REPORT_KEY, 8);
	dvd_authinfo ai;
	ai.type = DVD_LU_SEND_AGID;
	ai.lsa.agid = *p_agid;
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
	if (i_ret == 0)
	{
		*p_protection = DvdProtCSSCPPM;
		*p_agid = ai.lsa.agid;
		return 0;
	}
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDAuthenticationGrantIDInfo,
                   kDVDKeyFormatAGID_CSS );

    dvd.grantID = *p_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0) {
		*p_protection = DvdProtCSSCPPM;
	    *p_agid = dvdbs.grantID;
	}
#endif
	return i_ret;
}

int ioctl_ReportAgidCprm(int *p_protection, int *p_agid)
{
	int i_ret;
#ifdef _WIN32
	int i_bytes;
	ioctl_Init(GPCMD_REPORT_KEY, 8);
	sptd.Cdb[10] = DVD_REPORT_AGID_CPRM | (*p_agid << 6);
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0 && *(uint16_t*)&sptd_buf[0] == 0x0600)
	{
		*p_protection = DvdProtCPRM;
		*p_agid = sptd_buf[7] >> 6;
		return 0;
	}
#elif __linux__
	int i_bytes;
	ioctl_Init(GPCMD_REPORT_KEY, 8);
	swb.io_hdr.cmdp[10] = DVD_REPORT_AGID_CPRM | (*p_agid << 6);
	i_ret = ioctl_Send(&i_bytes);
	if (i_ret == 0 && *(uint16_t*)&sptd_buf[0] == 0x0600)
	{
		*p_protection = DvdProtCPRM;
		*p_agid = sptd_buf[7] >> 6;
		return 0;
	}
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDAuthenticationGrantIDInfo,
                   kDVDKeyFormatAGID_CPRM );

    dvd.grantID = *p_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0) {
		*p_protection = DvdProtCPRM;
	    *p_agid = dvdbs.grantID;
		return 0;
	}
#endif
	return -1;
}

int ioctl_ReportChallenge(int *p_agid, uint8_t *p_challenge)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_CHALLENGE_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	key =  (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_CHALLENGE_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdChallengeKey;
	key->KeyFlags   = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
		memcpy(p_challenge, key->KeyData, DVD_CHALLENGE_SIZE);
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_LU_SEND_CHALLENGE;
	ai.lsc.agid = *p_agid;
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
	if (i_ret == 0)
		memcpy(p_challenge, ai.lsc.chal, DVD_CHALLENGE_SIZE);
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDChallengeKeyInfo,
                   kDVDKeyFormatChallengeKey );

    dvd.grantID = *p_agid;

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0)
	    memcpy( p_challenge, dvdbs.challengeKeyValue, DVD_CHALLENGE_SIZE );
#endif
	else
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	return i_ret;
}

int ioctl_ReportASF(int *p_agid, int *p_asf)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_ASF_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_ASF_LENGTH;
	key->SessionId = *p_agid;
	key->KeyType    = DvdAsf;
	key->KeyFlags   = 0;
	((PDVD_ASF)key->KeyData)->SuccessFlag = *p_asf;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
		*p_asf = ((PDVD_ASF)key->KeyData)->SuccessFlag;
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_LU_SEND_ASF;
	ai.lsasf.agid = *p_agid;
	ai.lsasf.asf = *p_asf;
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
	if (i_ret == 0)
		*p_asf = ai.lsasf.asf;
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDAuthenticationSuccessFlagInfo,
                   kDVDKeyFormatASF );

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0)
	    *p_asf = dvdbs.successFlag;
#endif
	else
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	return i_ret;
}

int ioctl_ReportKey1(int *p_agid, uint8_t *p_key)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_BUS_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_BUS_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdBusKey1;
	key->KeyFlags   = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key, key->KeyLength, key, key->KeyLength, &i_bytes, NULL ) ? 0 : -1;
	if (i_ret == 0)
		memcpy(p_key, key->KeyData, DVD_KEY_SIZE);
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_LU_SEND_KEY1;
	ai.lsk.agid = *p_agid;
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
	if (i_ret == 0)
		memcpy(p_key, ai.lsk.key, DVD_KEY_SIZE);
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDKey1Info,
                   kDVDKeyFormatKey1 );

    dvd.grantID = *p_agid;

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0)
	    memcpy( p_key, dvdbs.key1Value, DVD_KEY_SIZE );
#endif
	else
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	return i_ret;
}

int ioctl_InvalidateAgid(int *p_agid)
{
	int i_ret;
#ifdef _WIN32
	DWORD i_bytes;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_END_SESSION
		, p_agid, sizeof(*p_agid), NULL, 0, &i_bytes, NULL ) ? 0 : -1;
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_INVALIDATE_AGID;
	ai.lsa.agid = *p_agid;
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_send_key_t, DVDAuthenticationGrantIDInfo,
                   kDVDKeyFormatAGID_Invalidate );

    dvd.grantID = *p_agid;

    i_ret = ioctl( h_dvd, DKIOCDVDSENDKEY, &dvd );
#endif
	return i_ret;
}

int ioctl_SendChallenge(int *p_agid, uint8_t *p_challenge)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_CHALLENGE_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_CHALLENGE_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdChallengeKey;
	key->KeyFlags   = 0;
	memcpy(key->KeyData, p_challenge, DVD_CHALLENGE_SIZE);
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_SEND_KEY, key
		, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_HOST_SEND_CHALLENGE;
	ai.hsc.agid = *p_agid;
	memcpy(ai.hsc.chal, p_challenge, DVD_CHALLENGE_SIZE);
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
#elif __MACH__
	INIT_DVDIOCTL( dk_dvd_send_key_t, DVDChallengeKeyInfo,
                   kDVDKeyFormatChallengeKey );

    dvd.grantID = *p_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    dvdbs.dataLength[ 1 ] = 0xe;
    memcpy( dvdbs.challengeKeyValue, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = ioctl( h_dvd, DKIOCDVDSENDKEY, &dvd );
#endif
	return i_ret;
}

int ioctl_SendKey2(int *p_agid, uint8_t *p_key)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_BUS_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_BUS_KEY_LENGTH;
	key->SessionId  = *p_agid;
	key->KeyType    = DvdBusKey2;
	key->KeyFlags   = 0;
	memcpy(key->KeyData, p_key, DVD_KEY_SIZE);
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_SEND_KEY, key
		, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
#elif __linux__
	dvd_authinfo ai;
	ai.type = DVD_HOST_SEND_KEY2;
	ai.hsk.agid = *p_agid;
	memcpy(ai.hsk.key, p_key, DVD_KEY_SIZE);
	i_ret = ioctl(h_dvd, DVD_AUTH, &ai);
#elif __MACH__
	INIT_DVDIOCTL( dk_dvd_send_key_t, DVDKey2Info,
                   kDVDKeyFormatKey2 );

    dvd.grantID = *p_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    dvdbs.dataLength[ 1 ] = 0xa;
    memcpy( dvdbs.key2Value, p_key, DVD_KEY_SIZE );

    i_ret = ioctl( h_dvd, DKIOCDVDSENDKEY, &dvd );
#endif
	return i_ret;
}

int ioctl_ReportRPC(int *p_type, int *p_mask, int *p_scheme)
{
	int i_ret;
#ifdef _WIN32
	uint8_t buf[DVD_RPC_KEY_LENGTH];
	PDVD_COPY_PROTECT_KEY key;
	DWORD i_bytes;
	key = (PDVD_COPY_PROTECT_KEY)&buf;
	memset(&buf, 0, sizeof(buf));
	key->KeyLength  = DVD_RPC_KEY_LENGTH;
	key->KeyType    = DvdGetRpcKey;
	key->KeyFlags   = 0;
	i_ret = DeviceIoControl(h_dvd, IOCTL_DVD_READ_KEY, key
		, key->KeyLength, key, key->KeyLength, &i_bytes, NULL) ? 0 : -1;
	if (i_ret == 0)
	{
		*p_type = ((PDVD_RPC_KEY)key->KeyData)->TypeCode;
		*p_mask = ((PDVD_RPC_KEY)key->KeyData)->RegionMask;
		*p_scheme = ((PDVD_RPC_KEY)key->KeyData)->RpcScheme;
	}
#elif __linux__
    dvd_authinfo auth_info = { 0 };

    auth_info.type = DVD_LU_SEND_RPC_STATE;

    i_ret = ioctl( h_dvd, DVD_AUTH, &auth_info );

	if (i_ret == 0)
	{
		*p_type = auth_info.lrpcs.type;
		*p_mask = auth_info.lrpcs.region_mask;
		*p_scheme = auth_info.lrpcs.rpc_scheme;
	}
#elif __MACH__
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDRegionPlaybackControlInfo,
                   kDVDKeyFormatRegionState );

    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    i_ret = ioctl( h_dvd, DKIOCDVDREPORTKEY, &dvd );

	if (i_ret == 0)
	{
		*p_type = dvdbs.typeCode;
		*p_mask = dvdbs.driveRegion;
		*p_scheme = dvdbs.rpcScheme;
	}
#endif
	else
	{
		OutputLastErrorNumAndString(__FUNCTION__, __LINE__);
	}
	return i_ret;
}
