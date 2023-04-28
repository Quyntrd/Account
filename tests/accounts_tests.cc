#include <gtest/gtest.h>

#include <accounts/accounts.h>

TEST(AccountsTests, Dep_ComputeValue) {
    const auto dep1 = Account::create_Deposit("TDI", 10000, 7.5);
    const auto dep2 = Account::create_Deposit("KRI", 11200, 11);

    EXPECT_NEAR(dep1->compute_value(dep1->get_bal(), dep1->get_per()), 16250, 1);
    EXPECT_NEAR(dep2->compute_value(dep2->get_bal(), dep2->get_per()), 21467, 1);
}

TEST(AccountTests, Pay_ComputeValue) {
    const auto pay1 = Account::create_Payment("TDI", 10000, 0);
    const auto pay2 = Account::create_Payment("KRI", 13000, 0);

    EXPECT_EQ(pay1->compute_value(pay1->get_bal(), pay1->get_per()), 10000);
    EXPECT_EQ(pay2->compute_value(pay2->get_bal(), pay2->get_per()), 13000);
}
TEST(AccountTests, Cred_ComputeValue) {
    const auto cred1 = Account::create_Credit("TDI", -10000, 13);
    const auto cred2 = Account::create_Credit("KRI", -5000, 17);

    EXPECT_NEAR(cred1->compute_value(cred1->get_bal(), cred1->get_per()), -20833, 1);
    EXPECT_NEAR(cred2->compute_value(cred2->get_bal(), cred2->get_per()), -12083, 1);
}
TEST(AccountListTests, IndexOfMaxBalance) {
    const auto dep1 = Account::create_Deposit("TDI", 10000, 7.5);
    const auto dep2 = Account::create_Deposit("KRI", 11200, 11);
    const auto pay1 = Account::create_Payment("TDI", 10000, 0);
    const auto pay2 = Account::create_Payment("KRI", 13000, 0);
    const auto cred1 = Account::create_Credit("TDI", -10000, 13);
    const auto cred2 = Account::create_Credit("KRI", -5000, 17);
    AccList alist;
    alist.add(dep1);
    alist.add(dep2);
    alist.add(pay1);
    alist.add(pay2);
    alist.add(cred1);
    const auto index = i_max_balance(alist);
    ASSERT_EQ(index, 6);
}

TEST(AccountListTests, Remove) {
    AccList alist = AccList();
    const auto dep1 = Account::create_Deposit("TDI", 10000, 7.5);
    const auto dep2 = Account::create_Deposit("KRI", 11200, 11);
    const auto pay1 = Account::create_Payment("TDI", 10000, 0);
    const auto pay2 = Account::create_Payment("KRI", 13000, 0);
    const auto cred1 = Account::create_Credit("TDI", -10000, 13);
    const auto cred2 = Account::create_Credit("KRI", -5000, 17);
    alist.add(dep1);
    alist.add(dep2);
    alist.add(pay1);
    alist.add(pay2);
    alist.add(cred1);
    alist.add(cred2);
    alist.remove(0);
    alist.remove(0);
    int siz = alist.size();
    float bal = alist[0]->get_bal();
    EXPECT_EQ(bal, 10000);
    EXPECT_EQ(siz, 7);
}   
TEST(AccountListTests, Insert) {
    AccList alist = AccList();
    const auto dep1 = Account::create_Deposit("TDI", 10000, 7.5);
    const auto dep2 = Account::create_Deposit("KRI", 11200, 11);
    const auto pay1 = Account::create_Payment("TDI", 10000, 0);
    const auto pay2 = Account::create_Payment("KRI", 13000, 0);
    const auto cred1 = Account::create_Credit("TDI", -10000, 13);
    const auto cred2 = Account::create_Credit("KRI", -5000, 17);
    alist.insert(0, dep1);
    alist.insert(1, dep2);
    alist.insert(2, pay1);
    alist.insert(3, pay2);
    alist.insert(4, cred1);
    float bal = alist[3]->get_bal();
    float bal1 = alist[4]->get_bal();
    EXPECT_EQ(bal, 13000);
    EXPECT_EQ(bal1, -10000);
}

TEST(AccountListTests, OperatorCopy) {
    AccList alist1 = AccList();
    AccList alist2 = AccList();
    const auto dep1 = Account::create_Deposit("TDI", 10000, 7.5);
    const auto dep2 = Account::create_Deposit("KRI", 11200, 11);
    alist1.insert(0, dep1);
    alist2.insert(0, dep2);
    alist1 = alist2;
    EXPECT_EQ(alist1[0]->get_bal(), dep2->get_bal());
}