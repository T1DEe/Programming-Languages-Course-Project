#pragma once
#pragma once
#include "pch.h"
//#define LEX_ZAMENA '@'

void CallPolishNotation(LT::LexTable* lextable, IT::IdTable* idtable);

bool PolishNotation(	//Построение польской записи в таблице лексем
	int				lextable_pos,		// позиция выражения в lextable
	LT::LexTable*	lextable,			// таблица лексем
	IT::IdTable*	idtable				// таблица идентификаторов
);