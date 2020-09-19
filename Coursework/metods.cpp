#define _CRT_SECURE_NO_WARNINGS
#include"metods.h"

student* metods::create() {
	student* pstart = new student;
	pstart->id_student = 1;
	check_potok(1);
	cout << "������� ������� " << endl;
	cin.getline(pstart->fio.surname, 20);
	check_potok();
	cout << "������� ��� " << endl;
	cin.getline(pstart->fio.name, 20);
	check_potok();
	cout << "������� �������� " << endl;
	cin.getline(pstart->fio.otchestvo, 20);
	check_potok();

	cout << "������� ��� '�' ��� '�'" << endl;
	do {
		cin >> pstart->pol;
		if (pstart->pol == '�' || pstart->pol == '�') {
			check_potok();
			break;
		}
		cout << "�� ����� ����������� �������� ��� ����" << endl;
		check_potok();
	} while (1);

	cout << "������� ���� �������� " << endl;
	do {
		cin >> pstart->birthday.day;
		if (pstart->birthday.day >= 1 && pstart->birthday.day <= 31) {
			check_potok();
			break;
		}
		cout << "�� ����� ����������� ����" << endl;
		check_potok();
	} while (1);

	cout << "������� ����� �������� " << endl;
	do {
		cin >> pstart->birthday.mounth;
		if (pstart->birthday.mounth >= 1 && pstart->birthday.mounth <= 12) {
			check_potok();
			break;
		}
		cout << "�� ����� ����������� �����" << endl;
		check_potok();
	} while (1);
	cout << "������� ��� �������� " << endl;
	do {
		cin >> pstart->birthday.year;
		if (pstart->birthday.year >= 1910 && pstart->birthday.year <= 2004) {
			check_potok();
			break;
		}
		cout << "�� ����� ����������� ���" << endl;
		check_potok();
	} while (1);

	cout << "������� ��� �����������" << endl;
	do {
		cin >> pstart->univesity.year_post;
		if (pstart->birthday.year + 16 <= pstart->univesity.year_post) {
			check_potok(1);
			break;
		}
		cout << "�� ����� ����������� ���" << endl;
		check_potok();
	} while (1);
	cout << "������� �������� ���������� " << endl;
	cin.getline(pstart->univesity.facultet, 100);
	check_potok();
	cout << "������� �������� ������� " << endl;
	cin.getline(pstart->univesity.kafedra, 70);
	check_potok();
	cout << "������� �������� ������ " << endl;
	cin.getline(pstart->univesity.group, 20);
	check_potok();
	cout << "������� ����� �������� ������" << endl;
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
				cout << "������� ����� ������" << endl;
				id = check_input_int();
				if (id > 0 && id < 10) break;
				else cout << "�� ����� �� ���������� ����� ������" << endl;
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
				cout << "������� �������� �������� " << endl;
				cin.getline(p, 50);
				check_potok();
			} while (searchp(pprom, pprom->predmet, p));
			strcpy(ppromp->name_predmet, p);
			cout << "������ �� ���� " << endl;
			do {
				ocen = check_input_int();
				if (ocen > 1 && ocen < 6) {
					ppromp->mark = ocen;
					check_potok();
					break;
				}
				else {
					cout << "�� ����� ����� �� ��������������� ������� �� ���� ������� ����� " << endl;
					check_potok();
				}
			} while (1);
			cout << "���� ��� �������� � ���� ������? ��-1 ���-0 " << endl;
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
				cout << "������� ������������ ���������� ��������� ��� ����� ������" << endl;
				ppromp->next_predmet = pprom->predmet;
				check_potok();
			}
		}
		cout << "���� ��� ������ � ������� �������� ? ��-1 ���-0 " << endl;
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
			cout << "������� ������������ ���������� ������" << endl;
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
			cout << "������� ����� ������� ��������" << endl;
			cin.getline(zach, 20);
			do {
				if (strcmp(pprompst->univesity.number_zachet, zach) == 0) {
					cout << "������� � ����� ������� ������� ������ ��� ����" << endl;
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
		cout << "������� ������� " << endl;
		cin.getline(ptecs->fio.surname, 20);
		check_potok();
		cout << "������� ��� " << endl;
		cin.getline(ptecs->fio.name, 20);
		check_potok();
		cout << "������� �������� " << endl;
		cin.getline(ptecs->fio.otchestvo, 20);
		check_potok();

		cout << "������� ��� '�' ��� '�'" << endl;
		do {
			cin >> ptecs->pol;
			if (ptecs->pol == '�' || ptecs->pol == '�') {
				check_potok();
				break;
			}
			cout << "�� ����� ����������� �������� ��� ����" << endl;
			check_potok();
		} while (1);

		cout << "������� ���� �������� " << endl;
		do {
			cin >> ptecs->birthday.day;
			if (ptecs->birthday.day >= 1 && ptecs->birthday.day <= 31) {
				check_potok();
				break;
			}
			cout << "�� ����� ����������� ����" << endl;
			check_potok();
		} while (1);

		cout << "������� ����� �������� " << endl;
		do {
			cin >> ptecs->birthday.mounth;
			if (ptecs->birthday.mounth >= 1 && ptecs->birthday.mounth <= 12) {
				check_potok();
				break;
			}
			cout << "�� ����� ����������� �����" << endl;
			check_potok();
		} while (1);
		cout << "������� ��� �������� " << endl;
		do {
			cin >> ptecs->birthday.year;
			if (ptecs->birthday.year >= 1910 && ptecs->birthday.year <= 2004) {
				check_potok();
				break;
			}
			cout << "�� ����� ����������� ���" << endl;
			check_potok();
		} while (1);

		cout << "������� ��� �����������" << endl;
		do {
			cin >> ptecs->univesity.year_post;
			if (ptecs->birthday.year + 16 <= ptecs->univesity.year_post) {
				check_potok(1);
				break;
			}
			cout << "�� ����� ����������� ���" << endl;
			check_potok();
		} while (1);
		cout << "������� �������� ���������� " << endl;
		cin.getline(ptecs->univesity.facultet, 100);
		check_potok();
		cout << "������� �������� ������� " << endl;
		cin.getline(ptecs->univesity.kafedra, 70);
		check_potok();
		cout << "������� �������� ������ " << endl;
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
					cout << "������� ����� ������" << endl;
					id = check_input_int();
					if (id > 0 && id < 10) break;
					else {
						cout << "�� ����� �� ���������� ����� ������" << endl;
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
					cout << "������� �������� �������� " << endl;
					cin.getline(p, 50);
					check_potok();
				} while (searchp(pprom, pprom->predmet, p));
				strcpy(ppromp->name_predmet, p);
				cout << "������ �� ���� " << endl;
				do {
					ocen = check_input_int();
					if (ocen > 1 && ocen < 6) {
						ppromp->mark = ocen;
						break;
					}
					else {
						cout << "�� ����� ����� �� ��������������� ������� �� ���� ������� ����� " << endl;
						check_potok();
					}
				} while (1);
				cout << "���� ��� �������� � ���� ������? ��-1 ���-0 " << endl;
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
					cout << "������� ������������ ���������� ��������� ��� ����� ������" << endl;
					ppromp->next_predmet = pprom->predmet;
					check_potok();
				}
			}
			cout << "���� ��� ������ � ������� �������� ? ��-1 ���-0 " << endl;
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
				cout << "������� ������������ ���������� ������" << endl;
				pprom->next_semestr = ptecs->semestr;
				check_potok();
			}
		}
		pproms->next_student = ptecs;
		cout << "��������� ��� �������� ? ��-1 ���-0" << endl;
		flug = check_input_int();
		ptecs->next_student = pstarts;
		if (flug < 1) break;
		pproms = ptecs;
	}
}

int metods::search(student* pstart, semestrs* pprom, int id) {
	do {
		if (pprom->id_semestr == id) {
			cout << "������ � ����� ����� ��� ����" << endl;
			return 1;
		}
		pprom = pprom->next_semestr;
	} while (pstart->semestr != pprom);
	return 0;
}

int metods::searchp(semestrs* pprom, predmets* ppromp, char p[]) {
	do {
		if (strcmp(ppromp->name_predmet, p) == 0) {
			cout << "����� ������� ��� ����" << endl;
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
		cout << "������� ����� ������� ��������" << endl;
		cin.getline(zach, 20);
		student* pstart = pprom;
		do {
			if (strcmp(pprom->univesity.number_zachet, zach) == 0) {
				return pprom;
			}
			pprom = pprom->next_student;
		} while (pstart != pprom);
		cout << "�������� � ����� ������� ������� ������ �� ��� ������, ��������� ������������ ����� ������" << endl;
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
	cout << "������� �������� ���� �������� ��-1  ���-0" << endl;
	check_potok();
	if (check_input_int()) {
		do {
			cout << "������� ������ �������" << endl;
			check_potok();
			low = check_input_int();
			if (low >= 1910 && low <= 2004) break;
			else cout << "�� ����� ����������� ������" << endl;
		} while (1);
		do {
			cout << "������� ������� �������" << endl;
			check_potok();
			high = check_input_int();
			if (high <= 2004 && high >= low) break;
			else cout << "�� ����� ����������� ������" << endl;
		} while (1);
		do {
			cout << "����������� ���� ���������, � ������� �� ��� ����� �������� ��� �� ����� ������ 1)3 2)3 � 4 3)5" << endl;
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
			if (flug < 1 || flug>3) cout << "�� �� ������� �� ������ ������, ����������� ��������� �����" << endl;
		} while (1);
	}
	else {
		do {
			cout << "����������� ���� ���������, � ������� �� ��� ����� �������� ��� �� ����� ������ 1)3 2)3 � 4 3)5" << endl;
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
			if (flug < 1 || flug>3) cout << "�� �� ������� �� ������ ������, ����������� ��������� �����" << endl;
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
	char menu1[] = { "1.�������� ���" };
	char menu2[] = { "2.�������� ���" };
	char menu3[] = { "3.�������� ������ � ���� ��������" };
	char menu4[] = { "4.�������� ������ �� ���������" };
	char menu5[] = { "5.�������� ������ � ������" };
	char menu6[] = { "6.����� �� ����� ����" };
	while (1) {
		cout << menu1 << endl << menu2 << endl << menu3 << endl << menu4 << endl << menu5 << endl << menu6 << endl;
		check_potok();
		menu = check_input_int();
		if (menu == 1) {
			while (1) {
				cout << "1.�������� �������" << endl << "2.�������� ���" << endl << "3.�������� ��������" << endl << "4.����� �� ����� ����" << endl;
				check_potok();
				menu = check_input_int();
				check_potok(1);
				if (menu == 1) {
					cout << "������� ����� �������" << endl;
					cin.getline(pprom->fio.surname, 20);
				}
				if (menu == 2) {
					cout << "������� ����� ���" << endl;
					cin.getline(pprom->fio.name, 20);
				}
				if (menu == 3) {
					cout << "������� ����� ��������" << endl;
					cin.getline(pprom->fio.otchestvo, 20);
				}
				if (menu == 4) {
					break;
				}
				if (menu < 1 || menu > 4) {
					cout << "�� �� ������� �������� ������ ����. ������ �����? ��-1 , ���-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
			menu = 1;
		}
		if (menu == 2) {
			check_potok();
			cout << "������� ����� ���" << endl;
			do {
				cin >> pprom->pol;
				if (pprom->pol == '�' || pprom->pol == '�') {
					check_potok();
					break;
				}
				cout << "�� ����� ����������� �������� ��� ����" << endl;
				check_potok();
			} while (1);
		}
		if (menu == 3) {
			while (1) {
				cout << "1.�������� ���� ��������" << endl << "2.�������� ����� ��������" << endl << "3.�������� ��� ��������" << endl << "4.����� �� ����� ����" << endl;
				check_potok();
				menu = check_input_int();
				check_potok();
				if (menu == 1) {
					cout << "������� ����� ���� �������� " << endl;
					do {
						cin >> pprom->birthday.day;
						if (pprom->birthday.day >= 1 && pprom->birthday.day <= 31) break;
						cout << "�� ����� ����������� ����" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 2) {
					cout << "������� ����� ����� �������� " << endl;
					do {
						cin >> pprom->birthday.mounth;
						if (pprom->birthday.mounth >= 1 && pprom->birthday.mounth <= 12) break;
						cout << "�� ����� ����������� �����" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 3) {
					cout << "������� ����� ��� �������� " << endl;
					do {
						cin >> pprom->birthday.year;
						if (pprom->birthday.year >= 1910 && pprom->birthday.year <= 2004)break;
						cout << "�� ����� ����������� ���" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 4) {
					break;
				}
				if (menu < 1 || menu > 4) {
					cout << "�� �� ������� �������� ������ ����. ������ �����? ��-1 , ���-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
			menu = 3;
		}
		if (menu == 4) {
			while (1) {
				cout << "1.�������� ��� �����������" << endl << "2.�������� �������� ����������" << endl << "3.�������� �������� �������" << endl << "4.�������� �������� ������" << endl << "5.�������� ����� �������� ������" << endl << "6.����� �� ����� ����" << endl;
				check_potok();
				menu = check_input_int();
				if (menu == 1) {
					check_potok();
					cout << "������� ����� ��� �����������" << endl;
					do {
						cin >> pprom->univesity.year_post;
						if (pprom->birthday.year + 16 <= pprom->univesity.year_post)break;
						cout << "�� ����� ����������� ���" << endl;
						check_potok();
					} while (1);
				}
				if (menu == 2) {
					check_potok(1);
					cout << "������� �������� ���������� " << endl;
					cin.getline(pprom->univesity.facultet, 100);
				}
				if (menu == 3) {
					check_potok(1);
					cout << "������� �������� ������� " << endl;
					cin.getline(pprom->univesity.kafedra, 70);
				}
				if (menu == 4) {
					check_potok(1);
					cout << "������� �������� ������ " << endl;
					cin.getline(pprom->univesity.group, 20);
				}
				if (menu == 5) {
					char zach[21];
					student* pprompst = pstart;
					check_potok(1);
					do {
						cout << "������� ����� ����� ������� ��������" << endl;
						cin.getline(zach, 20);
						do {
							if (strcmp(pprompst->univesity.number_zachet, zach) == 0) {
								cout << "������� � ����� ������� ������� ������ ��� ����" << endl;
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
					cout << "�� �� ������� �������� ������ ����. ������ �����? ��-1 , ���-0" << endl;
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
				cout << "1.�������� ����� ������ " << endl << "2.�������� ������ �� ��������" << endl << "3.�������� �������� ��������" << endl << "4.����� �� ����� ����" << endl;
				check_potok();
				menu = check_input_int();
				if (menu == 1) {
					while (1) {
						while (1) {
							cout << "������� ����� ������" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "�� ����� �� ���������� �������� ��� ������ ������" << endl;
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
						else cout << "������ � ����� ������� �� ���� �������� � ������� ��������" << endl;
					}
					while (1) {
						while (1) {
							cout << "������� ����� ����� ������" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "�� ����� �� ���������� �������� ��� ������ ������" << endl;
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
							cout << "������� ����� ������" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "�� ����� �� ���������� �������� ��� ������ ������" << endl;
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
						else cout << "������ � ����� ������� �� ���� �������� � ������� ��������" << endl;
					}
					check_potok(1);
					while (1) {
						pprompp = ptecp->predmet;
						cout << "������� �������� �������� " << endl;
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
							cout << "����� ������� �� ��� ������ � ������� ��������" << endl;
							check_potok();
						}
					}
					cout << "������� ����� ������ �� ��������" << endl;
					do {
						check_potok();
						menu = check_input_int();
						if (menu > 1 && menu < 6) {
							ptecpp->mark = menu;
							break;
						}
						else cout << "�� ����� ����� �� ��������������� ������� �� ���� ������� ����� " << endl;
					} while (1);
					menu = 2;
				}
				if (menu == 3) {
					while (1) {
						while (1) {
							cout << "������� ����� ������" << endl;
							check_potok();
							menu = check_input_int();
							if (menu >= 1 && menu <= 9) break;
							else cout << "�� ����� ������������ �������� ��� ������ ������" << endl;
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
						else cout << "������ � ����� ������� �� ���� �������� � ������� ��������" << endl;
					}
					check_potok(1);
					while (1) {
						pprompp = ptecp->predmet;
						cout << "������� �������� �������� " << endl;
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
							cout << "����� ������� �� ��� ������ � ������� ��������" << endl;
							check_potok();
						}
					}
					while (1) {
						cout << "������� ����� �������� ��������" << endl;
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
					cout << "�� �� ������� �������� ������ ����. ������ �����? ��-1 , ���-0" << endl;
					if (check_input_int() > 0) break;
				}
			}
		}
		if (menu == 6)break;
		if (menu < 1 || menu > 6) {
			cout << "�� �� ������� �������� ������ ����. ������ �����? ��-1 , ���-0" << endl;
			if (check_input_int() > 0) break;
		}
	}
}

student* metods::delet(student* pstart) {
	int menu, flugs = 0, flugp = 0;

	while (1) {
		cout << "1.������� ������ � ��������" << endl << "2.������� ������ ������ � ��������" << endl << "3.������� ������ � ��������" << endl << "4.����� �� ����" << endl;
		check_potok();
		menu = check_input_int();
		if (menu > 0 && menu < 4) {
			student* pprom = searchs(pstart);
			if (menu == 1) {
				student* ptecp = pstart;
				if (pprom == pprom->next_student) {
					cout << "� ����� ���� ����� ���� ������ � ��������, ������ � �������� ���� ����� ������" << endl;
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
						cout << "������� ����� ������" << endl;
						check_potok();
						menu = check_input_int();
						if (menu >= 1 && menu <= 9) break;
						else cout << "�� ����� �� ���������� �������� ��� ������ ������" << endl;
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
					else cout << "������ � ����� ������� �� ���� �������� � ������� ��������" << endl;
				}
				ppromp = pprom->semestr;
				pprompe = pprom->semestr;
				if (ptecp == ptecp->next_semestr) {
					cout << "� �������� ���� ����� ���� ������ � �����" << endl;
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
						cout << "������� ����� ������" << endl;
						check_potok();
						menu = check_input_int();
						if (menu >= 1 && menu <= 9) break;
						else cout << "�� ����� ������������ �������� ��� ������ ������" << endl;
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
					else cout << "������ � ����� ������� �� ���� �������� � ������� ��������" << endl;
				}
				check_potok(1);
				while (1) {
					pprompp = ptecp->predmet;
					cout << "������� �������� �������� " << endl;
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
						cout << "����� ������� �� ��� ������ � ������� ��������" << endl;
						check_potok();
					}
				}
				pprompp = ptecp->predmet;
				ppromppe = ptecp->predmet;
				if (ptecpp == ptecpp->next_predmet) {
					cout << "� �������� ���� ����� ���� ������� � ���� �����" << endl;
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
			cout << "�� �� ������� �� ������ ������ ����. ������ �����? ��-1 , ���-0" << endl;
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
				cout << "������� ����� ������" << endl;
				check_potok();
				id = check_input_int();
				if (id > 0 && id < 10) break;
				else cout << "�� ����� �� ���������� ����� ������" << endl;
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
				cout << "������� �������� �������� " << endl;
				cin.getline(p, 50);
				check_potok();
			} while (searchp(ptecp, ptecp->predmet, p));
			strcpy(pprompp->name_predmet, p);
			cout << "������ �� ���� " << endl;
			do {
				ocen = check_input_int();
				if (ocen > 1 && ocen < 6) {
					pprompp->mark = ocen;
					break;
				}
				else cout << "�� ����� ����� �� ��������������� ������� �� ���� ������� ����� " << endl;
			} while (1);
			cout << "���� ��� �������� � ���� ������? ��-1 ���-0 " << endl;
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
				cout << "������� ������������ ���������� ��������� ��� ����� ������" << endl;
				pprompp->next_predmet = ptecp->predmet;
			}
		}
	}
	else {
		cout << "� ������� �������� ������������ ���������� ������" << endl;
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
			cout << "������� ����� ������" << endl;
			check_potok();
			flug = check_input_int();
			if (flug >= 1 && flug <= 9) break;
			else cout << "�� ����� ������������ �������� ��� ������ ������" << endl;
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
		else cout << "������ � ����� ������� �� ���� �������� � ������� ��������" << endl;
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
			cout << "������� �������� �������� " << endl;
			cin.getline(pre, 50);
			check_potok();
		} while (searchp(ptecp, ptecp->predmet, pre));
		strcpy(pprompp->name_predmet, pre);
		cout << "������ �� ���� " << endl;
		do {
			ocen = check_input_int();
			if (ocen > 1 && ocen < 6) {
				pprompp->mark = ocen;
				break;
			}
			else cout << "�� ����� ����� �� ��������������� ������� �� ���� ������� ����� " << endl;
		} while (1);
	}
	else {
		cout << "� ������� �������� � ���� ������ ������������ ���������� ���������" << endl;
	}
}

metods::~metods() {};
metods::metods() {};