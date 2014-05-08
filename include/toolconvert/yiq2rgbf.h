#ifndef _YIQ2RGBF_H_
#define _YIQ2RGBF_H_


#include "yiq2rgb.h"
#include "toolfile/dbugtools.h"

class CYiq2rgbF : public CYiq2rgb
{
public:
	CYiq2rgbF();
	virtual ~CYiq2rgbF();

public:
	virtual void yiq2rgb(char *src, char *dst, int width, int height, int unit = 1);

private:
	CDbugTools	m_dbug;
};


#endif
