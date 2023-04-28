#pragma once
#include <string>
using namespace std;

	enum AccountType {
		Payment,
		Deposit,
		Credit
	};
	class Account;

	using AccountPtr = Account*;

	class Account
	{
	private:
		AccountType Type;

		string FSP;

		float Balance;

		float Percents;

		

	public:
		Account();
		Account(AccountType type, string fsp, float balance, float percents);
		static AccountPtr create_Payment(string fsp, float balance, float percents);

		static AccountPtr create_Deposit(string fsp, float balance, float percents);

		static AccountPtr create_Credit(string fsp, float balance, float percents);

		float compute_value(float bal, float perc) const;

		AccountType get_type() const;

		string get_fsp() const;

		float get_per() const;

		float get_bal() const;
		void Swap(Account other)noexcept;
		AccountPtr clone() const;
		friend istream& operator>>(istream& in, Account& item);
		friend ostream& operator<<(ostream& out, const Account& item);
	};

	bool operator==(const Account& lhs, const Account& rhs);
	bool operator!=(const Account& lhs, const Account& rhs);

	class AccList {
	private:
		AccountPtr* _Acc; 
		int _size;
	public:
		AccList(); 
		AccList(const AccList& other);
		int size() const;

		AccountPtr operator[](int index) const;

		AccList& operator=(const AccList& rhs);

		void swap(AccList& other);

		void add(AccountPtr a);

		void remove(int index);

		void insert(int index, AccountPtr a);
		void show_all();

		~AccList();
	};



	int i_max_balance(const AccList& a); 
