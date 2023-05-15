#include <gtest/gtest.h>

#include <accounts/accounts.h>

TEST(AccountTests, AccountConstructorTest) {
	Payment acc1 = Payment("Vladimir Zhirinovsky", 100000);
	EXPECT_EQ(acc1.get_full_name(), "Vladimir Zhirinovsky");
}
TEST(AccountTests, AccountConstructorTest2) {
	Payment acc1 = Payment("Vladimir Zhirinovsky", 100000);
	EXPECT_EQ(acc1.get_balance(), 100000);
}
TEST(AccountTests, AccountConstructorTest3) {
	Deposit acc1 = Deposit("Vitaliy Cal", 100000, 13);
	EXPECT_EQ(acc1.get_full_name(), "Vitaliy Cal");
}
TEST(AccountTests, AccountConstructorTest4) {
	Deposit acc1 = Deposit("Vitaliy Cal", 100000, 13);
	EXPECT_EQ(acc1.get_balance(), 100000);
}
TEST(AccountTests, AccountConstructorTest5) {
	Deposit acc1 = Deposit("Vitaliy Cal", 100000, 13);
	EXPECT_EQ(acc1.get_percents(), 13);
}
TEST(AccountTests, AccountConstructorTest6) {
	Credit acc1 = Credit("Daniil Terebilkin", 12345, 14);
	EXPECT_EQ(acc1.get_full_name(), "Daniil Terebilkin");
}
TEST(AccountTests, AccountConstructorTest7) {
	Credit acc1 = Credit("Daniil Terebilkin", 12345, 14);
	EXPECT_EQ(acc1.get_balance(), 12345);
}
TEST(AccountTests, AccountConstructorTest8) {
	Credit acc1 = Credit("Daniil Terebilkin", 12345, 14);
	EXPECT_EQ(acc1.get_percents(), 14);
}
TEST(AccountTest, AccountComputeValue) {
	Payment acc1 = Payment("Vladimir Zhirinovsky", 100000);
	EXPECT_EQ(acc1.compute_value(), 100000);
}
TEST(AccountTest, AccountComputeValue1) {
	Deposit acc1 = Deposit("Vitaliy Cal", 100000, 13);
	EXPECT_NEAR(acc1.compute_value(), 101083, 1);
}
TEST(AccountTest, AccountComputeValue2) {
	Credit acc1 = Credit("Daniil Terebilkin", 12345, 14);
	EXPECT_NEAR(acc1.compute_value(), 12200, 1);
}
TEST(AccountListTest, AccountListErase) {
	AccList AL = AccList();
	AL.erase(0);
	EXPECT_EQ(AL.size(), 4);
	EXPECT_EQ(AL[0]->compute_value(), 0);
}
TEST(AccountListTest, AccountListClear) {
	AccList AL = AccList();
	AL.clear();
	EXPECT_EQ(AL.size(), 0);
}
TEST(AccountListTest, AccountListMaxBal) {
	AccList AL;
	AL.insert(0, make_shared<Payment>("Vladimir Zhirinovsky", 100000));
	AL.insert(1, make_shared<Payment>("Vladimir Zhirinovsky", 100000));
	AL.insert(2, make_shared<Deposit>("Vitaliy Cal", 10000, 13));
	AL.insert(3, make_shared<Deposit>("Vitaliy Cal", 10000, 13));
	AL.insert(4, make_shared<Payment>("Vladimir Zhirinovsky", 100000));
	EXPECT_EQ(AL.find_with_max_balance(), 0);
}
TEST(ExceptionTest, ExceptionIndexOut) {
	AccList AL = AccList();
	EXPECT_THROW(AL[-1]->compute_value(), std::runtime_error);
	EXPECT_THROW(AL[10]->compute_value(), std::runtime_error);
}
TEST(ExceptionTest, ExceptionEmptyTest) {
	AccList AL = AccList();
	for (int i = 0; i < 5; ++i) {
		AL.erase(0);
	}
	EXPECT_THROW(AL.erase(1), std::runtime_error);
}