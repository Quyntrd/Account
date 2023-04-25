#include <accounts/accounts.h>
#include <stdexcept>
#include <cassert>
using namespace acc;
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


bool acc::operator==(const Account& lhs, const Account& rhs) { //ѕока не уверен, по какому признаку сравнивать
	return
		lhs.get_bal() == rhs.get_bal() &&
		lhs.get_fsp() == lhs.get_fsp() &&
		lhs.get_type() == rhs.get_type() &&
		lhs.get_per() == lhs.get_per();
}

bool acc::operator!=(const Account& lhs, const Account& rhs) {
	return !(lhs == rhs);
}

int acc::i_max_balance(const AccList& a) {
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

AccList::AccList() :
	_Acc(nullptr),
	_size(0)
{ }

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