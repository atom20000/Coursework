#define _CRT_SECURE_NO_WARNINGS
#include"student.h"

student::student() {
	id_student = 0;
	pol = ' ';
	strcpy(fio.name, " ");
	strcpy(fio.surname, " ");
	strcpy(fio.otchestvo, " ");
	birthday.day = 0;
	birthday.mounth = 0;
	birthday.year = 0;
	strcpy(univesity.facultet, " ");
	strcpy(univesity.group, " ");
	strcpy(univesity.kafedra, " ");
	strcpy(univesity.number_zachet, " ");
	univesity.year_post = 0;
	next_student = nullptr;
	semestr = nullptr;
};
student::~student(){
	id_student = 0;
	pol = ' ';
	strcpy(fio.name, " ");
	strcpy(fio.surname, " ");
	strcpy(fio.otchestvo, " ");
	birthday.day = 0;
	birthday.mounth = 0;
	birthday.year = 0;
	strcpy(univesity.facultet, " ");
	strcpy(univesity.group, " ");
	strcpy(univesity.kafedra, " ");
	strcpy(univesity.number_zachet, " ");
	univesity.year_post = 0;
	next_student = nullptr;
	semestr = nullptr;
	cout << "Запись о студенте удалена" << endl;
}
