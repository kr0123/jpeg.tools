#ifndef _TYPEPROP_H_
#define _TYPEPROP_H_


#include "global.h"


class CTypeProp
{
public:
	int		getVwc(int width, int height, int format, int unit = 1);
	int		getLinewidth(int width, int format, int unit = 1);
	char * GetFormatDesc(int fmt);

};


#endif
