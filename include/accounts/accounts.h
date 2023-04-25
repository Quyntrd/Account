#pragma once
#include <string>
using namespace std;
namespace acc {
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

		Account(AccountType type, string fsp, float balance, float percents);

	public:
		static AccountPtr create_Payment(string fsp, float balance, float percents);

		static AccountPtr create_Deposit(string fsp, float balance, float percents);

		static AccountPtr create_Credit(string fsp, float balance, float percents);

		float compute_value(float bal, float perc) const;

		AccountType get_type() const;

		string get_fsp() const;

		float get_per() const;

		float get_bal() const;

		AccountPtr clone() const;
	};

	bool operator==(const Account& lhs, const Account& rhs);
	bool operator!=(const Account& lhs, const Account& rhs);

	class AccList {
	private:
		AccountPtr* _Acc; // Массив указателей
		int _size;
	public:
		AccList(); //Конструктор по умолчанию
		AccList(const AccList& other);
		int size() const;

		AccountPtr operator[](int index) const; //Перегрузка оператор квадратных скобок

		AccList& operator=(const AccList& rhs);

		void swap(AccList& other);

		void add(AccountPtr a); //Добавление записи

		void remove(int index); //Удаление записи по индексу

		void insert(int index, AccountPtr a); // Вставка записи по индексу	

		~AccList(); // Декструктор
	};



	int i_max_balance(const AccList& a); //Поиск записи в массиве по максимольному балансу
}