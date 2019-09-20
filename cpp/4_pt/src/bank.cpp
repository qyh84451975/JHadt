#include "../include/queue.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

const int MIN_PER_HR = 60;

bool newcustomer(double x);

int main() {
    Item temp;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
    std::srand(std::time(0));
    cout << "开始之前，来个小小的测试，先输入一个数，我来判断它是不是2的n次方：";
    int test;
    cin >> test;
    if (temp.isRight(test)) {
        cout << "是的！" << endl;
    } else {
        cout << "不是的" << endl;
    }
    cout << "输入队列最大长度：";
    int qs;
    cin >> qs;
    Queue line(qs);

    cout << "模拟几小时，请输入：";
    int hours;
    cin >> hours;

    long cyclelimit = MIN_PER_HR * hours;
    cout << "请输入每小时客户的平均人数：";
    double perhour;
    cin >> perhour;
    double min_per_cust;
    min_per_cust = MIN_PER_HR / perhour;

    long turnaways = 0;
    long customers = 0;
    long served    = 0;
    long sum_line  = 0;
    int  wait_time = 0;
    long line_wait = 0;

    for (int cycle = 0; cycle < cyclelimit; cycle++) {
        if (newcustomer(min_per_cust)) {
            if (line.isfull())
                turnaways++;
            else {
                customers++;
                temp.set(cycle);
                line.enqueue(temp);
            }
        }
        if (wait_time <= 0 && !line.isempty()) {
            line.dequeue(temp);
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();
            served++;
        }
        if (wait_time > 0)
            wait_time--;
        sum_line += line.queuecount();
    }
    if (customers > 0) {
        cout << "customers accepted: " << customers << endl;
        cout << "  customers served: " << served << endl;
        cout << "         turnaways: " << turnaways << endl;
        cout << "average queue size: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << (double)sum_line / cyclelimit << endl;
        cout << " average wait time: "
             << (double)line_wait / served << " minutes" << endl;
    } else {
        cout << "No customers!" << endl;
    }
    cout << "Done!" << endl;
    return 0;
}

bool newcustomer(double x) {
    return (std::rand() * x / RAND_MAX < 1);
}