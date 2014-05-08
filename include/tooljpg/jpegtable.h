#ifndef _TOOLS_JPEGTABLE_H_
#define _TOOLS_JPEGTABLE_H_


#include "tools/global.h"


typedef struct tag_THuffValue
{
	int		value;
	int		length;
} THuffValue, *PTHuffValue;


extern const UINT8 gJpegDefaultLumTbl[];
extern const UINT8 gDefaultLumTbl[];
extern const UINT8 gJpegDefaultChrTbl[];
extern const UINT8 gDefaultChrTbl[];
extern const UINT8 gZigZag[];
extern const unsigned char gAlterZigZag[2][64];
extern const UINT8 gDefaultHuffmanTbl[];
extern const UINT8 gJpegDefaultImgpara[]; 
extern const int gDctMatrix[];
extern const int gInvTable[];

extern const int gDefHuffTblSize;
extern const int gJpegImgparaSize;


#endif
