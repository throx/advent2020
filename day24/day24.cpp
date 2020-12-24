#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

#include "../shared/Point.h"

using namespace std;

const map<string, Point2> DIRS = {
    {"w", Point2({-1, 0})},
    {"e", Point2({1, 0})},
    {"nw", Point2({-1, -1})},
    {"ne", Point2({0, -1})},
    {"sw", Point2({0, 1})},
    {"se", Point2({1, 1})}
};

void Dump(const map<Point2, bool>& world) {
    cout << endl;
    if (world.empty())
    {
        return;
    }

    auto xlimits = minmax_element(world.begin(), world.end(), [](auto& a, auto& b) { return a.first[0] < b.first[0]; });
    auto ylimits = minmax_element(world.begin(), world.end(), [](auto& a, auto& b) { return a.first[1] < b.first[1]; });

    for (int y = ylimits.first->first[1]; y <= ylimits.second->first[1]; ++y) {
        cout << string(ylimits.second->first[1] - y, ' ');
        for (int x = xlimits.first->first[0]; x <= xlimits.second->first[0]; ++x) {
            auto it = world.find(Point2({ x, y }));
            if (it != world.end()) {
                cout << "*";
            }
            else {
                cout << " ";
            }

            if (-0.5*y + x == 0) {
                cout << "|";
            }
            else if (y == 0) {
                cout << "-";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    vector<vector<Point2>> input;

    string s;
    while (getline(cin, s)) {
        input.push_back({});
        while (!s.empty()) {
            for (auto& p : DIRS) {
                if (s.substr(0, p.first.length()) == p.first) {
                    input.back().push_back(p.second);
                    s = s.substr(p.first.length());
                    break;
                }
            }
        }
    }

    map<Point2, bool> world;
    for (auto& l : input) {
        Point2 pos;
        for (auto& p : l) {
            pos += p;
        }
        world[pos] = !world[pos];
    }

    int sol1 = count_if(world.begin(), world.end(), [](auto& x) { return x.second; });
    cout << "Black count = " << sol1 << endl;

    //world.clear();
    //world[Point2({ 0, 0 })] = true;
    //world[Point2({ 1, 0 })] = true;
    //world[Point2({ 2, 0 })] = true;
    //Dump(world);

    for (int day = 0; day < 100; ++day) {
        map<Point2, int> counts;
        map<Point2, bool> newworld;

        // Make counts
        for (auto& p : world) {
            if (p.second) {
                for (auto& d : DIRS) {
                    ++counts[p.first + d.second];
                }
            }
        }

        for (auto& c : counts) {
            if (world[c.first]) {

                // Argh!  So annoyed.  Had it right in 18 minutes, except for the && being an ||.
                // Took an hour to debug.
                if ((c.second > 0) && (c.second < 3)) {
                    newworld[c.first] = true;
                }
            }
            else {
                if (c.second == 2) {
                    newworld[c.first] = true;
                }
            }
        }

        world.swap(newworld);

        //Dump(world);
        //int c = count_if(world.begin(), world.end(), [](auto& x) { return x.second; });
        //cout << "Iter " << day + 1 << " = " << c << endl;
    }

    int sol2 = count_if(world.begin(), world.end(), [](auto& x) { return x.second; });
    cout << "Black count 2 = " << sol2 << endl;

}
