#ifndef _BASEITEM_H_
#define _BASEITEM_H_


#include "global.h"

typedef void ChannelCallBack(void);

class CBaseItem
{
public:
	CBaseItem();
	virtual ~CBaseItem();

public:
	virtual int		Read(char *buf, int len);
	virtual int		Write(char *buf, int len);
};

class CBaseObject : public CBaseItem
{
public:
	CBaseObject();
	virtual ~CBaseObject();

public:
	virtual void	Close(void);
	virtual void	Open(void);
	virtual int		IsOpened(void);
};

enum CHNLRWMODEenum {
	CALLBACK_MODE,
	WAITING_MODE,
};

class CBaseChannel : public CBaseObject
{
public:
	CBaseChannel();
	virtual ~CBaseChannel();

public:
	void	SetCallBack(ChannelCallBack *pcall);
	void	SetRWmode(int mode = CALLBACK_MODE);
	int		GetRWmode(void);

protected:
	volatile int	m_rwMode;
	ChannelCallBack *m_pcall;
};


#endif
