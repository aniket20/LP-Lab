#ifndef __SLR_H__
#define __SLR_H__
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