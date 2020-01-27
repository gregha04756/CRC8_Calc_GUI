#include "pch.h"
#include "crc8sae_j1850.h"

// This code assumes that unsigned is 4 bytes.

unsigned crc8sae_j1850_bit(unsigned crc, void const *mem, size_t len) {
	unsigned char const *data = (unsigned char const *)mem;
	if (data == NULL)
		return 0;
	crc = ~crc;
	while (len--) {
		crc ^= *data++;
		for (unsigned k = 0; k < 8; k++)
			crc = crc & 0x80 ? (crc << 1) ^ 0x1d : crc << 1;
	}
	crc = ~crc;
	crc &= 0xff;
	return crc;
}

unsigned crc8sae_j1850_rem(unsigned crc, unsigned val, unsigned bits) {
	crc = ~crc;
	val &= 0x100 - (0x100 >> bits);
	crc ^= val;
	while (bits--)
		crc = crc & 0x80 ? (crc << 1) ^ 0x1d : crc << 1;
	crc = ~crc;
	crc &= 0xff;
	return crc;
}

#define table_byte table_word[0]

static unsigned char const table_word[][256] = {
   {0x3b, 0x26, 0x01, 0x1c, 0x4f, 0x52, 0x75, 0x68, 0xd3, 0xce, 0xe9, 0xf4, 0xa7,
	0xba, 0x9d, 0x80, 0xf6, 0xeb, 0xcc, 0xd1, 0x82, 0x9f, 0xb8, 0xa5, 0x1e, 0x03,
	0x24, 0x39, 0x6a, 0x77, 0x50, 0x4d, 0xbc, 0xa1, 0x86, 0x9b, 0xc8, 0xd5, 0xf2,
	0xef, 0x54, 0x49, 0x6e, 0x73, 0x20, 0x3d, 0x1a, 0x07, 0x71, 0x6c, 0x4b, 0x56,
	0x05, 0x18, 0x3f, 0x22, 0x99, 0x84, 0xa3, 0xbe, 0xed, 0xf0, 0xd7, 0xca, 0x28,
	0x35, 0x12, 0x0f, 0x5c, 0x41, 0x66, 0x7b, 0xc0, 0xdd, 0xfa, 0xe7, 0xb4, 0xa9,
	0x8e, 0x93, 0xe5, 0xf8, 0xdf, 0xc2, 0x91, 0x8c, 0xab, 0xb6, 0x0d, 0x10, 0x37,
	0x2a, 0x79, 0x64, 0x43, 0x5e, 0xaf, 0xb2, 0x95, 0x88, 0xdb, 0xc6, 0xe1, 0xfc,
	0x47, 0x5a, 0x7d, 0x60, 0x33, 0x2e, 0x09, 0x14, 0x62, 0x7f, 0x58, 0x45, 0x16,
	0x0b, 0x2c, 0x31, 0x8a, 0x97, 0xb0, 0xad, 0xfe, 0xe3, 0xc4, 0xd9, 0x1d, 0x00,
	0x27, 0x3a, 0x69, 0x74, 0x53, 0x4e, 0xf5, 0xe8, 0xcf, 0xd2, 0x81, 0x9c, 0xbb,
	0xa6, 0xd0, 0xcd, 0xea, 0xf7, 0xa4, 0xb9, 0x9e, 0x83, 0x38, 0x25, 0x02, 0x1f,
	0x4c, 0x51, 0x76, 0x6b, 0x9a, 0x87, 0xa0, 0xbd, 0xee, 0xf3, 0xd4, 0xc9, 0x72,
	0x6f, 0x48, 0x55, 0x06, 0x1b, 0x3c, 0x21, 0x57, 0x4a, 0x6d, 0x70, 0x23, 0x3e,
	0x19, 0x04, 0xbf, 0xa2, 0x85, 0x98, 0xcb, 0xd6, 0xf1, 0xec, 0x0e, 0x13, 0x34,
	0x29, 0x7a, 0x67, 0x40, 0x5d, 0xe6, 0xfb, 0xdc, 0xc1, 0x92, 0x8f, 0xa8, 0xb5,
	0xc3, 0xde, 0xf9, 0xe4, 0xb7, 0xaa, 0x8d, 0x90, 0x2b, 0x36, 0x11, 0x0c, 0x5f,
	0x42, 0x65, 0x78, 0x89, 0x94, 0xb3, 0xae, 0xfd, 0xe0, 0xc7, 0xda, 0x61, 0x7c,
	0x5b, 0x46, 0x15, 0x08, 0x2f, 0x32, 0x44, 0x59, 0x7e, 0x63, 0x30, 0x2d, 0x0a,
	0x17, 0xac, 0xb1, 0x96, 0x8b, 0xd8, 0xc5, 0xe2, 0xff},
   {0x85, 0xc9, 0x1d, 0x51, 0xa8, 0xe4, 0x30, 0x7c, 0xdf, 0x93, 0x47, 0x0b, 0xf2,
	0xbe, 0x6a, 0x26, 0x31, 0x7d, 0xa9, 0xe5, 0x1c, 0x50, 0x84, 0xc8, 0x6b, 0x27,
	0xf3, 0xbf, 0x46, 0x0a, 0xde, 0x92, 0xf0, 0xbc, 0x68, 0x24, 0xdd, 0x91, 0x45,
	0x09, 0xaa, 0xe6, 0x32, 0x7e, 0x87, 0xcb, 0x1f, 0x53, 0x44, 0x08, 0xdc, 0x90,
	0x69, 0x25, 0xf1, 0xbd, 0x1e, 0x52, 0x86, 0xca, 0x33, 0x7f, 0xab, 0xe7, 0x6f,
	0x23, 0xf7, 0xbb, 0x42, 0x0e, 0xda, 0x96, 0x35, 0x79, 0xad, 0xe1, 0x18, 0x54,
	0x80, 0xcc, 0xdb, 0x97, 0x43, 0x0f, 0xf6, 0xba, 0x6e, 0x22, 0x81, 0xcd, 0x19,
	0x55, 0xac, 0xe0, 0x34, 0x78, 0x1a, 0x56, 0x82, 0xce, 0x37, 0x7b, 0xaf, 0xe3,
	0x40, 0x0c, 0xd8, 0x94, 0x6d, 0x21, 0xf5, 0xb9, 0xae, 0xe2, 0x36, 0x7a, 0x83,
	0xcf, 0x1b, 0x57, 0xf4, 0xb8, 0x6c, 0x20, 0xd9, 0x95, 0x41, 0x0d, 0x4c, 0x00,
	0xd4, 0x98, 0x61, 0x2d, 0xf9, 0xb5, 0x16, 0x5a, 0x8e, 0xc2, 0x3b, 0x77, 0xa3,
	0xef, 0xf8, 0xb4, 0x60, 0x2c, 0xd5, 0x99, 0x4d, 0x01, 0xa2, 0xee, 0x3a, 0x76,
	0x8f, 0xc3, 0x17, 0x5b, 0x39, 0x75, 0xa1, 0xed, 0x14, 0x58, 0x8c, 0xc0, 0x63,
	0x2f, 0xfb, 0xb7, 0x4e, 0x02, 0xd6, 0x9a, 0x8d, 0xc1, 0x15, 0x59, 0xa0, 0xec,
	0x38, 0x74, 0xd7, 0x9b, 0x4f, 0x03, 0xfa, 0xb6, 0x62, 0x2e, 0xa6, 0xea, 0x3e,
	0x72, 0x8b, 0xc7, 0x13, 0x5f, 0xfc, 0xb0, 0x64, 0x28, 0xd1, 0x9d, 0x49, 0x05,
	0x12, 0x5e, 0x8a, 0xc6, 0x3f, 0x73, 0xa7, 0xeb, 0x48, 0x04, 0xd0, 0x9c, 0x65,
	0x29, 0xfd, 0xb1, 0xd3, 0x9f, 0x4b, 0x07, 0xfe, 0xb2, 0x66, 0x2a, 0x89, 0xc5,
	0x11, 0x5d, 0xa4, 0xe8, 0x3c, 0x70, 0x67, 0x2b, 0xff, 0xb3, 0x4a, 0x06, 0xd2,
	0x9e, 0x3d, 0x71, 0xa5, 0xe9, 0x10, 0x5c, 0x88, 0xc4},
   {0x4f, 0xc0, 0x4c, 0xc3, 0x49, 0xc6, 0x4a, 0xc5, 0x43, 0xcc, 0x40, 0xcf, 0x45,
	0xca, 0x46, 0xc9, 0x57, 0xd8, 0x54, 0xdb, 0x51, 0xde, 0x52, 0xdd, 0x5b, 0xd4,
	0x58, 0xd7, 0x5d, 0xd2, 0x5e, 0xd1, 0x7f, 0xf0, 0x7c, 0xf3, 0x79, 0xf6, 0x7a,
	0xf5, 0x73, 0xfc, 0x70, 0xff, 0x75, 0xfa, 0x76, 0xf9, 0x67, 0xe8, 0x64, 0xeb,
	0x61, 0xee, 0x62, 0xed, 0x6b, 0xe4, 0x68, 0xe7, 0x6d, 0xe2, 0x6e, 0xe1, 0x2f,
	0xa0, 0x2c, 0xa3, 0x29, 0xa6, 0x2a, 0xa5, 0x23, 0xac, 0x20, 0xaf, 0x25, 0xaa,
	0x26, 0xa9, 0x37, 0xb8, 0x34, 0xbb, 0x31, 0xbe, 0x32, 0xbd, 0x3b, 0xb4, 0x38,
	0xb7, 0x3d, 0xb2, 0x3e, 0xb1, 0x1f, 0x90, 0x1c, 0x93, 0x19, 0x96, 0x1a, 0x95,
	0x13, 0x9c, 0x10, 0x9f, 0x15, 0x9a, 0x16, 0x99, 0x07, 0x88, 0x04, 0x8b, 0x01,
	0x8e, 0x02, 0x8d, 0x0b, 0x84, 0x08, 0x87, 0x0d, 0x82, 0x0e, 0x81, 0x8f, 0x00,
	0x8c, 0x03, 0x89, 0x06, 0x8a, 0x05, 0x83, 0x0c, 0x80, 0x0f, 0x85, 0x0a, 0x86,
	0x09, 0x97, 0x18, 0x94, 0x1b, 0x91, 0x1e, 0x92, 0x1d, 0x9b, 0x14, 0x98, 0x17,
	0x9d, 0x12, 0x9e, 0x11, 0xbf, 0x30, 0xbc, 0x33, 0xb9, 0x36, 0xba, 0x35, 0xb3,
	0x3c, 0xb0, 0x3f, 0xb5, 0x3a, 0xb6, 0x39, 0xa7, 0x28, 0xa4, 0x2b, 0xa1, 0x2e,
	0xa2, 0x2d, 0xab, 0x24, 0xa8, 0x27, 0xad, 0x22, 0xae, 0x21, 0xef, 0x60, 0xec,
	0x63, 0xe9, 0x66, 0xea, 0x65, 0xe3, 0x6c, 0xe0, 0x6f, 0xe5, 0x6a, 0xe6, 0x69,
	0xf7, 0x78, 0xf4, 0x7b, 0xf1, 0x7e, 0xf2, 0x7d, 0xfb, 0x74, 0xf8, 0x77, 0xfd,
	0x72, 0xfe, 0x71, 0xdf, 0x50, 0xdc, 0x53, 0xd9, 0x56, 0xda, 0x55, 0xd3, 0x5c,
	0xd0, 0x5f, 0xd5, 0x5a, 0xd6, 0x59, 0xc7, 0x48, 0xc4, 0x4b, 0xc1, 0x4e, 0xc2,
	0x4d, 0xcb, 0x44, 0xc8, 0x47, 0xcd, 0x42, 0xce, 0x41},
   {0xa8, 0x35, 0x8f, 0x12, 0xe6, 0x7b, 0xc1, 0x5c, 0x34, 0xa9, 0x13, 0x8e, 0x7a,
	0xe7, 0x5d, 0xc0, 0x8d, 0x10, 0xaa, 0x37, 0xc3, 0x5e, 0xe4, 0x79, 0x11, 0x8c,
	0x36, 0xab, 0x5f, 0xc2, 0x78, 0xe5, 0xe2, 0x7f, 0xc5, 0x58, 0xac, 0x31, 0x8b,
	0x16, 0x7e, 0xe3, 0x59, 0xc4, 0x30, 0xad, 0x17, 0x8a, 0xc7, 0x5a, 0xe0, 0x7d,
	0x89, 0x14, 0xae, 0x33, 0x5b, 0xc6, 0x7c, 0xe1, 0x15, 0x88, 0x32, 0xaf, 0x3c,
	0xa1, 0x1b, 0x86, 0x72, 0xef, 0x55, 0xc8, 0xa0, 0x3d, 0x87, 0x1a, 0xee, 0x73,
	0xc9, 0x54, 0x19, 0x84, 0x3e, 0xa3, 0x57, 0xca, 0x70, 0xed, 0x85, 0x18, 0xa2,
	0x3f, 0xcb, 0x56, 0xec, 0x71, 0x76, 0xeb, 0x51, 0xcc, 0x38, 0xa5, 0x1f, 0x82,
	0xea, 0x77, 0xcd, 0x50, 0xa4, 0x39, 0x83, 0x1e, 0x53, 0xce, 0x74, 0xe9, 0x1d,
	0x80, 0x3a, 0xa7, 0xcf, 0x52, 0xe8, 0x75, 0x81, 0x1c, 0xa6, 0x3b, 0x9d, 0x00,
	0xba, 0x27, 0xd3, 0x4e, 0xf4, 0x69, 0x01, 0x9c, 0x26, 0xbb, 0x4f, 0xd2, 0x68,
	0xf5, 0xb8, 0x25, 0x9f, 0x02, 0xf6, 0x6b, 0xd1, 0x4c, 0x24, 0xb9, 0x03, 0x9e,
	0x6a, 0xf7, 0x4d, 0xd0, 0xd7, 0x4a, 0xf0, 0x6d, 0x99, 0x04, 0xbe, 0x23, 0x4b,
	0xd6, 0x6c, 0xf1, 0x05, 0x98, 0x22, 0xbf, 0xf2, 0x6f, 0xd5, 0x48, 0xbc, 0x21,
	0x9b, 0x06, 0x6e, 0xf3, 0x49, 0xd4, 0x20, 0xbd, 0x07, 0x9a, 0x09, 0x94, 0x2e,
	0xb3, 0x47, 0xda, 0x60, 0xfd, 0x95, 0x08, 0xb2, 0x2f, 0xdb, 0x46, 0xfc, 0x61,
	0x2c, 0xb1, 0x0b, 0x96, 0x62, 0xff, 0x45, 0xd8, 0xb0, 0x2d, 0x97, 0x0a, 0xfe,
	0x63, 0xd9, 0x44, 0x43, 0xde, 0x64, 0xf9, 0x0d, 0x90, 0x2a, 0xb7, 0xdf, 0x42,
	0xf8, 0x65, 0x91, 0x0c, 0xb6, 0x2b, 0x66, 0xfb, 0x41, 0xdc, 0x28, 0xb5, 0x0f,
	0x92, 0xfa, 0x67, 0xdd, 0x40, 0xb4, 0x29, 0x93, 0x0e},
   {0x49, 0x23, 0x9d, 0xf7, 0xfc, 0x96, 0x28, 0x42, 0x3e, 0x54, 0xea, 0x80, 0x8b,
	0xe1, 0x5f, 0x35, 0xa7, 0xcd, 0x73, 0x19, 0x12, 0x78, 0xc6, 0xac, 0xd0, 0xba,
	0x04, 0x6e, 0x65, 0x0f, 0xb1, 0xdb, 0x88, 0xe2, 0x5c, 0x36, 0x3d, 0x57, 0xe9,
	0x83, 0xff, 0x95, 0x2b, 0x41, 0x4a, 0x20, 0x9e, 0xf4, 0x66, 0x0c, 0xb2, 0xd8,
	0xd3, 0xb9, 0x07, 0x6d, 0x11, 0x7b, 0xc5, 0xaf, 0xa4, 0xce, 0x70, 0x1a, 0xd6,
	0xbc, 0x02, 0x68, 0x63, 0x09, 0xb7, 0xdd, 0xa1, 0xcb, 0x75, 0x1f, 0x14, 0x7e,
	0xc0, 0xaa, 0x38, 0x52, 0xec, 0x86, 0x8d, 0xe7, 0x59, 0x33, 0x4f, 0x25, 0x9b,
	0xf1, 0xfa, 0x90, 0x2e, 0x44, 0x17, 0x7d, 0xc3, 0xa9, 0xa2, 0xc8, 0x76, 0x1c,
	0x60, 0x0a, 0xb4, 0xde, 0xd5, 0xbf, 0x01, 0x6b, 0xf9, 0x93, 0x2d, 0x47, 0x4c,
	0x26, 0x98, 0xf2, 0x8e, 0xe4, 0x5a, 0x30, 0x3b, 0x51, 0xef, 0x85, 0x6a, 0x00,
	0xbe, 0xd4, 0xdf, 0xb5, 0x0b, 0x61, 0x1d, 0x77, 0xc9, 0xa3, 0xa8, 0xc2, 0x7c,
	0x16, 0x84, 0xee, 0x50, 0x3a, 0x31, 0x5b, 0xe5, 0x8f, 0xf3, 0x99, 0x27, 0x4d,
	0x46, 0x2c, 0x92, 0xf8, 0xab, 0xc1, 0x7f, 0x15, 0x1e, 0x74, 0xca, 0xa0, 0xdc,
	0xb6, 0x08, 0x62, 0x69, 0x03, 0xbd, 0xd7, 0x45, 0x2f, 0x91, 0xfb, 0xf0, 0x9a,
	0x24, 0x4e, 0x32, 0x58, 0xe6, 0x8c, 0x87, 0xed, 0x53, 0x39, 0xf5, 0x9f, 0x21,
	0x4b, 0x40, 0x2a, 0x94, 0xfe, 0x82, 0xe8, 0x56, 0x3c, 0x37, 0x5d, 0xe3, 0x89,
	0x1b, 0x71, 0xcf, 0xa5, 0xae, 0xc4, 0x7a, 0x10, 0x6c, 0x06, 0xb8, 0xd2, 0xd9,
	0xb3, 0x0d, 0x67, 0x34, 0x5e, 0xe0, 0x8a, 0x81, 0xeb, 0x55, 0x3f, 0x43, 0x29,
	0x97, 0xfd, 0xf6, 0x9c, 0x22, 0x48, 0xda, 0xb0, 0x0e, 0x64, 0x6f, 0x05, 0xbb,
	0xd1, 0xad, 0xc7, 0x79, 0x13, 0x18, 0x72, 0xcc, 0xa6},
   {0xe6, 0xa0, 0x6a, 0x2c, 0xe3, 0xa5, 0x6f, 0x29, 0xec, 0xaa, 0x60, 0x26, 0xe9,
	0xaf, 0x65, 0x23, 0xf2, 0xb4, 0x7e, 0x38, 0xf7, 0xb1, 0x7b, 0x3d, 0xf8, 0xbe,
	0x74, 0x32, 0xfd, 0xbb, 0x71, 0x37, 0xce, 0x88, 0x42, 0x04, 0xcb, 0x8d, 0x47,
	0x01, 0xc4, 0x82, 0x48, 0x0e, 0xc1, 0x87, 0x4d, 0x0b, 0xda, 0x9c, 0x56, 0x10,
	0xdf, 0x99, 0x53, 0x15, 0xd0, 0x96, 0x5c, 0x1a, 0xd5, 0x93, 0x59, 0x1f, 0xb6,
	0xf0, 0x3a, 0x7c, 0xb3, 0xf5, 0x3f, 0x79, 0xbc, 0xfa, 0x30, 0x76, 0xb9, 0xff,
	0x35, 0x73, 0xa2, 0xe4, 0x2e, 0x68, 0xa7, 0xe1, 0x2b, 0x6d, 0xa8, 0xee, 0x24,
	0x62, 0xad, 0xeb, 0x21, 0x67, 0x9e, 0xd8, 0x12, 0x54, 0x9b, 0xdd, 0x17, 0x51,
	0x94, 0xd2, 0x18, 0x5e, 0x91, 0xd7, 0x1d, 0x5b, 0x8a, 0xcc, 0x06, 0x40, 0x8f,
	0xc9, 0x03, 0x45, 0x80, 0xc6, 0x0c, 0x4a, 0x85, 0xc3, 0x09, 0x4f, 0x46, 0x00,
	0xca, 0x8c, 0x43, 0x05, 0xcf, 0x89, 0x4c, 0x0a, 0xc0, 0x86, 0x49, 0x0f, 0xc5,
	0x83, 0x52, 0x14, 0xde, 0x98, 0x57, 0x11, 0xdb, 0x9d, 0x58, 0x1e, 0xd4, 0x92,
	0x5d, 0x1b, 0xd1, 0x97, 0x6e, 0x28, 0xe2, 0xa4, 0x6b, 0x2d, 0xe7, 0xa1, 0x64,
	0x22, 0xe8, 0xae, 0x61, 0x27, 0xed, 0xab, 0x7a, 0x3c, 0xf6, 0xb0, 0x7f, 0x39,
	0xf3, 0xb5, 0x70, 0x36, 0xfc, 0xba, 0x75, 0x33, 0xf9, 0xbf, 0x16, 0x50, 0x9a,
	0xdc, 0x13, 0x55, 0x9f, 0xd9, 0x1c, 0x5a, 0x90, 0xd6, 0x19, 0x5f, 0x95, 0xd3,
	0x02, 0x44, 0x8e, 0xc8, 0x07, 0x41, 0x8b, 0xcd, 0x08, 0x4e, 0x84, 0xc2, 0x0d,
	0x4b, 0x81, 0xc7, 0x3e, 0x78, 0xb2, 0xf4, 0x3b, 0x7d, 0xb7, 0xf1, 0x34, 0x72,
	0xb8, 0xfe, 0x31, 0x77, 0xbd, 0xfb, 0x2a, 0x6c, 0xa6, 0xe0, 0x2f, 0x69, 0xa3,
	0xe5, 0x20, 0x66, 0xac, 0xea, 0x25, 0x63, 0xa9, 0xef},
   {0xfc, 0xa1, 0x46, 0x1b, 0x95, 0xc8, 0x2f, 0x72, 0x2e, 0x73, 0x94, 0xc9, 0x47,
	0x1a, 0xfd, 0xa0, 0x45, 0x18, 0xff, 0xa2, 0x2c, 0x71, 0x96, 0xcb, 0x97, 0xca,
	0x2d, 0x70, 0xfe, 0xa3, 0x44, 0x19, 0x93, 0xce, 0x29, 0x74, 0xfa, 0xa7, 0x40,
	0x1d, 0x41, 0x1c, 0xfb, 0xa6, 0x28, 0x75, 0x92, 0xcf, 0x2a, 0x77, 0x90, 0xcd,
	0x43, 0x1e, 0xf9, 0xa4, 0xf8, 0xa5, 0x42, 0x1f, 0x91, 0xcc, 0x2b, 0x76, 0x22,
	0x7f, 0x98, 0xc5, 0x4b, 0x16, 0xf1, 0xac, 0xf0, 0xad, 0x4a, 0x17, 0x99, 0xc4,
	0x23, 0x7e, 0x9b, 0xc6, 0x21, 0x7c, 0xf2, 0xaf, 0x48, 0x15, 0x49, 0x14, 0xf3,
	0xae, 0x20, 0x7d, 0x9a, 0xc7, 0x4d, 0x10, 0xf7, 0xaa, 0x24, 0x79, 0x9e, 0xc3,
	0x9f, 0xc2, 0x25, 0x78, 0xf6, 0xab, 0x4c, 0x11, 0xf4, 0xa9, 0x4e, 0x13, 0x9d,
	0xc0, 0x27, 0x7a, 0x26, 0x7b, 0x9c, 0xc1, 0x4f, 0x12, 0xf5, 0xa8, 0x5d, 0x00,
	0xe7, 0xba, 0x34, 0x69, 0x8e, 0xd3, 0x8f, 0xd2, 0x35, 0x68, 0xe6, 0xbb, 0x5c,
	0x01, 0xe4, 0xb9, 0x5e, 0x03, 0x8d, 0xd0, 0x37, 0x6a, 0x36, 0x6b, 0x8c, 0xd1,
	0x5f, 0x02, 0xe5, 0xb8, 0x32, 0x6f, 0x88, 0xd5, 0x5b, 0x06, 0xe1, 0xbc, 0xe0,
	0xbd, 0x5a, 0x07, 0x89, 0xd4, 0x33, 0x6e, 0x8b, 0xd6, 0x31, 0x6c, 0xe2, 0xbf,
	0x58, 0x05, 0x59, 0x04, 0xe3, 0xbe, 0x30, 0x6d, 0x8a, 0xd7, 0x83, 0xde, 0x39,
	0x64, 0xea, 0xb7, 0x50, 0x0d, 0x51, 0x0c, 0xeb, 0xb6, 0x38, 0x65, 0x82, 0xdf,
	0x3a, 0x67, 0x80, 0xdd, 0x53, 0x0e, 0xe9, 0xb4, 0xe8, 0xb5, 0x52, 0x0f, 0x81,
	0xdc, 0x3b, 0x66, 0xec, 0xb1, 0x56, 0x0b, 0x85, 0xd8, 0x3f, 0x62, 0x3e, 0x63,
	0x84, 0xd9, 0x57, 0x0a, 0xed, 0xb0, 0x55, 0x08, 0xef, 0xb2, 0x3c, 0x61, 0x86,
	0xdb, 0x87, 0xda, 0x3d, 0x60, 0xee, 0xb3, 0x54, 0x09},
   {0xe3, 0xbc, 0x5d, 0x02, 0x82, 0xdd, 0x3c, 0x63, 0x21, 0x7e, 0x9f, 0xc0, 0x40,
	0x1f, 0xfe, 0xa1, 0x7a, 0x25, 0xc4, 0x9b, 0x1b, 0x44, 0xa5, 0xfa, 0xb8, 0xe7,
	0x06, 0x59, 0xd9, 0x86, 0x67, 0x38, 0xcc, 0x93, 0x72, 0x2d, 0xad, 0xf2, 0x13,
	0x4c, 0x0e, 0x51, 0xb0, 0xef, 0x6f, 0x30, 0xd1, 0x8e, 0x55, 0x0a, 0xeb, 0xb4,
	0x34, 0x6b, 0x8a, 0xd5, 0x97, 0xc8, 0x29, 0x76, 0xf6, 0xa9, 0x48, 0x17, 0xbd,
	0xe2, 0x03, 0x5c, 0xdc, 0x83, 0x62, 0x3d, 0x7f, 0x20, 0xc1, 0x9e, 0x1e, 0x41,
	0xa0, 0xff, 0x24, 0x7b, 0x9a, 0xc5, 0x45, 0x1a, 0xfb, 0xa4, 0xe6, 0xb9, 0x58,
	0x07, 0x87, 0xd8, 0x39, 0x66, 0x92, 0xcd, 0x2c, 0x73, 0xf3, 0xac, 0x4d, 0x12,
	0x50, 0x0f, 0xee, 0xb1, 0x31, 0x6e, 0x8f, 0xd0, 0x0b, 0x54, 0xb5, 0xea, 0x6a,
	0x35, 0xd4, 0x8b, 0xc9, 0x96, 0x77, 0x28, 0xa8, 0xf7, 0x16, 0x49, 0x5f, 0x00,
	0xe1, 0xbe, 0x3e, 0x61, 0x80, 0xdf, 0x9d, 0xc2, 0x23, 0x7c, 0xfc, 0xa3, 0x42,
	0x1d, 0xc6, 0x99, 0x78, 0x27, 0xa7, 0xf8, 0x19, 0x46, 0x04, 0x5b, 0xba, 0xe5,
	0x65, 0x3a, 0xdb, 0x84, 0x70, 0x2f, 0xce, 0x91, 0x11, 0x4e, 0xaf, 0xf0, 0xb2,
	0xed, 0x0c, 0x53, 0xd3, 0x8c, 0x6d, 0x32, 0xe9, 0xb6, 0x57, 0x08, 0x88, 0xd7,
	0x36, 0x69, 0x2b, 0x74, 0x95, 0xca, 0x4a, 0x15, 0xf4, 0xab, 0x01, 0x5e, 0xbf,
	0xe0, 0x60, 0x3f, 0xde, 0x81, 0xc3, 0x9c, 0x7d, 0x22, 0xa2, 0xfd, 0x1c, 0x43,
	0x98, 0xc7, 0x26, 0x79, 0xf9, 0xa6, 0x47, 0x18, 0x5a, 0x05, 0xe4, 0xbb, 0x3b,
	0x64, 0x85, 0xda, 0x2e, 0x71, 0x90, 0xcf, 0x4f, 0x10, 0xf1, 0xae, 0xec, 0xb3,
	0x52, 0x0d, 0x8d, 0xd2, 0x33, 0x6c, 0xb7, 0xe8, 0x09, 0x56, 0xd6, 0x89, 0x68,
	0x37, 0x75, 0x2a, 0xcb, 0x94, 0x14, 0x4b, 0xaa, 0xf5}
};

unsigned crc8sae_j1850_byte(unsigned crc, void const *mem, size_t len) {
	unsigned char const *data = (unsigned char const *)mem;
	if (data == NULL)
		return 0;
	crc &= 0xff;
	while (len--)
		crc = table_byte[crc ^ *data++];
	return crc;
}

// This code assumes that integers are stored little-endian.

unsigned crc8sae_j1850_word(unsigned crc, void const *mem, size_t len) {
	unsigned char const *data = (unsigned char const *)mem;
	if (data == NULL)
		return 0;
	crc &= 0xff;
	while (len && ((ptrdiff_t)data & 0x7)) {
		crc = table_byte[crc ^ *data++];
		len--;
	}
	if (len >= 8) {
		do {
			uintmax_t word = crc ^ *(uintmax_t const *)data;
			crc = table_word[7][word & 0xff] ^
				table_word[6][(word >> 8) & 0xff] ^
				table_word[5][(word >> 16) & 0xff] ^
				table_word[4][(word >> 24) & 0xff] ^
				table_word[3][(word >> 32) & 0xff] ^
				table_word[2][(word >> 40) & 0xff] ^
				table_word[1][(word >> 48) & 0xff] ^
				table_word[0][word >> 56];
			data += 8;
			len -= 8;
		} while (len >= 8);
	}
	while (len--)
		crc = table_byte[crc ^ *data++];
	return crc;
}