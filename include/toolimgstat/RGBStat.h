#ifndef __TOOLIMGSTAT_RGBSTAT_H__
#define __TOOLIMGSTAT_RGBSTAT_H__


#include "toolmath/baseconvert.h"
#include "toolfile/dbugtools.h"

class CRgbStat : public CBaseConvert
{
public:
	CRgbStat(void);
	virtual ~CRgbStat(void);

protected:
	/*
	void Rgb565Msg(int * des, char * src, int srcfmt, int unit);
	void Rgb24Msg(int * des, char * src, int srcfmt, int unit);
	void Rgb32Msg(int * des, char * src, int srcfmt, int unit);
	*/

public:
	CDbugTools m_dbug;

protected:
	int m_nCountR;
	int m_nCountG;
	int m_nCountB;
};


#endif
