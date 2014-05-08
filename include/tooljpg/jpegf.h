
#ifndef _TOOLS_JPEGF_H_
#define _TOOLS_JPEGF_H_


#include "toolfile/dbugtools.h"
#include "jpeg.h"

enum {
	JPEGF_SUCCEED,
	JPEGF_FAILED
};

#define JPEGF_LIST		"jpgimg.lst"

class CJpegF : public CJpeg
{
public:
	int		CheckJpegList(char *list = JPEGF_LIST);
	void	SplitJpeg(char *srcf, char *list = JPEGF_LIST, char *dstf = NULL);
	void	JpegParse(char *filename, PTJpegIndex pinfo);

public:
	void	Jpeg2Blk(char *src, char *dest);

private:
	CDbugTools	m_dbug;
};


#endif
