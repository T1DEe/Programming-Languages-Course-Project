#pragma once
#pragma once
#include "pch.h"
//#define LEX_ZAMENA '@'

void CallPolishNotation(LT::LexTable* lextable, IT::IdTable* idtable);

bool PolishNotation(	//���������� �������� ������ � ������� ������
	int				lextable_pos,		// ������� ��������� � lextable
	LT::LexTable*	lextable,			// ������� ������
	IT::IdTable*	idtable				// ������� ���������������
);