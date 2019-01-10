#pragma once
#include "pch.h"
#include "Parameters.h"
#include <fstream>


namespace Log		//Работа с протоколом
{
	struct LOG		//Протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];		// имя файла протокола
		ofstream* stream;					// выходной поток
	};

	static const LOG INITLOG = { L"", NULL };		//Структура для начальной инициализации LOG
	LOG  GetLog(wchar_t logfile[]);					//Сформировать структуру LOG
	void WriteLine(LOG log, char* c, ...);			//Вывести в протокол конкатенацию строк
	void WriteLine(LOG log, wchar_t* c, ...);		//Вывести в протокол конкатенацию строк
	void WriteLog(LOG log);							//Вывести в протокол заголовок
	void WriteParm(LOG log, Parm::PARM parm);		//Вывести в протокол информацию о входных параметрах
	void WriteIn(LOG log, In::IN in);				//Вывести в протокол информациб о входном потоке
	void WriteError(LOG log, Error::ERROR error);	//Вывести в прокол информацию об ошибке
	void Close(LOG log);							//Закрыть протокол
}