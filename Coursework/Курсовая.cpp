#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <fstream>
#include <wincrypt.h>
#include "metods.h"

using namespace std;

void copy_stud(student* stud, student* pprom);
void copy_sem(semestrs* ptecp, semestrs* ppromp);
void copy_pre(predmets* ptecpp, predmets* pprompp);

class file {
protected:
	virtual student* file_load() = 0;
	virtual void file_save(student* pstart) = 0;
public:
	friend void menu();
};

class file_p : public file {
	void file_save(student* pstart) {
		char name[51];
		cout << "Введите название файла" << endl;
		check_potok(1);
		cin.getline(name, 50);
		ofstream file_save(name, ios::binary);
		if (!file_save) {
			cout << "Файл не создан" << endl;
			return;
		}
		if (pstart != nullptr) {
			student* pprom = pstart;
			do {

				file_save.write((char*)pprom, sizeof(student));
				semestrs* pstartp, * ppromp;
				predmets* pstartpp, * pprompp;
				pstartp = pprom->semestr;
				ppromp = pprom->semestr;
				do {
					pstartpp = ppromp->predmet;
					file_save.write((char*)ppromp, sizeof(semestrs));
					pprompp = ppromp->predmet;
					do {
						file_save.write((char*)pprompp, sizeof(predmets));
						pprompp = pprompp->next_predmet;
					} while (pstartpp != pprompp);
					file_save.put('?');
					ppromp = ppromp->next_semestr;
				} while (pstartp != ppromp);
				file_save.put('!');
				pprom = pprom->next_student;
			} while (pstart != pprom);
		}
		file_save.close();
	}
	student* file_load() {
		char name[51];
		cout << "Введите название файла" << endl;
		check_potok(1);
		cin.getline(name, 50);
		ifstream file_load(name, ios::binary);
		if (!file_load) {
			cout << "Файл не найден" << endl;
			return nullptr;
		}

		student* pstart = nullptr, * pprom, * ptec;
		semestrs* pstartp, * ppromp, * ptecp;
		predmets* pstartpp, * pprompp, * ptecpp;
		if (file_load.peek() != EOF) {
			pstart = new(student);
			pprom = pstart;
			while (1) {
				file_load.read((char*)pprom, sizeof(student));
				pprom->semestr = new semestrs;
				ppromp = pprom->semestr;
				pstartp = pprom->semestr;
				do {
					file_load.read((char*)ppromp, sizeof(semestrs));
					ppromp->predmet = new predmets;
					pstartpp = ppromp->predmet;
					pprompp = ppromp->predmet;
					do {
						file_load.read((char*)pprompp, sizeof(predmets));
						if (file_load.peek() != '?') {
							ptecpp = new predmets;
							pprompp->next_predmet = ptecpp;
							pprompp = ptecpp;
						}
						else {
							pprompp->next_predmet = pstartpp;
							file_load.seekg(1, ios::cur);
							break;
						}
					} while (1);
					if (file_load.peek() != '!') {
						ptecp = new semestrs;
						ppromp->next_semestr = ptecp;
						ppromp = ptecp;
					}
					else {
						ppromp->next_semestr = pstartp;
						file_load.seekg(1, ios::cur);
						break;
					}
				} while (1);
				if (file_load.peek() != EOF) {
					ptec = new student;
					pprom->next_student = ptec;
					pprom = ptec;
				}
				else {
					pprom->next_student = pstart;
					break;
				}
			}
		}
		else { cout << "Файл пустой из него нечего загружать" << endl; }
		file_load.close();
		return pstart;
	}
public:
	file_p() {};
	~file_p() {};
	friend void menu();
};

class file_crypt : public file {
	void file_save(student* pstart) {
		HCRYPTPROV discrip;
		HCRYPTKEY key;
		DWORD counts = sizeof(student);
		DWORD countse = sizeof(semestrs);
		DWORD countp = sizeof(predmets);
		DWORD sizebuf = 0;
		student* pprom, * ptec;
		semestrs* pstartp, * ppromp, * ptecp;
		predmets* pstartpp, * pprompp, * ptecpp;
		pprom = new student;
		ppromp = new semestrs;
		pprompp = new predmets;
		ptec = pstart;
		char name[51];
		char name_key[51];
		cout << "Введите название файла" << endl;
		check_potok(1);
		cin.getline(name, 50);
		cout << "Введите название файла ключа" << endl;
		check_potok();
		cin.getline(name_key, 50);
		ofstream file_save(name, ios::binary);
		ofstream file_key(name_key, ios::binary);
		if (!file_save) {
			cout << "Файл не создан" << endl;
			return;
		}
		if (!file_key) {
			cout << "Файл ключа не создан" << endl;
			return;
		}
		if (pstart != nullptr) {
			if (CryptAcquireContext(&discrip, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
				if (CryptGenKey(discrip, CALG_RC4, CRYPT_EXPORTABLE, &key)) {
					do {
						copy_stud(ptec, pprom);
						if (CryptEncrypt(key, 0, true, 0, (BYTE*)pprom, &counts, (DWORD)sizeof(student))) {
							file_save.write((char*)pprom, sizeof(student));
						}
						pstartp = ptec->semestr;
						ptecp = ptec->semestr;
						do {
							pstartpp = ptecp->predmet;
							copy_sem(ptecp, ppromp);
							if (CryptEncrypt(key, 0, true, 0, (BYTE*)ppromp, &countse, (DWORD)sizeof(semestrs))) {
								file_save.write((char*)ppromp, sizeof(semestrs));
							}
							ptecpp = ptecp->predmet;
							do {
								copy_pre(ptecpp, pprompp);
								if (CryptEncrypt(key, 0, true, 0, (BYTE*)pprompp, &countp, (DWORD)sizeof(predmets))) {
									file_save.write((char*)pprompp, sizeof(predmets));
								}
								ptecpp = ptecpp->next_predmet;
							} while (pstartpp != ptecpp);
							file_save.put('?');
							ptecp = ptecp->next_semestr;
						} while (pstartp != ptecp);
						file_save.put('!');
						ptec = ptec->next_student;
					} while (pstart != ptec);
				}
			}
			if (CryptExportKey(key, 0, PLAINTEXTKEYBLOB, 0, NULL, &sizebuf)) {
				BYTE* keys = static_cast<BYTE*>(malloc(sizebuf));
				if (CryptExportKey(key, 0, PLAINTEXTKEYBLOB, 0, keys, &sizebuf)) {
					file_key.write((char*)keys, sizebuf);
				}
			}

		}
		file_key.close();
		file_save.close();
	}
	student* file_load() {
		HCRYPTPROV discrip;
		HCRYPTKEY key;
		DWORD counts = sizeof(student);
		DWORD countse = sizeof(semestrs);
		DWORD countp = sizeof(predmets);
		student* pstart = nullptr, * pprom, * ptec, * ptecc;
		semestrs* pstartp, * ppromp, * ptecp, * ptecpc;
		predmets* pstartpp, * pprompp, * ptecpp, * ptecppc;
		char name[51];
		char name_key[51];
		cout << "Введите название файла" << endl;
		check_potok(1);
		cin.getline(name, 50);
		cout << "Введите название файла ключа" << endl;
		check_potok();
		cin.getline(name_key, 50);
		ifstream file_load(name, ios::binary);
		ifstream file_key(name_key, ios::binary);
		if (!file_load) {
			cout << "Файл не найден" << endl;
			return nullptr;
		}
		if (!file_key) {
			cout << "Файл ключа не найден" << endl;
			return nullptr;
		}
		if (file_load.peek() != EOF) {
			if (CryptAcquireContext(&discrip, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
				BYTE* keys = static_cast<BYTE*>(malloc(28));
				file_key.read((char*)keys, 28);
				if (CryptImportKey(discrip, keys, 28, 0, 0, &key)) {
					pstart = new(student);
					pprom = pstart;
					ptecc = new student;
					ptecpc = new semestrs;
					ptecppc = new predmets;
					while (1) {
						file_load.read((char*)ptecc, sizeof(student));
						if (CryptDecrypt(key, 0, true, 0, (BYTE*)ptecc, &counts)) {
							copy_stud(ptecc, pprom);
						}
						pprom->semestr = new semestrs;
						ppromp = pprom->semestr;
						pstartp = pprom->semestr;
						do {
							file_load.read((char*)ptecpc, sizeof(semestrs));
							if (CryptDecrypt(key, 0, true, 0, (BYTE*)ptecpc, &countse)) {
								copy_sem(ptecpc, ppromp);
							}
							ppromp->predmet = new predmets;
							pstartpp = ppromp->predmet;
							pprompp = ppromp->predmet;
							do {
								file_load.read((char*)ptecppc, sizeof(predmets));
								if (CryptDecrypt(key, 0, true, 0, (BYTE*)ptecppc, &countp)) {
									copy_pre(ptecppc, pprompp);
								}
								if (file_load.peek() != '?') {
									ptecpp = new predmets;
									pprompp->next_predmet = ptecpp;
									pprompp = ptecpp;
								}
								else {
									pprompp->next_predmet = pstartpp;
									file_load.seekg(1, ios::cur);
									break;
								}
							} while (1);
							if (file_load.peek() != '!') {
								ptecp = new semestrs;
								ppromp->next_semestr = ptecp;
								ppromp = ptecp;
							}
							else {
								ppromp->next_semestr = pstartp;
								file_load.seekg(1, ios::cur);
								break;
							}
						} while (1);
						if (file_load.peek() != EOF) {
							ptec = new student;
							pprom->next_student = ptec;
							pprom = ptec;
						}
						else {
							pprom->next_student = pstart;
							break;
						}
					}
				}
			}
		}
		else { cout << "Файл пустой из него нечего загружать" << endl; }
		file_key.close();
		file_load.close();
		return pstart;
	}
public:
	file_crypt() {};
	~file_crypt() {};
	friend void menu();
};

ostream& operator << (ostream& out, student* stud) {
	semestrs* pstart, * pprom;
	predmets* pstartp, * ppromp;
	out << endl;
	out << "Личная информация" << endl;
	out << "id студента: " << stud->id_student << endl;
	out << "ФИО студента: " << stud->fio.surname << " " << stud->fio.name << " " << stud->fio.otchestvo << endl;
	out << "пол: " << stud->pol << endl;
	out << "дата рождения: " << stud->birthday.day << "." << stud->birthday.mounth << "." << stud->birthday.year << endl << endl;

	out << "Информация из института" << endl;
	out << "год поступления: " << stud->univesity.year_post << endl;
	out << "название факультета: " << stud->univesity.facultet << endl;
	out << "название кафедры: " << stud->univesity.kafedra << endl;
	out << "номер группы: " << stud->univesity.group << endl;
	out << "номер зачетки: " << stud->univesity.number_zachet << endl << endl;
	
	pstart = stud->semestr;
	pprom = stud->semestr;
	do {
		pstartp = pprom->predmet;
		out << "Информация о " << pprom->id_semestr << " сесии" << endl;
		ppromp = pprom->predmet;
		do {
			out << ppromp->name_predmet << ": " << ppromp->mark << endl;
			ppromp = ppromp->next_predmet;
		} while (pstartp != ppromp);
		out << endl;
		pprom = pprom->next_semestr;
	} while (pstart != pprom);
	out << "------------------------------------------------------------------------" << endl << endl;
	return out;
}

void copy_stud(student* stud, student *pprom) {
	pprom->id_student = stud->id_student;
	strcpy(pprom->fio.name, stud->fio.name);
	strcpy(pprom->fio.surname, stud->fio.surname);
	strcpy(pprom->fio.otchestvo, stud->fio.otchestvo);
	pprom->pol = stud->pol;
	pprom->birthday.day = stud->birthday.day;
	pprom->birthday.mounth = stud->birthday.mounth;
	pprom->birthday.year = stud->birthday.year;
	strcpy(pprom->univesity.facultet, stud->univesity.facultet);
	strcpy(pprom->univesity.group, stud->univesity.group);
	strcpy(pprom->univesity.kafedra, stud->univesity.kafedra);
	strcpy(pprom->univesity.number_zachet, stud->univesity.number_zachet);
	pprom->univesity.year_post = stud->univesity.year_post;
	pprom->next_student = stud->next_student;
	pprom->semestr = stud->semestr;
}

void copy_sem(semestrs* ptecp,semestrs* ppromp) {
	ppromp->id_semestr = ptecp->id_semestr;
	ppromp->predmet = ptecp->predmet;
	ppromp->next_semestr = ppromp->next_semestr;
}

void copy_pre(predmets* ptecpp, predmets* pprompp) {
	strcpy(pprompp->name_predmet , ptecpp->name_predmet);
	pprompp->mark = ptecpp->mark;
	pprompp->id_predmet = ptecpp->id_predmet;
	pprompp->next_predmet = ptecpp->next_predmet;
}

void menu() {
	student* pstart = nullptr;
	int menus=0;
	metods metod;
	file* files;
	file_p file_prost;
	file_crypt file_crypto;
	while (pstart==nullptr) {
		cout << "1.Создать новый файл" << endl << "2.Загрузить из файла" << endl << "3.Завершить работу" << endl;
		check_potok();
		menus = check_input_int();
		if (menus == 1) {
			pstart = metod.create();
		}
		if (menus == 2) {
			cout << "1.Из обычного файла" << endl << "2.Из шифрованного файла" << endl;
			check_potok();
			menus = check_input_int();
			if (menus == 1) {
				files = &file_prost;
				pstart=files->file_load();
			}
			if (menus == 2) {
				files = &file_crypto;
				pstart=files->file_load();
			}
			menus = 2;
		}
		if (menus == 3) return;
		if (menus < 1 || menus > 3) {
			cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
			check_potok();
			if (check_input_int() > 0) return;
		}
	}
	while (1) {
		cout << "1.Добавить запись в список" << endl << "2.Изменить данные в списке" << endl << "3.Удалить запись из списка" << endl << "4.Выполнить задание варианта" << endl << "5.Распечатать список" << endl << "6.Сохранить данные в файл" << endl << "7.Завершить работу" << endl;
		check_potok();
		menus = check_input_int();
		if (menus == 1) {
			while (1) {
				cout << "1.Запись о студенте" << endl << "2.Запись о семестре" << endl << "3.Запись о предмете" << endl << "4.Выход из этого меню" << endl;
				check_potok();
				menus = check_input_int();
				if (menus == 1) metod.create(pstart);
				if (menus == 2) metod.dobav_semestr(pstart);
				if (menus == 3) metod.dobav_predmet(pstart);
				if (menus == 4) break;
				if (menus < 1 || menus > 4) {
					cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
					check_potok();
					if (check_input_int() > 0) break;
				}
			}
			menus = 1;
		}
		if (menus == 2) metod.change(pstart);
		if (menus == 3) metod.delet(pstart);
		if (menus == 4) metod.menu1_for_zadani(pstart);
		if (menus == 5) metod.print(pstart);
		if (menus == 6) {
			while (1) {
				cout << "1.Сохранить в обычном виде" << endl << "2.Сохранить в зашифрованном виде" << endl << "3.Выход из меню" << endl;
				check_potok();
				menus = check_input_int();
				if (menus == 1) {
					files = &file_prost;
					files->file_save(pstart);
					break;
				}
				if (menus == 2) {
					files = &file_crypto;
					files->file_save(pstart);
					break;
				}
				if (menus == 3) break;
				if (menus < 1 || menus > 3) {
					cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
					check_potok();
					if (check_input_int() > 0) break;
				}
			}
			menus = 6;
		}
		if (menus == 7) return;
		if (menus < 1 || menus > 7) {
			cout << "Вы не выбрали ниодного пункта меню. Хотите выйти? да-1 , нет-0" << endl;
			check_potok();
			if (check_input_int() > 0) return;
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu();
}