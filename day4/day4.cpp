#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <set>

using namespace std;

const set<string> REQARGS = {
    "byr",
    "iyr",
    "eyr",
    "hgt",
    "hcl",
    "ecl",
    "pid"};

const set<string> OPTARGS = { "cid" };

const regex HCL_REGEX("^#[a-f0-9]{6}$");
const regex PID_REGEX("^[0-9]{9}$");
const regex HGT_REGEX("^(\\d+)(cm|in)$");

const set<string> EYECOL = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

const map<string, function<bool(string)> > VALIDATOR = {
    { "byr", [](string v) {auto y = stoi(v);  return y >= 1920 && y <= 2002; } },
    { "iyr", [](string v) {auto y = stoi(v);  return y >= 2010 && y <= 2020; } },
    { "eyr", [](string v) {auto y = stoi(v);  return y >= 2020 && y <= 2030; } },
    { "hgt", [](string v) {
                            smatch m;
                            if (!regex_match(v, m, HGT_REGEX)) {
                                return false;
                            }
                            auto h = stoi(m[1]);
                            if (m[2] == "cm"s) {
                                return h >= 150 && h <= 193;
                            }
                            else if (m[2] == "in"s) {
                                return h >= 59 && h <= 76;
                            }
                            return false;
                          } },
    { "hcl", [](string v) {return regex_search(v, HCL_REGEX); } },
    { "ecl", [](string v) {return EYECOL.find(v) != EYECOL.end(); } },
    { "pid", [](string v) {return regex_search(v, PID_REGEX); } }
};

class Record
{
private:
    map<string, string> m_params;
    bool m_valid1;
    bool m_valid2;

public:
    Record(const string& src)
    {
        regex r("(\\w+):(\\S+)");
        sregex_iterator rit(src.begin(), src.end(), r);
        sregex_iterator rend;

        while (rit != rend) {
            smatch s = *rit;
            string k = s[1];
            string v = s[2];
            m_params[k] = v;
            ++rit;
        }
        
        validate();
    }
    
    void validate()
    {
        m_valid1 = 
            all_of(REQARGS.begin(), REQARGS.end(), [&](auto arg) { return m_params.find(arg) != m_params.end(); }) &&
            all_of(m_params.begin(), m_params.end(), [&](auto arg) { return REQARGS.find(arg.first) != REQARGS.end() || OPTARGS.find(arg.first) != OPTARGS.end(); });

        m_valid2 = m_valid1 &&
            all_of(m_params.begin(), m_params.end(), [&](auto arg) { return VALIDATOR.find(arg.first) == VALIDATOR.end() || VALIDATOR.find(arg.first)->second(arg.second); });
    }
    
    bool isValid1()
    {
        return m_valid1;
    }
    
    bool isValid2()
    {
        return m_valid2;
    }

    void dump()
    {
        cout << (m_valid1 ? "V" : "I");
        cout << (m_valid2 ? "V" : "I");
        cout << " - ";
        for (auto x: m_params) {
            cout << x.first << ":" << x.second << " ";
        }
        cout << endl;
    }
};

int main()
{
    string buf;
    
    list<Record> records;
    
    while (!cin.eof()) {
        string s;
        getline(cin, s);
        if (s.empty()) {
            Record r(buf);
            records.push_back(r);
            buf.clear();
        }
        else {
            buf = buf + s + " ";
        }
    }
    
    if (!buf.empty()) {
        Record r(buf);
        records.push_back(r);
    }
    
    for (auto r: records) {
        r.dump();
    }

    cout << "Total Valid by args = " << count_if(records.begin(), records.end(), [](auto x) { return x.isValid1();  }) << endl;
    cout << "Total Valid = " << count_if(records.begin(), records.end(), [](auto x) { return x.isValid2();  }) << endl;
}