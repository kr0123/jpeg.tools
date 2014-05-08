#ifndef _LINE411_BUFFER_H_
#define _LINE411_BUFFER_H_


#include "toolbuf/linebuf.h"

class CLine411Buf : public CLineBuf
{
public:
	CLine411Buf(int width = DEFAULT_LINEBUF_WIDTH, int edge = 4, int unit = 1);
	virtual ~CLine411Buf();

public:
	virtual int		Write(char *buf, int size);
	virtual void	Read(int pos, int *yuv);

public:
	virtual void operator = (CLine411Buf &a);

public:
	void	SetSize(int width = DEFAULT_LINEBUF_WIDTH, int edge = 4, int unit = 1);
	void	SetSize(char *buf, int width = DEFAULT_LINEBUF_WIDTH, int edge = 4, int unit = 1);
	void	SetFormat(int format);
	
private:
	int		m_format;
};


#endif
