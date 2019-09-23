#include "../include/tablenn.h"
#include <iostream>

TableTannisPlayer::TableTannisPlayer(const string &fn, const string &ln, bool ht)
    : firstname(fn), lastname(ln), hasTable(ht) {}
void TableTannisPlayer::Name() const { std::cout << lastname << ", " << firstname << std::endl; }

RatePlayer::RatePlayer(unsigned int r, const string &fn, const string &ln, bool ht)
    : TableTannisPlayer(fn, ln, ht) {
    rating = r;
}

RatePlayer::RatePlayer(unsigned int r, const TableTannisPlayer &tp)
    : TableTannisPlayer(tp), rating(r) {}