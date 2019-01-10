#pragma once
#include "pch.h"
#include "IT.h"
#include "LT.h"

#define FUNC_MAX_SIZE 5

namespace Lex
{
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable idtable;
	};
	LEX Lexer(In::IN, Log::LOG log);
}
