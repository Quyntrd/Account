#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#define ItemPtr shared_ptr<Account> 
using namespace std;

	class Account
	{
	public:
		void set_full_name(string full_name);
		void set_balance(float balance);
		string get_full_name() const;
		float get_balance() const;

		virtual float compute_value() const = 0;

		virtual unique_ptr<Account> clone() const = 0;
		virtual bool equals(shared_ptr<Account> other) const = 0;
		virtual void print(ostream& stream) const = 0;
		virtual ~Account() = default;
	protected:
		string full_name;
		float balance;
		Account() = default;
		Account(const Account& account) = default;
		Account& operator=(const Account& other) = default;
	};
	class Payment : public Account {
	public:

		Payment();
		Payment(string full_name, float balance);
		~Payment() = default;

		unique_ptr<Account> clone() const override;
		bool equals(shared_ptr<Account> other) const override;
		void print(ostream& out) const override;
		friend istream& operator>>(istream& in, shared_ptr<Payment>& item);
		float compute_value() const override;
	};
	class Deposit : public Account {
		float percents;
	public:
		void set_percents(float percents);
		float get_percents() const;

		Deposit();
		Deposit(string full_name, float balance, float percents);
		~Deposit() = default;

		unique_ptr<Account> clone() const override;
		bool equals(shared_ptr<Account> other) const override;
		void print(ostream& out) const override;
		friend istream& operator>>(istream& in, shared_ptr<Deposit>& item);
		float compute_value() const override;
	};
	class Credit : public Account {
		float percents;
	public:
		void set_percents(float percents);
		float get_percents() const;

		Credit();
		Credit(string full_name, float balance, float percents);
		~Credit() = default;

		unique_ptr<Account> clone() const override;
		bool equals(shared_ptr<Account> other) const override;
		void print(ostream& out) const override;
		friend istream& operator>>(istream& in, shared_ptr<Credit>& item);
		float compute_value() const override;
	};
	

	class AccList {

	private:

		vector<ItemPtr> _account;

	public:
		AccList();
		AccList(vector<ItemPtr> accounts);
		AccList(const AccList& other);

		ItemPtr get_acc_by_i(int index);
		int size();

		ItemPtr operator[](int index) const;
		ItemPtr& operator[](int index);
		AccList& operator=(AccList other);
		void insert(int index, ItemPtr account);
		void erase(int index);
		void clear();
		void print_current(int index);
		void show_all();
		void Swap(AccList& other) noexcept;
		friend bool operator==(const AccList& lhs, const AccList& rhs);
		friend bool operator!=(const AccList& lhs, const AccList& rhs);
		int find_with_max_balance();
	};