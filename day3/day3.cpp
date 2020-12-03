// day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

__int64 checktrees(vector<string>& map, int dx, int dy)
{
    int x = 0;
    int y = 0;
    __int64 trees = 0;

    while (y < map.size()) {
        int rx = x % map[y].length();
        if (map[y][rx] == '#') {
            ++trees;
        }

        x += dx;
        y += dy;
    }

    cout << "  Slope (" << dx << "," << dy << ") = " << trees << endl;
    return trees;
}

int main()
{
    string s;
    vector<string> map;

    while (!cin.eof()) {
        getline(cin, s);
        map.push_back(s);
    }

    __int64 part1 = checktrees(map, 3, 1);
    cout << "Part 1 = " << part1 << endl;

    __int64 part2 =
        checktrees(map, 1, 1) *
        checktrees(map, 3, 1) *
        checktrees(map, 5, 1) *
        checktrees(map, 7, 1) *
        checktrees(map, 1, 2);

    cout << "Part 2 = " << part2 << endl;
}
