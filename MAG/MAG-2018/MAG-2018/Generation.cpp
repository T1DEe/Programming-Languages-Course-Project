#include "pch.h"
#include <stack>

namespace Generation
{
	void Generation(Lex::LEX lex, Log::LOG log)
	{
		*(log.stream) << ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\t	includelib ../Debug/Lib.lib\n\tExitProcess PROTO :DWORD\n\n";
		*(log.stream) << "\toutputn PROTO: DWORD\n\toutputr PROTO: DWORD\n\tlen PROTO: DWORD\n\tpows PROTO: DWORD, :DWORD\n";
		*(log.stream) << "\n.stack 4096\n";

		*(log.stream) << ".const\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::IDTYPE_LIT)
			{
				*(log.stream) << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::IDDATATYPE_ROW)
				{
					*(log.stream) << " BYTE " << lex.idtable.table[i].value.rowValue.str << ", 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::IDDATATYPE_NUM)
				{
					*(log.stream) << " DWORD " << lex.idtable.table[i].value.numValue << endl;
				}
			}
		}

		*(log.stream) << ".data\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexem == LEX_TAB)
			{
				*(log.stream) << "\t" << lex.idtable.table[lex.lextable.table[i + 2].indexTI].id;
				*(log.stream) << " DWORD ?\n";
				i += 3;
			}
		}

		stack<string> stk;				// стек для правильной последовательности передачи параметров в функцию ассемблера
		string func_name = "";			// имя локальной функции
		bool isInfuncion = false;		// внутри локальной функции	
		bool isMain = false;			// внутри главной функции


		*(log.stream) << "\n.code\n\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexem)
			{
				case LEX_FUNC:
				{
					*(log.stream) << (func_name = lex.idtable.table[lex.lextable.table[++i].indexTI].id) << " PROC ";
					while (lex.lextable.table[i].lexem != LEX_RIGHTHESIS)
					{
						if (lex.idtable.table[lex.lextable.table[i].indexTI].idType == IT::IDTYPE_PAR)
						{
							*(log.stream) << lex.idtable.table[lex.lextable.table[i].indexTI].id << " : ";
							if (lex.idtable.table[lex.lextable.table[i].indexTI].idDataType == IT::IDDATATYPE_NUM)
							{
								*(log.stream) << "SDWORD";
							}
							else
							{
								*(log.stream) << "DWORD";
							}
						}
						if (lex.lextable.table[i].lexem == LEX_COMMA)
							*(log.stream) << ", ";

						i++;
					}
					isInfuncion = true;
					*(log.stream) << endl;
					
					break;
				}
				case LEX_MAIN:
				{
					isMain = true;
					*(log.stream) << "main PROC\n";
					break;
				}
				case LEX_EQUAL:
				{
					int result_position = i - 1;
					while (lex.lextable.table[i].lexem != LEX_SEMICOLON)
					{
						switch (lex.lextable.table[i].lexem)
						{
							case LEX_ID:
							case LEX_NUM:
							{
								*(log.stream) << "\tpush " << lex.idtable.table[lex.lextable.table[i].indexTI].id << endl;
								stk.push(lex.idtable.table[lex.lextable.table[i].indexTI].id);
								break;
							}
							case LEX_ROW:
							{
								*(log.stream) << "\tpush offset " << lex.idtable.table[lex.lextable.table[i].indexTI].id << endl;
								stk.push("offset " + lex.idtable.table[lex.lextable.table[i].indexTI].id);
								break;
							}
							case LEX_SUBST:
							{
								for (int j = 1; j <= lex.lextable.table[i].priority; j++)
								{
									*(log.stream) << "\tpop edx\n";
								}
								for (int j = 1; j <= lex.lextable.table[i].priority; j++)
								{
									*(log.stream) << "\tpush " << stk.top() << endl;
									stk.pop();
								}
								*(log.stream) << "\t\tcall " << lex.idtable.table[lex.lextable.table[i].indexTI].id << "\n\tpush eax\n";
								break;
							}
							case LEX_ACTION:
							{
								switch (lex.idtable.table[lex.lextable.table[i].indexTI].id[0])
								{
									case LEX_MULTIPLY:
									{
										*(log.stream) << "\tpop eax\n\tpop ebx\n";
										*(log.stream) << "\tmul ebx\n\tpush eax\n";
										break;
									}
									case LEX_PLUS:
									{
										*(log.stream) << "\tpop eax\n\tpop ebx\n";
										*(log.stream) << "\tadd eax, ebx\n\tpush eax\n";
										break;
									}
									case LEX_MINUS:
									{
										*(log.stream) << "\tpop ebx\n\tpop eax\n";
										*(log.stream) << "\tsub eax, ebx\n\tpush eax\n";
										break;
									}
								}
								break;
							}
						}
						i++;
					}
					*(log.stream) << "\tpop " << lex.idtable.table[lex.lextable.table[result_position].indexTI].id << "\n";
					break;
				}
				case LEX_RET:
				{
					*(log.stream) << "\tpush ";
					i++;
					if (lex.idtable.table[lex.lextable.table[i].indexTI].idType == IT::IDTYPE_LIT)
					{
						*(log.stream) << lex.idtable.table[lex.lextable.table[i++].indexTI].value.numValue;
					}
					else
					{
						*(log.stream) << lex.idtable.table[lex.lextable.table[i++].indexTI].id;
					}
					*(log.stream) << "\n\tret\n";
					break;
				}
				case LEX_RIGHTBRACE:
				{
					if (isMain && !isInfuncion)
					{
						*(log.stream) << "\tpush 0\n\tcall ExitProcess\nmain ENDP\nend main";
					}
					if (isInfuncion)
					{
						*(log.stream) << func_name << " ENDP\n\n";
						isInfuncion = false;
					}
					break;
				}
				case LEX_OUTPUT:
				{
					if (lex.idtable.table[lex.lextable.table[i + 2].indexTI].idDataType == IT::IDDATATYPE_NUM)
					{
						*(log.stream) << "\tpush " << lex.idtable.table[lex.lextable.table[i + 2].indexTI].id << "\n\t\tcall outputn\n";
					}
					else
					{
						*(log.stream) << "\tpush offset " << lex.idtable.table[lex.lextable.table[i + 2].indexTI].id << "\n\t\tcall outputr\n";
					}
					break;
				}
			}
		}
	}
}