#ifndef _FILTER_4X4_H_
#define _FILTER_4X4_H_


#include "filter4x4base.h"

class CFilter444 : public CFilter4X4Base<CLine444Buf>
{
public:
	CFilter444(int width = 128, int unit = 1);
	virtual ~CFilter444();
};

class CFilterRgb : public CFilter4X4Base<CLine444Buf>
{
public:
	CFilterRgb(int width = 128, int unit = 1);
	virtual ~CFilterRgb();
};

class CFilter411 : public CFilter4X4Base<CLine411Buf>
{
public:
	CFilter411(int width = 128, int unit = 1);
	virtual ~CFilter411();

public:
	void	SetFormat(int format);
};

class CFilter422 : public CFilter4X4Base<CLine422Buf>
{
public:
	CFilter422(int width = 128, int unit = 1);
	virtual ~CFilter422();

public:
	void	SetFormat(int format);
};


#endif
