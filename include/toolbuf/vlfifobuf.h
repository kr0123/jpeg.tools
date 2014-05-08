#ifndef _VARLEN_FIFO_BUFFER_H_
#define _VARLEN_FIFO_BUFFER_H_


#include "ufifobuf.h"

class CVLfifoBuf : public CUfifoBuf
{
public:
	CVLfifoBuf(int size = BUFFER_DEFAULT_SIZE, int unit = 1);
	virtual ~CVLfifoBuf();

public:
	void	Write(int val);
	int		Read();
};


#endif
