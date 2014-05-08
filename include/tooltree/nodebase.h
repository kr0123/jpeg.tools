#ifndef _NODEBASE_H_
#define _NODEBASE_H_


enum KEYNODEPROPenum
{
	LEAF_NODE,
	NODE_NODE
};

class CNodeBase
{
public:
	CNodeBase(void);
	virtual ~CNodeBase(void);

public:
	int  GetNodeProp(void);
	void SetNodeProp(int sel);

private:
	int m_prop;
};


#endif
