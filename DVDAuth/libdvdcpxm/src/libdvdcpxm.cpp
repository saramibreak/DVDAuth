#include <stdio.h>

#include "dvd_command.h"
#include "dvd_css.h"
#include "dvdcpxm.h"
#include "libdvdcpxm.h"

int media_type = 0;
uint64_t media_key = 0;

uint64_t id_album = 0;
uint64_t id_media = 0;
uint64_t vr_k_te  = 0;

uint32_t sbox_f[256];

static uint8_t sbox[256] = {
	0x3a, 0xd0, 0x9a, 0xb6, 0xf5, 0xc1, 0x16, 0xb7, 
	0x58, 0xf6, 0xed, 0xe6, 0xd9, 0x8c, 0x57, 0xfc, 
	0xfd, 0x4b, 0x9b, 0x47, 0x0e, 0x8e, 0xff, 0xf3, 
	0xbb, 0xba, 0x0a, 0x80, 0x15, 0xd7, 0x2b, 0x36, 
	0x6a, 0x43, 0x5a, 0x89, 0xb4, 0x5d, 0x71, 0x19, 
	0x8f, 0xa0, 0x88, 0xb8, 0xe8, 0x8a, 0xc3, 0xae, 
	0x7c, 0x4e, 0x3d, 0xb5, 0x96, 0xcc, 0x21, 0x00, 
	0x1a, 0x6b, 0x12, 0xdb, 0x1f, 0xe4, 0x11, 0x9d, 
	0xd3, 0x93, 0x68, 0xb0, 0x7f, 0x3b, 0x52, 0xb9, 
	0x94, 0xdd, 0xa5, 0x1b, 0x46, 0x60, 0x31, 0xec, 
	0xc9, 0xf8, 0xe9, 0x5e, 0x13, 0x98, 0xbf, 0x27, 
	0x56, 0x08, 0x91, 0xe3, 0x6f, 0x20, 0x40, 0xb2, 
	0x2c, 0xce, 0x02, 0x10, 0xe0, 0x18, 0xd5, 0x6c, 
	0xde, 0xcd, 0x87, 0x79, 0xaf, 0xa9, 0x26, 0x50, 
	0xf2, 0x33, 0x92, 0x6e, 0xc0, 0x3f, 0x39, 0x41, 
	0xaa, 0x5b, 0x7d, 0x24, 0x03, 0xd6, 0x2f, 0xeb, 
	0x0b, 0x99, 0x86, 0x4c, 0x51, 0x45, 0x8d, 0x2e, 
	0xef, 0x07, 0x7b, 0xe2, 0x4d, 0x7a, 0xfe, 0x25, 
	0x5c, 0x29, 0xa2, 0xa8, 0xb1, 0xf0, 0xb3, 0xc4, 
	0x30, 0x7e, 0x63, 0x38, 0xcb, 0xf4, 0x4f, 0xd1, 
	0xdf, 0x44, 0x32, 0xdc, 0x17, 0x5f, 0x66, 0x2a, 
	0x81, 0x9e, 0x77, 0x4a, 0x65, 0x67, 0x34, 0xfa, 
	0x54, 0x1e, 0x14, 0xbe, 0x04, 0xf1, 0xa7, 0x9c, 
	0x8b, 0x37, 0xee, 0x85, 0xab, 0x22, 0x0f, 0x69, 
	0xc5, 0xd4, 0x05, 0x84, 0xa4, 0x73, 0x42, 0xa1, 
	0x64, 0xe1, 0x70, 0x83, 0x90, 0xc2, 0x48, 0x0d, 
	0x61, 0x1c, 0xc6, 0x72, 0xfb, 0x76, 0x74, 0xe7, 
	0x01, 0xd8, 0xc8, 0xd2, 0x75, 0xa3, 0xcf, 0x28, 
	0x82, 0x1d, 0x49, 0x35, 0xc7, 0xbd, 0xca, 0xa6, 
	0xac, 0x0c, 0x62, 0xad, 0xf9, 0x3c, 0xea, 0x2d, 
	0x59, 0xda, 0x3e, 0x97, 0x6d, 0x09, 0xf7, 0x55, 
	0xe5, 0x23, 0x53, 0x9f, 0x06, 0xbc, 0x95, 0x78, 
};

static device_key_t cppm_device_keys[] =
{
	{0x00, 0x4821, 0x6d05086b755c81},
	{0x01, 0x091c, 0x97ace18dd26973},
	{0x02, 0x012a, 0xfefc0a25a38d42},
	{0x03, 0x469b, 0x0780491970db2c},
	{0x04, 0x0f9b, 0x0bedd116d43484},
	{0x05, 0x59b2, 0x566936bcebe294},
	{0x06, 0x5fc8, 0xdc610f649b1fc0},
	{0x07, 0x11de, 0x6ee01d3872c2d9},
	{0x08, 0x52b6, 0xd0132c376e439b},
	{0x09, 0x135f, 0x800faa66206922},
	{0x0a, 0x3806, 0x9d1aa1460885c2},
	{0x0b, 0x2da2, 0x9833f21818ba33},
	{0x0c, 0x113f, 0xd50aa7d022045a},
	{0x0d, 0x11ec, 0x88abee7bb83a32},
	{0x0e, 0x071b, 0x9b45eea4e7d140},
	{0x0f, 0x5c55, 0x5a49f860cca5cf},

	{0x00, 0x0375, 0x1a12793404c279},
	{0x01, 0x4307, 0x61418b44cea550},
	{0x02, 0x1f70, 0x52bde5b73adcda},
	{0x03, 0x1bbc, 0x70a031ae493159},
	{0x04, 0x1f9d, 0x0a570636aedb61},
	{0x05, 0x4e7b, 0xc313563e7883e9},
	{0x06, 0x07c4, 0x32c55f7bc42d45},
	{0x07, 0x4216, 0x4f854df6c1d721},
	{0x08, 0x11c5, 0xc0e3f0f3df33cc},
	{0x09, 0x0486, 0xbfca7754db5de6},
	{0x0a, 0x2f82, 0xa964fc061af87c},
	{0x0b, 0x236a, 0xb96d68856c45d5},
	{0x0c, 0x5beb, 0xd2ca3cbb7d13cc},
	{0x0d, 0x3db6, 0x58cf827ff3c540},
	{0x0e, 0x4b22, 0xbb4037442a869c},
	{0x0f, 0x59b5, 0x3a83e0ddf37a6e},
};

static device_key_t cprm_device_keys[] =
{
	{0x00, 0x0809, 0xd50fe4150d32d2},
	{0x01, 0x0719, 0x3131c69e825462},
	{0x02, 0x0408, 0x7c2e6878b3a494},
	{0x03, 0x040a, 0x3c9f93ec5848a2},
	{0x04, 0x03bc, 0x614f4bda9876a5},
	{0x05, 0x0812, 0x2e901a9227fc47},
	{0x06, 0x090d, 0xeebf4957d53d62},
	{0x07, 0x0322, 0x6314ec2ca6b32b},
	{0x08, 0x0035, 0x14f6d08c096483},
	{0x09, 0x07c5, 0x8f7eff1d689a81},
	{0x0a, 0x069a, 0xff4b538492c611},
	{0x0b, 0x0bd8, 0x909300c14c1467},
	{0x0c, 0x01d1, 0xba5826ef832e2b},
	{0x0d, 0x0583, 0xa92e636998767d},
	{0x0e, 0x02e8, 0x313f0a51478df8},
	{0x0f, 0x08fc, 0xd28ce525a2be4b},
};

int ioctl_ReadCPRMMediaId(int *p_agid, uint8_t *p_buffer)
{
	int i_bytes;
	int i_ret;

#ifdef _WIN32
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, CPRM_MEDIA_ID_SIZE + 4);
	sptd.Cdb[7]  = CPRM_STRUCT_MEDIA_ID;
	sptd.Cdb[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes); 
	if (i_ret == 0)
		memcpy(p_buffer, sptd_buf + 4, CPRM_MEDIA_ID_SIZE);
#elif __linux__
	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, CPRM_MEDIA_ID_SIZE + 4);
	swb.io_hdr.cmdp[7] = CPRM_STRUCT_MEDIA_ID;
	swb.io_hdr.cmdp[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes); 
	if (i_ret == 0)
		memcpy(p_buffer, sptd_buf + 4, CPRM_MEDIA_ID_SIZE);
#elif __MACH__
	dk_dvd_read_structure_t dvd;
	uint8_t dvdbs[CPRM_MEDIA_ID_SIZE + 4];
	dvd.format = CPRM_STRUCT_MEDIA_ID;
	dvd.buffer = &dvdbs;
	dvd.bufferLength = sizeof(dvdbs);
    
	dvd.grantID = *p_agid;

    i_ret = ioctl( h_dvd, DKIOCDVDREADSTRUCTURE, &dvd );
	if (i_ret == 0)
		memcpy(p_buffer, dvd.buffer, sizeof(dvd.bufferLength));
#endif
	return i_ret;
}

int ioctl_ReadCPRMMKBPack(int *p_agid, int mkb_pack, uint8_t *p_mkb_pack, int *p_total_packs)
{
	int i_ret;

	ioctl_Init(GPCMD_READ_DISC_STRUCTURE, CPRM_MKB_PACK_SIZE + 4);
#ifdef _WIN32
	int i_bytes;
	sptd.Cdb[2]  = ((uint8_t*)&mkb_pack)[3];
	sptd.Cdb[3]  = ((uint8_t*)&mkb_pack)[2];
	sptd.Cdb[4]  = ((uint8_t*)&mkb_pack)[1];
	sptd.Cdb[5]  = ((uint8_t*)&mkb_pack)[0];
	sptd.Cdb[7]  = CPRM_STRUCT_MKB;
	sptd.Cdb[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes); 
	if (i_ret == 0)
	{
		*p_total_packs = sptd_buf[3];
		memcpy(p_mkb_pack, sptd_buf + 4, CPRM_MKB_PACK_SIZE);
	}
#elif __linux__
	int i_bytes;
	swb.io_hdr.cmdp[2] = ((uint8_t*)&mkb_pack)[3];
	swb.io_hdr.cmdp[3] = ((uint8_t*)&mkb_pack)[2];
	swb.io_hdr.cmdp[4] = ((uint8_t*)&mkb_pack)[1];
	swb.io_hdr.cmdp[5] = ((uint8_t*)&mkb_pack)[0];
	swb.io_hdr.cmdp[7] = CPRM_STRUCT_MKB;
	swb.io_hdr.cmdp[10] = *p_agid << 6;
	i_ret = ioctl_Send(&i_bytes); 
	if (i_ret == 0)
	{
		*p_total_packs = sptd_buf[3];
		memcpy(p_mkb_pack, sptd_buf + 4, CPRM_MKB_PACK_SIZE);
	}
#elif __MACH__
	dk_dvd_read_structure_t dvd;
	uint8_t dvdbs[CPRM_MKB_PACK_SIZE];
	dvd.format = CPRM_STRUCT_MKB;
	dvd.buffer = &dvdbs;
	dvd.bufferLength = sizeof(dvdbs);
    
	dvd.grantID = *p_agid;

    i_ret = ioctl( h_dvd, DKIOCDVDREADSTRUCTURE, &dvd );
	if (i_ret == 0)
		memcpy(p_mkb_pack, dvd.buffer, sizeof(dvd.bufferLength));
#endif
	return i_ret;
}

uint32_t mask32(int n)
{
	uint32_t val = 0;
	switch (n) {
	case 1:
		val = 0x01;
		break;
	case 2:
		val = 0x03;
		break;
	case 3:
		val = 0x07;
		break;
	case 4:
		val = 0x0F;
		break;
	case 5:
		val = 0x1F;
		break;
	case 6:
		val = 0x3F;
		break;
	case 7:
		val = 0x7F;
		break;
	case 8:
		val = 0xFF;
		break;
	case 9:
		val = 0x1FF;
		break;
	case 10:
		val = 0x3FF;
		break;
	case 11:
		val = 0x7FF;
		break;
	case 12:
		val = 0xFFF;
		break;
	case 13:
		val = 0x1FFF;
		break;
	case 14:
		val = 0x3FFF;
		break;
	case 15:
		val = 0x7FFF;
		break;
	case 16:
		val = 0xFFFF;
		break;
	case 17:
		val = 0x1FFFF;
		break;
	case 18:
		val = 0x3FFFF;
		break;
	case 19:
		val = 0x7FFFF;
		break;
	case 20:
		val = 0xFFFFF;
		break;
	case 21:
		val = 0x1FFFFF;
		break;
	case 22:
		val = 0x3FFFFF;
		break;
	case 23:
		val = 0x7FFFFF;
		break;
	case 24:
		val = 0xFFFFFF;
		break;
	case 25:
		val = 0x1FFFFFF;
		break;
	case 26:
		val = 0x3FFFFFF;
		break;
	case 27:
		val = 0x7FFFFFF;
		break;
	case 28:
		val = 0xFFFFFFF;
		break;
	case 29:
		val = 0x1FFFFFFF;
		break;
	case 30:
		val = 0x3FFFFFFF;
		break;
	case 31:
		val = 0x7FFFFFFF;
		break;
	default:
		break;
	}
	return val;
}

static uint32_t rol32(uint32_t code, int n)
{
	return (code << n) | ((code >> (32 - n)) & mask32(n));
}

uint8_t mask8(int n)
{
	uint8_t val = 0;
	switch (n) {
	case 1:
		val = 0x01;
		break;
	case 2:
		val = 0x03;
		break;
	case 3:
		val = 0x07;
		break;
	case 4:
		val = 0x0F;
		break;
	case 5:
		val = 0x1F;
		break;
	case 6:
		val = 0x3F;
		break;
	case 7:
		val = 0x7F;
		break;
	default:
		break;
	}
	return val;
}

static uint8_t rol8(uint8_t code, int n)
{
	return (code << n) | ((code >> (8 - n)) & mask8(n));
}

static uint32_t F(uint32_t code, uint32_t key)
{
	uint32_t work;

	work = code + key;
	work ^= sbox_f[work & 0xff];
	work ^= rol32(work, 9) ^ rol32(work, 22);
	return work;
}

void c2_init()
{
	int i;
	unsigned char c0, c1, c2, c3;
	
	for (i = 0; i < 256; i++)
	{
		c0 = sbox[i];
		c1 = rol8((c0 ^ 0x65), 1);
		c2 = rol8((c0 ^ 0x2b), 5);
		c3 = rol8((c0 ^ 0xc9), 2);
		c0 ^= i;
		sbox_f[i] = (c3 << 24) + (c2 << 16) + (c1 << 8) + c0;
	}
}

uint64_t c2_enc(uint64_t code, uint64_t key)
{
	uint32_t L, R, t;
	uint32_t ktmpa, ktmpb, ktmpc, ktmpd;
	uint32_t sk[10];
	int      round;

	L     = (uint32_t)((code >> 32) & 0xffffffff);
	R     = (uint32_t)((code      ) & 0xffffffff);
	ktmpa = (uint32_t)((key  >> 32) & 0x00ffffff);
	ktmpb = (uint32_t)((key       ) & 0xffffffff);
	for (round = 0; round < 10; round++)
	{
		ktmpa &= 0x00ffffff;
		sk[round] = ktmpb + ((uint32_t)sbox[(ktmpa & 0xff) ^ round] << 4);
		ktmpc = ((ktmpb >> (32 - 17)) & 0x1ffff);
		ktmpd = ((ktmpa >> (24 - 17)) & 0x1ffffff);
		ktmpa = (ktmpa << 17) | ktmpc;
		ktmpb = (ktmpb << 17) | ktmpd;
	}
	for (round = 0; round < 10; round++)
	{
		L += F(R, sk[round]);
		t = L; L = R; R = t;
	}
	t = L; L = R; R = t;
	return (((uint64_t)L) << 32) | R;
}

uint64_t c2_dec(uint64_t code, uint64_t key)
{
	uint32_t L, R, t;
	uint32_t ktmpa, ktmpb, ktmpc, ktmpd;
	uint32_t sk[10];
	int      round;

	L  =    (uint32_t)((code >> 32) & 0xffffffff);
	R  =    (uint32_t)((code      ) & 0xffffffff);
	ktmpa = (uint32_t)((key  >> 32) & 0x00ffffff);
	ktmpb = (uint32_t)((key       ) & 0xffffffff);
	for (round = 0; round < 10; round++)
	{
		ktmpa &= 0x00ffffff;
		sk[round] = ktmpb + ((uint32_t)sbox[(ktmpa & 0xff) ^ round] << 4);
		ktmpc = ((ktmpb >> (32 - 17)) & 0x1ffff);
		ktmpd = ((ktmpa >> (24 - 17)) & 0x1ffffff);
		ktmpa = (ktmpa << 17) | ktmpc;
		ktmpb = (ktmpb << 17) | ktmpd;
	}
	for (round = 9; round >= 0; round--)
	{
		L -= F(R, sk[round]);
		t = L; L = R; R = t;
	}
	t = L; L = R; R = t;
	return (((uint64_t)L) << 32) | R;
}

uint64_t c2_g(uint64_t code, uint64_t key)
{
	return c2_enc(code, key) ^ code;
}

void c2_ecbc(void *p_buffer, uint64_t key, int length)
{
	uint32_t L, R, t;
	uint32_t ktmpa, ktmpb, ktmpc, ktmpd;
	uint32_t sk[10];
	uint64_t inout, inkey;
	int      round, key_round, i;

	inkey = key;
	key_round = 10;
	for (i = 0; i < length; i += 8)
	{
		inout = *(uint64_t*)p_buffer;
		B2N_64(inout);
		L  =    (uint32_t)((inout >> 32) & 0xffffffff);
		R  =    (uint32_t)((inout      ) & 0xffffffff);
		ktmpa = (uint32_t)((inkey >> 32) & 0x00ffffff);
		ktmpb = (uint32_t)((inkey      ) & 0xffffffff);
		for (round = 0; round < key_round; round++)
		{
			ktmpa &= 0x00ffffff;
			sk[round] = ktmpb + ((uint32_t)sbox[(ktmpa & 0xff) ^ round] << 4);
			ktmpc = ((ktmpb >> (32 - 17)) & 0x1ffff);
			ktmpd = ((ktmpa >> (24 - 17)) & 0x1ffffff);
			ktmpa = (ktmpa << 17) | ktmpc;
			ktmpb = (ktmpb << 17) | ktmpd;
		}
		for (round = 0; round < 10; round++)
		{
			L += F(R, sk[round % key_round]);
			if (round == 4)
			{
				inkey = key ^ (((uint64_t)(R & 0x00ffffff) << 32) | L);
			}
			t = L; L = R; R = t;
		}
		t = L; L = R; R = t;
		inout = (((uint64_t)L) << 32) | R;
		B2N_64(inout);
		*((uint64_t*)p_buffer) = inout;
		*((uint64_t*)p_buffer) += 1;
		key_round = 2;
	}
}

void c2_dcbc(void *p_buffer, uint64_t key, int length)
{
	uint32_t L, R, t;
	uint32_t ktmpa, ktmpb, ktmpc, ktmpd;
	uint32_t sk[10];
	uint64_t inout, inkey;
	int      round, key_round, i;

	inkey = key;
	key_round = 10;
	for (i = 0; i < length; i += 8)
	{
		inout = *(uint64_t*)p_buffer;
		B2N_64(inout);
		L  =    (uint32_t)((inout >> 32) & 0xffffffff);
		R  =    (uint32_t)((inout      ) & 0xffffffff);
		ktmpa = (uint32_t)((inkey >> 32) & 0x00ffffff);
		ktmpb = (uint32_t)((inkey      ) & 0xffffffff);
		for (round = 0; round < key_round; round++)
		{
			ktmpa &= 0x00ffffff;
			sk[round] = ktmpb + ((uint32_t)sbox[(ktmpa & 0xff) ^ round] << 4);
			ktmpc = ((ktmpb >> (32 - 17)) & 0x1ffff);
			ktmpd = ((ktmpa >> (24 - 17)) & 0x1ffffff);
			ktmpa = (ktmpa << 17) | ktmpc;
			ktmpb = (ktmpb << 17) | ktmpd;
		}
		for (round = 9; round >= 0; round--)
		{
			L -= F(R, sk[round % key_round]);
			t = L; L = R; R = t;
			if (round == 5)
			{
				inkey = key ^ (((uint64_t)(R & 0x00ffffff) << 32) | L);
			}
		}
		t = L; L = R; R = t;
		inout = (((uint64_t)L) << 32) | R;
		B2N_64(inout);
		*((uint64_t*)p_buffer) = inout;
		*((uint64_t*)p_buffer) += 1;
		key_round = 2;
	}
}

uint8_t *cppm_get_mkb(char *psz_mkb)
{
	FILE    *f_mkb;
	uint8_t *p_mkb = NULL;
	char    mkb_signature[12];
	size_t  mkb_size;

	f_mkb = fopen(psz_mkb, "rb");
	if (!f_mkb)
		return NULL;
	if (fread(mkb_signature, 1, 12, f_mkb) == 12)
	{
		if (memcmp(mkb_signature, "DVDAUDIO.MKB", 12) == 0)
		{
			if (fread(&mkb_size, 1, 4, f_mkb) == 4)
			{
				B2N_32(mkb_size);
				p_mkb = (uint8_t *)malloc(mkb_size);
				if (p_mkb)
				{
					if (fread(p_mkb, 1, mkb_size, f_mkb) != mkb_size)
					{
						free(p_mkb);
						p_mkb = NULL;
					}
				}
			}
		}
	}
	fclose(f_mkb);
	return p_mkb;
}

uint8_t *cprm_get_mkb(unsigned short ProtectionType)
{
	uint8_t mkb_pack[CPRM_MKB_PACK_SIZE];
	uint8_t *p_mkb = NULL;
	int mkb_packs, i;

	if (GetBusKey(ProtectionType))
		return (uint8_t *)-1;
	mkb_packs = 16;
	if (ioctl_ReadCPRMMKBPack(&css.agid, 0, (uint8_t*)mkb_pack, &mkb_packs))
		return NULL;
	p_mkb = (uint8_t *)malloc(mkb_packs * CPRM_MKB_PACK_SIZE - 16);
	if (!p_mkb)
		return NULL;
	memcpy(p_mkb, &mkb_pack[16], CPRM_MKB_PACK_SIZE - 16);
	for (i = 1; i < mkb_packs; i++)
	{
		if (ioctl_ReadCPRMMKBPack(&css.agid, i, (uint8_t*)p_mkb + i * CPRM_MKB_PACK_SIZE - 16, &mkb_packs)) {
			free(p_mkb);
			p_mkb = NULL;
			break;
		}
	}
	INT nSize = mkb_packs * CPRM_MKB_PACK_SIZE - 16;
	fprintf(fpLog, "MediaKeyBlock\n"
		"        +0 +1 +2 +3 +4 +5 +6 +7  +8 +9 +A +B +C +D +E +F\n");
	for (INT k = 0; k < nSize; k += 16) {
		if (16 > nSize - k) {
			fprintf(fpLog, "%04X : ", k);
			for (INT j = 0; j < nSize - k; j++) {
				if (j == 8) {
					fprintf(fpLog, " ");
				}
				fprintf(fpLog, "%02X ", p_mkb[k + j]);
			}
		}
		else {
			fprintf(fpLog,
				"%05X : %02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X   "
				, k, p_mkb[k], p_mkb[k + 1], p_mkb[k + 2], p_mkb[k + 3], p_mkb[k + 4], p_mkb[k + 5]
				, p_mkb[k + 6], p_mkb[k + 7], p_mkb[k + 8], p_mkb[k + 9], p_mkb[k + 10], p_mkb[k + 11]
				, p_mkb[k + 12], p_mkb[k + 13], p_mkb[k + 14], p_mkb[k + 15]);
			for (INT j = 0; j < 16; j++) {
				INT ch = isprint(p_mkb[k + j]) ? p_mkb[k + j] : '.';
				fprintf(fpLog, "%c", ch);
			}
		}
		fprintf(fpLog, "\n");
	}
	return p_mkb;
}

int cppm_set_id_album(unsigned short ProtectionType)
{
	uint8_t p_buffer[DVD_DISCKEY_SIZE];
	int i;

	id_album = 0;
	if (GetBusKey(ProtectionType))
		return -1;
	if (ioctl_ReadDiscKey(&css.agid, p_buffer))
		return -1;
	if (GetASF() != 1)
	{
		ioctl_InvalidateAgid(&css.agid);
		return -1;
	}
	for (i = 0; i < DVD_DISCKEY_SIZE; i++)
		p_buffer[i] ^= css.p_bus_key[4 - (i % KEY_SIZE)];
	fprintf(fpLog, "AlbumIdentifier: %02x %02x %02x %02x %02x %02x %02x %02x\n"
		, p_buffer[80], p_buffer[81], p_buffer[82], p_buffer[83]
		, p_buffer[84], p_buffer[85], p_buffer[86], p_buffer[87]);
	id_album = *(uint64_t*)&p_buffer[80];
	B2N_64(id_album);
	return 0;
}

int cprm_set_id_media(unsigned short ProtectionType)
{
	uint8_t p_buffer[CPRM_MEDIA_ID_SIZE + 4];

	id_media = 0;
	if (GetBusKey(ProtectionType))
		return -1;
	/* Get CPRM IDmedia and DVD-MAC(IDmedia) keys */
	if (ioctl_ReadCPRMMediaId(&css.agid, p_buffer))
		return -1;
	fprintf(fpLog, "MediaIdentifier: %02x %02x %02x %02x %02x %02x %02x %02x\n"
		, p_buffer[0], p_buffer[1], p_buffer[2], p_buffer[3]
		, p_buffer[4], p_buffer[5], p_buffer[6], p_buffer[7]);
	id_media = *(uint64_t*)&(((cprm_media_id_t*)p_buffer)->id_media);
	B2N_64(id_media);
	return 0;
}

#define f(c, r) (((uint64_t)c << 32) | (uint64_t)r)

int process_mkb(uint8_t *p_mkb, device_key_t *p_dev_keys, int nr_dev_keys, uint64_t *p_media_key)
{
	int mkb_pos, length, i, i_dev_key, no_more_keys, no_more_records;
	uint8_t record_type, column;
	uint64_t buffer, verification_data;

	i_dev_key = 0;
	no_more_keys = 0;
	while (!no_more_keys)
	{
		mkb_pos = 0;
		no_more_records = 0;
		while (!no_more_records)
		{
			record_type = *(uint8_t*)&p_mkb[mkb_pos];
			length = *(uint32_t*)&p_mkb[mkb_pos] & 0xffffff00;
			B2N_32(length);
			if (length >= 12)
			{
				buffer = *(uint64_t*)&p_mkb[mkb_pos + 4];
			}
			else
			{
				if (length < 4)
					length = 4;
			}
			printf("mkb record_type: 0x%02hhx, length: %d\n", record_type, length);
			switch (record_type) {
			case 0x82: /* Conditionally calculate media key record */
				B2N_64(buffer);
				buffer = c2_dec(buffer, media_key);
				if ((buffer & 0xffffffff00000000) != 0xdeadbeef00000000)
					break;
				B2N_64(buffer);
			case 0x01: /* Calculate media key record */
				column = ((uint8_t*)&buffer)[4];
				/*
				if (column >= 16 || ((uint8_t*)&buffer)[5] != 0 || ((uint8_t*)&buffer)[6] != 0 || ((uint8_t*)&buffer)[7] != 1)
					break;
				*/
				/* Get appropriate device key for column */
				no_more_keys = 1;
				for (i = i_dev_key; i < nr_dev_keys; i++)	
				{
					if (p_dev_keys[i].col == column)
					{
						no_more_keys = 0;
						i_dev_key = i;
						break;
					}
				}
				if (no_more_keys)
					break;
				if (12 + p_dev_keys[i_dev_key].row * 8 + 8 > length)
					break;
				buffer = *(uint64_t*)&p_mkb[mkb_pos + 12 + p_dev_keys[i_dev_key].row * 8];
				B2N_64(buffer);
				if (record_type == 0x82)
					buffer = c2_dec(buffer, media_key);
				media_key = (c2_dec(buffer, p_dev_keys[i_dev_key].key) & 0x00ffffffffffffff) ^ f(column, p_dev_keys[i_dev_key].row);
				buffer = c2_dec(verification_data, media_key);
				if ((buffer & 0xffffffff00000000) == 0xdeadbeef00000000)
				{
					*p_media_key = media_key;
					fprintf(fpLog, "MediaKey: %02x %02x %02x %02x %02x %02x %02x\n"
						, (uint8_t)(media_key >> 48 & 0xff), (uint8_t)(media_key >> 40 & 0xff)
						, (uint8_t)(media_key >> 32 & 0xff), (uint8_t)(media_key >> 24 & 0xff)
						, (uint8_t)(media_key >> 16 & 0xff), (uint8_t)(media_key >> 8 & 0xff)
						, (uint8_t)(media_key & 0xff));
					return 0;
				}
				break;
			case 0x02: /* End of media key record */
				no_more_records = 1;
				break;
			case 0x81: /* Verify media key record */
				B2N_64(buffer);
				verification_data = buffer;
				break;
			default:
				break;
			}
			mkb_pos += length;
		}
		i_dev_key++;
	}
	return -1;
}

int vr_get_k_te(char *psz_vr_mangr)
{
	FILE    *f_vr_m;
	uint8_t vmgi_mat[512];
	int ret = -1;

	f_vr_m = fopen(psz_vr_mangr, "rb");
	if (!f_vr_m)
		return -1;
	if (fread(vmgi_mat, 1, 512, f_vr_m) == 512)
	{
		if (memcmp(vmgi_mat, "DVD_RTR_VMG0", 12) == 0)
		{
			vr_k_te = 0;
			if (vmgi_mat[267] & 1) /* Check encrypted title key status bit */
			{
				vr_k_te = *(uint64_t*)&vmgi_mat[268]; /* Get Kte */
				B2N_64(vr_k_te);
				fprintf(fpLog, "EncryptedTitleKey: %02x %02x %02x %02x %02x %02x %02x %02x\n"
					, vmgi_mat[268], vmgi_mat[269], vmgi_mat[270], vmgi_mat[271]
					, vmgi_mat[272], vmgi_mat[273], vmgi_mat[274], vmgi_mat[275]);
			}
			ret = 0;
		}
	}
	fclose(f_vr_m);
	return ret;
}

int dvdcss_init(unsigned short ProtectionType)
{
	int ret = GetDiscKey(ProtectionType);
	if (ret == 0) {
		for (int i = 0; i < css.vob[0].idx; i++) {
			fprintf(fpLog, "LBA: %7d, Filename: %s, ", css.vob[i].lba, css.vob[i].fname);
			ret = GetTitleKey(css.vob[i].lba, ProtectionType);
			if (ret == 0) {
				fprintf(fpLog, "DecryptedTitleKey: %02X %02X %02X %02X %02X\n"
					, css.p_title_key[0], css.p_title_key[1], css.p_title_key[2]
					, css.p_title_key[3], css.p_title_key[4]);
			}
			else if (ret == -2) {
				fprintf(fpLog, "No TitleKey\n");
			}
		}
	}
	return ret;
}

int dvdcpxm_init(char *psz_target, unsigned short ProtectionType)
{
	char psz_file[_MAX_PATH];
	uint8_t *p_mkb;
	int ret = -1;

	c2_init();
	printf("ProtectionType: %d\n", ProtectionType);
	switch (ProtectionType)
	{
	case COPYRIGHT_PROTECTION_NONE:
		ret = 0;
		break;
	case COPYRIGHT_PROTECTION_CPPM:
		if (cppm_set_id_album(ProtectionType) == 0)
		{
#ifdef _WIN32
			strcpy(psz_file, "?:\\AUDIO_TS\\DVDAUDIO.MKB");
			psz_file[0] = psz_target[0];
#else
			strcpy(psz_file, psz_target);
			strcat(psz_file, "/AUDIO_TS/DVDAUDIO.MKB");
#endif
			printf("fname: %s\n", psz_file);
			p_mkb = cppm_get_mkb(psz_file);
			if (!p_mkb)
			{
#ifdef _WIN32
				strcpy(psz_file, "?:\\AUDIO_TS\\DVDAUDIO.BUP");
				psz_file[0] = psz_target[0];
#else
				strcpy(psz_file, psz_target);
				strcat(psz_file, "/AUDIO_TS/DVDAUDIO.BUP");
#endif
				printf("fname: %s\n", psz_file);
				p_mkb = cppm_get_mkb(psz_file);
			}
			if (p_mkb)
			{
				ret = process_mkb(p_mkb, cppm_device_keys, sizeof(cppm_device_keys) / sizeof(*cppm_device_keys), &media_key);
				free(p_mkb);
				if (ret) break;
			}
		}
		break;
	case COPYRIGHT_PROTECTION_CPRM:
		if (cprm_set_id_media(ProtectionType) == 0)
		{
			p_mkb = cprm_get_mkb(ProtectionType);
			if (p_mkb)
			{
				ret = process_mkb(p_mkb, cprm_device_keys, sizeof(cprm_device_keys) / sizeof(*cprm_device_keys), &media_key);
				free(p_mkb);
				if (ret) break;
			}
#ifdef _WIN32
			strcpy(psz_file, "?:\\DVD_RTAV\\VR_MANGR.IFO");
			psz_file[0] = psz_target[0];
#else
			strcpy(psz_file, psz_target);
			strcat(psz_file, "/DVD_RTAV/VR_MANGR.IFO");
#endif
			printf("fname: %s\n", psz_file);
			ret = vr_get_k_te(psz_file);
			if (ret)
			{
#ifdef _WIN32
				strcpy(psz_file, "?:\\DVD_RTAV\\VR_MANGR.BUP");
				psz_file[0] = psz_target[0];
#else
				strcpy(psz_file, psz_target);
				strcat(psz_file, "/DVD_RTAV/VR_MANGR.BUP");
#endif
				printf("fname: %s\n", psz_file);
				ret = vr_get_k_te(psz_file);
				if (ret) break;
			}
		}
		break;
	}
	return media_type;
}

int dvd_init(char *psz_target, char* psz_protection)
{
	int ret = -1;
#ifdef _WIN32
	char psz_dvddev[8];
	strcpy(psz_dvddev, "\\\\.\\?:");
	psz_dvddev[4] = psz_target[0];
	h_dvd = dvddev_open(psz_dvddev);
#else
#if defined (__linux__) || defined (__MACH__)
	h_dvd = dvddev_open(psz_target);
#ifdef __linux__
	const int nStrSize = _MAX_PATH;
	char str[nStrSize] = {};

	_snprintf(str, nStrSize,
		"findmnt -m | grep %s 2>/dev/null > /tmp/DVDAuth.txt", psz_target);
	system(str);

	FILE* fp = fopen("/tmp/DVDAuth.txt", "r");
	if (!fp) {
		fprintf(stderr, "Failed to open /tmp/DVDAuth.txt\n");
		return -1;
	}

	char buf[nStrSize] = {};
	fgets(buf, sizeof(buf), fp);
	char* pTrimBuf[4] = {};
	pTrimBuf[0] = _tcstok(buf, " "); // space
	for (int nRoop = 1; nRoop < 4; nRoop++) {
		pTrimBuf[nRoop] = strtok(NULL, " "); // space
	}
	printf("mount point: %s\n", pTrimBuf[0]);
	remove("/tmp/DVDAuth.txt");
	if (!pTrimBuf[0]) {
		fprintf(stderr, "Failed to open %s\n", psz_target);
		return -1;
	}
#endif
#endif
#endif
	if (h_dvd == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Device open error: %d\n", GetLastError());
		return -1;
	}
	DVD_COPYRIGHT_DESCRIPTOR copyright;
	if (ioctl_ReadCopyright(0, &copyright) < 0)
	{
		dvddev_close(h_dvd);
		return -1;
	}

	if (!strncmp(psz_protection, "css", 3)) {
		printf("CopyrightProtectionType: %d\n", copyright.CopyrightProtectionType);
		ret = dvdcss_init(copyright.CopyrightProtectionType);
	}
	else {
		ret = dvdcpxm_init(psz_target, copyright.CopyrightProtectionType);
	}
	dvddev_close(h_dvd);
	return ret;
}

int mpeg2_check_pes_scrambling_control(uint8_t *p_block)
{
	int pes_scrambling_control;

	pes_scrambling_control = 0;
	if (*(uint32_t*)p_block == 0xba010000)
	{
		pes_scrambling_control = (p_block[20] & 0x30) >> 4;
	}
	return pes_scrambling_control;
}

void mpeg2_reset_pes_scrambling_control(uint8_t *p_block)
{
	if (*(uint32_t*)p_block == 0xba010000)
	{
		p_block[20] &= 0xCD; // reset pes_scrambling_control and copyright flags;
	}
}

void mpeg2_reset_cci(uint8_t *p_block)
{
	uint8_t *p_mlp_pcm, *p_curr;
	int pes_sid;
	int pes_len;

	p_curr = p_block;
	if (*(uint32_t*)p_block == 0xba010000)
	{
		p_curr += 14 + (p_curr[13] & 0x07);
		while (p_curr < p_block + DVDCPXM_BLOCK_SIZE)
		{
			pes_len = (p_curr[4] << 8) + p_curr[5];
			if ((*(uint32_t*)p_curr & 0x00ffffff) == 0x00010000)
			{
				pes_sid = p_curr[3];
				if (pes_sid == 0xbd) // private stream 1
				{
					p_mlp_pcm = p_curr + 9 + p_curr[8];
					switch (p_mlp_pcm[0])  // stream id
					{
					case 0xa0: // PCM stream id
						if (p_mlp_pcm[3] > 8) p_mlp_pcm[12] = CCI_BYTE; // reset CCI
						break;
					case 0xa1: // MLP stream di
						if (p_mlp_pcm[3] > 4) p_mlp_pcm[8] = CCI_BYTE; // reset CCI
						break;
					}
				}
				p_curr += 6 + pes_len;
			}
			else break;
		}
	}
}

int cppm_decrypt_block(uint8_t *p_buffer, int flags)
{
	uint64_t d_kc_i, k_au, k_i, k_c;
	int encrypted;

	encrypted = 0;
	if (mpeg2_check_pes_scrambling_control(p_buffer))
	{
		k_au = c2_g(id_album, media_key) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[24];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_au) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[32];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[40];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[48];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[84];
		B2N_64(d_kc_i);
		k_c = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		c2_dcbc(&p_buffer[DVDCPXM_BLOCK_SIZE - DVDCPXM_ENCRYPTED_SIZE], k_c, DVDCPXM_ENCRYPTED_SIZE);
		mpeg2_reset_pes_scrambling_control(p_buffer);
		encrypted = 1;
	}
	if ((flags & DVDCPXM_PRESERVE_CCI) != DVDCPXM_PRESERVE_CCI)
		mpeg2_reset_cci(p_buffer);
	return encrypted;
}

int cprm_decrypt_block(uint8_t *p_buffer, int flags)
{
	uint64_t d_kc_i, k_au, k_i, k_c;
	int encrypted;

	encrypted = 0;
	if (mpeg2_check_pes_scrambling_control(p_buffer))
	{
		k_au = c2_g(id_album, media_key) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[24];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_au) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[32];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[40];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[48];
		B2N_64(d_kc_i);
		k_i = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		d_kc_i = *(uint64_t*)&p_buffer[84];
		B2N_64(d_kc_i);
		k_c = c2_g(d_kc_i, k_i) & 0x00ffffffffffffff;
		c2_dcbc(&p_buffer[DVDCPXM_BLOCK_SIZE - DVDCPXM_ENCRYPTED_SIZE], k_c, DVDCPXM_ENCRYPTED_SIZE);
		mpeg2_reset_pes_scrambling_control(p_buffer);
		encrypted = 1;
	}
	if ((flags & DVDCPXM_PRESERVE_CCI) != DVDCPXM_PRESERVE_CCI)
		mpeg2_reset_cci(p_buffer);
	return encrypted;
}

int dvdcpxm_decrypt(void *p_buffer, int nr_blocks, int flags)
{
	switch (media_type)
	{
	case COPYRIGHT_PROTECTION_CPPM:
		return cppm_decrypt_block((uint8_t*)p_buffer, flags);
	case COPYRIGHT_PROTECTION_CPRM:
		return cprm_decrypt_block((uint8_t*)p_buffer, flags);
	}
	return 0;
}

