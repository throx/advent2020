#include <iostream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include <map>

using namespace std;

class Record
{
private:
    map<string, string> m_params;
    bool m_valid;
    
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
        
    }
    
    void isValid()
    {
        return m_valid;
    }
    
    void dump()
    {
        cout << (valid ? "Valid" : "Invalid");
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
            buf = buf + s;
        }
    }
    
    if (!buf.empty()) {
        Record r(buf);
        records.push_back(r);
    }
    
    for (auto r: records) {
        r.dump();
    }
}