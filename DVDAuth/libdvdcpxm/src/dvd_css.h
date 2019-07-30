#pragma once

#include <windows.h>

#include "stdint.h"
#include "dvd_command.h"

#define KEY_SIZE 5

typedef uint8_t dvd_key_t[KEY_SIZE];

typedef struct _css_t
{
	int       protection;
	int       agid;
	dvd_key_t p_bus_key;
	dvd_key_t p_disc_key;
	dvd_key_t p_title_key;
	struct _vob {
		CHAR fname[128];
		INT lba;
		INT idx;
	} vob[256];
} css_t;

extern FILE* fpLog;
extern css_t css;

extern int  GetTitleKey   (int nLBA, unsigned short ProtectionType);
extern int  GetDiscKey    (unsigned short ProtectionType);
extern int  GetBusKey     (unsigned short ProtectionType);
extern int  GetASF        (void);
extern int  GetRPC        (void);
extern void CryptKey      (int i_key_type, int i_variant, uint8_t *p_challenge, uint8_t *p_key);
extern void DecryptKey    (uint8_t invert, uint8_t *p_key, uint8_t *p_crypted, uint8_t *p_result);
extern int  DecryptDiscKey(uint8_t *p_struct_disckey, dvd_key_t p_disc_key);
extern void DecryptTitleKey(uint8_t invert, uint8_t *p_key, uint8_t *p_crypted, uint8_t *p_result);
