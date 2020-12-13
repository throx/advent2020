#include <iostream>
#include <string>
#include <vector>
#include "../shared/chineseremainder.h"

using namespace std;

int main()
{
    vector<int> buses;

    string s;
    getline(cin, s);
    int start = stoi(s);

    while (getline(cin, s, ','))
    {
        if (s != "x"s) {
            buses.push_back(stoi(s));
        }
        else {
            buses.push_back(0);
        }
    }

    {
        int t = start;
        int bus = 0;
        while (!bus) {
            for (auto x : buses) {
                if (x != 0 && t % x == 0) {
                    bus = x;
                    break;
                }
            }
            if (!bus) ++t;
        }

        cout << "Bus = " << bus << " Time = " << t << " Delay = " << (t - start) << " Product = " << (t - start) * bus << endl;
    }

    {
        // This could be better.  It assumes primes, and there's no reason to dumb-old increment when you could play with
        // modulo arithmetic.
        __int64 t = start;
        __int64 inc = 1;
        for (int i = 0; i < buses.size(); ++i) {
            if (buses[i] == 0) continue;
            __int64 x = buses[i];
            while ((t+i) % x != 0) {
                t += inc;
            }
            inc *= x;
        }

        // Check
        for (int i = 0; i < buses.size(); ++i) {
            cout << " Time " << t + i;
            if (buses[i] != 0) {
                cout << " Bus = " << buses[i] << " Mod = " << (t + i) % buses[i];
            }
            cout << endl;
        }

        cout << "Magic time = " << t << endl;
    }

    {
        // Better way, with Chinese Remainder
        vector<__int64> n, a;
        for (int i = 0; i < buses.size(); ++i)
        {
            if (buses[i] == 0) continue;
            n.push_back(buses[i]);
            a.push_back(buses[i]-i);
        }
        __int64 t = chineseRemainder(n, a);
        cout << "Magic time = " << t << endl;
    }
}
