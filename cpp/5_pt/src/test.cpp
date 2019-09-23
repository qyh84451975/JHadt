#include "../include/tablenn.h"
#include <iostream>
using namespace std;
int main() {
    TableTannisPlayer player1("qian", "yuhang", true);
    TableTannisPlayer player2("qian", "jian", false);
    RatePlayer rateplayer1(1140, "zuo", "mengting", true);
    rateplayer1.Name();
    // player1.Name();
    if (rateplayer1.HasTable()) {
        cout << "有桌子" << endl;
    } else {
        cout << "没桌子" << endl;
    }
    player2.Name();
    if (player2.HasTable()) {
        cout << "有桌子" << endl;
    } else {
        cout << "没桌子" << endl;
    }
    RatePlayer rateplayer2(1121, player2);
    rateplayer2.Name();
    cout << " " << rateplayer2.Rating() << endl;
}