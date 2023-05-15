#pragma warning(disable:6386)
#include <accounts/accounts.h>
#include <stdexcept>
#include <cassert>
#include <string>
#include <iostream>
using namespace std;
void Account::set_full_name(string full_name) {
	this->full_name = full_name;
}
void Account::set_balance(float balance) {
	this->balance = balance;
}

void Deposit::set_percents(float percents) {
	this->percents = percents;
}
void Credit::set_percents(float percents) {
	this->percents = percents;
}
string Account::get_full_name() const {
	return full_name;
}
float Account::get_balance() const {
	return balance;
}
float Deposit::get_percents() const {
	return percents;
}
float Credit::get_percents() const {
	return percents;
}
Payment::Payment() {
	full_name = "default";
	balance = 0;
}
Deposit::Deposit() {
	full_name = "default";
	balance = 0;
	percents = 0;
}
Credit::Credit() {
	full_name = "default";
	balance = 0;
	percents = 0;
}
Payment::Payment(string full_name, float balance) {
	this->full_name = full_name;
	this->balance = balance;
}
Deposit::Deposit(string full_name, float balance, float percents) {
	this->full_name = full_name;
	this->balance = balance;
	this->percents = percents;
}
Credit::Credit(string full_name, float balance, float percents) {
	this->full_name = full_name;
	this->balance = balance;
	this->percents = percents;
}
AccList::AccList() {
	for (int i = 0; i < 5; ++i) {
		_account.push_back(make_shared<Payment>());
	}
}
AccList::AccList(vector<ItemPtr> accounts) {
	_account = vector<ItemPtr>(accounts.size());
	for (int i = 0; i < _account.size(); ++i) {
		this->_account[i] = make_shared<Payment>();
	}
}
AccList::AccList(const AccList& other) {
	this->_account = other._account;
}
float Payment::compute_value() const {
	return balance;
}
float Deposit::compute_value() const {
	float bal = balance + balance * percents / 100 / 12;
	return bal;
}
float Credit::compute_value() const {
	float bal = balance - balance * percents / 100 / 12;
	return bal;
}
unique_ptr<Account> Payment::clone() const {
	return make_unique<Payment>(full_name, balance);
}
unique_ptr<Account> Deposit::clone() const {
	return make_unique<Deposit>(full_name, balance, percents);
}
unique_ptr<Account> Credit::clone() const {
	return make_unique<Credit>(full_name, balance, percents);
}
void Payment::print(ostream& out) const {
	out << "Payment " << full_name << ' ' << balance;
}
void Deposit::print(ostream& out) const {
	out << "Deposit " << full_name << ' ' << balance << ' ' << percents;
}
void Credit::print(ostream& out) const {
	out << "Credit " << full_name << ' ' << balance<< ' ' << percents;
}
int AccList::find_with_max_balance() {
	int index = 0;
	float max_balance = 0;
	for (int i = 0; i < _account.size(); ++i)
	{
		float cur_balance = _account[i]->get_balance();
		if (cur_balance > max_balance)
		{
			index = i;
			max_balance = cur_balance;
		}
	}
	return index;
}
void AccList::Swap(AccList& other) noexcept {
	swap(_account, other._account);
}
bool Payment::equals(shared_ptr<Account> other) const {
	const auto d_other = dynamic_pointer_cast<Payment>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (full_name == d_other->full_name && balance == d_other->balance);
}
bool Deposit::equals(shared_ptr<Account> other) const {
	const auto d_other = dynamic_pointer_cast<Deposit>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (full_name == d_other->full_name && balance == d_other->balance && percents == d_other->percents);
}
bool Credit::equals(shared_ptr<Account> other) const {
	const auto d_other = dynamic_pointer_cast<Credit>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (full_name == d_other->full_name && balance == d_other->balance && percents == d_other->percents);
}
bool operator==(const AccList& lhs, const AccList& rhs) {
	return ((lhs._account) == (rhs._account));
}
bool operator!=(const AccList& lhs, const AccList& rhs) {
	return !(lhs == rhs);
}

AccList& AccList::operator=(AccList other) {
	Swap(other);
	return *this;
}
ItemPtr AccList::operator[](int index) const {
	if (index < 0 || index >= _account.size())
	{
		throw runtime_error("Index out of range.");
	}
	return _account[index];
}
ItemPtr& AccList::operator[](int index) {
	if (index < 0 || index >= _account.size())
	{
		throw runtime_error("Index out of range.");
	}
	return _account[index];
}
ItemPtr AccList::get_acc_by_i(int index) {
	return _account[index];
}
int AccList::size() {
	return static_cast<int>(_account.size());
}
void AccList::insert(int index, ItemPtr account) {
	if (index < 0 || index > _account.size()) {
		throw runtime_error("Index out of range.");
	}
	_account.insert(_account.begin() + index, account);
}
void AccList::erase(int index) {
	if (index < 0 || index > _account.size()) {
		throw runtime_error("List is empty.");
	}
	_account.erase(_account.begin() + index);
}
void AccList::clear() {
	_account.clear();
}

istream& operator>>(istream& in, shared_ptr<Payment>& item) {
	cout << "Enter full name:\n";
	in >> item->full_name;
	cout << "Enter balance:\n";
	in >> item->balance;
	return in;
}
istream& operator>>(istream& in, shared_ptr<Deposit>& item) {
	cout << "Enter full name:\n";
	in >> item->full_name;
	cout << "Enter balance:\n";
	in >> item->balance;
	cout << "Enter percents:\n";
	in >> item->percents;
	return in;
}
istream& operator>>(istream& in, shared_ptr<Credit>& item) {
	cout << "Enter full name:\n";
	in >> item->full_name;
	cout << "Enter balance:\n";
	in >> item->balance;
	cout << "Enter percents:\n";
	in >> item->percents;
	return in;
}
void AccList::print_current(int index) {
	_account[index]->print(cout);
}
void AccList::show_all() {
	cout << "Current list:\n";
	for (int i = 0; i < _account.size(); ++i) {
		cout << i << ':';
		print_current(i);
		cout << endl;
	}
}