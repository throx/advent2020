// day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <regex>
#include <set>

using namespace std;

struct BagCount {
    string desc;
    int count;
};

typedef list<BagCount> BagCounts;
typedef set<string> Bags;

typedef map<string, BagCounts> BagMap;
typedef map<string, Bags> RevBagMap;

const regex BAG_REGEX("(.+?) bags contain (.+)");
const regex CONTENTS_REGEX("(\\d) (.*?) bag");

void DFS(const RevBagMap& map, string start, Bags& b)
{
    auto it = map.find(start);
    if (it == map.end()) return;

    for (auto bagit = it->second.begin(); bagit != it->second.end(); ++bagit) {
        if (b.find(*bagit) == b.end()) {
            b.insert(*bagit);
            DFS(map, *bagit, b);
        }
    }
}

int DFSCount(const BagMap& map, string start)
{
    auto it = map.find(start);
    if (it == map.end()) return 0;

    int c = 1;  // One for this bag.
    for (auto bagit = it->second.begin(); bagit != it->second.end(); ++bagit) {
        c += bagit->count * DFSCount(map, bagit->desc);
    }

    return c;
}

int main()
{
    BagMap bagmap;
    RevBagMap revbagmap;

    // Read input
    while (!cin.eof()) {
        string l;
        getline(cin, l);

        // Parse line
        smatch sm;
        if (!regex_match(l, sm, BAG_REGEX)) {
            cerr << "Bad Line: " << l << endl;
            return 1;
        }

        string desc = sm[1];
        string contents = sm[2];

        BagCounts bags;
        sregex_iterator ri(contents.begin(), contents.end(), CONTENTS_REGEX);
        sregex_iterator rend;
        while (ri != rend) {
            smatch sm2 = *ri;
            int c = stoi(sm2[1]);
            string d = sm2[2];

            // Update direct map
            BagCount bc{ d, c };
            bags.push_back(bc);

            // Update revmap too
            revbagmap[d].insert(desc);
            ++ri;
        }

        bagmap[desc] = bags;
    }

    Bags soln1;
    DFS(revbagmap, "shiny gold"s, soln1);

    cout << "Solution 1:" << endl;
    for (auto s : soln1) {
        cout << "  " << s << endl;
    }
    cout << " Count = " << soln1.size() << endl;
    cout << endl;

    cout << "Solution 2: " << DFSCount(bagmap, "shiny gold"s) - 1 << endl;

    return 0;
}
