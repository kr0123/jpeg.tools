#ifndef _LINEFIFO_BUFFER_H_
#define _LINEFIFO_BUFFER_H_


#include "ufifobuf.h"

class CLineFifo : public CUfifoBuf
{
public:
	CLineFifo(int width = BUFFER_DEFAULT_SIZE, int unit = 1);
	virtual ~CLineFifo();

public:
	virtual int		Write(char *buf, int size);
	virtual int		Read(char *buf, int width);

public:
	void	SetSize(int width = BUFFER_DEFAULT_SIZE, int unit = 1);
	void	SetSize(char *buf, int width = BUFFER_DEFAULT_SIZE, int unit = 1);

public:
	int		Write(int val);
	int		Read(void);

public:
	int		IsFifoValid(void);

private:
	int		m_width;
	int		m_linewidth;
};


#endif
