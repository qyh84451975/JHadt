/*
 * @Author: qyh
 * @Date:   2019-09-23 06:47:34
 * @Last Modified by:   qyh
 * @Last Modified time: 2019-09-23 07:38:08
 */

// #include "../include/brass.h"
// #include <iostream>

// using namespace std;

// int main() {
//     Brass qyh("钱玉航", 381299, 4000.00);
//     BrassPlus qj("钱剑", 382288, 3000.00);
//     qyh.ViewAcc();
//     cout << endl;
//     qj.ViewAcc();
//     cout << endl;
//     cout << "钱剑账户存1000元" << endl;
//     qj.Deposit(1000.00);
//     cout << "更新后的账户余额：" << qj.Balance() << "元" << endl;
//     cout << "钱玉航账户取4200元" << endl;
//     qyh.WithDraw(4200.00);
//     cout << "更新后的账户余额：" << qyh.Balance() << "元" << endl;
//     cout << "钱剑账户取4300元" << endl;
//     qj.WithDraw(4300.00);
//     qj.ViewAcc();
//     return 0;
// }
// 在公有继承模型下指向父类的指针数组，那么这个父类指针既可以指向自己也可以指向子类对象，因此用一个数组即可实现多态
#include "../include/brass.h"
#include <iostream>
#include <string>
using namespace std;
const int CLIENTS = 4;

int main(int argc, char const *argv[]) {
    Brass *p_clients[CLIENTS];
    string temp;
    long tempnum;
    double tempbal;
    char kind;

    for (int i = 0; i < CLIENTS; i++) {
        cout << "输入客户姓名：";
        getline(cin, temp);
        cout << "输入客户账户名：";
        cin >> tempnum;
        cout << "输入余额：";
        cin >> tempbal;
        cout << "输入1进入Brass, 输入2进入BrassPlus：";
        while (cin >> kind && (kind != '1' && kind != '2'))
            cout << "叫你输1或2, 你非要输个其他的？：" << endl;
        if (kind == '1')
            p_clients[i] = new Brass(temp, tempnum, tempbal);
        else {
            double tmax, trate;
            cout << "透支额度：";
            cin >> tmax;
            cout << "输入利率（小数就行了）,算了，给你举个例子吧：0.11225  ：";
            cin >> trate;
            p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
        }
        while (cin.get() != '\n')
            continue;
    }
    cout << endl;
    for (int i = 0; i < CLIENTS; i++) {
        p_clients[i]->ViewAcc();
        cout << endl;
    }
    for (int i = 0; i < CLIENTS; i++) {
        delete p_clients[i];
    }
    cout << "结束，收逼" << endl;
    return 0;
}