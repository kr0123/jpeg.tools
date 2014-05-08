
#ifndef _FILEINPUT_H_
#define _FILEINPUT_H_


#include "filebin.h"

class CFileInput : public CFileBin
{
public:
	CFileInput(char *filename = NULL, int size = BUFFER_DEFAULT_SIZE);

public:
	void	Open(char *df);
	void	Open(char *path, char *df);
};


#endif
