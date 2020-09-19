#pragma once
#include <iostream>
#include <cstring>

using namespace std;

struct fios {
	char surname[21];
	char name[21];
	char otchestvo[21];
};

struct birthdays {
	int day;
	int mounth;
	int year;
};

struct univesitys {
	int year_post;
	char facultet[101];
	char kafedra[71];
	char group[21];
	char number_zachet[21];
};

struct predmets {
	int id_predmet;
	char name_predmet[51];
	int mark;
	predmets* next_predmet;
};

struct semestrs {
	int id_semestr;
	predmets* predmet;
	semestrs* next_semestr;
};

class student {
private:
	int id_student;
	char pol;
	fios fio;
	birthdays birthday;
	univesitys univesity;
	semestrs* semestr;
	student* next_student;
public:
	student();
	~student();
	friend class file_p;
	friend class file_crypt;
	friend class metods;
	friend ostream& operator << (ostream& out, student* stud);
	friend void copy_stud(student* stud, student* pprom);
};