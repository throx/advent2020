#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <map>

#include "../shared/Point.h"

using namespace std;

// For debugging
template<int N>
void Dump(const set<Point<N>>& g)
{
    if (g.size() == 0) {
        cout << "EMPTY!" << endl << endl;
        return;
    }
    auto xlim = minmax_element(g.begin(), g.end(), [](const Point<N>& a, const Point<N>& b) { return a[0] < b[0]; });
    auto ylim = minmax_element(g.begin(), g.end(), [](const Point<N>& a, const Point<N>& b) { return a[1] < b[1]; });

    for (auto y = ylim.first->at(1); y <= ylim.second->at(1); ++y) {
        for (auto x = xlim.first->at(0); x <= xlim.second->at(0); ++x) {
            if (g.find(Point<N>({ x, y })) != g.end()) {
                cout << '#';
            }
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

template<int N>
set<Point<N>> Load(vector<string> input)
{
    set<Point<N>> grid;

    for (int y = 0; y < input.size(); ++y) {
        for (int x = 0; x < input[y].length(); ++x) {
            if (input[y][x] == '#') {
                grid.insert(Point<N>({ x, y }));
            }
        }
    }

    return grid;
}

template<int N>
void Step(set<Point<N>>& grid)
{
    map<Point<N>, int> n;
    for (auto& p : grid) {
        p.DoNeighbours([&](const Point<N>& a) { ++n[a]; });
    }

    set<Point<N>> newgrid;
    for (auto& ni : n) {
        if (grid.find(ni.first) != grid.end()) {
            if (ni.second == 2 || ni.second == 3) {
                newgrid.insert(ni.first);
            }
        }
        else {
            if (ni.second == 3) {
                newgrid.insert(ni.first);
            }
        }
    }

    grid.swap(newgrid);
}

int main()
{
    vector<string> input;
    string s;
    while (getline(cin, s)) input.push_back(s);

    {
        auto grid = Load<3>(input);
        for (int t = 0; t < 6; ++t) {
            Step(grid);
        }

        cout << "Number of cubes at 6 = " << grid.size() << endl;
    }

    {
        auto grid = Load<4>(input);
        for (int t = 0; t < 6; ++t) {
            Step(grid);
        }

        cout << "Number of cubes at 6 = " << grid.size() << endl;
    }
}
