#include <accounts/accounts.h>
#include <stdexcept>
#include <cassert>
#include <iostream>
using namespace std;

AccountPtr Account::create_Payment(const string fsp, const float balance, const float percents) {
	return new Account(AccountType::Payment, fsp, balance, percents);
}

AccountPtr Account::create_Deposit(const string fsp, const float balance, const float percents) {
	return new Account(AccountType::Deposit, fsp, balance, percents);
}

AccountPtr Account::create_Credit(const string fsp, const float balance, const float percents) {
	return new Account(AccountType::Credit, fsp, balance, percents);
}
AccountPtr Account::clone() const {
	return new Account(Type, FSP, Balance, Percents);
}
Account::Account() {
	Type = AccountType::Payment;
	FSP = "KRI";
	Balance = 10000;
	Percents = 0;
}
Account::Account(const AccountType type, const string fsp, const float balance, const float percents): Type(type), FSP(fsp), Balance(balance), Percents(percents){}

AccountType Account::get_type() const {
	return Type;
}
float Account::get_bal() const {
	return Balance;
}
float Account::get_per() const {
	return Percents;
}
string Account::get_fsp() const {
	return FSP;
}
AccountPtr AccList::operator[](const int index) const {
	if (index < 0 || _size <= index) {
		throw out_of_range("[AccList::operator[]] Index is out of range");
	}
	return _Acc[index];
}

void Account::Swap(Account other) noexcept {
	swap(Type, other.Type);
	swap(FSP, other.FSP);
	swap(Balance, other.Balance);
	swap(Percents, other.Percents);
}
bool operator==(const Account& lhs, const Account& rhs) { //ѕока не уверен, по какому признаку сравнивать
	return
		lhs.get_bal() == rhs.get_bal() &&
		lhs.get_fsp() == lhs.get_fsp() &&
		lhs.get_type() == rhs.get_type() &&
		lhs.get_per() == lhs.get_per();
}

bool operator!=(const Account& lhs, const Account& rhs) {
	return !(lhs == rhs);
}

int i_max_balance(const AccList& a) {
	int max_i = -1;
	float max_balance = 0;
	const auto n = a.size();
	for (int i = 0; i < n; i++) {
		const auto bal = a[i]->get_bal();
		if (max_i == -1 || max_balance < bal) {
			max_i = i;
			max_balance = bal;
		}
	}
	return max_i;
}

float Account::compute_value(float bal, float perc) const{
	switch (Type) {
	case AccountType::Deposit:
		return bal + (bal * perc / 12);
	case AccountType::Credit:
		return -(-bal + (-bal * perc / 12));
	case AccountType::Payment:
		return bal;
	default:
		throw runtime_error("[Account::set_percents] Invalid function type");
	}
}

AccList::AccList()
{
	this->_size = 3;
	_Acc = new Account * [_size];
	for (int i = 0; i < _size; ++i) {
		_Acc[i] = new Account();
	}
}

AccList::AccList(const AccList& other):
	_Acc(new AccountPtr[other._size]), _size(other._size)
{
	for (int i = 0; i < _size; ++i) {
		_Acc[i] = other[i]->clone();
	}	
}

AccList& AccList::operator=(const AccList& rhs) {
	AccList copy(rhs);
	copy.swap(*this);
	return *this;
}

int AccList::size() const {
	return _size;
}

void AccList::swap(AccList& other) {
	std::swap(this->_Acc, other._Acc);
	std::swap(this->_size, other._size);
}
AccList::~AccList() {
	for (int i = 0; i < _size; i++) {
		delete _Acc[i];
	}
	delete[] _Acc;
}

void AccList::add(AccountPtr const a) {
	auto new_accs = new AccountPtr[_size + 1];

	for (int i = 0; i < _size; ++i) {
		new_accs[i] = _Acc[i];
	}
	new_accs[_size] = a;
	
	delete[] _Acc;
	_Acc = new_accs;
	++_size;
}

void AccList::remove(int index) {
	for (int i = index; i < _size; i++) {
		_Acc[i] = _Acc[i + 1];
	}
	--_size;
}

void AccList::insert(int index, AccountPtr a) {
	auto new_accs = new AccountPtr[_size + 1];
	
	if (index < 0 || index >= _size) {
		throw std::runtime_error("Index out of range");
	}
	new_accs[index] = a;
	for (int i = 0; i < index; ++i) {
		new_accs[i] = _Acc[i];
	}
	
	for (int i = _size; i > index; --i) {
		new_accs[i] = _Acc[i - 1];
	}
	

	delete[] _Acc;
	_Acc = new_accs;
	++_size;
}

void AccList::show_all() {
	cout << "Index " << "Type " << "FSP " << "Balance " << "Percents " << endl;
	for (int i = 0; i < _size; i++) {
		if (_Acc[i]->get_type() == Payment) {
			cout << i << "::" << "Payment " << _Acc[i]->get_fsp() << " " << _Acc[i]->get_bal() << " " << _Acc[i]->get_per() << endl;
		}
		else if (_Acc[i]->get_type() == Deposit) {
			cout << i << "::" << "Deposit " << _Acc[i]->get_fsp()<< " " << _Acc[i]->get_bal()<< " " << _Acc[i]->get_per() << endl;
		}
		else if (_Acc[i]->get_type() == Credit) {
			cout << i << "::" << "Credit " << _Acc[i]->get_fsp()<< " " << _Acc[i]->get_bal()<< " " << _Acc[i]->get_per() << endl;
		} 
	}
}
istream& operator>>(std::istream& in, AccountType& item_type) {
	int type;
	in >> type;
	switch (type) {
	case 0:
		item_type = Deposit;
		break;
	case 1:
		item_type = Payment;
		break;
	case 2:
		item_type = Credit;
		break;
	default:
		throw std::runtime_error("Wrong type exception");

	}
	return in;
}

istream& operator>>(istream& in, Account& item) {
	cout << "Choose your account:\n 0 - Deposit\n 1 - Payment \n 2 - Credit\n";
	in >> item.Type;
	cout << "Enter Full Name:\n";
	in >> item.FSP;
	cout << "Enter Balance:\n";
	in >> item.Balance;
	cout << "Enter Percents:\n";
	in >> item.Percents;
	return in;
}
ostream& operator<<(ostream& out, const Account& other) {
	if (other.Type == Deposit) {
		return out << "Account(" << "Account Type: Deposit" << "Full name: " << other.FSP << "Balance: " << other.Balance << "Percents: " << other.Percents << ")";
	}
	else if (other.Type == Payment) {
		return out << "Account(" << "Account Type: Payment" << "Full name: " << other.FSP << "Balance: " << other.Balance << "Percents: " << other.Percents << ")";
	}
	else if (other.Type == Credit) {
		return out << "Account(" << "Account Type: Credit" << "Full name: " << other.FSP << "Balance: " << other.Balance << "Percents: " << other.Percents << ")";
	}
}
