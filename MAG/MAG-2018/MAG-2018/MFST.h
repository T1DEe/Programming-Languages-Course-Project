#pragma once
#include "pch.h"
#include <stack>

#define MFST_DIAGN_MAXSIZE	2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
#define MFST_TRACE_START(log) *(log.stream)<<endl<< setfill(' ') << setw( 4)<<left<<"Шаг"<<":"<<\
									setw(20)<<left<<"Правило"<<\
									setw(30)<<left<<"Входная лента"<<\
									setw(20)<<left<<"Стек"<<endl;


typedef stack<short> MFSTSTSTACK;	//Стек автомата

namespace MFST											//Магазинный автомат
{                  
	struct MfstState		//Состояние автомата (для сохранения)
	{
		short lenta_position;		// позиция на ленте
		short ruleNo;				// номер текущего правила
		short rulechainNo;			// номер текущей цепочки текущего правила
		MFSTSTSTACK stack;			// стек автомата
		
		MfstState();
		
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		
		MfstState(
			short pposition,       // позиция на ленте
			MFSTSTSTACK pst,       // стек автомата
			short pnrule,          // номер текущего правила
			short pnrulechain      // номер текущей цепочки
		);
	};
	struct Mfst			//Магазинный автомат
	{
		enum RC_STEP {		//Код возврата функции step
			NS_OK,					// найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,				// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,			// не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,				// неизвестный нетерминальный символ грамматики
			TS_OK,					// тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,					// тек. символ ленты != вершине стека, восстановлено состояние 
			LENTA_END,				// текущая позиция ленты >= lenta_size
			SURPRISE				// неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis	//Диагностика
		{
			short lenta_position;			// позиция на ленте
			RC_STEP rc_step;				// код завершения шага
			short ruleNo;					// номер правила
			short rule_chainNo;				// номер цепочки правила
			
			MfstDiagnosis();
			
			MfstDiagnosis(
				short plenta_position,	// позиция на ленте
				RC_STEP prc_step,		// код завершения шага
				short pnrule,			// номер правила 
				short pnrule_chain		// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// последние самые глубокие сообщения
		GRBALPHABET* lenta;					// перекодированная (TS/NS) лента (из LEX)
		short lenta_position;				// текущая позиция на ленте
		short ruleNo;						// номер текущего правила
		short rulechainNo;					// номер текущей цепочки текущего правила
		short lenta_size;					// размер ленты
		GRB::Greibach greibach;				// грамматика Грейбах
		Lex::LEX lex;						// результат работы лексического анализатора
		MFSTSTSTACK stack;					// стек автомата
		std::stack<MfstState> storestate;	// стек для сохранения состояний
		
		Mfst();
		Mfst(
			Lex::LEX plex,				// результат работы лексического анализатора
			GRB::Greibach pgrebach		// грамматика Грейбах
		);

		char* getContainStack(char* buf);						//Получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);	//Лента: n символов с pos
		char* getDiagnosis(short n, char* buf);					//Получить n-ую строку диагностики или 0х00
		bool saveState(Log::LOG log);							//Сохранить состояние автомата
		bool restState(Log::LOG log);							//Восстановить состояние автомата
		bool push_chain(										//Поместить цепочку правила в стек
			GRB::Rule::Chain chain		// цепочка правил
		);
		Mfst::RC_STEP step(Log::LOG log);		//Выполнить шаг автомата
		bool start(Log::LOG log);				//Запустить автомат
		bool saveDiagnosis(
			RC_STEP pprc_step			// код завершения шага
		);
		void printRules(Log::LOG &log);			//Вывести последовательность правил (дерево разбора)

	
	};
}