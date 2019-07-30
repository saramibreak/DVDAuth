#include "dvd_css.h"

uint8_t p_css_tab1[256] =
{
	0x33, 0x73, 0x3b, 0x26, 0x63, 0x23, 0x6b, 0x76,
	0x3e, 0x7e, 0x36, 0x2b, 0x6e, 0x2e, 0x66, 0x7b,
	0xd3, 0x93, 0xdb, 0x06, 0x43, 0x03, 0x4b, 0x96,
	0xde, 0x9e, 0xd6, 0x0b, 0x4e, 0x0e, 0x46, 0x9b,
	0x57, 0x17, 0x5f, 0x82, 0xc7, 0x87, 0xcf, 0x12,
	0x5a, 0x1a, 0x52, 0x8f, 0xca, 0x8a, 0xc2, 0x1f,
	0xd9, 0x99, 0xd1, 0x00, 0x49, 0x09, 0x41, 0x90,
	0xd8, 0x98, 0xd0, 0x01, 0x48, 0x08, 0x40, 0x91,
	0x3d, 0x7d, 0x35, 0x24, 0x6d, 0x2d, 0x65, 0x74,
	0x3c, 0x7c, 0x34, 0x25, 0x6c, 0x2c, 0x64, 0x75,
	0xdd, 0x9d, 0xd5, 0x04, 0x4d, 0x0d, 0x45, 0x94,
	0xdc, 0x9c, 0xd4, 0x05, 0x4c, 0x0c, 0x44, 0x95,
	0x59, 0x19, 0x51, 0x80, 0xc9, 0x89, 0xc1, 0x10,
	0x58, 0x18, 0x50, 0x81, 0xc8, 0x88, 0xc0, 0x11,
	0xd7, 0x97, 0xdf, 0x02, 0x47, 0x07, 0x4f, 0x92,
	0xda, 0x9a, 0xd2, 0x0f, 0x4a, 0x0a, 0x42, 0x9f,
	0x53, 0x13, 0x5b, 0x86, 0xc3, 0x83, 0xcb, 0x16,
	0x5e, 0x1e, 0x56, 0x8b, 0xce, 0x8e, 0xc6, 0x1b,
	0xb3, 0xf3, 0xbb, 0xa6, 0xe3, 0xa3, 0xeb, 0xf6,
	0xbe, 0xfe, 0xb6, 0xab, 0xee, 0xae, 0xe6, 0xfb,
	0x37, 0x77, 0x3f, 0x22, 0x67, 0x27, 0x6f, 0x72,
	0x3a, 0x7a, 0x32, 0x2f, 0x6a, 0x2a, 0x62, 0x7f,
	0xb9, 0xf9, 0xb1, 0xa0, 0xe9, 0xa9, 0xe1, 0xf0,
	0xb8, 0xf8, 0xb0, 0xa1, 0xe8, 0xa8, 0xe0, 0xf1,
	0x5d, 0x1d, 0x55, 0x84, 0xcd, 0x8d, 0xc5, 0x14,
	0x5c, 0x1c, 0x54, 0x85, 0xcc, 0x8c, 0xc4, 0x15,
	0xbd, 0xfd, 0xb5, 0xa4, 0xed, 0xad, 0xe5, 0xf4,
	0xbc, 0xfc, 0xb4, 0xa5, 0xec, 0xac, 0xe4, 0xf5,
	0x39, 0x79, 0x31, 0x20, 0x69, 0x29, 0x61, 0x70,
	0x38, 0x78, 0x30, 0x21, 0x68, 0x28, 0x60, 0x71,
	0xb7, 0xf7, 0xbf, 0xa2, 0xe7, 0xa7, 0xef, 0xf2,
	0xba, 0xfa, 0xb2, 0xaf, 0xea, 0xaa, 0xe2, 0xff
};

uint8_t p_css_tab2[256] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x09, 0x08, 0x0b, 0x0a, 0x0d, 0x0c, 0x0f, 0x0e,
	0x12, 0x13, 0x10, 0x11, 0x16, 0x17, 0x14, 0x15,
	0x1b, 0x1a, 0x19, 0x18, 0x1f, 0x1e, 0x1d, 0x1c,
	0x24, 0x25, 0x26, 0x27, 0x20, 0x21, 0x22, 0x23,
	0x2d, 0x2c, 0x2f, 0x2e, 0x29, 0x28, 0x2b, 0x2a,
	0x36, 0x37, 0x34, 0x35, 0x32, 0x33, 0x30, 0x31,
	0x3f, 0x3e, 0x3d, 0x3c, 0x3b, 0x3a, 0x39, 0x38,
	0x49, 0x48, 0x4b, 0x4a, 0x4d, 0x4c, 0x4f, 0x4e,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x5b, 0x5a, 0x59, 0x58, 0x5f, 0x5e, 0x5d, 0x5c,
	0x52, 0x53, 0x50, 0x51, 0x56, 0x57, 0x54, 0x55,
	0x6d, 0x6c, 0x6f, 0x6e, 0x69, 0x68, 0x6b, 0x6a,
	0x64, 0x65, 0x66, 0x67, 0x60, 0x61, 0x62, 0x63,
	0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x7a, 0x79, 0x78,
	0x76, 0x77, 0x74, 0x75, 0x72, 0x73, 0x70, 0x71,
	0x92, 0x93, 0x90, 0x91, 0x96, 0x97, 0x94, 0x95,
	0x9b, 0x9a, 0x99, 0x98, 0x9f, 0x9e, 0x9d, 0x9c,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x89, 0x88, 0x8b, 0x8a, 0x8d, 0x8c, 0x8f, 0x8e,
	0xb6, 0xb7, 0xb4, 0xb5, 0xb2, 0xb3, 0xb0, 0xb1,
	0xbf, 0xbe, 0xbd, 0xbc, 0xbb, 0xba, 0xb9, 0xb8,
	0xa4, 0xa5, 0xa6, 0xa7, 0xa0, 0xa1, 0xa2, 0xa3,
	0xad, 0xac, 0xaf, 0xae, 0xa9, 0xa8, 0xab, 0xaa,
	0xdb, 0xda, 0xd9, 0xd8, 0xdf, 0xde, 0xdd, 0xdc,
	0xd2, 0xd3, 0xd0, 0xd1, 0xd6, 0xd7, 0xd4, 0xd5,
	0xc9, 0xc8, 0xcb, 0xca, 0xcd, 0xcc, 0xcf, 0xce,
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
	0xff, 0xfe, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8,
	0xf6, 0xf7, 0xf4, 0xf5, 0xf2, 0xf3, 0xf0, 0xf1,
	0xed, 0xec, 0xef, 0xee, 0xe9, 0xe8, 0xeb, 0xea,
	0xe4, 0xe5, 0xe6, 0xe7, 0xe0, 0xe1, 0xe2, 0xe3
};

uint8_t p_css_tab3[512] =
{
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff,
	0x00, 0x24, 0x49, 0x6d, 0x92, 0xb6, 0xdb, 0xff
};

uint8_t p_css_tab4[256] =
{
	0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
	0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
	0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
	0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
	0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
	0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
	0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
	0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
	0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
	0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
	0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
	0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
	0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
	0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
	0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
	0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
	0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};

uint8_t p_css_tab5[256] =
{
	0xff, 0x7f, 0xbf, 0x3f, 0xdf, 0x5f, 0x9f, 0x1f,
	0xef, 0x6f, 0xaf, 0x2f, 0xcf, 0x4f, 0x8f, 0x0f,
	0xf7, 0x77, 0xb7, 0x37, 0xd7, 0x57, 0x97, 0x17,
	0xe7, 0x67, 0xa7, 0x27, 0xc7, 0x47, 0x87, 0x07,
	0xfb, 0x7b, 0xbb, 0x3b, 0xdb, 0x5b, 0x9b, 0x1b,
	0xeb, 0x6b, 0xab, 0x2b, 0xcb, 0x4b, 0x8b, 0x0b,
	0xf3, 0x73, 0xb3, 0x33, 0xd3, 0x53, 0x93, 0x13,
	0xe3, 0x63, 0xa3, 0x23, 0xc3, 0x43, 0x83, 0x03,
	0xfd, 0x7d, 0xbd, 0x3d, 0xdd, 0x5d, 0x9d, 0x1d,
	0xed, 0x6d, 0xad, 0x2d, 0xcd, 0x4d, 0x8d, 0x0d,
	0xf5, 0x75, 0xb5, 0x35, 0xd5, 0x55, 0x95, 0x15,
	0xe5, 0x65, 0xa5, 0x25, 0xc5, 0x45, 0x85, 0x05,
	0xf9, 0x79, 0xb9, 0x39, 0xd9, 0x59, 0x99, 0x19,
	0xe9, 0x69, 0xa9, 0x29, 0xc9, 0x49, 0x89, 0x09,
	0xf1, 0x71, 0xb1, 0x31, 0xd1, 0x51, 0x91, 0x11,
	0xe1, 0x61, 0xa1, 0x21, 0xc1, 0x41, 0x81, 0x01,
	0xfe, 0x7e, 0xbe, 0x3e, 0xde, 0x5e, 0x9e, 0x1e,
	0xee, 0x6e, 0xae, 0x2e, 0xce, 0x4e, 0x8e, 0x0e,
	0xf6, 0x76, 0xb6, 0x36, 0xd6, 0x56, 0x96, 0x16,
	0xe6, 0x66, 0xa6, 0x26, 0xc6, 0x46, 0x86, 0x06,
	0xfa, 0x7a, 0xba, 0x3a, 0xda, 0x5a, 0x9a, 0x1a,
	0xea, 0x6a, 0xaa, 0x2a, 0xca, 0x4a, 0x8a, 0x0a,
	0xf2, 0x72, 0xb2, 0x32, 0xd2, 0x52, 0x92, 0x12,
	0xe2, 0x62, 0xa2, 0x22, 0xc2, 0x42, 0x82, 0x02,
	0xfc, 0x7c, 0xbc, 0x3c, 0xdc, 0x5c, 0x9c, 0x1c,
	0xec, 0x6c, 0xac, 0x2c, 0xcc, 0x4c, 0x8c, 0x0c,
	0xf4, 0x74, 0xb4, 0x34, 0xd4, 0x54, 0x94, 0x14,
	0xe4, 0x64, 0xa4, 0x24, 0xc4, 0x44, 0x84, 0x04,
	0xf8, 0x78, 0xb8, 0x38, 0xd8, 0x58, 0x98, 0x18,
	0xe8, 0x68, 0xa8, 0x28, 0xc8, 0x48, 0x88, 0x08,
	0xf0, 0x70, 0xb0, 0x30, 0xd0, 0x50, 0x90, 0x10,
	0xe0, 0x60, 0xa0, 0x20, 0xc0, 0x40, 0x80, 0x00
};

uint8_t p_crypt_tab0[256] =
{
	0xB7, 0xF4, 0x82, 0x57, 0xDA, 0x4D, 0xDB, 0xE2,
	0x2F, 0x52, 0x1A, 0xA8, 0x68, 0x5A, 0x8A, 0xFF,
	0xFB, 0x0E, 0x6D, 0x35, 0xF7, 0x5C, 0x76, 0x12,
	0xCE, 0x25, 0x79, 0x29, 0x39, 0x62, 0x08, 0x24,
	0xA5, 0x85, 0x7B, 0x56, 0x01, 0x23, 0x68, 0xCF,
	0x0A, 0xE2, 0x5A, 0xED, 0x3D, 0x59, 0xB0, 0xA9,
	0xB0, 0x2C, 0xF2, 0xB8, 0xEF, 0x32, 0xA9, 0x40,
	0x80, 0x71, 0xAF, 0x1E, 0xDE, 0x8F, 0x58, 0x88,
	0xB8, 0x3A, 0xD0, 0xFC, 0xC4, 0x1E, 0xB5, 0xA0,
	0xBB, 0x3B, 0x0F, 0x01, 0x7E, 0x1F, 0x9F, 0xD9,
	0xAA, 0xB8, 0x3D, 0x9D, 0x74, 0x1E, 0x25, 0xDB,
	0x37, 0x56, 0x8F, 0x16, 0xBA, 0x49, 0x2B, 0xAC,
	0xD0, 0xBD, 0x95, 0x20, 0xBE, 0x7A, 0x28, 0xD0,
	0x51, 0x64, 0x63, 0x1C, 0x7F, 0x66, 0x10, 0xBB,
	0xC4, 0x56, 0x1A, 0x04, 0x6E, 0x0A, 0xEC, 0x9C,
	0xD6, 0xE8, 0x9A, 0x7A, 0xCF, 0x8C, 0xDB, 0xB1,
	0xEF, 0x71, 0xDE, 0x31, 0xFF, 0x54, 0x3E, 0x5E,
	0x07, 0x69, 0x96, 0xB0, 0xCF, 0xDD, 0x9E, 0x47,
	0xC7, 0x96, 0x8F, 0xE4, 0x2B, 0x59, 0xC6, 0xEE,
	0xB9, 0x86, 0x9A, 0x64, 0x84, 0x72, 0xE2, 0x5B,
	0xA2, 0x96, 0x58, 0x99, 0x50, 0x03, 0xF5, 0x38,
	0x4D, 0x02, 0x7D, 0xE7, 0x7D, 0x75, 0xA7, 0xB8,
	0x67, 0x87, 0x84, 0x3F, 0x1D, 0x11, 0xE5, 0xFC,
	0x1E, 0xD3, 0x83, 0x16, 0xA5, 0x29, 0xF6, 0xC7,
	0x15, 0x61, 0x29, 0x1A, 0x43, 0x4F, 0x9B, 0xAF,
	0xC5, 0x87, 0x34, 0x6C, 0x0F, 0x3B, 0xA8, 0x1D,
	0x45, 0x58, 0x25, 0xDC, 0xA8, 0xA3, 0x3B, 0xD1,
	0x79, 0x1B, 0x48, 0xF2, 0xE9, 0x93, 0x1F, 0xFC,
	0xDB, 0x2A, 0x90, 0xA9, 0x8A, 0x3D, 0x39, 0x18,
	0xA3, 0x8E, 0x58, 0x6C, 0xE0, 0x12, 0xBB, 0x25,
	0xCD, 0x71, 0x22, 0xA2, 0x64, 0xC6, 0xE7, 0xFB,
	0xAD, 0x94, 0x77, 0x04, 0x9A, 0x39, 0xCF, 0x7C
};

uint8_t p_crypt_tab1[256] =
{
	0x8C, 0x47, 0xB0, 0xE1, 0xEB, 0xFC, 0xEB, 0x56,
	0x10, 0xE5, 0x2C, 0x1A, 0x5D, 0xEF, 0xBE, 0x4F,
	0x08, 0x75, 0x97, 0x4B, 0x0E, 0x25, 0x8E, 0x6E,
	0x39, 0x5A, 0x87, 0x53, 0xC4, 0x1F, 0xF4, 0x5C,
	0x4E, 0xE6, 0x99, 0x30, 0xE0, 0x42, 0x88, 0xAB,
	0xE5, 0x85, 0xBC, 0x8F, 0xD8, 0x3C, 0x54, 0xC9,
	0x53, 0x47, 0x18, 0xD6, 0x06, 0x5B, 0x41, 0x2C,
	0x67, 0x1E, 0x41, 0x74, 0x33, 0xE2, 0xB4, 0xE0,
	0x23, 0x29, 0x42, 0xEA, 0x55, 0x0F, 0x25, 0xB4,
	0x24, 0x2C, 0x99, 0x13, 0xEB, 0x0A, 0x0B, 0xC9,
	0xF9, 0x63, 0x67, 0x43, 0x2D, 0xC7, 0x7D, 0x07,
	0x60, 0x89, 0xD1, 0xCC, 0xE7, 0x94, 0x77, 0x74,
	0x9B, 0x7E, 0xD7, 0xE6, 0xFF, 0xBB, 0x68, 0x14,
	0x1E, 0xA3, 0x25, 0xDE, 0x3A, 0xA3, 0x54, 0x7B,
	0x87, 0x9D, 0x50, 0xCA, 0x27, 0xC3, 0xA4, 0x50,
	0x91, 0x27, 0xD4, 0xB0, 0x82, 0x41, 0x97, 0x79,
	0x94, 0x82, 0xAC, 0xC7, 0x8E, 0xA5, 0x4E, 0xAA,
	0x78, 0x9E, 0xE0, 0x42, 0xBA, 0x28, 0xEA, 0xB7,
	0x74, 0xAD, 0x35, 0xDA, 0x92, 0x60, 0x7E, 0xD2,
	0x0E, 0xB9, 0x24, 0x5E, 0x39, 0x4F, 0x5E, 0x63,
	0x09, 0xB5, 0xFA, 0xBF, 0xF1, 0x22, 0x55, 0x1C,
	0xE2, 0x25, 0xDB, 0xC5, 0xD8, 0x50, 0x03, 0x98,
	0xC4, 0xAC, 0x2E, 0x11, 0xB4, 0x38, 0x4D, 0xD0,
	0xB9, 0xFC, 0x2D, 0x3C, 0x08, 0x04, 0x5A, 0xEF,
	0xCE, 0x32, 0xFB, 0x4C, 0x92, 0x1E, 0x4B, 0xFB,
	0x1A, 0xD0, 0xE2, 0x3E, 0xDA, 0x6E, 0x7C, 0x4D,
	0x56, 0xC3, 0x3F, 0x42, 0xB1, 0x3A, 0x23, 0x4D,
	0x6E, 0x84, 0x56, 0x68, 0xF4, 0x0E, 0x03, 0x64,
	0xD0, 0xA9, 0x92, 0x2F, 0x8B, 0xBC, 0x39, 0x9C,
	0xAC, 0x09, 0x5E, 0xEE, 0xE5, 0x97, 0xBF, 0xA5,
	0xCE, 0xFA, 0x28, 0x2C, 0x6D, 0x4F, 0xEF, 0x77,
	0xAA, 0x1B, 0x79, 0x8E, 0x97, 0xB4, 0xC3, 0xF4
};

uint8_t p_crypt_tab2[256] =
{
	0xB7, 0x75, 0x81, 0xD5, 0xDC, 0xCA, 0xDE, 0x66,
	0x23, 0xDF, 0x15, 0x26, 0x62, 0xD1, 0x83, 0x77,
	0xE3, 0x97, 0x76, 0xAF, 0xE9, 0xC3, 0x6B, 0x8E,
	0xDA, 0xB0, 0x6E, 0xBF, 0x2B, 0xF1, 0x19, 0xB4,
	0x95, 0x34, 0x48, 0xE4, 0x37, 0x94, 0x5D, 0x7B,
	0x36, 0x5F, 0x65, 0x53, 0x07, 0xE2, 0x89, 0x11,
	0x98, 0x85, 0xD9, 0x12, 0xC1, 0x9D, 0x84, 0xEC,
	0xA4, 0xD4, 0x88, 0xB8, 0xFC, 0x2C, 0x79, 0x28,
	0xD8, 0xDB, 0xB3, 0x1E, 0xA2, 0xF9, 0xD0, 0x44,
	0xD7, 0xD6, 0x60, 0xEF, 0x14, 0xF4, 0xF6, 0x31,
	0xD2, 0x41, 0x46, 0x67, 0x0A, 0xE1, 0x58, 0x27,
	0x43, 0xA3, 0xF8, 0xE0, 0xC8, 0xBA, 0x5A, 0x5C,
	0x80, 0x6C, 0xC6, 0xF2, 0xE8, 0xAD, 0x7D, 0x04,
	0x0D, 0xB9, 0x3C, 0xC2, 0x25, 0xBD, 0x49, 0x63,
	0x8C, 0x9F, 0x51, 0xCE, 0x20, 0xC5, 0xA1, 0x50,
	0x92, 0x2D, 0xDD, 0xBC, 0x8D, 0x4F, 0x9A, 0x71,
	0x2F, 0x30, 0x1D, 0x73, 0x39, 0x13, 0xFB, 0x1A,
	0xCB, 0x24, 0x59, 0xFE, 0x05, 0x96, 0x57, 0x0F,
	0x1F, 0xCF, 0x54, 0xBE, 0xF5, 0x06, 0x1B, 0xB2,
	0x6D, 0xD3, 0x4D, 0x32, 0x56, 0x21, 0x33, 0x0B,
	0x52, 0xE7, 0xAB, 0xEB, 0xA6, 0x74, 0x00, 0x4C,
	0xB1, 0x7F, 0x82, 0x99, 0x87, 0x0E, 0x5E, 0xC0,
	0x8F, 0xEE, 0x6F, 0x55, 0xF3, 0x7E, 0x08, 0x90,
	0xFA, 0xB6, 0x64, 0x70, 0x47, 0x4A, 0x17, 0xA7,
	0xB5, 0x40, 0x8A, 0x38, 0xE5, 0x68, 0x3E, 0x8B,
	0x69, 0xAA, 0x9B, 0x42, 0xA5, 0x10, 0x01, 0x35,
	0xFD, 0x61, 0x9E, 0xE6, 0x16, 0x9C, 0x86, 0xED,
	0xCD, 0x2E, 0xFF, 0xC4, 0x5B, 0xA0, 0xAE, 0xCC,
	0x4B, 0x3B, 0x03, 0xBB, 0x1C, 0x2A, 0xAC, 0x0C,
	0x3F, 0x93, 0xC7, 0x72, 0x7A, 0x09, 0x22, 0x3D,
	0x45, 0x78, 0xA9, 0xA8, 0xEA, 0xC9, 0x6A, 0xF7,
	0x29, 0x91, 0xF0, 0x02, 0x18, 0x3A, 0x4E, 0x7C
};

uint8_t p_crypt_tab3[288] =
{
	0x73, 0x51, 0x95, 0xE1, 0x12, 0xE4, 0xC0, 0x58,
	0xEE, 0xF2, 0x08, 0x1B, 0xA9, 0xFA, 0x98, 0x4C,
	0xA7, 0x33, 0xE2, 0x1B, 0xA7, 0x6D, 0xF5, 0x30,
	0x97, 0x1D, 0xF3, 0x02, 0x60, 0x5A, 0x82, 0x0F,
	0x91, 0xD0, 0x9C, 0x10, 0x39, 0x7A, 0x83, 0x85,
	0x3B, 0xB2, 0xB8, 0xAE, 0x0C, 0x09, 0x52, 0xEA,
	0x1C, 0xE1, 0x8D, 0x66, 0x4F, 0xF3, 0xDA, 0x92,
	0x29, 0xB9, 0xD5, 0xC5, 0x77, 0x47, 0x22, 0x53,
	0x14, 0xF7, 0xAF, 0x22, 0x64, 0xDF, 0xC6, 0x72,
	0x12, 0xF3, 0x75, 0xDA, 0xD7, 0xD7, 0xE5, 0x02,
	0x9E, 0xED, 0xDA, 0xDB, 0x4C, 0x47, 0xCE, 0x91,
	0x06, 0x06, 0x6D, 0x55, 0x8B, 0x19, 0xC9, 0xEF,
	0x8C, 0x80, 0x1A, 0x0E, 0xEE, 0x4B, 0xAB, 0xF2,
	0x08, 0x5C, 0xE9, 0x37, 0x26, 0x5E, 0x9A, 0x90,
	0x00, 0xF3, 0x0D, 0xB2, 0xA6, 0xA3, 0xF7, 0x26,
	0x17, 0x48, 0x88, 0xC9, 0x0E, 0x2C, 0xC9, 0x02,
	0xE7, 0x18, 0x05, 0x4B, 0xF3, 0x39, 0xE1, 0x20,
	0x02, 0x0D, 0x40, 0xC7, 0xCA, 0xB9, 0x48, 0x30,
	0x57, 0x67, 0xCC, 0x06, 0xBF, 0xAC, 0x81, 0x08,
	0x24, 0x7A, 0xD4, 0x8B, 0x19, 0x8E, 0xAC, 0xB4,
	0x5A, 0x0F, 0x73, 0x13, 0xAC, 0x9E, 0xDA, 0xB6,
	0xB8, 0x96, 0x5B, 0x60, 0x88, 0xE1, 0x81, 0x3F,
	0x07, 0x86, 0x37, 0x2D, 0x79, 0x14, 0x52, 0xEA,
	0x73, 0xDF, 0x3D, 0x09, 0xC8, 0x25, 0x48, 0xD8,
	0x75, 0x60, 0x9A, 0x08, 0x27, 0x4A, 0x2C, 0xB9,
	0xA8, 0x8B, 0x8A, 0x73, 0x62, 0x37, 0x16, 0x02,
	0xBD, 0xC1, 0x0E, 0x56, 0x54, 0x3E, 0x14, 0x5F,
	0x8C, 0x8F, 0x6E, 0x75, 0x1C, 0x07, 0x39, 0x7B,
	0x4B, 0xDB, 0xD3, 0x4B, 0x1E, 0xC8, 0x7E, 0xFE,
	0x3E, 0x72, 0x16, 0x83, 0x7D, 0xEE, 0xF5, 0xCA,
	0xC5, 0x18, 0xF9, 0xD8, 0x68, 0xAB, 0x38, 0x85,
	0xA8, 0xF0, 0xA1, 0x73, 0x9F, 0x5D, 0x19, 0x0B,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x33, 0x72, 0x39, 0x25, 0x67, 0x26, 0x6D, 0x71,
	0x36, 0x77, 0x3C, 0x20, 0x62, 0x23, 0x68, 0x74,
	0xC3, 0x82, 0xC9, 0x15, 0x57, 0x16, 0x5D, 0x81
};

css_t css;

int GetTitleKey(int nLBA, unsigned short ProtectionType)
{
	uint8_t p_buffer[KEY_SIZE];
	dvd_key_t p_title_key;
	int i;
	if (GetBusKey(ProtectionType) < 0)
	{
		fprintf(fpLog, "Failed to GetBusKey\n");
		return -1;
	}
	/* Get encrypted title key */
	if (ioctl_ReadTitleKey(&css.agid, nLBA, p_buffer))
	{
		fprintf(fpLog, "Failed to ReadTitleKey\n");
		return -1;
	}
	/* This should have invaidated the AGID and got us ASF=1. */
	if (GetASF() != 1)
	{
		ioctl_InvalidateAgid(&css.agid);
		fprintf(fpLog, "Failed to GetASF\n");
		return -1;
	}
	/* Shuffle title key using bus key */
	for (i = 0; i < KEY_SIZE; i++)
		p_buffer[i] ^= css.p_bus_key[4 - (i % KEY_SIZE)];
	if (!(p_buffer[0] | p_buffer[1] | p_buffer[2] | p_buffer[3] | p_buffer[4]))
	{
		return -2;
	}
	fprintf(fpLog, "EncryptedTitleKey: %02X %02X %02X %02X %02X, "
		, p_buffer[0], p_buffer[1], p_buffer[2], p_buffer[3], p_buffer[4]);
	/* Decrypt title key with disc key. */
	DecryptTitleKey(0, css.p_disc_key, p_buffer, p_title_key);
	memcpy(css.p_title_key, p_title_key, KEY_SIZE);
	return 0;
}

int GetDiscKey(unsigned short ProtectionType)
{
	uint8_t p_buffer[DVD_DISCKEY_SIZE];
	dvd_key_t p_disc_key;
	int i;
	if (GetBusKey(ProtectionType) < 0)
	{
		fprintf(fpLog, "Failed to GetBusKey\n");
		return -1;
	}
	/* Get encrypted disc key */
	if (ioctl_ReadDiscKey(&css.agid, p_buffer))
	{
		fprintf(fpLog, "Failed to ReadDiscKey\n");
		return -1;
	}
	/* This should have invaidated the AGID and got us ASF=1. */
	if (GetASF() != 1)
	{
		ioctl_InvalidateAgid(&css.agid);
		fprintf(fpLog, "Failed to GetASF\n");
		return -1;
	}
	/* Shuffle disc key using bus key */
	for (i = 0; i < DVD_DISCKEY_SIZE; i++)
		p_buffer[i] ^= css.p_bus_key[4 - (i % KEY_SIZE)];

	fprintf(fpLog, "AllDiscKeys ((40 bits per 1 key) * 409 keys)\n");
	for (int j = 0; j < 409; j++) {
		fprintf(fpLog, "[%03d]: %02X %02X %02X %02X %02X"
			, j + 1, p_buffer[5 * j], p_buffer[5 * j + 1]
			, p_buffer[5 * j + 2], p_buffer[5 * j + 3], p_buffer[5 * j + 4]);
		if (j % 4 == 0) {
			fprintf(fpLog, "\n");
		}
		else {
			fprintf(fpLog, " ");
		}
	}

	/* Decrypt disc key with player key. */
	if (DecryptDiscKey(p_buffer, p_disc_key) == -1)
	{
		fprintf(fpLog, "Failed to DecryptDiscKey\n");
		return -1;
	}
	memcpy(css.p_disc_key, p_disc_key, KEY_SIZE);
	return 0;
}

int GetBusKey(unsigned short ProtectionType)
{
	uint8_t   p_buffer[10];
	uint8_t   p_challenge[2*KEY_SIZE];
	dvd_key_t p_key1;
	dvd_key_t p_key2;
	dvd_key_t p_key_check;
	uint8_t   i_variant = 0;
	int       i_ret = -1;
	int	      i;
	/* We might have to reset hung authentication processes in the drive
	 * by invalidating the corresponding AGID'.  As long as we haven't got
	 * an AGID, invalidate one (in sequence) and try again. */
	for (i = 0; i_ret == -1 && i < 4 ; ++i)
	{
		/* This is really _not good_, should be handled by the OS.
		 * Invalidating an AGID could make another process fail somewhere
		 * in its authentication process. */
		css.agid = i;
		ioctl_InvalidateAgid(&css.agid);
		if (ProtectionType == 1)
		{
			i_ret = ioctl_ReportAgidCssCppm(&css.protection, &css.agid);
		}
		else if (ProtectionType == 2)
		{
			i_ret = ioctl_ReportAgidCprm(&css.protection, &css.agid);
		}
	}
	/* Unable to authenticate without AGID */
	if (i_ret == -1) return -1;
	/* Setup a challenge, any values should work */
	for (i = 0; i < 10; ++i)
		p_challenge[i] = i;
	/* Get challenge from host */
	for (i = 0; i < 10; ++i)
		p_buffer[9-i] = p_challenge[i];
	/* Send challenge to LU */
	if (ioctl_SendChallenge(&css.agid, p_buffer))
	{
		ioctl_InvalidateAgid(&css.agid);
		return -1;
	}
	/* Get key1 from LU */
	if (ioctl_ReportKey1(&css.agid, p_buffer))
	{
		ioctl_InvalidateAgid(&css.agid);
		return -1;
	}
	/* Send key1 to host */
	for (i = 0; i < KEY_SIZE; i++)
		p_key1[i] = p_buffer[4-i];
	for (i = 0; i < 32; ++i)
	{
		CryptKey(0, i, p_challenge, p_key_check);
		if (memcmp(p_key_check, p_key1, KEY_SIZE) == 0)
		{
			i_variant = i;
			break;
		}
	}
	if (i == 32)
	{
		ioctl_InvalidateAgid(&css.agid);
		return -1;
	}
	/* Get challenge from LU */
	if (ioctl_ReportChallenge(&css.agid, p_buffer))
	{
		ioctl_InvalidateAgid(&css.agid);
		return -1;
	}
	/* Send challenge to host */
	for (i = 0; i < 10; ++i)
		p_challenge[i] = p_buffer[9-i];
	CryptKey(1, i_variant, p_challenge, p_key2);
	/* Get key2 from host */
	for (i = 0; i < KEY_SIZE; ++i)
		p_buffer[4-i] = p_key2[i];
	/* Send key2 to LU */
	if (ioctl_SendKey2(&css.agid, p_buffer))
	{
		ioctl_InvalidateAgid(&css.agid);
		return -1;
	}
	/* The drive has accepted us as authentic. */
	memcpy(p_challenge, p_key1, KEY_SIZE);
	memcpy(p_challenge + KEY_SIZE, p_key2, KEY_SIZE);
	CryptKey(2, i_variant, p_challenge, css.p_bus_key);
	return 0;
}

int GetASF()
{
	int i_asf = 0;
	if (ioctl_ReportASF(&css.agid, &i_asf) != 0)
		/* The ioctl process has failed */
		return -1;
	return i_asf;
}

int GetRPC()
{
	int p_type, p_mask, p_scheme;
	if (ioctl_ReportRPC(&p_type, &p_mask, &p_scheme) != 0)
		/* The ioctl process has failed */
		return -1;
	return 0;
}

void CryptKey(int i_key_type, int i_variant, uint8_t *p_challenge, uint8_t *p_key)
{
	/* Permutation table for challenge */
	uint8_t pp_perm_challenge[3][10] =
		{ { 1, 3, 0, 7, 5, 2, 9, 6, 4, 8 },
		  { 6, 1, 9, 3, 8, 5, 7, 4, 0, 2 },
		  { 4, 0, 3, 5, 7, 2, 8, 6, 1, 9 } };

	/* Permutation table for variant table for key2 and buskey */
	uint8_t pp_perm_variant[2][32] =
		{ { 0x0a, 0x08, 0x0e, 0x0c, 0x0b, 0x09, 0x0f, 0x0d,
				0x1a, 0x18, 0x1e, 0x1c, 0x1b, 0x19, 0x1f, 0x1d,
				0x02, 0x00, 0x06, 0x04, 0x03, 0x01, 0x07, 0x05,
				0x12, 0x10, 0x16, 0x14, 0x13, 0x11, 0x17, 0x15 },
		  { 0x12, 0x1a, 0x16, 0x1e, 0x02, 0x0a, 0x06, 0x0e,
				0x10, 0x18, 0x14, 0x1c, 0x00, 0x08, 0x04, 0x0c,
				0x13, 0x1b, 0x17, 0x1f, 0x03, 0x0b, 0x07, 0x0f,
				0x11, 0x19, 0x15, 0x1d, 0x01, 0x09, 0x05, 0x0d } };

	uint8_t p_variants[32] =
		{ 0xB7, 0x74, 0x85, 0xD0, 0xCC, 0xDB, 0xCA, 0x73,
			0x03, 0xFE, 0x31, 0x03, 0x52, 0xE0, 0xB7, 0x42,
			0x63, 0x16, 0xF2, 0x2A, 0x79, 0x52, 0xFF, 0x1B,
			0x7A, 0x11, 0xCA, 0x1A, 0x9B, 0x40, 0xAD, 0x01 };

	/* The "secret" key */
	uint8_t p_secret[5] = { 0x55, 0xD6, 0xC4, 0xC5, 0x28 };

	uint8_t p_bits[30], p_scratch[10], p_tmp1[5], p_tmp2[5];
	uint8_t i_lfsr0_o;  /* 1 bit used */
	uint8_t i_lfsr1_o;  /* 1 bit used */
	uint8_t i_css_variant, i_cse, i_index, i_combined, i_carry;
	uint8_t i_val = 0;
	uint32_t i_lfsr0, i_lfsr1;
	int i_term = 0;
	int i_bit;
	int i;

	for (i = 9; i >= 0; --i)
		p_scratch[i] = p_challenge[pp_perm_challenge[i_key_type][i]];

	i_css_variant = (i_key_type == 0) ? i_variant :	pp_perm_variant[i_key_type-1][i_variant];

	/*
	 * This encryption engine implements one of 32 variations
	 * one the same theme depending upon the choice in the
	 * variant parameter (0 - 31).
	 *
	 * The algorithm itself manipulates a 40 bit input into
	 * a 40 bit output.
	 * The parameter 'input' is 80 bits.  It consists of
	 * the 40 bit input value that is to be encrypted followed
	 * by a 40 bit seed value for the pseudo random number
	 * generators.
	 */

	/* Feed the secret into the input values such that
	 * we alter the seed to the LFSR's used above,  then
	 * generate the bits to play with.
	 */
	for( i = 5 ; --i >= 0 ; )
		p_tmp1[i] = p_scratch[5 + i] ^ p_secret[i] ^ p_crypt_tab2[i];

	/*
	 * We use two LFSR's (seeded from some of the input data bytes) to
	 * generate two streams of pseudo-random bits.  These two bit streams
	 * are then combined by simply adding with carry to generate a final
	 * sequence of pseudo-random bits which is stored in the buffer that
	 * 'output' points to the end of - len is the size of this buffer.
	 *
	 * The first LFSR is of degree 25,  and has a polynomial of:
	 * x^13 + x^5 + x^4 + x^1 + 1
	 *
	 * The second LSFR is of degree 17,  and has a (primitive) polynomial of:
	 * x^15 + x^1 + 1
	 *
	 * I don't know if these polynomials are primitive modulo 2,  and thus
	 * represent maximal-period LFSR's.
	 *
	 *
	 * Note that we take the output of each LFSR from the new shifted in
	 * bit,  not the old shifted out bit.  Thus for ease of use the LFSR's
	 * are implemented in bit reversed order.
	 *
	 */

	/* In order to ensure that the LFSR works we need to ensure that the
	 * initial values are non-zero.  Thus when we initialise them from
	 * the seed,  we ensure that a bit is set.
	 */
	i_lfsr0 = (p_tmp1[0] << 17) | (p_tmp1[1] << 9) | ((p_tmp1[2] & ~7) << 1 ) | 8 | (p_tmp1[2] & 7);
	i_lfsr1 = (p_tmp1[3] << 9) | 0x100 | p_tmp1[4];

	i_index = sizeof(p_bits);
	i_carry = 0;

	do
	{
		for(i_bit = 0, i_val = 0 ; i_bit < 8 ; ++i_bit)
		{
			i_lfsr0_o = (uint8_t)(((i_lfsr0 >> 24) ^ (i_lfsr0 >> 21) ^ (i_lfsr0 >> 20) ^ (i_lfsr0 >> 12)) & 1);
			i_lfsr0 = (i_lfsr0 << 1) | i_lfsr0_o;

			i_lfsr1_o = (uint8_t)(((i_lfsr1 >> 16) ^ (i_lfsr1 >> 2)) & 1);
			i_lfsr1 = (i_lfsr1 << 1) | i_lfsr1_o;

			i_combined = !i_lfsr1_o + i_carry + !i_lfsr0_o;
			/* taking bit 1 */
			i_carry = (i_combined >> 1) & 1;
			i_val |= (i_combined & 1) << i_bit;
		}

		p_bits[--i_index] = i_val;
	} while(i_index > 0);

	/* This term is used throughout the following to
	 * select one of 32 different variations on the
	 * algorithm.
	 */
	i_cse = p_variants[i_css_variant] ^ p_crypt_tab2[i_css_variant];

	/* Now the actual blocks doing the encryption.  Each
	 * of these works on 40 bits at a time and are quite
	 * similar.
	 */
	i_index = 0;
	for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_scratch[i])
	{
		i_index = p_bits[25 + i] ^ p_scratch[i];
		i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

		p_tmp1[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
	}
	p_tmp1[4] ^= p_tmp1[0];

	for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp1[i])
	{
		i_index = p_bits[20 + i] ^ p_tmp1[i];
		i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

		p_tmp2[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
	}
	p_tmp2[4] ^= p_tmp2[0];

	for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp2[i])
	{
		i_index = p_bits[15 + i] ^ p_tmp2[i];
		i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;
		i_index = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;

		p_tmp1[i] = p_crypt_tab0[i_index] ^ p_crypt_tab2[i_index];
	}
	p_tmp1[4] ^= p_tmp1[0];

	for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp1[i])
	{
		i_index = p_bits[10 + i] ^ p_tmp1[i];
		i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

		i_index = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;

		p_tmp2[i] = p_crypt_tab0[i_index] ^ p_crypt_tab2[i_index];
	}
	p_tmp2[4] ^= p_tmp2[0];

	for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp2[i])
	{
		i_index = p_bits[5 + i] ^ p_tmp2[i];
		i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

		p_tmp1[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
	}
	p_tmp1[4] ^= p_tmp1[0];

	for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp1[i])
	{
		i_index = p_bits[i] ^ p_tmp1[i];
		i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

		p_key[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
	}

	return;
}

void DecryptKey(uint8_t invert, uint8_t *p_key, uint8_t *p_crypted, uint8_t *p_result)
{
	unsigned int	i_lfsr1_lo;
	unsigned int	i_lfsr1_hi;
	unsigned int	i_lfsr0;
	unsigned int	i_combined;
	uint8_t	      o_lfsr0;
	uint8_t       o_lfsr1;
	uint8_t       k[5];
	int           i;

	i_lfsr1_lo = p_key[0] | 0x100;
	i_lfsr1_hi = p_key[1];
#if 0
	i_lfsr0	= ((p_key[4] << 17) | (p_key[3] << 9) | (p_key[2] << 1)) + 8 - (p_key[2] & 7);
	i_lfsr0	= (p_css_tab4[i_lfsr0 & 0xff] << 24) | (p_css_tab4[(i_lfsr0 >> 8) & 0xff] << 16) |
	          (p_css_tab4[(i_lfsr0 >> 16) & 0xff] << 8) | p_css_tab4[(i_lfsr0 >> 24) & 0xff];
#else
	i_lfsr0 = *((unsigned int *)(p_key + 2));
	o_lfsr1 = i_lfsr0 & 7;
	i_lfsr0 = i_lfsr0 * 2 + 8 - o_lfsr1;
#endif
	i_combined = 0;
	for(i = 0 ; i < KEY_SIZE ; ++i)
	{
		o_lfsr1	 = p_css_tab2[i_lfsr1_hi] ^ p_css_tab3[i_lfsr1_lo];
		i_lfsr1_hi  = i_lfsr1_lo >> 1;
		i_lfsr1_lo  = ((i_lfsr1_lo & 1) << 8) ^ o_lfsr1;
		o_lfsr1	 = p_css_tab4[o_lfsr1];
#if 0
		o_lfsr0 = (((((((i_lfsr0 >> 8) ^ i_lfsr0) >> 1)	^ i_lfsr0) >> 3) ^ i_lfsr0) >> 7);
		i_lfsr0 = (i_lfsr0 >> 8) | (o_lfsr0 << 24);
#else
		o_lfsr0 = (((((((i_lfsr0 >> 3) ^ i_lfsr0) >> 1) ^ i_lfsr0) >> 8) ^ i_lfsr0) >> 5) & 0xff;
		i_lfsr0 = (i_lfsr0 << 8) | o_lfsr0;
		o_lfsr0 = p_css_tab4[o_lfsr0];
#endif
		i_combined += (o_lfsr0 ^ invert) + o_lfsr1;
		k[i] = i_combined & 0xff;
		i_combined >>= 8;
	}

	p_result[4] = k[4] ^ p_css_tab1[p_crypted[4]] ^ p_crypted[3];
	p_result[3] = k[3] ^ p_css_tab1[p_crypted[3]] ^ p_crypted[2];
	p_result[2] = k[2] ^ p_css_tab1[p_crypted[2]] ^ p_crypted[1];
	p_result[1] = k[1] ^ p_css_tab1[p_crypted[1]] ^ p_crypted[0];
	p_result[0] = k[0] ^ p_css_tab1[p_crypted[0]] ^ p_result[4];

	p_result[4] = k[4] ^ p_css_tab1[p_result[4]] ^ p_result[3];
	p_result[3] = k[3] ^ p_css_tab1[p_result[3]] ^ p_result[2];
	p_result[2] = k[2] ^ p_css_tab1[p_result[2]] ^ p_result[1];
	p_result[1] = k[1] ^ p_css_tab1[p_result[1]] ^ p_result[0];
	p_result[0] = k[0] ^ p_css_tab1[p_result[0]];

	return;
}

void DecryptTitleKey(uint8_t invert, uint8_t *p_key, uint8_t *p_crypted, uint8_t *p_result)
{
	unsigned int	i_lfsr1_lo;
	unsigned int	i_lfsr1_hi;
	unsigned int	i_lfsr0;
	unsigned int	i_combined;
	uint8_t	      o_lfsr0;
	uint8_t       o_lfsr1;
	uint8_t       k[5];
	int           i;

	i_lfsr1_lo = p_key[0] | 0x100;
	i_lfsr1_hi = p_key[1];
#if 0
	i_lfsr0 = ((p_key[4] << 17) | (p_key[3] << 9) | (p_key[2] << 1)) + 8 - (p_key[2] & 7);
	i_lfsr0 = (p_css_tab4[i_lfsr0 & 0xff] << 24) | (p_css_tab4[(i_lfsr0 >> 8) & 0xff] << 16) |
		(p_css_tab4[(i_lfsr0 >> 16) & 0xff] << 8) | p_css_tab4[(i_lfsr0 >> 24) & 0xff];
#else
	i_lfsr0 = *((unsigned int *)(p_key + 2));
	o_lfsr1 = i_lfsr0 & 7;
	i_lfsr0 = i_lfsr0 * 2 + 8 - o_lfsr1;
#endif
	i_combined = 0;
	for (i = 0; i < KEY_SIZE; ++i)
	{
		o_lfsr1 = p_css_tab2[i_lfsr1_hi] ^ p_css_tab3[i_lfsr1_lo];
		i_lfsr1_hi = i_lfsr1_lo >> 1;
		i_lfsr1_lo = ((i_lfsr1_lo & 1) << 8) ^ o_lfsr1;
		o_lfsr1 = p_css_tab4[o_lfsr1];
#if 0
		o_lfsr0 = (((((((i_lfsr0 >> 8) ^ i_lfsr0) >> 1) ^ i_lfsr0) >> 3) ^ i_lfsr0) >> 7);
		i_lfsr0 = (i_lfsr0 >> 8) | (o_lfsr0 << 24);
#else
		o_lfsr0 = (((((((i_lfsr0 >> 3) ^ i_lfsr0) >> 1) ^ i_lfsr0) >> 8) ^ i_lfsr0) >> 5) & 0xff;
		i_lfsr0 = (i_lfsr0 << 8) | o_lfsr0;
		o_lfsr0 = p_css_tab5[o_lfsr0];
#endif
		i_combined += (o_lfsr0 ^ invert) + o_lfsr1;
		k[i] = i_combined & 0xff;
		i_combined >>= 8;
	}

	p_result[4] = k[4] ^ p_css_tab1[p_crypted[4]] ^ p_crypted[3];
	p_result[3] = k[3] ^ p_css_tab1[p_crypted[3]] ^ p_crypted[2];
	p_result[2] = k[2] ^ p_css_tab1[p_crypted[2]] ^ p_crypted[1];
	p_result[1] = k[1] ^ p_css_tab1[p_crypted[1]] ^ p_crypted[0];
	p_result[0] = k[0] ^ p_css_tab1[p_crypted[0]] ^ p_result[4];

	p_result[4] = k[4] ^ p_css_tab1[p_result[4]] ^ p_result[3];
	p_result[3] = k[3] ^ p_css_tab1[p_result[3]] ^ p_result[2];
	p_result[2] = k[2] ^ p_css_tab1[p_result[2]] ^ p_result[1];
	p_result[1] = k[1] ^ p_css_tab1[p_result[1]] ^ p_result[0];
	p_result[0] = k[0] ^ p_css_tab1[p_result[0]];

	return;
}

static const dvd_key_t player_keys[] =
{
	{ 0x01, 0xaf, 0xe3, 0x12, 0x80 },
	{ 0x12, 0x11, 0xca, 0x04, 0x3b },
	{ 0x14, 0x0c, 0x9e, 0xd0, 0x09 },
	{ 0x14, 0x71, 0x35, 0xba, 0xe2 },
	{ 0x1a, 0xa4, 0x33, 0x21, 0xa6 },
	{ 0x26, 0xec, 0xc4, 0xa7, 0x4e },
	{ 0x2c, 0xb2, 0xc1, 0x09, 0xee },
	{ 0x2f, 0x25, 0x9e, 0x96, 0xdd },
	{ 0x33, 0x2f, 0x49, 0x6c, 0xe0 },
	{ 0x35, 0x5b, 0xc1, 0x31, 0x0f },
	{ 0x36, 0x67, 0xb2, 0xe3, 0x85 },
	{ 0x39, 0x3d, 0xf1, 0xf1, 0xbd },
	{ 0x3b, 0x31, 0x34, 0x0d, 0x91 },
	{ 0x45, 0xed, 0x28, 0xeb, 0xd3 },
	{ 0x48, 0xb7, 0x6c, 0xce, 0x69 },
	{ 0x4b, 0x65, 0x0d, 0xc1, 0xee },
	{ 0x4c, 0xbb, 0xf5, 0x5b, 0x23 },
	{ 0x51, 0x67, 0x67, 0xc5, 0xe0 },
	{ 0x53, 0x94, 0xe1, 0x75, 0xbf },
	{ 0x57, 0x2c, 0x8b, 0x31, 0xae },
	{ 0x63, 0xdb, 0x4c, 0x5b, 0x4a },
	{ 0x7b, 0x1e, 0x5e, 0x2b, 0x57 },
	{ 0x85, 0xf3, 0x85, 0xa0, 0xe0 },
	{ 0xab, 0x1e, 0xe7, 0x7b, 0x72 },
	{ 0xab, 0x36, 0xe3, 0xeb, 0x76 },
	{ 0xb1, 0xb8, 0xf9, 0x38, 0x03 },
	{ 0xb8, 0x5d, 0xd8, 0x53, 0xbd },
	{ 0xbf, 0x92, 0xc3, 0xb0, 0xe2 },
	{ 0xcf, 0x1a, 0xb2, 0xf8, 0x0a },
	{ 0xec, 0xa0, 0xcf, 0xb3, 0xff },
	{ 0xfc, 0x95, 0xa9, 0x87, 0x35 }
};

int DecryptDiscKey(uint8_t *p_struct_disckey, dvd_key_t p_disc_key)
{
	uint8_t p_verify[KEY_SIZE];
	uint32_t i, n = 0;
	/* Decrypt disc key with the above player keys */
	for (n = 0; n < sizeof(player_keys) / sizeof(dvd_key_t); n++)
	{
		for(i = 1; i < 409; i++)
		{
			/* Check if player key n is the right key for position i. */
			DecryptKey(0, (uint8_t*)player_keys[n], p_struct_disckey + 5 * i, p_disc_key);
			/* The first part in the struct_disckey block is the
			 * 'disc key' encrypted with itself.  Using this we
			 * can check if we decrypted the correct key. */
			DecryptKey(0, p_disc_key, p_struct_disckey, p_verify);
			/* If the position / player key pair worked then return. */
			if (memcmp(p_disc_key, p_verify, KEY_SIZE) == 0) {
				fprintf(fpLog, "PlayerKey[%ld]: %02X %02X %02X %02X %02X\n"
					, n + 1, player_keys[n][0], player_keys[n][1]
					, player_keys[n][2], player_keys[n][3], player_keys[n][4]);
				fprintf(fpLog, "DecryptedDiscKey[%03ld]: %02X %02X %02X %02X %02X\n"
					, i + 1, p_disc_key[0], p_disc_key[1], p_disc_key[2]
					, p_disc_key[3], p_disc_key[4]);
				return 0;
			}
		}
	}
	/* Have tried all combinations of positions and keys,
	 * and we still didn't succeed. */
	memset(p_disc_key, 0, KEY_SIZE);
	return -1;
}
