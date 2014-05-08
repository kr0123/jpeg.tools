#ifndef _RGB2YIQF_H_
#define _RGB2YIQF_H_


#include "rgb2yiq.h"

class CRgb2yiqF : public CRgb2yiq
{
public:
	CRgb2yiqF();
	virtual ~CRgb2yiqF();

public:
	virtual void rgb2yiq(char *src, char *dst, int width, int height, int unit = 1);

private:
	CDbugTools	m_dbug;
};


#endif
