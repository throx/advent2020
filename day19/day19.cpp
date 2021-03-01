#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// A rule is either a sequence of other rules, or a sequence of characters.
// Characters are stored as negative, because I'm cheap.
typedef list<int> Rule;

// Alternative Rules (list of lists)
typedef list<Rule> Rules;

// RulesMap is a map of a ruleset number to a list of alternative Rules
typedef map<int, Rules> RulesMap;

// Check if a particular ruleset matches the string starting at position 'pos', and
// return the set of positions the rule may match up to (because rules may match
// in multiple ways).  If the rule matches nothing, then just return a set containing
// the current position.
set<int> match_rule(RulesMap& rm, int rulenum, const string& sample, int pos)
{
    //cout << "Testing " << rulenum << " " << endl;

    // The positions this rule matches up to.
    set<int> result;

    // Loop through the rules that are part of this ruleset
    for (auto& rule : rm[rulenum]) {

        //cout << "Testing " << rulenum << " variant ";
        //for (int i : rule) cout << i << " ";
        //cout << endl;

        // Init the set with the current position, which is always an
        // option (ie don't use the ruleset).
        set<int> sp = { pos };

        // Match each part in turn
        for (int sub : rule) {

            // If it's a literal...
            if (sub < 0) {

                // Check all the potential positions, if any of them
                // match the literal then add in the next spot because
                // the ruleset can consume it.  Need to use temporary
                // because iterating and inserting are bad together
                set<int> sp_;
                for (auto p : sp) {
                    if (sample[p] == -sub) {
                        sp_.insert(p + 1);
                    }
                }
                sp.swap(sp_);
            }
            else {

                // Otherwise, loop through the positions and see if the
                // subrule matches.  If so, then we add in the set of
                // potential positions returned.
                set<int> sp_;
                for (auto p : sp) {
                    set<int> matched = match_rule(rm, sub, sample, p);
                    sp_.insert(matched.begin(), matched.end());
                }
                sp.swap(sp_);
            }
        }

        // Add the set of potentials we've discovered to the results.
        result.insert(sp.begin(), sp.end());
    }

    //cout << "  #" << rulenum << " has " << result.size() << " matches" << endl;
    return result;
}

// Match rule #0 against the entire sample string
bool match_all(RulesMap& rm, const string& sample)
{
    auto result = match_rule(rm, 0, sample, 0);
    return any_of(result.begin(), result.end(), [&](int x) {return x == sample.length(); });
}

// THE MAIN FUNCTION!!!!
int main()
{
    string s;
    RulesMap rm;

    // Parse Rules
    while (true) {
        getline(cin, s);

        // Finish on blank line
        if (s.empty()) break;

        // Ignore comments
        if (s[0] == '#') continue;

        // Read in ruleset number
        int num;
        num = stoi(s);

        // Split to after the colon
        s = s.substr(s.find(':') + 1);
        Rules rs;
        Rule r;

        // Loop through alternates
        while (true) {

            // Eat whitespace
            while (!s.empty() && s[0] == ' ') s = s.substr(1);

            // End when eaten everything
            if (s.empty()) break;

            // If it's an alternate, add current rule to set and re-init
            if (s[0] == '|') {
                rs.push_back(r);
                r.clear();
                s = s.substr(1);
            }

            // If it's a literal, add negative to rule
            else if (s[0] == '"') {
                r.push_back(-s[1]);
                s = s.substr(3);
            }

            // Otherwise just add the rule number
            else {
                size_t pos;
                int num = stoi(s, &pos);
                r.push_back(num);
                s = s.substr(pos);
            }
        }

        // Add the last one from the loop
        rs.push_back(r);
        rm[num] = rs;
    }

    // Parse samples from input
    vector<string> samples;
    while (getline(cin, s)) {
        samples.push_back(s);
    }

    // Loop through all the samples checking them
    int ok = 0;
    for (auto& sample : samples) {
        if (match_all(rm, sample)) {
            cout << sample << endl;
            ++ok;
        }
    }

    cout << "Num ok (1) = " << ok << endl;

    // For part 2, replace the rules 8 and 11 with recursive versions
    ok = 0;
    rm[8] = { {42}, {42, 8} };
    rm[11] = { {42, 31}, {42, 11, 31} };

    // Once again, loop through the samples
    for (auto& sample : samples) {
        if (match_all(rm, sample)) {
            cout << sample << endl;
            ++ok;
        }
    }

    cout << "Num ok (2) = " << ok << endl;
}
