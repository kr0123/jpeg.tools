#ifndef _CHARTOOLS_H_
#define _CHARTOOLS_H_


class CCharTools
{
public:
	int		Char2Hex(char a, int *x);
	int		Char2Dec(char a, int *x);

	char	CharUpCase(char a);
	int		IsDigital(char a);
	int		IsAlpha(char a);
	int		IsOpcode(char a);
	int		IsBlank(char a);
};


#endif
