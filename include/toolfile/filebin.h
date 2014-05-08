
#ifndef _FILEBIN_H_
#define _FILEBIN_H_


#include "filebase.h"
#include "toolbuf/bufferbase.h"

class CFileBin : public CFileBase, public CBufferBase
{
public:
	CFileBin(char *filename = NULL, char *rwmode = "rb", int size = BUFFER_DEFAULT_SIZE);
	virtual ~CFileBin();

public:
	virtual int Read(char *buf, int len);
	virtual int Write(char *buf, int len);
	void Open(char *filename = NULL, char *rwmode = "rb", int size = BUFFER_DEFAULT_SIZE);
	virtual void Close(void);

public:
	void Fseek(long pos, int start);

private:
	void ClearPoint(void);

private:
	int m_wpoint;
	int m_rpoint;
};


#endif
