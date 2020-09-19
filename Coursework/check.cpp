#include "check.h"

int check_input_int() {
	int check;
	do {
		cin >> check;
		if (!cin) {
			cout << "Вы ввели не целое число " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else break;
	} while (1);
	return check;
}

void check_potok() {
	if (!cin) {
		cin.clear();
		cin.ignore(1000, '\n');
	}
}

void check_potok(int i) {
	if (!cin) {
		cin.clear();
		cin.ignore(1000, '\n');
	}
	else cin.ignore();
}