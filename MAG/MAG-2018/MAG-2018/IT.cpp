#include "pch.h"
#include "IT.h"
#include "Error.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable* idTable = new IdTable;
		idTable->maxsize = size;
		idTable->size = 0;
		idTable->table = new Entry[size];
		
		return (*idTable);
	}

	void Add(IdTable& idtable, Entry entry)
	{
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return (idtable.table[n]);
	}

	int IsId(IdTable& idtable, string id)
	{
		for (int i = 0; i < idtable.size; i++) 
		{
			if (idtable.table[i].id == id)
				return i;
		}

		return TI_NULLIDX;
	}


	int IsDublId(IdTable& idtable, string id)
	{
		for (int i = 0; i < idtable.size - 1; i++) 
		{
			if (idtable.table[i].id == id)
				return i;
		}

		return TI_NULLIDX;
	}


	int CheckId(IdTable& idtable, string value)
	{
		bool rc = false;
		int i;

		for (i = 0; i < idtable.size; i++) {
			if (idtable.table[i].value.rowValue.str == value) 
			{
				rc = true;
				break;
			}
		}

		return rc ? i : TI_NULLIDX;
	}


	int CheckId(IdTable& idtable, int value)
	{
		bool rc = false;
		int i;

		for (i = 0; i < idtable.size; i++) 
		{
			if (idtable.table[i].value.numValue == value)
			{
				if (idtable.table[i].idType == IDTYPE_LIT && idtable.table[i].idDataType == IDDATATYPE_NUM)
				{
					rc = true;
					break;
				}
			}
		}

		return rc ? i : TI_NULLIDX;
	}

	void WriteTable(Log::LOG log, IdTable& idtable)
	{
		int i, numberOP = 0;

		*(log.stream) << setfill('-') << setw(140) << '-' << endl;
		*(log.stream) << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << endl;
		*(log.stream) << setw(140) << '-' << endl;

		for (i = 0; i < idtable.size; i++) 
		{
			*(log.stream) << setfill(' ') << setw(4) << std::right << i << " | ";
			*(log.stream) << setw(13) << left << idtable.table[i].id << " | ";
			
			switch (idtable.table[i].idDataType) 
			{
				case  IDDATATYPE_NUM:
				{
					*(log.stream) << setw(10) << left;

					if (idtable.table[i].idType == IDTYPE_ACT)
						*(log.stream) << "-" << " | ";
					else
						*(log.stream) << "numeral" << " | ";

					break;
				}
				case  IDDATATYPE_ROW:
				{
					*(log.stream) << setw(10) << left;

					if (idtable.table[i].idType == IDTYPE_ACT)
						*(log.stream) << "-" << " | ";
					else
						*(log.stream) << "row" << " | ";

					break;
				}
				default:
				{
					*(log.stream) << setw(10) << left << "unknown" << " | ";

					break;
				}
			}

			switch (idtable.table[i].idType) 
			{
				case IDTYPE_TAB:
				{
					*(log.stream) << setw(18) << left << "переменная" << " | ";
					break;
				}
				case IDTYPE_FUN:
				{
					*(log.stream) << setw(18) << left << "функция" << " | ";
					break;
				}
				case IDTYPE_PAR:
				{
					*(log.stream) << setw(18) << left << "параметр" << " | ";
					break;
				}
				case IDTYPE_LIT:
				{
					*(log.stream) << setw(18) << left << "литерал" << " | ";
					break;
				}
				case IDTYPE_ACT:
				{
					*(log.stream) << setw(18) << left << "оператор" << " | ";
					numberOP++;
					break;
				}
				default:
				{
					*(log.stream) << setw(18) << left << "unknown" << " | ";
					break;
				}
			}

			*(log.stream) << setw(11) << left << idtable.table[i].idFirstInLT << " | ";
			
			if (idtable.table[i].idDataType == IDDATATYPE_NUM && (idtable.table[i].idType == IDTYPE_TAB || idtable.table[i].idType == IDTYPE_LIT)) 
			{
				*(log.stream) << setw(18) << left << idtable.table[i].value.numValue;
			}
			else if (idtable.table[i].idDataType == IDDATATYPE_ROW && (idtable.table[i].idType == IDTYPE_TAB || idtable.table[i].idType == IDTYPE_LIT)) 
			{
				*(log.stream) << "[" << idtable.table[i].value.rowValue.lenghtstr << "]\"" << idtable.table[i].value.rowValue.str << "\"";
			}
			else 
				*(log.stream) << "-";
			
			*(log.stream) << endl;
		}

		*(log.stream) << setfill('-') << setw(87) << '-' << endl;
		*(log.stream) << "Количество идентификаторов: " << i - numberOP << endl;
		*(log.stream) << setw(87) << '-' << endl;
	}

	void ShowTable(IdTable& idtable)
	{
		int i, numberOP = 0;
		
		cout << setfill('-') << setw(87) << '-' << endl;
		cout << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << endl;
		cout << setw(87) << '-' << endl;
		
		for (i = 0; i < idtable.size; i++) 
		{
			cout << setfill(' ') << setw(4) << std::right << i << " | ";
			cout << setw(13) << left << idtable.table[i].id << " | ";
			
			switch (idtable.table[i].idDataType) 
			{
				case  IDDATATYPE_NUM:
				{
					cout << setw(10) << left;

					if (idtable.table[i].idType == IDTYPE_ACT)
						cout << "-" << " | ";
					else
						cout << "numeral" << " | ";

					break;
				}
				case  IDDATATYPE_ROW:
				{
					cout << setw(10) << left;
					
					if (idtable.table[i].idType == IDTYPE_ACT)
						cout << "-" << " | ";
					else
						cout << "row" << " | ";
					
					break;
				}
				default:
					cout << setw(10) << left << "unknown" << " | "; break;
			}

			switch (idtable.table[i].idType) 
			{
				case IDTYPE_TAB:
				{
					cout << setw(18) << left << "переменная" << " | ";
					break;
				}
				case IDTYPE_FUN:
				{
					cout << setw(18) << left << "функция" << " | ";
					break;
				}
				case IDTYPE_PAR:
				{
					cout << setw(18) << left << "параметр" << " | ";
					break;
				}
				case IDTYPE_LIT:
				{
					cout << setw(18) << left << "литерал" << " | ";
					break;
				}
				case IDTYPE_ACT:
				{
					cout << setw(18) << left << "оператор" << " | ";
					numberOP++;
					break;
				}
				default:
					cout << setw(18) << left << "unknown" << " | ";
					break;
			}

			cout << setw(11) << left << idtable.table[i].idFirstInLT << " | ";
			
			if (idtable.table[i].idDataType == IDDATATYPE_NUM && (idtable.table[i].idType == IDTYPE_TAB || idtable.table[i].idType == IDTYPE_LIT)) {
				cout << setw(18) << left << idtable.table[i].value.numValue;
			}
			else if (idtable.table[i].idDataType == IDDATATYPE_ROW && (idtable.table[i].idType == IDTYPE_TAB || idtable.table[i].idType == IDTYPE_LIT)) {
				cout << "[" << idtable.table[i].value.rowValue.lenghtstr << "]\"" << idtable.table[i].value.rowValue.str << "\"";
			}
			else
				cout << "-";

			cout << endl;
		}

		cout << setfill('-') << setw(87) << '-' << endl;
		cout << "Количество идентификаторов: " << i - numberOP << endl <<endl;
		cout << setw(87) << '-' << endl;
	}
}