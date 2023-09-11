#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>

class Marine {
	static int total_marine_num;

	int hp;
	int coord_x, coord_y;
	bool is_dead;

	const int default_damage;

public:
	Marine();
	Marine(int x, int y);
	Marine(int x, int y, int default_damage);
	//Marine(int x, int y, const char* marine_name);
	~Marine() {
		total_marine_num--;
	}

	int attack();
	void be_attacked(int damage_earn);
	void move(int x, int y);

	void show_status();
	static void show_total_marine();
};

int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
	std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

Marine::Marine()
	:hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y)
	:coord_x(x), coord_y(y), hp(50), default_damage(5), is_dead(false) {
	total_marine_num++;
}
Marine::Marine(int x, int y, int default_damage)
	:coord_x(x), coord_y(y), hp(50), default_damage(default_damage), is_dead(false) {
	total_marine_num++;
}
/*Marine::Marine(int x, int y) {
	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
	name = NULL;
}
Marine::Marine(int x, int y, const char* marine_name) {
	name = new char[strlen(marine_name) + 1];
	strcpy(name, marine_name);

	coord_x = x;
	coord_y = y;
	hp = 50;
	damage = 5;
	is_dead = false;
}
Marine::~Marine() {
	std::cout << name << " 의 소멸자 호출 ! " << std::endl;
	if (name != NULL) {
		delete[] name;
	}
}*/

void Marine::move(int x, int y) {
	coord_x = x;
	coord_y = y;
}
int Marine::attack() { return default_damage; }
void Marine::be_attacked(int damage_earn) {
	hp -= damage_earn;
	if (hp <= 0) is_dead = true;
}
void Marine::show_status() {
	std::cout << " *** Marine :  ***" << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
	std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

class Photon_Cannon {
	int hp, shield;
	int coord_x, coord_y;
	int damage;

public:
	Photon_Cannon(int x, int y);
	Photon_Cannon(const Photon_Cannon& pc);
	
	void show_status();
};
Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
	std::cout << "복사 생성자 호출 !" << std::endl;
	hp = pc.hp;
	shield = pc.shield;
	coord_x = pc.coord_x;
	coord_y = pc.coord_y;
	damage = pc.damage;
}
Photon_Cannon::Photon_Cannon(int x, int y) {
	std::cout << "생성자 호출 !" << std::endl;
	hp = shield = 100;
	coord_x = x;
	coord_y = y;
	damage = 20;
}
void Photon_Cannon::show_status() {
	std::cout << "Photon Cannon " << std::endl;
	std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
	std::cout << " HP : " << hp << std::endl;
}

void create_marine() {
	Marine marine3(10, 10, 4);
	//marine3.show_status();
	Marine::show_total_marine();
}

int main() {
	Marine* marines[100];

	marines[0] = new Marine(2, 3,5);
	Marine::show_total_marine();
	marines[1] = new Marine(3,5,10);
	Marine::show_total_marine();

	//marines[0]->show_status();
	//marines[1]->show_status();

	create_marine();

	std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
	marines[0]->be_attacked(marines[1]->attack());

	marines[0]->show_status();
	marines[1]->show_status();

	delete marines[0];
	delete marines[1];

	std::cout<<std::endl;

	Photon_Cannon pc1(3, 3);
	Photon_Cannon pc2(pc1);
	Photon_Cannon pc3(1,1);
	//pc3 = pc2;

	pc1.show_status();
	pc2.show_status();
	pc3.show_status();
}