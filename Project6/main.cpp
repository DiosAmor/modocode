#include "utils.h"
#include "table.h"
#include "cell.h"

#include<fstream>

int main() {
	MyExcel::TxtTable table(5, 5);
	//std::ofstream out("test.txt");
	/*
	table.reg_cell(new MyExcel::Cell("Hello~!", 0, 0, &table), 0, 0);
	table.reg_cell(new MyExcel::Cell("C++", 0, 1, &table), 0, 1);

	table.reg_cell(new MyExcel::Cell("Programming", 1, 1, &table), 1, 1);
	*/
	table.reg_cell(new MyExcel::NumberCell(2, 1, 1, &table), 1, 1);
	table.reg_cell(new MyExcel::NumberCell(3, 1, 2, &table), 1, 2);
	table.reg_cell(new MyExcel::NumberCell(4, 2, 1, &table), 2, 1);
	table.reg_cell(new MyExcel::NumberCell(5, 2, 2, &table), 2, 2);
	table.reg_cell(new MyExcel::ExprCell("B2+B3*(C2+C3-2)", 3, 3, &table), 3, 2);
	table.reg_cell(new MyExcel::StringCell("B2 + B3 * ( C2 + C3 - 2 ) = ", 3, 2, &table), 3, 1);

	std::cout << table;
	//out << table;
	return 0;
}
