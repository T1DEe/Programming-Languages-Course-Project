#include "pch.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	Log::LOG log = Log::INITLOG;
	try
	{
		setlocale(0, "");
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::GetLog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);

		In::IN in = In::GetIn(parm.in);
		Log::WriteIn(log, in);

		log = Log::GetLog(parm.lex);
		Lex::LEX lex = Lex::Lexer(in, log);

		log = Log::GetLog(parm.syn);
		MFST_TRACE_START(log)
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(log);
		mfst.printRules(log);

		CallPolishNotation(&lex.lextable, &lex.idtable);
		LT::Write(log, lex.lextable);
		IT::WriteTable(log, lex.idtable);

		log = Log::GetLog(parm.out);
		Generation::Generation(lex, log);
		Log::Close(log);

	}
	catch (Error::ERROR exception)
	{
		Log::WriteError(log, exception);
		cout << endl;
	}
	catch (...)
	{
		cout << "Ошибка: сбой системы" << endl;
	}

	return 0;
};