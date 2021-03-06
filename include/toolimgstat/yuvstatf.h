#ifndef __TOOLIMGSTAT_YUVSTATF_H__
#define __TOOLIMGSTAT_YUVSTATF_H__


#include "yuvstat.h"

class CYuvStatF : public CYuvStat
{
public:
	CYuvStatF(void);
	virtual ~CYuvStatF(void);

public:
	void printYuvfmtMsg(int * des, char * src,int srcfmt, int width, int height, int unit);
    
protected:	
	//void Yuv411Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	//void Yuv420Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	void Yuv422Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	//void Yuv444Msg(int * des, char * src, int srcfmt, int width, int height, int unit);
	void updateYuv(int * des, int * ndes);
	
};


#endif
