#ifndef BRASS_H_
#define BRASS_H_

#include <string>

using namespace std;

class Brass {
private:
    string fullName;
    long accNum;
    double balance; //余额
public:
    Brass(const string &s = "NullBody", long acc = -1, double bal = 0.0);
    void Deposit(double amt);
    virtual void WithDraw(double amt);
    double Balance() const;
    virtual void ViewAcc() const;
    virtual ~Brass() {}
};

class BrassPlus : public Brass {
private:
    double maxLoan;
    double rate;
    double owewBank;

public:
    BrassPlus(const string &s = "NullBody", long acc = -1, double bal = 0.0, double ml = 500,
              double r = 0.11125);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.11125);
    virtual void ViewAcc() const;
    virtual void WithDraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; }
    void ResetOwes() { owewBank = 0; }
};

#endif