/*

#include <iostream>
#include <memory>

class Foo {
	int a, b;

public:
	Foo(int a, int b) :a(a), b(b) { std::cout << "생성자 호출!" << std::endl; }
	void print() { std::cout << "a: " << a << ", b : " << b << std::endl; }
	~Foo() { std::cout << "소멸자 호출!" << std::endl; }
};

int main() {
	auto ptr = std::make_unique<Foo>(3, 5);
	ptr->print();
}
*/

#include <iostream>
#include <memory>
#include <vector>

class A {
	int* data;

public:
	A(int i) {
		std::cout << "자원을 획득함!" << std::endl;
		data = new int[100];
		data[0] = i;
	}

	void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }

	~A() {
		std::cout << "자원을 해제함!" << std::endl;
		delete[] data;
	}
};

int main() {
	std::vector<std::unique_ptr<A>> vec;
	//std::unique_ptr<A> pa(new A(1));

	//vec.push_back(std::move(pa));

	vec.emplace_back(new A(1));
	vec.back()->some();
}