#include "pch.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		bool isIn = false,
			 isOut = false,
			 isLog = false,
			 isLex = false,
			 isSyn = false;
		PARM parm;
		wchar_t *buf;

		for (int i = 1; i < argc; i++) 
		{
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)
				throw ERROR_THROW(104);

			if (buf = wcsstr(argv[i], PARM_IN))
			{
				wcscpy_s(parm.in, buf + wcslen(PARM_IN));
				isIn = true;
			}

			if (buf = wcsstr(argv[i], PARM_OUT))
			{
				wcscpy_s(parm.out, buf + wcslen(PARM_OUT));
				isOut = true;
			}

			if (buf = wcsstr(argv[i], PARM_LOG))
			{
				wcscpy_s(parm.log, buf + wcslen(PARM_LOG));
				isLog = true;
			}

			if (buf = wcsstr(argv[i], PARM_LEX))
			{
				wcscpy_s(parm.lex, buf + wcslen(PARM_LEX));
				isLex = true;
			}

			if (buf = wcsstr(argv[i], PARM_SYN))
			{
				wcscpy_s(parm.syn, buf + wcslen(PARM_SYN));
				isSyn = true;
			}
		}

		if (!isIn)
			throw ERROR_THROW(100);

		if (!isOut) 
		{
			wcscpy_s(parm.out, parm.in);
			wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
		}
		if (!isLog)
		{
			wcscpy_s(parm.log, parm.in);
			wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		if (!isLex)
		{
			wcscpy_s(parm.lex, parm.in);
			wcsncat_s(parm.lex, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));	//PARM_LEX_DEFAULT_EXT
		}
		if (!isSyn)
		{
			wcscpy_s(parm.syn, parm.in);
			wcsncat_s(parm.syn, PARM_SYN_DEFAULT_EXT, wcslen(PARM_SYN_DEFAULT_EXT));
		}
		
		return parm;
	}
};