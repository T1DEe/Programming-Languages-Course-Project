#include "pch.h"

int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];

//-------------------------------------------------------------------------
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
#define MFST_TRACE1(log)	*(log.stream)<<setw(4)<<left<<++FST_TRACE_n << ": "\
							<<setw(20)<<left<<rule.getCRule(rbuf, rulechainNo)\
							<<setw(30)<<left<<getCLenta(lbuf, lenta_position)\
							<<setw(20)<<left<<getContainStack(sbuf)<<endl;

#define MFST_TRACE2(log)	*(log.stream)<<setw(4)<<left<< FST_TRACE_n << ": "\
							<<setw(20)<<left<<" "\
							<<setw(30)<<left<<getCLenta(lbuf, lenta_position)\
							<<setw(20)<<left<<getContainStack(sbuf)<<endl;

#define MFST_TRACE3(log)	*(log.stream)<<setw(4)<<left<< ++FST_TRACE_n << ": "\
							<<setw(20)<<left<<" "\
							<<setw(30)<<left<<getCLenta(lbuf, lenta_position)\
							<<setw(20)<<left<<getContainStack(sbuf)<<endl;

#define MFST_TRACE4(c, log)   *(log.stream)<<setw(4)<<left<< ++FST_TRACE_n<<": "<<setw(20)<<left<<c<<endl;
#define MFST_TRACE5(c, log)   *(log.stream)<<setw(4)<<left<< FST_TRACE_n<<": "<<setw(20)<<left<<c<<endl;
#define MFST_TRACE6(c,k, log) *(log.stream)<<setw(4)<<left<< FST_TRACE_n<<": "<<setw(20)<<left<<c<<k<<endl;
#define MFST_TRACE7(log)	  *(log.stream)<<setw(4)<<left<< state.lenta_position<<": " \
							  <<setw(20)<<left<<rule.getCRule(rbuf,state.rulechainNo)<<endl;
//-------------------------------------------------------------------------

namespace MFST
{
	MfstState::MfstState()
	{
		lenta_position = 0;
		rulechainNo = -1;
		ruleNo = -1;
	}
	
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)			  
	{				  //(позиция на ленте, стек автомата, номер текущей цепочки и текущего правила)
		lenta_position = pposition;
		stack = pst;
		rulechainNo = pnrulechain;
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain) 				  
	{				  //(позиция на ленте, стек автомата,номер текущего правила, номер текущей цепочки)
		lenta_position = pposition;		// позиция на ленте
		stack = pst;					// стек автомата
		ruleNo = pnrule;
		rulechainNo = pnrulechain;		// номер текущего правила и цепочки
	}

	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		ruleNo = -1;
		rule_chainNo = -1;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)		// Диагностика
	{								//(позиция на ленте, код завершения шага, номер правила, номер цепочки правила)
		lenta_position = plenta_position;		// позиция на ленте
		rc_step = prc_step;					    // код завершения шага
		ruleNo = pnrule;						// номер правила
		rule_chainNo = pnrule_chain;			// номер цепочки правила
	}

	Mfst::Mfst()
	{
		lenta = 0;
		lenta_position = 0;
		lenta_size = 0;
	}

	Mfst::Mfst(Lex::LEX plex, GRB::Greibach pgreibach)		
	{
		greibach = pgreibach;			// результат работы лексического анализатора, грамматика Грейбах
		lex = plex;
		lenta = new short[lenta_size = lex.lextable.size];
		
		for (int k = 0; k < lenta_size; k++)				// заносит в ленту терминалы
		{
			lenta[k] = TS(lex.lextable.table[k].lexem);
		}
		
		lenta_position = 0;
		stack.push(greibach.stbottomT);		// добавляет дно стека
		stack.push(greibach.startN);		// добавляет стартовый символ
		rulechainNo = -1;					// изначально правило равно -1
	}

	Mfst::RC_STEP Mfst::step(Log::LOG log) //выполнить шаг автомата
	{
		RC_STEP rc = SURPRISE;
		if (lenta_position < lenta_size)
		{
			if (ISNS(stack.top()))		// если в вершине стека содерж нетерм
			{
				GRB::Rule rule;
				if ((ruleNo = greibach.getRule(stack.top(), rule)) >= 0)	 // ищем правило по нетерминалу
				{
					GRB::Rule::Chain chain;
					if ((rulechainNo = rule.getNextChain(lenta[lenta_position], chain, rulechainNo + 1)) >= 0) //получаем следующую цепочку и выводим её номер, илбо возвращаем -1
					{
						MFST_TRACE1(log)		// вывод
						saveState(log);			// сохранить состояние автомата
						stack.pop();		    // извлекаем верхушку стека.
						push_chain(chain);		// поместить цепочку правила в стек
						rc = NS_OK;				// найдено правило и цепочка... цепочка записана в стек
						MFST_TRACE2(log)		// вывод
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE", log)		// вывод
							saveDiagnosis(NS_NORULECHAIN);					// код завершения
						rc = restState(log) ? NS_NORULECHAIN : NS_NORULE;	// восстановить состояние автомата
					}
				}
				else
					rc = NS_ERROR;		// если не подобрали никакое правило для текущ нетерминала
			}
			else if ((stack.top() == lenta[lenta_position]))		// если текущий символ ленты равен вершине стека
			{
				lenta_position++;		// продвигаем ленту
				stack.pop();			// вершина стека
				rulechainNo = -1;		// номер текущего правила равен -1
				rc = TS_OK;
				MFST_TRACE3(log)
			}
			else		// пытаемся восстановить предыдущее сост и подобрать для него другую цепочку
			{
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN", log)
					rc = restState(log) ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			if (stack.top() == greibach.stbottomT)		// если символ в стеке и символ дна стека их грамматики грейбах совпадают
			{
				rc = LENTA_END;
				MFST_TRACE4("--------------LENTA_END", log)
			}
			else
				throw ERROR_THROW(215);
		}
		return rc;
	}

	bool Mfst::push_chain(GRB::Rule::Chain chain)		//поместить цепочку правила в стек в обратном порядке!!! (цепочка правила)
	{
		
		for (int k = chain.chainLenght - 1; k >= 0; k--)//к = длинне цепочке-1. заносим цепочку в стек
		{
			stack.push(chain.nt[k]);
		}
		return true;
	}

	bool Mfst::saveState(Log::LOG log)		//Сохранить состояние автомата
	{
		storestate.push(MfstState(lenta_position, stack, ruleNo, rulechainNo));		// стек для сохранения состояния. заносим сохраняемое состояние
		MFST_TRACE6("SAVESTATE: ", storestate.size(), log)
		
		return true;
	}

	bool Mfst::restState(Log::LOG log)		//Восстановить состояние автомата
	{
		bool rc = false;
		MfstState state;		//стек состояний
		if (rc = (storestate.size() > 0))		// если размер стека сост больше 0
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			stack = state.stack;
			ruleNo = state.ruleNo;
			rulechainNo = state.rulechainNo;
			storestate.pop();
			MFST_TRACE5("RESTATE", log)
			MFST_TRACE2(log)
		}
		return rc;
	}

	bool Mfst::saveDiagnosis(RC_STEP pprc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position)
		{
			k++;
		}
		if (rc = (k < MFST_DIAGN_NUMBER)) 
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, pprc_step, ruleNo, rulechainNo);
			
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++)
			{
				diagnosis[j].lenta_position = -1;
			}
		}
		return rc;
	}

	bool Mfst::start(Log::LOG log)		//Начало работы автомата
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(log);
		
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
		{
			rc_step = step(log);
		}
		
		switch (rc_step)
		{
			case LENTA_END:
			{
				MFST_TRACE4("----------------------------->LENTA_END", log)
				*(log.stream) << "---------------------------------------------------------------------------------------\n";
				sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
				*(log.stream) << setw(4) << left << 0 << ": всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок\n";
				rc = true;
				break;
			}
			case NS_NORULE:
			{	
				*(log.stream) << "NS_NORULE";
				*(log.stream) << getDiagnosis(0, buf) << endl;
				*(log.stream) << getDiagnosis(1, buf) << endl;
				*(log.stream) << getDiagnosis(2, buf) << endl;
				break;
			}
			case NS_NORULECHAIN:	
			{
				MFST_TRACE4("---------->NS_NORULECHAIN", log)
				break;
			}
			case NS_ERROR:
			{
				MFST_TRACE4("---------->NS_ERROR", log) 
				break;
			}
			case SURPRISE:
			{
				MFST_TRACE4("---------->SURPRISE", log) break;
			}
		}
		return rc;
	}

	char* Mfst::getContainStack(char* buf)		//Получаем содержимое стека
	{
		for (int k = (signed)stack.size() - 1; k >= 0; k--)
		{
			short p = stack._Get_container()[k];
			buf[stack.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);		// в символьный массив записываем содержимое стека
		}
		buf[stack.size()] = 0x00;
		return buf;
	}

	char* Mfst::getCLenta(char* buf, short pos, short n)			//Получаем содержимое входной ленты
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)
		{
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);		// в символьный массив записываем содержим ленты
		}
		buf[i - pos] = 0x00;
		return buf;
	}

	char* Mfst::getDiagnosis(short n, char* buf)
	{
		char *rc = (char*)"";
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = greibach.getRule(diagnosis[n].ruleNo).idDiagnosticError;
			Error::ERROR err = ERROR_THROW_IN(errid, lex.lextable.table[lpos].lineNo, -1);
			throw ERROR_THROW_IN(errid, lex.lextable.table[lpos].lineNo, -1);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lex.lextable.table[lpos].lineNo, err.message);
			rc = buf;
		}
		return rc;
	}

	void Mfst::printRules(Log::LOG &log)		//Выводим дерево разбора
	{
		MfstState state;
		GRB::Rule rule;

		*(log.stream) << endl << "Дерево разбора :" << endl;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			rule = greibach.getRule(state.ruleNo);
			MFST_TRACE7(log)
		}
	}
}