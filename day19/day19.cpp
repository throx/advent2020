#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef list<int> Rule;
typedef list<Rule> Rules;
typedef map<int, Rules> RulesMap;

set<int> match_rule(RulesMap& rm, int rulenum, const string& sample, int pos)
{
    //cout << "Testing " << rulenum << " " << endl;

    // Total matches
    set<int> result;

    // Match any rule
    for (auto& rule : rm[rulenum]) {

        //cout << "Testing " << rulenum << " variant ";
        //for (int i : rule) cout << i << " ";
        //cout << endl;

        // Match each sub in turn
        set<int> sp = { pos };
        for (int sub : rule) {
            if (sub < 0) {
                set<int> sp_;
                for (auto p : sp) {
                    if (sample[p] == -sub) {
                        sp_.insert(p + 1);
                    }
                }
                sp.swap(sp_);
            }
            else {
                set<int> sp_;
                for (auto p : sp) {
                    set<int> matched = match_rule(rm, sub, sample, p);
                    sp_.insert(matched.begin(), matched.end());
                }
                sp.swap(sp_);
            }
        }

        result.insert(sp.begin(), sp.end());
    }

    //cout << "  #" << rulenum << " has " << result.size() << " matches" << endl;
    return result;
}

bool match_all(RulesMap& rm, const string& sample)
{
    auto result = match_rule(rm, 0, sample, 0);
    return any_of(result.begin(), result.end(), [&](int x) {return x == sample.length(); });
}

int main()
{
    string s;
    RulesMap rm;

    while (true) {
        getline(cin, s);
        if (s.empty()) break;
        if (s[0] == '#') continue;

        int num;
        num = stoi(s);

        s = s.substr(s.find(':') + 1);
        Rules rs;
        Rule r;
        while (true) {
            while (!s.empty() && s[0] == ' ') s = s.substr(1);
            if (s.empty()) break;
            if (s[0] == '|') {
                rs.push_back(r);
                r.clear();
                s = s.substr(1);
            }
            else if (s[0] == '"') {
                r.push_back(-s[1]);
                s = s.substr(3);
            }
            else {
                size_t pos;
                int num = stoi(s, &pos);
                r.push_back(num);
                s = s.substr(pos);
            }
        }
        rs.push_back(r);
        rm[num] = rs;
    }

    vector<string> samples;
    while (getline(cin, s)) {
        samples.push_back(s);
    }

    int ok = 0;
    for (auto& sample : samples) {
        if (match_all(rm, sample)) {
            cout << sample << endl;
            ++ok;
        }
    }

    cout << "Num ok (1) = " << ok << endl;

    ok = 0;
    rm[8] = { {42}, {42, 8} };
    rm[11] = { {42, 31}, {42, 11, 31} };

    for (auto& sample : samples) {
        if (match_all(rm, sample)) {
            cout << sample << endl;
            ++ok;
        }
    }

    cout << "Num ok (2) = " << ok << endl;
}
