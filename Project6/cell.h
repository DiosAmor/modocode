#pragma once
#include "utils.h"
#include "table.h"


namespace MyExcel {
	class Table;
	class TxtTable;

	class Cell {
	protected:
		int x, y;
		Table* table;

		string data;

	public:
		virtual string stringify();
		virtual int to_numeric();

		Cell(string data, int x, int y, Table* table);
	};
}