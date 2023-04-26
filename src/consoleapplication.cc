#include <iostream>
#include <windows.h>
#include <accounts/accounts.h>
#include <stdexcept>
#include <string>

void menu() {
	system("cls");
	cout << "Welcome, please, choose from 1 to 6" << endl;
	cout << "1 - Insert an element into the list at the specified index" << endl;
	cout << "2 - Remove an element from the list at the specified index" << endl;
	cout << "3 - Display the account list" << endl;
	cout << "4 - Search in the list of the first account with the maximum balance" << endl;
	cout << "5 - Account balance calculation" << endl;
	cout << "6 - End session" << endl;
	cout << "> ";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleCP(1251);
	AccList Accs = AccList();
	Account item = Account();
	int input = -1;
	int idx;
	while (input != 6) {
		menu();
		cin >> input;
		switch (input) {
		case 1:
			system("cls");
			Accs.show_all();
			cout << "Insert the index: ";
			cin >> idx;
			cin >> item;
			Accs.insert(idx, &item);
			break;
		case 2:
			system("cls");
			Accs.show_all();
			cout << "Insert the index: ";
			cin >> idx;
			Accs.remove(idx);
			break;
		case 3:
			system("cls");
			Accs.show_all();
			break;
		case 4:
			system("cls");
			Accs.show_all();
			idx = i_max_balance(Accs);
			cout << "Index of max balance: " << idx << endl;
			break;
		case 5: 
			system("cls");
			Accs.show_all();
			cout << "Insert the index: ";
			cin >> idx;
			Account* a = Accs[idx];
			int b = a->compute_value(a->get_bal(), a->get_per());
			cout << "Computed value: " << b << endl;
		}
		if (input != 6)
			system("pause");
	}
}