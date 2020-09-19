#define _CRT_SECURE_NO_WARNINGS
#include"metods.h"

student* metods::create() {
	student* pstart = new student;
	pstart->id_student = 1;
	check_potok(1);
	cout << "Введите фамилию " << endl;
	cin.getline(pstart->fio.surname, 20);
	check_potok();
	cout << "Введите имя " << endl;
	cin.getline(pstart->fio.name, 20);
	check_potok();
	cout << "Введите отчество " << endl;
	cin.getline(pstart->fio.otchestvo, 20);
	check_potok();

	cout << "Введите пол 'м' или 'ж'" << endl;
	do {
		cin >> pstart->pol;
		if (pstart->pol == 'м' || pstart->pol == 'ж') {
			check_potok();
			break;
		}
		cout << "Вы ввели некоректное значение для пола" << endl;
		check_potok();
	} while (1);

	cout << "Введите день рождения " << endl;
	do {
		cin >> pstart->birthday.day;
		if (pstart->birthday.day >= 1 && pstart->birthday.day <= 31) {
			check_potok();
			break;
		}
		cout << "Вы ввели некоректный день" << endl;
		check_potok();
	} while (1);

	cout << "Введите месяц рождения " << endl;
	do {
		cin >> pstart->birthday.mounth;
		if (pstart->birthday.mounth >= 1 && pstart->birthday.mounth <= 12) {
			check_potok();
			break;
		}
		cout << "Вы ввели некоректный месяц" << endl;
		check_potok();
	} while (1);
	cout << "Введите год рождения " << endl;
	do {
		cin >> pstart->birthday.year;
		if (pstart->birthday.year >= 1910 && pstart->birthday.year <= 2004) {
			check_potok();
			break;
		}
		cout << "Вы ввели некоректный год" << endl;
		check_potok();
	} while (1);

	cout << "Введите год поступления" << endl;
	do {
		cin >> pstart->univesity.year_post;
		if (pstart->birthday.year + 16 <= pstart->univesity.year_post) {
			check_potok(1);
			break;
		}
		cout << "Вы ввели некоректный год" << endl;
		check_potok();
	} while (1);
	cout << "Введите название факультета " << endl;
	cin.getline(pstart->univesity.facultet, 100);
	check_potok();
	cout << "Введите казвание кафедры " << endl;
	cin.getline(pstart->univesity.kafedra, 70);
	check_potok();
	cout << "Введите название группы " << endl;
	cin.getline(pstart->univesity.group, 20);
	check_potok();
	cout << "Введите номер зачетной книжки" << endl;
	cin.getline(pstart->univesity.number_zachet, 20);
	check_potok();
	int flug, ocen, id;
	semestrs* ptec, * pprom;
	predmets* ptecp, * ppromp, * pstartp;
	char p[51];
	pstart->semestr = new semestrs;
	pprom = pstart->semestr;
	pprom->next_semestr = pstart->semestr;
	for (int i = 1; i < 10; i++) {
		do {
			do {
				cout << "Введите номер сессии" << endl;
				id = check_input_int();
				if (id > 0 && id < 10) break;
				else cout << "Вы ввели не корректный номер сессии" << endl;
			} while (1);
		} while (search(pstart, pstart->semestr, id));
		pprom->id_semestr = id;
		pprom->predmet = new predmets;
		ppromp = pprom->predmet;
		pstartp = ppromp;
		ppromp->next_predmet = ppromp;
		check_potok(1);
		for (int j = 1; j < 11; j++) {
			do {
				cout << "Введите название предмета " << endl;
				cin.getline(p, 50);
				check_potok();
			} while (searchp(pprom, pprom->predmet, p));
			strcpy(ppromp->name_predmet, p);
			cout << "Оценка по нему " << endl;
			do {
				ocen = check_input_int();
				if (ocen > 1 && ocen < 6) {
					ppromp->mark = ocen;
					check_potok();
					break;
				}
				else {
					cout << "Вы ввели число не соответствующие оценкам по пяти бальной шкале " << endl;
					check_potok();
				}
			} while (1);
			cout << "Есть еще предметы в этой сессии? Да-1 Нет-0 " << endl;
			flug = check_input_int();
			if (flug < 1) {
				ppromp->next_predmet = pstartp;
				break;
			}
			if (j < 10) {
				ptecp = new predmets;
				ppromp->next_predmet = ptecp;
				ppromp = ptecp;
				ppromp->next_predmet = pprom->predmet;
				check_potok(1);
			}
			else {
				cout << "Введено максимальное количество предметов для одной ссесии" << endl;
				ppromp->next_predmet = pprom->predmet;
				check_potok();
			}
		}
		cout << "Есть еще сессии у данного студента ? Да-1 Нет-0 " << endl;
		flug = check_input_int();
		if (flug < 1) {
			pprom->next_semestr = pstart->semestr;
			break;
		}
		if (i < 9) {
			ptec = new semestrs;
			pprom->next_semestr = ptec;
			pprom = ptec;
			pprom->next_semestr = pstart->semestr;
			check_potok();
		}
		else {
			cout << "Введено максимальное количество сессий" << endl;
			pprom->next_semestr = pstart->semestr;
		}
	}
	pstart->next_student = pstart;
	return pstart;
}

void metods::create(student* pstarts) {
	char zach[21];
	int flug;
	student* pprompst = pstarts;
	while (1) {
		check_potok(1);
		do {
			cout << "Введите номер зачетки студента" << endl;
			cin.getline(zach, 20);
			do {
				if (strcmp(pprompst->univesity.number_zachet, zach) == 0) {
					cout << "Студент с таким номером заченой книжки уже есть" << endl;
					break;
				}
				pprompst = pprompst->next_student;
			} while (pstarts != pprompst);
			check_potok();
			if (pprompst == pstarts) break;
			pprompst = pstarts;
		} while (1);
		student* pproms = pstarts;
		do {
			pproms = pproms->next_student;
		} while (pproms->next_student != pstarts);
		student* ptecs = new student;
		strcpy(ptecs->univesity.number_zachet, zach);
		ptecs->id_student = pproms->id_student + 1;
		cout << "Введите фамилию " << endl;
		cin.getline(ptecs->fio.surname, 20);
		check_potok();
		cout << "Введите имя " << endl;
		cin.getline(ptecs->fio.name, 20);
		check_potok();
		cout << "Введите отчество " << endl;
		cin.getline(ptecs->fio.otchestvo, 20);
		check_potok();

		cout << "Введите пол 'м' или 'ж'" << endl;
		do {
			cin >> ptecs->pol;
			if (ptecs->pol == 'м' || ptecs->pol == 'ж') {
				check_potok();
				break;
			}
			cout << "Вы ввели некоректное значение для пола" << endl;
			check_potok();
		} while (1);

		cout << "Введите день рождения " << endl;
		do {
			cin >> ptecs->birthday.day;
			if (ptecs->birthday.day >= 1 && ptecs->birthday.day <= 31) {
				check_potok();
				break;
			}
			cout << "Вы ввели некоректный день" << endl;
			check_potok();
		} while (1);

		cout << "Введите месяц рождения " << endl;
		do {
			cin >> ptecs->birthday.mounth;
			if (ptecs->birthday.mounth >= 1 && ptecs->birthday.mounth <= 12) {
				check_potok();
				break;
			}
			cout << "Вы ввели некоректный месяц" << endl;
			check_potok();
		} while (1);
		cout << "Введите год рождения " << endl;
		do {
			cin >> ptecs->birthday.year;
			if (ptecs->birthday.year >= 1910 && ptecs->birthday.year <= 2004) {
				check_potok();
				break;
			}
			cout << "Вы ввели некоректный год" << endl;
			check_potok();
		} while (1);

		cout << "Введите год поступления" << endl;
		do {
			cin >> ptecs->univesity.year_post;
			if (ptecs->birthday.year + 16 <= ptecs->univesity.year_post) {
				check_potok(1);
				break;
			}
			cout << "Вы ввели некоректный год" << endl;
			check_potok();
		} while (1);
		cout << "Введите название факультета " << endl;
		cin.getline(ptecs->univesity.facultet, 100);
		check_potok();
		cout << "Введите казвание кафедры " << endl;
		cin.getline(ptecs->univesity.kafedra, 70);
		check_potok();
		cout << "Введите название группы " << endl;
		cin.getline(ptecs->univesity.group, 20);
		check_potok();
		int flug, ocen, id;
		semestrs* ptec, * pprom;
		predmets* ptecp, * ppromp, * pstartp;
		char p[51];
		ptecs->semestr = new semestrs;
		pprom = ptecs->semestr;
		pprom->next_semestr = ptecs->semestr;
		for (int i = 1; i < 10; i++) {
			do {
				do {
					cout << "Введите номер сессии" << endl;
					id = check_input_int();
					if (id > 0 && id < 10) break;
					else {
						cout << "Вы ввели не корректный номер сессии" << endl;
						check_potok();
					}
				} while (1);
			} while (search(ptecs, ptecs->semestr, id));
			pprom->id_semestr = id;
			pprom->predmet = new predmets;
			ppromp = pprom->predmet;
			pstartp = ppromp;
			ppromp->next_predmet = ppromp;
			check_potok(1);
			for (int j = 1; j < 11; j++) {
				do {
					cout << "Введите название предмета " << endl;
					cin.getline(p, 50);
					check_potok();
				} while (searchp(pprom, pprom->predmet, p));
				strcpy(ppromp->name_predmet, p);
				cout << "Оценка по нему " << endl;
				do {
					ocen = check_input_int();
					if (ocen > 1 && ocen < 6) {
						ppromp->mark = ocen;
						break;
					}
					else {
						cout << "Вы ввели число не соответствующие оценкам по пяти бальной шкале " << endl;
						check_potok();
					}
				} while (1);
				cout << "Есть еще предметы в этой сессии? Да-1 Нет-0 " << endl;
				flug = check_input_int();
				if (flug < 1) {
					ppromp->next_predmet = pstartp;
					break;
				}
				if (j < 10) {
					ptecp = new predmets;
					ppromp->next_predmet = ptecp;
					ppromp = ptecp;
					ppromp->next_predmet = pprom->predmet;
					check_potok(1);
				}
				else {
					cout << "Введено максимальное количество предметов для одной ссесии" << endl;
					ppromp->next_predmet = pprom->predmet;
					check_potok();
				}
			}
			cout << "Есть еще сессии у данного студента ? Да-1 Нет-0 " << endl;
			flug = check_input_int();
			if (flug < 1) {
				pprom->next_semestr = ptecs->semestr;
				break;
			}
			if (i < 9) {
				ptec = new semestrs;
				pprom->next_semestr = ptec;
				pprom = ptec;
				pprom->next_semestr = ptecs->semestr;
				check_potok();
			}
			else {
				cout << "Введено максимальное количество сессий" << endl;
				pprom->next_semestr = ptecs->semestr;
				check_potok();
			}
		}
		pproms->next_student = ptecs;
		cout << "Добавлять еще студента ? Да-1 Нет-0" << endl;
		flug = check_input_int();
		ptecs->next_student = pstarts;
		if (flug < 1) break;
		pproms = ptecs;
	}
}

int metods::search(student* pstart, semestrs* pprom, int id) {
	do {
		if (pprom->id_semestr == id) {
			cout << "Сессия с таким номер уже есть" << endl;
			return 1;
		}
		pprom = pprom->next_semestr;
	} while (pstart->semestr != pprom);
	return 0;
}

int metods::searchp(semestrs* pprom, predmets* ppromp, char p[]) {
	do {
		if (strcmp(ppromp->name_predmet, p) == 0) {
			cout << "Такой предмет уже есть" << endl;
			return 1;
		}
		ppromp = ppromp->next_predmet;
	} while (pprom->predmet != ppromp);
	return 0;
}

student* metods::searchs(student* pprom) {
	char zach[21];
	check_potok(1);
	do {
		cout << "Введите номер зачетки студента" << endl;
		cin.getline(zach, 20);
		student* pstart = pprom;
		do {
			if (strcmp(pprom->univesity.number_zachet, zach) == 0) {
				return pprom;
			}
			pprom = pprom->next_student;
		} while (pstart != pprom);
		cout << "Студента с таким номером заченой книжки не был найден, проверьте правильность ввода данных" << endl;
		check_potok();
	} while (1);
}

int metods::check_mark(student* stud, int nom1, int nom2) {
	semestrs* pstart = stud->semestr;
	semestrs* pprom = stud->semestr;
	do {
		predmets* pstartp = stud->semestr->predmet;
		predmets* ppromp = stud->semestr->predmet;
		do {
			if (ppromp->mark == nom1 || ppromp->mark == nom2) return 0;
			ppromp = ppromp->next_predmet;
		} while (pstartp != ppromp);
		pprom = pprom->next_semestr;
	} while (pstart != pprom);
	return 1;
}

void metods::menu1_for_zadani(student* stud) {
	int low, high, flug;
	cout << "Выбрать интервал года рождения Да-1  Нет-0" << endl;
	check_potok();
	if (check_input_int()) {
		do {
			cout << "Введите нижнюю границу" << endl;
			check_potok();
			low = check_input_int();
			if (low >= 1910 && low <= 2004) break;
			else cout << "Вы ввели некоректные данные" << endl;
		} while (1);
		do {
			cout << "Введите верхнюю границу" << endl;
			check_potok();
			high = check_input_int();
			if (high <= 2004 && high >= low) break;
			else cout << "Вы ввели некоректные данные" << endl;
		} while (1);
		do {
			cout << "Распечатать всех студентов, у которых за все время обучения нет ни одной оценки 1)3 2)3 и 4 3)5" << endl;
			check_potok();
			flug = check_input_int();
			if (flug == 1) {
				student* pprom = stud;
				do {
					if (pprom->birthday.year >= low && pprom->birthday.year <= high) {
						if (check_mark(pprom, 3, 0)) cout << pprom << endl;
					}
					pprom = pprom->next_student;
				} while (pprom != stud);
				break;
			}
			if (flug == 2) {
				student* pprom = stud;
				do {
					if (pprom->birthday.year >= low && pprom->birthday.year <= high) {
						if (check_mark(pprom, 3, 4)) cout << pprom << endl;
					}
					pprom = pprom->next_student;
				} while (pprom != stud);
				break;
			}
			if (flug == 3) {
				student* pprom = stud;
				do {
					if (pprom->birthday.year >= low && pprom->birthday.year <= high) {
						if (check_mark(pprom, 5, 0)) cout << pprom << endl;
					}
					pprom = pprom->next_student;
				} while (pprom != stud);
				break;
			}
			if (flug < 1 || flug>3) cout << "Вы не выбрали ни одного пункта, произведите повторный выбор" << endl;
		} while (1);
	}
	else {
		do {
			cout << "Распечатать всех студентов, у которых за все время обучения нет ни одной оценки 1)3 2)3 и 4 3)5" << endl;
			check_potok();
			flug = check_input_int();
			if (flug == 1) {
				student* pprom = stud;
				do {
					if (check_mark(pprom, 3, 0)) cout << pprom << endl;
					pprom = pprom->next_student;
				} while (pprom != stud);
				break;
			}
			if (flug == 2) {
				student* pprom = stud;
				do {
					if (check_mark(pprom, 3, 4)) cout << pprom << endl;
					pprom = pprom->next_student;
				} while (pprom != stud);
				break;
			}
			if (flug == 3) {
				student* pprom = stud;
				do {
					if (check_mark(pprom, 5, 0)) cout << pprom << endl;
					pprom = pprom->next_student;
				} while (pprom != stud);
				break;
			}
			if (flug < 1 || flug>3) cout << "Вы не выбрали ни одного пункта, произведите повторный выбор" << endl;
		} while (1);
	}
}

void metods::print(student* pstart) {
	student* pprom = pstart;
	do {
		cout << pprom;
		pprom = pprom->next_student;
	} while (pstart != pprom);
}

void metods::change(student* pstart) {
	int menu, flugs = 0, flugp = 0;

	student* pprom = searchs(pstart);
	cout << pprom << endl << endl;
	char menu1[] = { "1.Изменить ФИО" };
	char menu2[] = { "2.Изменить пол" };
	char menu3[] = { "3.Изменить данные о дате рождения" };
	char menu4[] = { "4.Изменить данные об институте" };
	char menu5[] = { "5.Изменить данные о сесиях" };
	char menu6[] = { "6.Выйти из этого меню" };
	while (1) {
		cout << menu1 << endl << menu2 << endl << menu3 << endl << menu4 << endl << menu5 << endl << menu6 << endl;
		check_potok();
		menu = check_input_int();
		if (menu == 1) {
			while (1) {
				cout << "1.Изменить Фамилию" << endl << "2.Изменить Имя" << endl << "3.Изменить Отчество" << endl << "4.Выйти из этого меню" << endl;
				check_potok();
				menu = check_input_int();
				check_potok(1);
				if (menu == 1) {
					cout << "Введите новую фамилию" << endl;
					cin.getline(pprom->fio.surname, 20);
				}
				if (menu == 2) {
					cout << "Введите новое имя" << endl;
					cin.getline(pprom->fio.name, 20);
				}
				if (menu == 3) {
					cout << "Введите новое отчество" << endl;
					cin.getline(pprom->fio.otchestvo, 20);
				}
				if (menu == 4) {
					break;
				}
				if (menu < 1 || menu > 4) {
					cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
			menu = 1;
		}
		if (menu == 2) {
			check_potok();
			cout << "Введите новый пол" << endl;
			do {
				cin >> pprom->pol;
				if (pprom->pol == 'м' || pprom->pol == 'ж') {
					check_potok();
					break;
				}
				cout << "Вы ввели некоректное значение для пола" << endl;
				check_potok();
			} while (1);
		}
		if (menu == 3) {
			while (1) {
				cout << "1.Изменить день рождения" << endl << "2.Изменить месяц рождения" << endl << "3.Изменить год рождения" << endl << "4.Выйти из этого меню" << endl;
				check_potok();
				menu = check_input_int();
				check_potok();
				if (menu == 1) {
					cout << "Введите новый день рождения " << endl;
					do {
						cin >> pprom->birthday.day;
						if (pprom->birthday.day >= 1 && pprom->birthday.day <= 31) break;
						cout << "Вы ввели некоректный день" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 2) {
					cout << "Введите новый месяц рождения " << endl;
					do {
						cin >> pprom->birthday.mounth;
						if (pprom->birthday.mounth >= 1 && pprom->birthday.mounth <= 12) break;
						cout << "Вы ввели некоректный месяц" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 3) {
					cout << "Введите новый год рождения " << endl;
					do {
						cin >> pprom->birthday.year;
						if (pprom->birthday.year >= 1910 && pprom->birthday.year <= 2004)break;
						cout << "Вы ввели некоректный год" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 4) {
					break;
				}
				if (menu < 1 || menu > 4) {
					cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
			menu = 3;
		}
		if (menu == 4) {
			while (1) {
				cout << "1.Изменить год поступления" << endl << "2.Изменить название факультета" << endl << "3.Изменить название кафедры" << endl << "4.Изменить название группы" << endl << "5.Изменить номер зачетной книжки" << endl << "6.Выйти из этого меню" << endl;
				check_potok();
				menu = check_input_int();
				if (menu == 1) {
					check_potok();
					cout << "Введите новый год поступления" << endl;
					do {
						cin >> pprom->univesity.year_post;
						if (pprom->birthday.year + 16 <= pprom->univesity.year_post)break;
						cout << "Вы ввели некоректный год" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 2) {
					check_potok(1);
					cout << "Введите название факультета " << endl;
					cin.getline(pprom->univesity.facultet, 100);
				}
				if (menu == 3) {
					check_potok(1);
					cout << "Введите казвание кафедры " << endl;
					cin.getline(pprom->univesity.kafedra, 70);
				}
				if (menu == 4) {
					check_potok(1);
					cout << "Введите название группы " << endl;
					cin.getline(pprom->univesity.group, 20);
				}
				if (menu == 5) {
					char zach[21];
					student* pprompst = pstart;
					check_potok(1);
					do {
						cout << "Введите новый номер зачетки студента" << endl;
						cin.getline(zach, 20);
						do {
							if (strcmp(pprompst->univesity.number_zachet, zach) == 0) {
								cout << "Студент с таким номером заченой книжки уже есть" << endl;
								break;
							}
							pprompst = pprompst->next_student;
						} while (pstart != pprompst);
						if (pprompst == pstart) break;
						check_potok();
						pprompst = pstart;
					} while (1);
					strcpy(pprom->univesity.number_zachet, zach);
				}
				if (menu == 6) {
					break;
				}
				if (menu < 1 || menu > 6) {
					cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
			menu = 4;
		}
		if (menu == 5) {
			char pre[51];
			semestrs* ppromp, * ptecp = nullptr;
			predmets* pprompp, * ptecpp = nullptr;
			while (1) {
				cout << "1.Изменить номер сессии " << endl << "2.Изменить оценку по предмету" << endl << "3.Изменить название предмета" << endl << "4.Выйти из этого меню" << endl;
				check_potok();
				menu = check_input_int();
				if (menu == 1) {
					while (1) {
						while (1) {
							cout << "Введите номер сессии" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "Вы ввели не корректное значение для номера сессии" << endl;
						}
						ppromp = pprom->semestr;
						do {
							if (ppromp->id_semestr == menu) {
								ptecp = ppromp;
								flugs = 1;
								break;
							}
							ppromp = ppromp->next_semestr;
						} while (pprom->semestr != ppromp);
						if (flugs == 1)break;
						else cout << "Сессия с таким номером не была найденая у данного студента" << endl;
					}
					while (1) {
						while (1) {
							cout << "Введите новый номер сессии" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "Вы ввели не корректное значение для номера сессии" << endl;
						}
						if (!search(pprom, pprom->semestr, menu)) {
							ptecp->id_semestr = menu;
							break;
						}
					}
					menu = 1;
				}
				if (menu == 2) {
					while (1) {
						while (1) {
							cout << "Введите номер сессии" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "Вы ввели не корректное значение для номера сессии" << endl;
						}
						ppromp = pprom->semestr;
						do {
							if (ppromp->id_semestr == menu) {
								ptecp = ppromp;
								flugs = 1;
								break;
							}
							ppromp = ppromp->next_semestr;
						} while (pprom->semestr != ppromp);
						if (flugs == 1)break;
						else cout << "Сессия с таким номером не была найденая у данного студента" << endl;
					}
					check_potok(1);
					while (1) {
						pprompp = ptecp->predmet;
						cout << "Введите название предмета " << endl;
						cin.getline(pre, 50);
						do {
							if (strcmp(pprompp->name_predmet, pre) == 0) {
								ptecpp = pprompp;
								flugp = 1;
								break;
							}
							pprompp = pprompp->next_predmet;
						} while (ptecp->predmet != pprompp);
						if (flugp == 1)break;
						else {
							cout << "Такой предмет не был найден у данного студента" << endl;
							check_potok();
						}
					}
					cout << "Введите новую оценку по предмету" << endl;
					do {
						check_potok();
						menu = check_input_int();
						if (menu > 1 && menu < 6) {
							ptecpp->mark = menu;
							break;
						}
						else cout << "Вы ввели число не соответствующие оценкам по пяти бальной шкале " << endl;
					} while (1);
					menu = 2;
				}
				if (menu == 3) {
					while (1) {
						while (1) {
							cout << "Введите номер сессии" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "Вы ввели некорректное значение для номера сессии" << endl;
						}
						ppromp = pprom->semestr;
						do {
							if (ppromp->id_semestr == menu) {
								ptecp = ppromp;
								flugs = 1;
								break;
							}
							ppromp = ppromp->next_semestr;
						} while (pprom->semestr != ppromp);
						if (flugs == 1)break;
						else cout << "Сессия с таким номером не была найденая у данного студента" << endl;
					}
					check_potok(1);
					while (1) {
						pprompp = ptecp->predmet;
						cout << "Введите название предмета " << endl;
						cin.getline(pre, 50);
						do {
							if (strcmp(pprompp->name_predmet, pre) == 0) {
								ptecpp = pprompp;
								flugp = 1;
								break;
							}
							pprompp = pprompp->next_predmet;
						} while (ptecp->predmet != pprompp);
						if (flugp == 1)break;
						else {
							cout << "Такой предмет не был найден у данного студента" << endl;
							check_potok();
						}
					}
					while (1) {
						cout << "Введите новое название предмета" << endl;
						check_potok();
						cin.getline(pre, 50);
						if (!searchp(ptecp, ptecp->predmet, pre)) {
							strcpy(ptecpp->name_predmet, pre);
							break;
						}
					}
					menu = 3;
				}
				if (menu == 4) break;
				if (menu < 1 || menu > 4) {
					cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
		}
		if (menu == 6)break;
		if (menu < 1 || menu > 6) {
			cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
			if (check_input_int() > 0) break;
		}
	}
}

student* metods::delet(student* pstart) {
	int menu, flugs = 0, flugp = 0;

	while (1) {
		cout << "1.Удалить запись о студенте" << endl << "2.Удалить запись сессии у студента" << endl << "3.Удалить запись о предмете" << endl << "4.Выход из меню" << endl;
		check_potok();
		menu = check_input_int();
		if (menu > 0 && menu < 4) {
			student* pprom = searchs(pstart);
			if (menu == 1) {
				student* ptecp = pstart;
				if (pprom == pprom->next_student) {
					cout << "В файле была всего одна запись о студенте, послее её удаления файл будет пустым" << endl;
					delete pprom;
					return nullptr;
				}
				while (ptecp->next_student != pprom) {
					ptecp = ptecp->next_student;
				}
				if (pprom == pstart) {
					pstart = pprom->next_student;
				}
				ptecp->next_student = pprom->next_student;
				delete pprom;
			}
			if (menu == 2) {
				semestrs* ppromp, * ptecp = nullptr, * pprompe;
				//predmets* pprompp, * ptecpp;
				while (1) {
					while (1) {
						cout << "Введите номер сессии" << endl;
						check_potok();
						menu = check_input_int();
						if (menu >= 1 && menu <= 9) break;
						else cout << "Вы ввели не корректное значение для номера сессии" << endl;
					}
					ppromp = pprom->semestr;
					do {
						if (ppromp->id_semestr == menu) {
							ptecp = ppromp;
							flugs = 1;
							break;
						}
						ppromp = ppromp->next_semestr;
					} while (pprom->semestr != ppromp);
					if (flugs == 1)break;
					else cout << "Сессия с таким номером не была найденая у данного студента" << endl;
				}
				ppromp = pprom->semestr;
				pprompe = pprom->semestr;
				if (ptecp == ptecp->next_semestr) {
					cout << "У студента была всего одна запись о сесии" << endl;
					break;
				}
				do {
					pprompe = pprompe->next_semestr;
				} while (pprompe->next_semestr != pprom->semestr);
				while (ppromp->next_semestr != ptecp) {
					ppromp = ppromp->next_semestr;
				}
				if (pprompe->next_semestr == ptecp) {
					pprom->semestr = ptecp->next_semestr;
				}
				ppromp->next_semestr = ptecp->next_semestr;
				delete ptecp;
				menu = 2;
			}
			if (menu == 3) {
				char pre[51];
				semestrs* ppromp, * ptecp = nullptr;
				predmets* pprompp, * ppromppe, * ptecpp = nullptr;
				while (1) {
					while (1) {
						cout << "Введите номер сессии" << endl;
						check_potok();
						menu = check_input_int();
						if (menu >= 1 && menu <= 9) break;
						else cout << "Вы ввели некорректное значение для номера сессии" << endl;
					}
					ppromp = pprom->semestr;
					do {
						if (ppromp->id_semestr == menu) {
							ptecp = ppromp;
							flugs = 1;
							break;
						}
						ppromp = ppromp->next_semestr;
					} while (pprom->semestr != ppromp);
					if (flugs == 1)break;
					else cout << "Сессия с таким номером не была найденая у данного студента" << endl;
				}
				check_potok(1);
				while (1) {
					pprompp = ptecp->predmet;
					cout << "Введите название предмета " << endl;
					cin.getline(pre, 50);
					do {
						if (strcmp(pprompp->name_predmet, pre) == 0) {
							ptecpp = pprompp;
							flugp = 1;
							break;
						}
						pprompp = pprompp->next_predmet;
					} while (ptecp->predmet != pprompp);
					if (flugp == 1)break;
					else {
						cout << "Такой предмет не был найден у данного студента" << endl;
						check_potok();
					}
				}
				pprompp = ptecp->predmet;
				ppromppe = ptecp->predmet;
				if (ptecpp == ptecpp->next_predmet) {
					cout << "У студента была всего один предмет в этой сесии" << endl;
					break;
				}
				do {
					ppromppe = ppromppe->next_predmet;
				} while (ppromppe->next_predmet != ptecp->predmet);

				while (pprompp->next_predmet != ptecpp) {
					pprompp = pprompp->next_predmet;
				}
				if (ppromppe->next_predmet == ptecpp) {
					ppromp->predmet = ptecpp->next_predmet;
				}
				pprompp->next_predmet = ptecpp->next_predmet;
				delete ptecpp;
				menu = 3;
			}
		}
		if (menu == 4) break;
		if (menu < 1 || menu > 4) {
			cout << "Вы не выбрали ни одного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
			if (check_input_int() > 0) break;
		}
	}
	return pstart;
}

void metods::dobav_semestr(student* pstart) {
	int flug, ocen, id, count = 0;
	char p[51];
	student* pprom = searchs(pstart);
	semestrs* ppromp, * ptecp = nullptr;
	predmets* pprompp, * ptecpp, * pstartpp;
	ppromp = pprom->semestr;
	do {
		ppromp = ppromp->next_semestr;
		count++;
	} while (ppromp->next_semestr != pprom->semestr);
	if (count != 9) {
		ppromp->next_semestr = new semestrs;
		ptecp = ppromp->next_semestr;
		do {
			do {
				cout << "Введите номер сессии" << endl;
				check_potok();
				id = check_input_int();
				if (id > 0 && id < 10) break;
				else cout << "Вы ввели не корректный номер сессии" << endl;
			} while (1);
		} while (search(pprom, pprom->semestr, id));
		ptecp->id_semestr = id;
		ptecp->next_semestr = pstart->semestr;
		ptecp->predmet = new predmets;
		pprompp = ptecp->predmet;
		pstartpp = pprompp;
		pprompp->next_predmet = pprompp;
		check_potok(1);
		for (int j = 1; j < 11; j++) {
			do {
				cout << "Введите название предмета " << endl;
				cin.getline(p, 50);
				check_potok();
			} while (searchp(ptecp, ptecp->predmet, p));
			strcpy(pprompp->name_predmet, p);
			cout << "Оценка по нему " << endl;
			do {
				ocen = check_input_int();
				if (ocen > 1 && ocen < 6) {
					pprompp->mark = ocen;
					break;
				}
				else cout << "Вы ввели число не соответствующие оценкам по пяти бальной шкале " << endl;
			} while (1);
			cout << "Есть еще предметы в этой сессии? Да-1 Нет-0 " << endl;
			flug = check_input_int();
			if (flug < 1) {
				pprompp->next_predmet = pstartpp;
				break;
			}
			if (j < 10) {
				ptecpp = new predmets;
				pprompp->next_predmet = ptecpp;
				pprompp = ptecpp;
				pprompp->next_predmet = ptecp->predmet;
				check_potok(1);
			}
			else {
				cout << "Введено максимальное количество предметов для одной ссесии" << endl;
				pprompp->next_predmet = ptecp->predmet;
			}
		}
	}
	else {
		cout << "У данного студента максимальное количество сессий" << endl;
	}
}

void metods::dobav_predmet(student* pstart) {
	int flug, flugs, ocen, count = 0;
	char pre[51];
	student* pprom = searchs(pstart);
	semestrs* ppromp, * ptecp = nullptr;
	predmets* pprompp, * ptecpp, * pstartpp;
	while (1) {
		while (1) {
			cout << "Введите номер сессии" << endl;
			check_potok();
			flug = check_input_int();
			if (flug >= 1 && flug <= 9) break;
			else cout << "Вы ввели некорректное значение для номера сессии" << endl;
		}
		ppromp = pprom->semestr;
		do {
			if (ppromp->id_semestr == flug) {
				ptecp = ppromp;
				flugs = 1;
				break;
			}
			ppromp = ppromp->next_semestr;
		} while (pprom->semestr != ppromp);
		if (flugs == 1)break;
		else cout << "Сессия с таким номером не была найденая у данного студента" << endl;
	}
	pprompp = ptecp->predmet;
	do {
		pprompp = pprompp->next_predmet;
		count++;
	} while (pprompp->next_predmet != ptecp->predmet);
	check_potok(1);
	if (count != 10) {
		pprompp->next_predmet = new predmets;
		ptecpp = pprompp->next_predmet;
		ptecpp->next_predmet = ptecp->predmet;
		do {
			cout << "Введите название предмета " << endl;
			cin.getline(pre, 50);
			check_potok();
		} while (searchp(ptecp, ptecp->predmet, pre));
		strcpy(pprompp->name_predmet, pre);
		cout << "Оценка по нему " << endl;
		do {
			ocen = check_input_int();
			if (ocen > 1 && ocen < 6) {
				pprompp->mark = ocen;
				break;
			}
			else cout << "Вы ввели число не соответствующие оценкам по пяти бальной шкале " << endl;
		} while (1);
	}
	else {
		cout << "У данного студента в этой сессии максимальное количество предметов" << endl;
	}
}

metods::~metods() {};
metods::metods() {};