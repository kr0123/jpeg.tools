#ifndef __TOOLIMGSTAT_RGBSTATF_H__
#define __TOOLIMGSTAT_RGBSTATF_H__


#include "RGBStat.h"

class CRgbStatF : public CRgbStat
{
public:
	CRgbStatF(void);
	virtual ~CRgbStatF(void);

public:
	//void printRgbfmtMsg(int * des, char * src,int srcfmt, int width, int height, int unit);
    
protected:
	/*
	void Rgb24Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	void Rgb32Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	void Rgb555Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	void Rgb565Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	void updateRgb(int * des, int * ndes);
	*/
};


#endif
