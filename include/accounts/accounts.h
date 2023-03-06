#pragma once
#include <string>
using namespace std;
namespace acc {
	enum AccountType {
		Payment,
		Deposit,
		Credit
	};

	class Account
	{
	private:
		AccountType type;
		string FSP = "   ";
		float Balance;
		float Percents;
		Account(AccountType type, string FSP, float Balance, float Percents);
	public:
		static Account create_Payment(string fsp, float balance, float percents);
		static Account create_Deposit(string fsp, float balance, float percents);
		static Account create_Credit(string fsp, float balance, float percents);
		float compute_value(float bal, float perc) const;
		AccountType get_type() const;
		float get_per() const;
		float get_bal() const;
		Account();
	};

	class AccList {
	public:
		static const int CAP = 10;
	private:
		Account _Acc[CAP];
		int _sizes;
	public:
		AccList();

		int size() const;

		Account operator[](int index) const;

		void add(const Account a);

		void remove(int index);

		void insert(int index, Account a);

		

	};



	int i_max_balance(const AccList& a);
}