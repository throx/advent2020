#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <regex>

#include "../shared/shared.h"

using namespace std;

const regex INPUT_R("(.*) \\(contains (.*)\\)");

typedef set<string> StringSet;

int main()
{
    StringSet allings;
    StringSet allallgs;
    map<StringSet, StringSet> input;

    string s;
    while (getline(cin, s)) {
        smatch sm;
        regex_match(s.cbegin(), s.cend(), sm, INPUT_R);
        auto ings = split(sm[1], " ");
        auto allgs = split(sm[2], ", ");
        input[StringSet(ings.begin(), ings.end())] = StringSet(allgs.begin(), allgs.end());
        allings.insert(ings.begin(), ings.end());
        allallgs.insert(allgs.begin(), allgs.end());
    }

    // First, any allergen in the list must be in one of the ingreds.  So, map each
    // allergen to the ingred list, intersection all the other ingred lists for that
    // allergen.
    map<string, StringSet> filter;
    for (auto& k : input) {
        for (auto allg : k.second) {
            auto it = filter.find(allg);
            if (it == filter.end()) {
                filter[allg] = k.first;
            }
            else {
                StringSet inter;
                set_intersection(it->second.begin(), it->second.end(), k.first.begin(), k.first.end(), inserter(inter, inter.begin()));
                it->second.swap(inter);
            }
        }
    }

    // Now, any we know need to be taken away from all the others
    map<string, string> i2a, a2i;
    while (i2a.size() < filter.size()) {
        for (auto& x : filter) {
            if (x.second.size() == 1) {
                string val = *x.second.begin();
                i2a[val] = x.first;
                a2i[x.first] = val;
                for (auto& y : filter) {
                    if (x.first != y.first) {
                        if (y.second.find(val) != y.second.end()) {
                            y.second.erase(val);
                        }
                    }
                }
            }
        }
    }

    for (auto& k : i2a) {
        cout << k.first << " contains " << k.second << endl;
    }

    // work out soln 1
    int sol1 = 0;
    for (auto& i : input) {
        for (auto& ing : i.first) {
            if (i2a.find(ing) == i2a.end()) {
                ++sol1;
            }
        }
    }
    cout << "Part 1 = " << sol1 << endl;
    cout << "Part 2 = ";

    bool first = true;
    for (auto& k : a2i) {
        if (first) {
            first = false;
        }
        else {
            cout << ",";
        }
        cout << k.second;
    }
    cout << endl;
}

