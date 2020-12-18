#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <list>
#include <map>
#include <ctype.h>

using namespace std;

char gettoken(string line, int& pos)
{
    while (pos < line.length() && line[pos] == ' ') ++pos;
    if (pos < line.length()) {
        char tok = line[pos];
        ++pos;
        return tok;
    }
    return 0;
}

__int64 eval(string line, int mode)
{
    // Shunting yard algo
    list<char> ops;
    list<char> rpn;
    map<char, int> prec;
    prec['+'] = mode;
    prec['*'] = 1;
    prec['('] = -1;

    int pos = 0;
    char tok;
    while ((tok = gettoken(line, pos)) != 0) {
        if (isdigit(tok)) {
            rpn.push_back(tok);
        }
        else if (tok == '+' || tok == '*') {
            while (!ops.empty() && (prec[ops.front()] >= prec[tok])) {
                rpn.push_back(ops.front());
                ops.pop_front();
            }
            ops.push_front(tok);
        }
        else if (tok == '(') {
            ops.push_front(tok);
        }
        else if (tok == ')') {
            while (ops.front() != '(') {
                rpn.push_back(ops.front());
                ops.pop_front();
            }
            ops.pop_front();
        }
    }

    while (!ops.empty()) {
        rpn.push_back(ops.front());
        ops.pop_front();
    }

    list<__int64> stack;
    while (!rpn.empty()) {
        tok = rpn.front();
        rpn.pop_front();

        if (isdigit(tok)) {
            stack.push_front(tok - '0');
        }
        else if (tok == '+') {
            __int64 a = stack.front();
            stack.pop_front();
            a += stack.front();
            stack.pop_front();
            stack.push_front(a);
        }
        else if (tok == '*') {
            __int64 a = stack.front();
            stack.pop_front();
            a *= stack.front();
            stack.pop_front();
            stack.push_front(a);
        }
    }

    return stack.front();
}

int main()
{
    vector<string> lines;
    string s;
    while (getline(cin, s)) {
        lines.push_back(s);
    }

    __int64 sum1 = 0;
    __int64 sum2 = 0;
    for (auto& line : lines) {
        __int64 answer1 = eval(line, 1);
        sum1 += answer1;
        __int64 answer2 = eval(line, 2);
        sum2 += answer2;
        cout << line << " = " << answer1 << ", " << answer2 << endl;
    }

    cout << "Sum 1 = " << sum1 << endl;
    cout << "Sum 2 = " << sum2 << endl;
}
