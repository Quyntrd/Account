#pragma once
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
		char FSP[10];
		float Balance;
		float Percents;
		Account(AccountType type, char FSP, float Balance, float Percents);
	public:
		void set_percents(AccountType type, int Balance, float Percents) {
			this->Balance = Balance;
			if (this->type == Deposit) {
				Balance += Balance * Percents / 12;
			};
			if (this->type == Credit || Balance < 0) {
				Balance += (-1) * Balance * Percents / 12;
			};
		};
		float get_per() {
			return Percents;
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
		void add(Account a);
	};



	int i_max_balance(const AccList& a, const float x);
}