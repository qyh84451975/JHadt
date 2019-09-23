#ifndef TABLENN_H_
#define TABLENN_H_

#include <string>
using std::string;

class TableTannisPlayer {
private:
    string firstname;
    string lastname;
    bool hasTable;

public:
    TableTannisPlayer(const string &fn = "none", const string &ln = "none", bool hasTable = false);
    void Name() const;
    bool HasTable() const { return hasTable; }
    void ResetTable(bool v) { hasTable = v; }
};

class RatePlayer : public TableTannisPlayer {
private:
    unsigned int rating;

public:
    RatePlayer(unsigned int r = 0, const string &fn = "none", const string &ln = "none", bool ht = false);
    RatePlayer(unsigned int r, const TableTannisPlayer &tp);
    unsigned int Rating() const { return rating; }
    void ResetRating(unsigned int v) { rating = v; }
};

#endif