#include "cell.h"

namespace MyExcel {
	Cell::Cell(int x, int y, Table* table): x(x), y(y), table(table) {}

	StringCell::StringCell(string data, int x, int y, Table* t)
		:data(data),Cell(x,y,t) {}
	string StringCell::stringify() { return data; }
	int StringCell::to_numeric() { return 0; }

	NumberCell::NumberCell(int data, int x,int y, Table *t)
		:data(data),Cell(x,y,t){}
	string NumberCell::stringify() { return std::to_string(data); }
	int NumberCell::to_numeric() { return data; }

	
	DateCell::DateCell::DateCell(string s, int x, int y, Table* t) :Cell(x, y, t) {
		int year = atoi(s.c_str());
		int month = atoi(s.c_str() + 5);
		int day = atoi(s.c_str() + 8);

		tm timeinfo;

		timeinfo.tm_year = year - 1900;
		timeinfo.tm_mon = month - 1;
		timeinfo.tm_mday = day;
		timeinfo.tm_hour = 0;
		timeinfo.tm_min = 0;
		timeinfo.tm_sec = 0;

		data = mktime(&timeinfo);
	}
	string DateCell::stringify() {
		char buf[50];
		tm temp;
		localtime_s(&temp, &data);
		strftime(buf, 50, "%F", &temp);

		return string(buf);
	}
	int DateCell::to_numeric() { return static_cast<int>(data); }


	int ExprCell::to_numeric() {
		double result = 0;
		NumStack stack;

		for (int i = 0; i < exp_vec.size(); i++) {
			string s = exp_vec[i];

			//�� �� ���
			if (isalpha(s[0])) {
				stack.push(table->to_numeric(s));
			}
			//���� �� ��� (�� �ڸ��� ����)
			else if (isdigit(s[0])) {
				stack.push(atoi(s.c_str()));
			}
			else {
				double y = stack.pop();
				double x = stack.pop();
				switch (s[0]) {
				case '+':
					stack.push(x + y);
					break;
				case '-':
					stack.push(x - y);
					break;
				case '*':
					stack.push(x * y);
					break;
				case '/':
					stack.push(x / y);
					break;
				}
			}
		}
		return stack.pop();
	}
	int ExprCell::precedence(char c) {
		switch (c) {
		case '(':
		case '[':
		case '{':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		}
		return 0;
	}
	void ExprCell::parse_expression() {
		Stack stack;

		//���� ��ü�� ()�� �ѷ� �缭 exp_vec �� �����ִ� ������� push �ǵ���!
		data.insert(0, "(");
		data.push_back(')');

		for (int i = 0; i < data.length(); i++) {
			if (isalpha(data[i])) {
				exp_vec.push_back(data.substr(i, 2));
				i++;
			}
			else if (isdigit(data[i])) {
				exp_vec.push_back(data.substr(i, 1));
			}
			else if (data[i] == '(' || data[i] == '[' || data[i] == '{') {
				stack.push(data.substr(i, 1));
			}
			else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
				string t = stack.pop();
				while (t != "(" && t != "[" && t != "{") {
					exp_vec.push_back(t);
					t = stack.pop();
				}
			}
			else if (data[i] == '*' || data[i] == '-' || data[i] == '*' || data[i] == '/') {
				while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i])) {
					exp_vec.push_back(stack.pop());
				}
				stack.push(data.substr(i, 1));
			}
		}
	}
	ExprCell::ExprCell(string data, int x, int y, Table* t)
		:data(data), Cell(x, y, t) {
		//parsed_expr = new string[data.length()];

		exp_vec = Vector();
		ExprCell::parse_expression();

	}
	string ExprCell::stringify() { return std::to_string(ExprCell::to_numeric()); }

}