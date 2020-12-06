// day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

string setstring(set<char> s)
{
    return string(s.begin(), s.end());
}

int main()
{
    int sum1 = 0;
    int sum2 = 0;

    set<char> q1;
    set<char> q2;
    for (auto c : "abcdefghijklmnopqrstuvwxyz"s) q2.insert(c);

    while (!cin.eof()) {

        string s;
        getline(cin, s);

        if (!s.empty()) {
            for (auto c : s) q1.insert(c);

            set<char> temp;
            set<char> ss(s.begin(), s.end());
            set_intersection(q2.begin(), q2.end(), ss.begin(), ss.end(), inserter(temp, temp.begin()));
            q2.swap(temp);

        }
        else {
            cout << "Group \"" << setstring(q1) << "\" \"" << setstring(q2) << "\"" << endl;

            sum1 += q1.size();
            q1.clear();

            sum2 += q2.size();
            for (auto c : "abcdefghijklmnopqrstuvwxyz"s) q2.insert(c);
        }
    }

    cout << "Group \"" << setstring(q1) << "\" \"" << setstring(q2) << "\"" << endl;

    sum1 += q1.size();
    cout << "Total #1: " << sum1 << endl;

    sum2 += q2.size();
    cout << "Total #2: " << sum2 << endl;
}
