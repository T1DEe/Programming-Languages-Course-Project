#pragma once
#include "Log.h"
#define LT_NOPRIORITY 0xffffffff		// нет приоритета
#define LEXEMA_FIXZISE 1				// фиксированный размер лексемы
#define LT_MAXSIZE 4096					// максимальное кол-во строк в таблице лексем   
#define TL_TI_NULLIDX 0xffffffff		// нет элемента таблицы идентификаторов
#define LEX_T			't'				//	
#define LEX_NUM			'x'				//	digital
#define LEX_ROW			'y'				//	string
#define LEX_TAB			'v'				//	var
#define LEX_FUNC		'f'				//	function
#define LEX_MAIN		'm'				//	start
#define LEX_RET			'r'				//	ret
#define LEX_LITERAL		'l'				//	литерал
#define LEX_OUTPUT		'o'				//	show
#define LEX_POW			'p'				//	pow
#define LEX_LENGTH		'n'				//	strlen
#define LEX_ID			'i'				//	идентификатор
#define LEX_ACTION		'a'
#define LEX_SEMICOLON	';'				//	;
#define LEX_COLON		':'				//	:
#define LEX_COMMA		','				//	,
#define LEX_LEFTHESIS	'('				//	(
#define LEX_RIGHTHESIS	')'				//	)
#define LEX_EQUAL		'='				//  =
#define LEX_LEFTBRACE	'{'				//	{
#define LEX_RIGHTBRACE	'}'				//	}
#define LEX_PLUS		'+'				//	+
#define LEX_MINUS		'-'				//	-
#define LEX_MULTIPLY	'*'				//	*
#define LEX_STRLIT		'"'				//  "
#define LEX_SUBST		'@'
#define LEX_L			'L'				//  L
#define LEX_SEP			'|'				// символ конца строки

namespace LT													//“аблица лексем
{					
	struct Entry
	{
		char lexem;				// лексема
		int lineNo;				// номер строки в исходном коде
		int indexTI;			// индекс в таблице идентификаторов 
		short priority;			// приоритет дл€ операций
	};

	struct LexTable
	{
		int maxize;				// емкость таблицы лексем 
		int size;				// текущий размер таблицы лексем
		Entry* table;			// массив строк табилцы лексем	
	};

	LexTable Create(int size);
	Entry GetEntry(LexTable& lextable, int n);
	Entry Add(LexTable& lextable, Entry entry);
	void ShowTable(LexTable& lexTable);
	void Write(Log::LOG log, LexTable& lexTable);
}