#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <set>

using namespace std;

const regex RANGE_R("(.+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
struct Range
{
    string what;
    int from1;
    int to1;
    int from2;
    int to2;
    set<int> possible;
    int pos;

    Range(const string& w, int f1, int t1, int f2, int t2) : what(w), from1(f1), to1(t1), from2(f2), to2(t2), pos(-1) {}
    bool InRange(int x) { return (x >= from1 && x <= to1) || (x >= from2 && x <= to2); }
};

vector<int> Parse(const string& s) {
    vector<int> r;
    stringstream ss(s);
    string x;
    while (getline(ss, x, ',')) {
        r.push_back(stoi(x));
    }
    return r;
}

string CSV(const vector<int>& v) {
    if (v.empty()) return ""s;
    stringstream ss;
    auto it = v.begin();
    ss << *it;
    ++it;
    while (it != v.end()) {
        ss << ",";
        ss << *it;
        ++it;
    }

    return ss.str();
}

int main()
{
    vector<Range> rules;
    
    string s;
    while (true) {
        getline(cin, s);
        if (s.empty()) break;

        smatch sm;
        regex_match(s.cbegin(), s.cend(), sm, RANGE_R);
        rules.push_back(Range(sm[1], stoi(sm[2]), stoi(sm[3]), stoi(sm[4]), stoi(sm[5])));
    }
    cout << "Loaded " << rules.size() << " Rules" << endl;

    getline(cin, s);  // your ticket
    getline(cin, s);
    auto myticket = Parse(s);
    cout << "Loaded Ticket with " << myticket.size() << " Fields" << endl;

    getline(cin, s);  //blank
    getline(cin, s);  // nearby tickets
    vector<vector<int>> tickets;
    while (getline(cin, s)) {
        tickets.push_back(Parse(s));
    }
    cout << "Loaded " << tickets.size() << " Other Tickets" << endl;

    int sum = 0;
    vector<vector<int>> goodtickets;
    for (auto& t: tickets) {
        bool ticket_ok = true;
        for (auto& v: t) {
            bool ok = false;
            for (auto& r : rules) {
                if (r.InRange(v)) {
                    ok = true;
                }
            }

            if (!ok) {
                sum += v;
                ticket_ok = false;
            }
        }
        if (ticket_ok) {
            goodtickets.push_back(t);
        }
    }

    cout << "Error rate = " << sum << endl;
    cout << "Loaded " << goodtickets.size() << " Good Tickets" << endl;

    // Init rules
    set<int> possible;
    for (int i = 0; i < myticket.size(); ++i) {
        possible.insert(i);
    }
    for (auto& r : rules) {
        r.possible = possible;
    }

    goodtickets.push_back(myticket);

    // Mark possible mappings
    for (auto& t : goodtickets) {
        for (int v_pos = 0; v_pos < t.size(); ++v_pos) {
            int v = t[v_pos];
            for (auto& r : rules) {
                if (!r.InRange(v)) {
                    r.possible.erase(v_pos);
                    cout << "Excluding " << v_pos << " from " << r.what << " due to ticket " << CSV(t) << endl;
                }
            }
        }
    }

    // Now deduce mapping
    int mapped = 0;
    while (mapped < rules.size()) {
        for (auto& r : rules) {
            if (r.possible.size() == 1) {
                r.pos = *(r.possible.begin());
                for (auto& rr : rules) {
                    rr.possible.erase(r.pos);
                }
                ++mapped;
            }
        }
    }

    cout << endl;
    // Now print my ticket
    __int64 product = 1;
    for (auto& r : rules) {
        cout << r.what << ": " << myticket[r.pos] << endl;
        if (r.what.substr(0, 9) == "departure"s) {
            product *= myticket[r.pos];
        }
    }
    cout << endl;
    cout << "Product = " << product << endl;
}
