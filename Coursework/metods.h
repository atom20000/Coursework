#pragma once
#include"student.h"
#include"check.h"

class metods {
	student* create();
	void create(student* pstarts);
	int search(student* pstart, semestrs* pprom, int id);
	void menu1_for_zadani(student* pstart);
	int check_mark(student* stud, int nom1, int nom2);
	void print(student* pstart);
	student* searchs(student* pprom);
	int searchp(semestrs* pprom, predmets* ppromp, char p[]);
	void change(student* pstart);
	student* delet(student* pstart);
	void dobav_semestr(student* pstart);
	void dobav_predmet(student* pstart);

public:
	metods();
	~metods();
	friend void menu();
};