#include "pch.h"
#include "Error.h"

namespace In
{
	IN GetIn(wchar_t infile[])
	{
		ifstream sourceFile(infile);
		if (sourceFile.fail())
			throw ERROR_THROW(110);

		IN structIn;
		structIn.size = structIn.lines = structIn.ignor = 0;
		unsigned char symbol;
		int position = 0;
		int line = 1;
		char temp_lexema[IN_WORD_MAX_LEN];
		short wordLen = 0;

		while ((!sourceFile.eof()) && (symbol = sourceFile.get())) 
		{
			if (wordLen >= IN_WORD_MAX_LEN)
				throw ERROR_THROW_IN(101, line, -1);

			if (symbol == '\"')		// проверка на длину символьного литерала
			{
				temp_lexema[wordLen++] = symbol;
				do 
				{
					if (symbol == IN_CODE_ENDL)
						throw ERROR_THROW_IN(113, structIn.lines, -1);
					
					symbol = sourceFile.get();
					temp_lexema[wordLen++] = symbol;
					structIn.size++;
				} while (symbol != '\"');
				
				temp_lexema[wordLen] = '\0';
				structIn.queue_w.push({ temp_lexema, line });
				wordLen = 0;
				structIn.size += 1;
				
				continue;
			}

			if (symbol == IN_CODE_SPACE || structIn.code[(int)symbol] == IN::S || symbol == IN_CODE_ENDL) 
			{
				if (temp_lexema && wordLen)
				{
					temp_lexema[wordLen] = '\0';
					structIn.queue_w.push({ temp_lexema, line });
					wordLen = 0;
				}

				if (symbol == IN_CODE_SPACE)
				{
					structIn.ignor += 1;
				}

				if (structIn.code[(int)symbol] == IN::S)
				{
					char buf[2];
					buf[0] = symbol;
					buf[1] = '\0';
					structIn.queue_w.push({ buf, line });
					wordLen = 0;
				}

				if (symbol == IN_CODE_ENDL)
				{
					structIn.lines++;
					line += 1;
					position = 0;
				}
			}
			else if (structIn.code[(int)symbol] != IN::F)
			{
				position++;
				temp_lexema[wordLen++] = symbol;
				structIn.size++;
			}
			else
				throw  ERROR_THROW_IN(111, structIn.lines, position);

			if (structIn.size >= IN_MAX_LEN_TEXT)
				throw ERROR_THROW(104);
		}
		sourceFile.close();
		
		return structIn;
	}
}