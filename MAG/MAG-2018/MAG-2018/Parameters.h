#pragma once
#include <tchar.h>
#define PARM_MAX_SIZE 300			
#define PARM_IN  L"-in:"					// ключ для файла исходного кода
#define PARM_OUT L"-out:"					// ключ для файла объектного кода	
#define PARM_LOG L"-log:"					// ключ для файла журнала 
#define PARM_LEX  L"-lex:"
#define PARM_SYN  L"-syn:"
#define PARM_OUT_DEFAULT_EXT L".asm"		// расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"		// расширение файла протокола по умолчанию
#define PARM_LEX_DEFAULT_EXT  L".lex"
#define PARM_SYN_DEFAULT_EXT  L".syn"

namespace Parm
{
	struct PARM
	{
		wchar_t  in[PARM_MAX_SIZE];			// -in:     имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];			// -out:    имя файла объектного кода
		wchar_t log[PARM_MAX_SIZE];			// -log:    имя файла протокола
		wchar_t lex[PARM_MAX_SIZE];
		wchar_t syn[PARM_MAX_SIZE];
	};
	PARM getparm(int argc, _TCHAR* argv[]);		//Сформировать struct PARM на основе входных параметров функции main
}