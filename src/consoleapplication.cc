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
	AccList AL = AccList();
	shared_ptr<Payment> payment = make_shared<Payment>();
	shared_ptr<Deposit> deposit = make_shared<Deposit>();
	shared_ptr<Credit> credit = make_shared<Credit>();
	int input = -1;
	int idx, type;
	while (input != 6) {
		menu();
		cin >> input;
		switch (input) {
		case 1:
			system("cls");
			AL.show_all();
			cout << "Insert the index: ";
			cin >> idx;
			cout << "Choose type (0 - Payment, 1 - Deposit, 2 - Credit)\n";
			cin >> type;
			switch (type) {
			case 0: 
				cin >> payment;
				AL.insert(idx, payment);
				break;
			case 1:
				cin >> deposit;
				AL.insert(idx, deposit);
				break;
			case 2:
				cin >> credit;
				AL.insert(idx, credit);
				break;
			}
			break;
		case 2:
			system("cls");
			AL.show_all();
			cout << "Insert the index: ";
			cin >> idx;
			AL.erase(idx);
			break;
		case 3:
			system("cls");
			AL.show_all();
			break;
		case 4:
			system("cls");
			AL.show_all();
			idx = AL.find_with_max_balance();
			cout << "Index of max balance: " << idx << endl;
			break;
		case 5: 
			system("cls");
			AL.show_all();
			cout << "Insert the index: ";
			cin >> idx;
			int b = AL[idx]->compute_value();
			cout << "Computed value: " << b << endl;
		}
		if (input != 6)
			system("pause");
	}
}