#ifndef __CALR_H__
#define __CALR_H__
#include <bits/stdc++.h>
using namespace std;
struct production
{
    string sym;
    int psize;
    vector<string> arr;
     bool operator<(const production L) const {
                        return sym<L.sym;
                }
};
#endif