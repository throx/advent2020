#include <iostream>
#include <map>
#include <vector>

using namespace std;

const vector<int> INIT({ 1,12,0,20,8,16 });
//const vector<int> INIT({ 0,3,6 });
const int LIMIT = 30000000;
//const int LIMIT = 2020;

int main()
{
    map<int, int> lastseen;

    int t = 0;
    int x = 0;
    for (auto i : INIT) {
        if (t != 0) lastseen[x] = t;
        ++t;
        x = i;
        //cout << x << endl;
    }

    while (t < LIMIT) {
        auto it = lastseen.find(x);
        int v;
        if (it == lastseen.end()) {
            v = 0;
        }
        else {
            v = t - it->second;
        }

        lastseen[x] = t;
        ++t;
        x = v;
        //cout << x << endl;
    }

    cout << "The Number Spoken at " << LIMIT << " is " << x << endl;
}
