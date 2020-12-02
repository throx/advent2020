#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    int num_valid1 = 0;
    int num_valid2 = 0;

    regex r(R"#((\d+)-(\d+) (.): (.+))#");

    while (!cin.eof()) {
        string line;
        getline(cin, line);

        smatch m;
        if (!regex_match(line, m, r)) {
            return 1;
        }

        int low = stoi(m[1]);
        int high = stoi(m[2]);
        char c = m[3].str()[0];
        string pass = m[4];

        auto count = count_if(pass.begin(), pass.end(), [&](auto x) { return x == c; });
        if (low <= count && high >= count) {
            ++num_valid1;
        }

        if (pass.length() >= high) {
            if ((pass[low - 1] == c) != (pass[high - 1] == c)) {
                ++num_valid2;
            }
        }
    }

    cout << "Number valid (part 1) = " << num_valid1 << endl;
    cout << "Number valid (part 2) = " << num_valid2 << endl;
}
