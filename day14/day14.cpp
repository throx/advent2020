#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <map>
#include <numeric>
#include <set>

using namespace std;

const regex MASK_R("mask = ([01X]{36})");
const regex MEM_R("mem\\[(\\d+)\\] = (\\d+)");

void add_perms(set<__int64>& m, string s) {
    auto n = s.find('X');
    if (n != string::npos) {
        s[n] = '0';
        add_perms(m, s);
        s[n] = '1';
        add_perms(m, s);
    }
    else {
        m.insert(stoll(s, nullptr, 2));
    }
}

int main()
{
    string s;
    __int64 mask_ones = 0;
    __int64 mask_zeros = -1LL;
    __int64 mask_x0 = -1LL;
    set<__int64> mask_x1;

    map<__int64, __int64> mem1;
    map<__int64, __int64> mem2;

    while (getline(cin, s)) {
        smatch sm;
        if (regex_match(s.cbegin(), s.cend(), sm, MASK_R)) {
            string ones = sm[1];
            string zeros = sm[1];
            replace(ones.begin(), ones.end(), 'X', '0');
            replace(zeros.begin(), zeros.end(), 'X', '1');
            mask_ones = stoll(ones, nullptr, 2);
            mask_zeros = stoll(zeros, nullptr, 2);

            string xs = sm[1];
            replace(xs.begin(), xs.end(), '0', '1');
            replace(xs.begin(), xs.end(), 'X', '0');
            mask_x0 = stoll(xs, nullptr, 2);

            xs = sm[1];
            replace(xs.begin(), xs.end(), '1', '0');
            mask_x1.clear();
            add_perms(mask_x1, xs);
        }
        else if (regex_match(s.cbegin(), s.cend(), sm, MEM_R)) {
            __int64 pos = stoll(sm[1]);
            __int64 val = stoll(sm[2]);
            __int64 val1 = val & mask_zeros | mask_ones;
            mem1[pos] = val1;

            __int64 pos2 = pos & mask_x0 | mask_ones;
            for (auto x1 : mask_x1) {
                mem2[pos2 | x1] = val;
            }
        }
    }

    __int64 sum1 = accumulate(mem1.begin(), mem1.end(), 0LL, [](auto x, auto y) { return x + y.second; });
    cout << "Memory Sum #1 = " << sum1 << endl;

    __int64 sum2 = accumulate(mem2.begin(), mem2.end(), 0LL, [](auto x, auto y) { return x + y.second; });
    cout << "Memory Sum #2 = " << sum2 << endl;
}
