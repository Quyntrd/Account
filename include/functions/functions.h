#pragma once

enum AccountType {
	Payment,
	Deposit,
	Credit
};

class Account
{
private:
	AccountType type;
	char FSP;
	int Balance;
	float Percents;
public:
	void set_percents(int Balance, float Percents) {
		this->Balance = Balance;
		if (this->type == Deposit) {
			Balance +=Balance * Percents / 12;
		};
		if (this->type == Credit || Balance < 0) {
			Balance += (-1) * Balance * Percents / 12;
		};
	};
	float get_b() {
		return Balance;
	};
	void set_b(float Balance) {
		this->Balance = Balance;
	};
	Account() {
		this->type = Payment;
		this->FSP[10] = 'TDI';
		this->Balance = 10000;
		this->Percents = 0;
	};
	
	
};
Account MAX_Balance() {
	Account a[10];
	int max = 0;
	int max_i;
	int i;
	for (i = 0; i <= 10;i++) {
		float balance = a[i].get_b();
		if (balance > max) {
			max = balance;
			max_i = i;
		}
	}
	return a[i];
};