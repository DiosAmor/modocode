#include <iostream>
#include <cstring>
#include <vector>

class MyString {
	char* string_content;
	int string_length;

	int memory_capacity;

public:
	MyString();

	MyString(const char* str);

	//복사 생성자
	MyString(const MyString& str);

	// 이동 생성자
	MyString(MyString&& str) noexcept;

	void reserve(int size);
	MyString operator+(const MyString& s);
	// 일반적인 대입 연산자
	MyString &operator=(const MyString& s);
	// 이동 대입 연산자
	MyString& operator=(MyString&& s);

	~MyString();

	int length() const;

	void print();
	void println();
};

MyString::MyString() {
	std::cout << "생성자 호출 ! " << std::endl;
	string_length = 0;
	memory_capacity = 0;
	string_content = nullptr;
}

MyString::MyString(const char* str) {
	std::cout << "생성자 호출 ! " << std::endl;
	string_length = strlen(str);
	memory_capacity = string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
	std::cout << "복사 생성자 호출 ! " << std::endl;
	string_length = str.string_length;
	memory_capacity = str.string_length;
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
		string_content[i] = str.string_content[i];
}
MyString::MyString(MyString&& str) noexcept {
	std::cout << "이동 생성자 호출 ! " << std::endl;
	string_length = str.string_length;
	memory_capacity = str.memory_capacity;
	string_content =str.string_content;
	//메모리 해제 막기
	str.string_content = nullptr;
	str.string_length = 0;
	str.memory_capacity = 0;
}
MyString::~MyString() {
	if (string_content) delete[] string_content;
}

void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char* prev_string_content = string_content;
		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i != string_length; i++)
			string_content[i] = prev_string_content[i];

		if (prev_string_content != nullptr) delete[] prev_string_content;
	}
}

//복사
MyString& MyString::operator=(const MyString& s) {
	std::cout << "복사!" << std::endl;
	if (s.string_length > memory_capacity) {
		delete[] string_content;
		string_content = new char[s.string_length];
		memory_capacity = s.string_length;
	}
	string_length = s.string_length;
	for (int i = 0; i != string_length; i++) {
		string_content[i] = s.string_content[i];
	}

	return *this;
}
//이동
MyString& MyString::operator=(MyString&& s) {
	std::cout << "이동!" << std::endl;
	string_content = s.string_content;
	memory_capacity = s.memory_capacity;
	string_length = s.string_length;


	s.string_content = nullptr;
	s.memory_capacity = 0;
	s.string_length = 0;

	return *this;
}

MyString MyString::operator+(const MyString& s) {
	MyString str;
	str.reserve(string_length + s.string_length);
	for (int i = 0; i < string_length; i++)
		str.string_content[i] = string_content[i];
	for (int i = 0; i < s.string_length; i++)
		str.string_content[string_length + i] = s.string_content[i];
	str.string_length = string_length + s.string_length;
	return str;
}
int MyString::length() const { return string_length; }
void MyString::print() {
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];
}
void MyString::println(){
	for (int i = 0; i != string_length; i++) std::cout << string_content[i];

	std::cout << std::endl;
}

/*
template <typename T>
void my_swap(T& a, T& b) {
	T tmp(a);
	a = b;
	b = tmp;
}*/
template <typename T>
void my_swap(T& a, T& b) {
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}

int main() {
	/*MyString s("abc");
	std::vector<MyString> vec;
	vec.resize(0);

	std::cout << "첫 번째 추가 ---" << std::endl;
	vec.push_back(s);
	std::cout << "두 번째 추가 ---" << std::endl;
	vec.push_back(s);
	std::cout << "세 번째 추가 ---" << std::endl;
	vec.push_back(s);*/

	MyString str1("abc");
	MyString str2("def");
	std::cout << "Swap 전 ------" << std::endl;
	std::cout << "str1 : ";
	str1.println();
	std::cout << "str2 : ";
	str2.println();

	std::cout << "Swap 후 -----" << std::endl;
	my_swap(str1, str2);
	std::cout << "str1 : ";
	str1.println();
	std::cout << "str2 : ";
	str2.println();
}