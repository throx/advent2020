#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

int main()
{
    vector<string> actions;

    int x = 0;
    int y = 0;
    int f = 0;
    const string DIRS = "ESWN"s;

    {
        string s;
        while (getline(cin, s)) {
            actions.push_back(s);
        }
    }

    for (auto s: actions) {
        char c = s[0];
        int d = stoi(s.substr(1));

        if (c == 'F') c = DIRS[f];
        switch (c) {
        case 'N':
            y += d;
            break;
        case 'S':
            y -= d;
            break;
        case 'E':
            x += d;
            break;
        case 'W':
            x -= d;
            break;
        case 'L':
            f = f - (d / 90);
            while (f < 0) f += 4;
            break;
        case 'R':
            f = f + (d / 90);
            while (f > 3) f -= 4;
            break;
        }
    }

    cout << "Dist = " << abs(x) + abs(y) << endl;

    int dx = 10;
    int dy = 1;
    x = 0;
    y = 0;
    for (auto s : actions) {
        char c = s[0];
        int d = stoi(s.substr(1));

        switch (c) {
        case 'N':
            dy += d;
            break;
        case 'S':
            dy -= d;
            break;
        case 'E':
            dx += d;
            break;
        case 'W':
            dx -= d;
            break;
        case 'L':
            for (int i = 0; i < d; i += 90) {
                swap(dx, dy);
                dx = -dx;
            }
            break;
        case 'R':
            for (int i = 0; i < d; i += 90) {
                swap(dx, dy);
                dy = -dy;
            }
            break;
        case 'F':
            for (int i = 0; i < d; ++i) {
                x += dx;
                y += dy;
            }
        }
    }

    cout << "Dist = " << abs(x) + abs(y) << endl;

}
