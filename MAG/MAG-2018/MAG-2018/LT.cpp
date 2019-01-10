#include "pch.h"

namespace LT
{
	LexTable Create(int size)
	{
		LexTable *newTabl = new LexTable;			// �������� ���������� ������� ������
		newTabl->maxize = size;						// ������� ������������ �������
		newTabl->size = 0;							// ��������� ������ ����� ����
		newTabl->table = new Entry[size];			// �������� ������� ����� ������� ������
		memset(newTabl->table, 255, 255);			// ���������� ����������� ������� ����� �� 255
		return *newTabl;
	}

	Entry Add(LexTable& lextable, Entry entry)
	{
		return(lextable.table[lextable.size++] = entry);
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return (lextable.table[n]);
	}

	void Write(Log::LOG log, LexTable& lexTable)
	{
		int k = 1;
		*(log.stream) << "\n\n1: ";
		
		for (int i = 0; i < lexTable.size; i++) 
		{
			if (lexTable.table[i].lineNo != k)
			{
				*(log.stream) << "\n" << lexTable.table[i].lineNo << ": ";
				k = lexTable.table[i].lineNo;
				
				if (lexTable.table[i].indexTI != (int)TL_TI_NULLIDX)
					*(log.stream) << lexTable.table[i].lexem;		// << "[" << lexTable.table[i].indexTI << "]";
				else
					*(log.stream) << lexTable.table[i].lexem;
			}
			else
			{
				if (lexTable.table[i].indexTI != (int)TL_TI_NULLIDX)
					*(log.stream) << lexTable.table[i].lexem;		// << "[" << lexTable.table[i].idxTI << "]";
				else
					*(log.stream) << lexTable.table[i].lexem;
			}
		}

		*(log.stream) << "\n���������� ������ - " << lexTable.size << endl;
	}

	void ShowTable(LexTable& lexTable)
	{
		int k = 0;
		cout << "\n\n";
		for (int i = 0; i < lexTable.size; i++) 
		{
			if (lexTable.table[i].lineNo != k) 
			{
				cout << "\n" << lexTable.table[i].lineNo << ": ";
				k = lexTable.table[i].lineNo;
				
				if (lexTable.table[i].indexTI != (int)TL_TI_NULLIDX)
					cout << lexTable.table[i].lexem;				//<< "[" << lexTable.table[i].idxTI << "]"
				else
					cout << lexTable.table[i].lexem;
			}
			else 
			{
				if (lexTable.table[i].indexTI != (int)TL_TI_NULLIDX)
					cout << lexTable.table[i].lexem;				//<< "[" << lexTable.table[i].idxTI << "]"
				else
					cout << lexTable.table[i].lexem;
			}
		}
		cout << "\n���������� ������ - " << lexTable.size <<endl;
	}
}