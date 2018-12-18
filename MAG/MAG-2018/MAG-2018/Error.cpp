#include "pch.h"

namespace Error
{
	//	0   -  99  -  системные
	//	100 - 109  -  параметров
	//	110 - 119  -  открытия и чтения файлов
	//	120 - 199  -  ошибки лексического анализа
	//  200 - 299  -  ошибки синтаксического анализа
	//  300 - 399  -  ошибки семантического анализа

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		//	0   -  99  -  системные
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		//	100 - 109  -  параметров
		ERROR_ENTRY(100, "Ошибка запуска. Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "Ошибка запуска. Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		//	110 - 119  -  открытия и чтения файлов
		ERROR_ENTRY(110, "Ошибка проверки входного файла. Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Ошибка проверки входного файла. Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка проверки входного файла. Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(113, "Ошибка в записи строкового литерала"),
		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		//	120 - 199  -  ошибки лексического анализа
		ERROR_ENTRY(120, "Цепочка символов не разобрана"),
		ERROR_ENTRY(121, "Таблица лексем переполнена"),
		ERROR_ENTRY(122, "Таблица идентификаторов переполнена"),
		ERROR_ENTRY(123, "Дублирование идентификатора функции"),
		ERROR_ENTRY(124, "Дублирование арифметических операций"),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126),
		ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		//  200 - 299  -  ошибки синтаксического анализа
		ERROR_ENTRY(200, "Неверная структура программы"),
		ERROR_ENTRY(201, "Ошибочный оператор"),
		ERROR_ENTRY(202, "Неверное выражение"),
		ERROR_ENTRY(203, "Ошибка в параметрах функции или операторе объявления"),
		ERROR_ENTRY(204, "Ошибка в параметре вызываемой функции стандартной библиотеки"),
		ERROR_ENTRY(205, "Неверное завершение блока кода"),
		ERROR_ENTRY_NODEF(206),
		ERROR_ENTRY(207, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(208, "Ошибка арифметического оператора"),
		ERROR_ENTRY(209, "Ошибка в операторе ветвления"),
		ERROR_ENTRY(210, "Ошибка в возвращаемом выражении"),
		ERROR_ENTRY(211, "Не найден конец правила"),
		ERROR_ENTRY(212, "Цепочка разобрана не полностью (стек не пустой)"),
		ERROR_ENTRY(213, "Точка входа в программу не задана"),
		ERROR_ENTRY_NODEF(214),
		ERROR_ENTRY(215, "Не найден конец правила"),
		ERROR_ENTRY_NODEF(216), ERROR_ENTRY_NODEF(217), ERROR_ENTRY_NODEF(218), ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270),
		ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		//  300 - 399  -  ошибки семантического анализа
		ERROR_ENTRY(300, "Повторное объявление идентификатора"),
		ERROR_ENTRY(301, "Ошибка в типе идентификатора"),
		ERROR_ENTRY(302, "Ошибка в передаваемых значениях в функцию"),
		ERROR_ENTRY(303, "В функцию не переданы параметры"),
		ERROR_ENTRY(304, "Тип данных результата выражения не соответствует присваиваемому идентификатору"),
		ERROR_ENTRY(305, "Ошибка в параметре вызываемой функции len стандартной библиотеки"),
		ERROR_ENTRY(306, "Необъявленный идентификатор"),
		ERROR_ENTRY(307, "Несоответствие типов в операторе присваивания"),
		ERROR_ENTRY_NODEF(308),	ERROR_ENTRY_NODEF(309),

		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330),
		ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),

		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500), ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR GetError(int id)
	{
		if (id > ERROR_MAX_ENTRY || id < 0)
			return errors[0];

		return errors[id];
	}

	ERROR GetErrorIn(int id, int line = -1, int pos = -1)
	{
		if (id > ERROR_MAX_ENTRY || id < 0)
			return errors[0];
	
		errors[id].intext.line = line;
		errors[id].intext.pos = pos;
		return errors[id];
	}
}