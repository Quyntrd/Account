#include <accounts/accounts.h>
#include <stdexcept>
using namespace acc;
using namespace std;

Account Account::create_Payment(const string fsp, const float balance, const float percents) {
	return Account(AccountType::Payment, fsp, balance, percents);
}

Account Account::create_Deposit(const string fsp, const float balance, const float percents) {
	return Account(AccountType::Deposit, fsp, balance, percents);
}

Account Account::create_Credit(const string fsp, const float balance, const float percents) {
	return Account(AccountType::Credit, fsp, balance, percents);
}

Account::Account(): type(AccountType::Payment), FSP("TDI"), Balance(10000), Percents(0){}

Account::Account(const AccountType _type, const string fsp, const float balance, const float percents): type(_type), FSP(fsp), Balance(balance), Percents(percents){}

AccountType Account::get_type() const {
	return type;
}
float Account::get_bal() const {
	return Balance;
}
float Account::get_per() const {
	return Percents;
}
Account AccList::operator[](int index) const {
	if (index < 0 || _sizes <= index) {
		throw out_of_range("[FunctionList::operator[]] Index is out of range");
	}
	return _Acc[index];
}

int acc::i_max_balance(const AccList& a) {
	int max_i = -1;
	float max_balance = 0;
	const int n = a.size();
	for (int i = 0; i < n; i++) {
		const float bal = a[i].get_bal();
		if (max_i == -1 || max_balance < bal) {
			max_i = i;
			max_balance = bal;
		}
	}
	return max_i;
}

void AccList::add(const Account a) {
	if (_sizes == CAP) {
		throw runtime_error("[AccList::add] Capacity is reached.");
	}
	_Acc[_sizes] = a;
	++_sizes;
}

void AccList::remove(int index) {
	for (int i = index; i < _sizes; i++) {
		_Acc[i] = _Acc[i + 1];
	}
	--_sizes;
}

void AccList::insert(int index, Account a) {
	if(_sizes == CAP) {
		throw runtime_error("[AccList::add] Capacity is reached.");
	}
	for (int i = _sizes; i > index; i--) {
		_Acc[i] = _Acc[i - 1];
	}
	_Acc[index] = a;
	++_sizes;
}

float Account::compute_value(float bal, float perc) const{
	switch (type) {
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

AccList::AccList(): _sizes(0){}
int AccList::size() const {
	return _sizes;
}