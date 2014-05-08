#ifndef _RGB24_CONVERT_H_
#define _RGB24_CONVERT_H_


#include "raw2rgb.h"
#include "yuv400.h"
#include "yuv411.h"
#include "yuv422.h"
#include "yuv420.h"

class CRgb24Convert : protected CRaw2Rgb, protected CYuv400, 
						protected CYuv411, protected CYuv422, protected CYuv420
{
public:
	int Rgb24_Img(char *src, char *dest, int width, int height, int fmt);
	int Img2Rgb24(char *src, char *dest, int width, int height, int fmt);
};


#endif
