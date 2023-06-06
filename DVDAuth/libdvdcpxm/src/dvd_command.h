#pragma once

#pragma warning(disable:4200)

#include "stdint.h"
#include "dvd_device.h"
#ifdef __MACH__
#include <Kernel.framework/Headers/IOKit/storage/IODVDMediaBSDClient.h>
#define INIT_DVDIOCTL( DKDVD_TYPE, BUFFER_TYPE, FORMAT ) \
    DKDVD_TYPE dvd = { 0 }; \
    BUFFER_TYPE dvdbs = { 0 }; \
    dvd.format = FORMAT; \
    dvd.buffer = &dvdbs; \
    dvd.bufferLength = sizeof(dvdbs);
#endif

#define DVD_KEY_SIZE           5
#define DVD_CHALLENGE_SIZE    10
#define DVD_DISCKEY_SIZE    2048

#define GPCMD_READ_DISC_STRUCTURE 0xad
#define GPCMD_REPORT_KEY          0xa4
#define GPCMD_SEND_KEY            0xa3

#define DVD_STRUCT_PHYSICAL      0x00
#define DVD_STRUCT_COPYRIGHT     0x01
#define DVD_STRUCT_DISCKEY       0x02
#define DVD_STRUCT_BCA           0x03
#define DVD_STRUCT_MANUFACT      0x04

#define DVD_REPORT_AGID_CSSCPPM  0x00
#define DVD_REPORT_CHALLENGE     0x01
#define DVD_SEND_CHALLENGE       0x01
#define DVD_REPORT_KEY1          0x02
#define DVD_SEND_KEY2            0x03
#define DVD_REPORT_TITLE_KEY     0x04
#define DVD_REPORT_ASF           0x05
#define DVD_SEND_RPC             0x06
#define DVD_REPORT_RPC           0x08
#define DVD_REPORT_AGID_CPRM     0x11

#define DVD_CHALLENGE_KEY_LENGTH        (12 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_BUS_KEY_LENGTH              (8 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_TITLE_KEY_LENGTH            (8 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_DISC_KEY_LENGTH             (2048 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_RPC_KEY_LENGTH              (sizeof(DVD_RPC_KEY) + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_ASF_LENGTH                  (sizeof(DVD_ASF) + sizeof(DVD_COPY_PROTECT_KEY))

//typedef uint32_t DVD_SESSION_ID, *PDVD_SESSION_ID;

typedef struct _DVD_PHYSICAL_DESCRIPTOR
{
	uint8_t  PartVersion:4;
	uint8_t  BookType:4;
	uint8_t  MaximumRate:4;
	uint8_t  DiscSize:4;
	uint8_t  LayerType:4;
	uint8_t  TrackPath:1;
	uint8_t  NumberOfLayers:2;
	uint8_t  Reserved1:1;
	uint8_t  TrackDensity:4;
	uint8_t  LinearDensity:4;
	uint32_t StartPhysicalSectorOfDataArea;
	uint32_t EndPhysicalSectorOfDataArea;
	uint32_t EndPhysicalSectorOfLayer0;
	uint8_t  Reserved2:7;
	uint8_t  BCAFlag:1;
} DVD_PHYSICAL_DESCRIPTOR, *PDVD_PHYSICAL_DESCRIPTOR;

typedef enum
{
	DvdProtNone,
	DvdProtCSSCPPM,
	DvdProtCPRM
} DVD_PROT_TYPE;

#ifdef _WIN32
extern HANDLE h_dvd;
extern SCSI_PASS_THROUGH_DIRECT sptd;
#else
extern int h_dvd;
extern SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER swb;
#endif
extern uint8_t *sptd_buf;

extern void ioctl_Init           (int i_type, int i_size);
extern int  ioctl_Send           (int *p_bytes);
extern int  ioctl_ReadPhysical   (int i_layer, PDVD_PHYSICAL_DESCRIPTOR  p_physical);
extern int  ioctl_ReadCopyright  (int i_layer, PDVD_COPYRIGHT_DESCRIPTOR p_copyright);
extern int  ioctl_ReadDiscKey    (int *p_agid, uint8_t *p_key);
extern int  ioctl_ReadTitleKey   (int *p_agid, int i_pos, uint8_t *p_key);
extern int  ioctl_ReportAgidCssCppm(int *p_protection, int *p_agid);
extern int  ioctl_ReportAgidCprm (int *p_protection, int *p_agid);
extern int  ioctl_ReportChallenge(int *p_agid, uint8_t *p_challenge);
extern int  ioctl_ReportASF      (int *p_agid, int *p_asf);
extern int  ioctl_ReportKey1     (int *p_agid, uint8_t *p_key);
extern int  ioctl_InvalidateAgid (int *p_agid);
extern int  ioctl_SendChallenge  (int *p_agid, uint8_t *p_challenge);
extern int  ioctl_SendKey2       (int *p_agid, uint8_t *p_key);
extern int  ioctl_ReportRPC      (int *p_type, int *p_mask, int *p_scheme);
extern int  ioctl_ReadCPRMMediaId(int *p_agid, uint8_t *p_media_id);
extern int  ioctl_ReadCPRMMKBPack(int *p_agid, int mkb_pack, uint8_t *p_mkb_pack, int *p_total_packs);
