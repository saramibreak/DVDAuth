#ifndef _LIBDVDCPXM_H
#define _LIBDVDCPXM_H

#define COPYRIGHT_PROTECTION_NONE 0
#define COPYRIGHT_PROTECTION_CPPM 1
#define COPYRIGHT_PROTECTION_CPRM 2

#define CPRM_STRUCT_MEDIA_ID 0x06
#define CPRM_STRUCT_MKB      0x07

#define CPRM_MEDIA_ID_SIZE   20
#define CPRM_MKB_PACK_SIZE   24576
#define CPRM_MKB_SIZE        (16 * CPRM_MKB_PACK_SIZE - 16)

#define CCI_BYTE 0x00;

typedef struct {
	uint8_t  col;
	uint16_t row;
	uint64_t key;
}	device_key_t;

typedef struct {
	struct {
		uint8_t type:4;
		uint8_t reserved:4;
		uint8_t manufacturer_id[2];
		uint8_t serial_number[5];
	} id_media;
	uint8_t dvd_mac[10];
} cprm_media_id_t;

typedef	struct {
	uint8_t mkb_hash[8];
	uint8_t reserved[8];
} cprm_mkb_desc_t;

typedef struct {
	cprm_mkb_desc_t mkb_desc;
	uint8_t         mkb[CPRM_MKB_SIZE];
} cprm_mkb_t;

#endif
