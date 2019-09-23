/*
 * @Author: qyh
 * @Date:   2019-09-23 05:49:12
 * @Last Modified by:   qyh
 * @Last Modified time: 2019-09-23 07:04:45
 */
#include "../include/brass.h"
#include <iostream>
using namespace std;

// format stuff
typedef ios_base::fmtflags format;
typedef streamsize precis;
format setFormat();
void restore(format f, precis p);

// Brass methods
Brass::Brass(const string &s, long an, double bal) {
    fullName = s;
    accNum   = an;
    balance  = bal;
}

void Brass::Deposit(double amt) {
    if (amt < 0) {
        cout << "取钱失败，取消操作！" << endl;
    } else {
        balance += amt;
    }
}

void Brass::WithDraw(double amt) {
    format initialState = setFormat();
    precis prec         = cout.precision(2);
    if (amt < 0) {
        cout << "你存负的钱，神经病吗？" << endl;
    } else if (amt <= balance) {
        balance -= amt;
    } else {
        cout << "你准备取 " << amt << " "
             << "元, "
             << "你觉得你能取出来比你账户余额还多的钱吗？"
             << "建议办张信用卡！" << endl;
    }
    restore(initialState, prec);
}

double Brass::Balance() const { return balance; }

void Brass::ViewAcc() const {
    format initialState = setFormat();
    precis prec         = cout.precision(2);
    cout << "客户：" << fullName << endl;
    cout << "账号：" << accNum << endl;
    cout << "余额：" << balance << "元" << endl;
    restore(initialState, prec);
}
// BrassPlus methods

BrassPlus::BrassPlus(const string &s, long an, double bal, double ml, double r)
    : Brass(s, an, bal) {
    maxLoan  = ml;
    owewBank = 0.0;
    rate     = r;
}

BrassPlus::BrassPlus(const Brass &ba, double ml, double r) : Brass(ba) {
    maxLoan  = ml;
    owewBank = 0.0;
    rate     = r;
}
//重定义ViewAcc
void BrassPlus::ViewAcc() const {
    format initialState = setFormat();
    precis prec         = cout.precision(2);

    Brass::ViewAcc();
    cout << "最大贷款：" << maxLoan << "元" << endl;
    cout << "欠钱：" << owewBank << "元" << endl;
    cout.precision(3);
    cout << "贷款利率：" << 100 * rate << "%" << endl;
    restore(initialState, prec);
}

//重定义WithDraw   取钱
void BrassPlus::WithDraw(double amt) {
    format initialState = setFormat();
    precis prec         = cout.precision(2);

    double bal = Balance();
    if (amt <= bal) {
        Brass::WithDraw(amt);
    } else if (amt <= bal + maxLoan - owewBank) {
        double advance = amt - bal;
        owewBank += advance * (1.0 + rate);
        cout << "透支了：" << advance << "元" << endl;
        cout << "Finance Charge: " << advance * rate << "元" << endl;
        Deposit(advance);
        Brass::WithDraw(amt);
    } else {
        cout << "信用卡限额，操作取消" << endl;
    }
    restore(initialState, prec);
}

format setFormat() { return cout.setf(ios_base::fixed, ios_base::floatfield); }

void restore(format f, precis p) {
    cout.setf(f, ios_base::floatfield);
    cout.precision(p);
}