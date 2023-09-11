#pragma once
#include "utils.h"
#include "cell.h"

#include <iostream>


namespace MyExcel {
	class Cell;

	class Table {
	protected:
		int max_row_size, max_col_size;

		Cell*** data_table;

	public:
		Table(int max_row_size, int max_col_size);

		~Table();

		void reg_cell(Cell* c, int row, int col);

		int to_numeric(const string& s);
		int to_numeric(int row, int col);

		string stringify(const string& s);
		string stringify(int row, int col);

		virtual string print_table() = 0;
	};

	class TxtTable : public Table {
		string repeat_char(int n, char c);

		string col_num_to_str(int n);

	public:
		TxtTable(int row, int col);

		string print_table();

	};
	std::ostream& operator<<(std::ostream& o, Table& table);
}