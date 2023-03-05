#include <accounts/accounts.h>
#include <stdexcept>
using namespace acc;
using namespace std;

Account AccList::operator[](int index) const {
	if (index < 0 || _sizes <= index) {
		throw out_of_range("[FunctionList::operator[]] Index is out of range");
	}

}

int i_max_balance(const AccList& a, const float x) {
	int max_i = -100;
	float max_balance = 0;
	const int n = a.size();
	for (int i = 0; i < n; i++) {
		const float bal = a[i].get_b();
		if (max_i == -100 || max_balance < bal) {
			max_i = i;
			max_balance = bal;
		}
	}
	return max_i;
}

void AccList::add(const Account a) {
	if (_sizes == CAP) {
		throw runtime_error("[AccList::add] Capasity is reached.");
	}
	_Acc[_sizes] = a;
	++_sizes;
}