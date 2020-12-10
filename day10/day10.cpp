#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> jolts;

    // Power output is zero
    jolts.push_back(0);

    while (!cin.eof()) {
        int j;
        cin >> j;
        jolts.push_back(j);
    }

    // Sort the adapters so we can just run from lowest to highest and look
    // at the differences.
    sort(jolts.begin(), jolts.end());

    // Last adapter is max + 3
    jolts.push_back(jolts.back() + 3);

    // Just create an array of all the diffs.  Maximum is size() if everything is
    // one apart.  Sort of assuming input is well formed, and unique.
    vector<int> diffs;
    diffs.resize(jolts.size());
    for (int x = 0; x < jolts.size() - 1; ++x) {
        ++(diffs[jolts[x + 1] - jolts[x]]);
    }

    cout << "1 Jolt = " << diffs[1] << endl;
    cout << "3 Jolt = " << diffs[3] << endl;
    cout << "Soln1 = " << diffs[1] * diffs[3] << endl;

    // Now to count the ways, we just run from the top, counting each way we can go
    // from there, and adding the number of ways we got to the current item to each
    // valid next item.

    vector<__int64> ways;
    ways.resize(jolts.size());
    ways[0] = 1;

    for (int x = 0; x < jolts.size() - 1; ++x) {

        // At most 3 ahead (all single jolt jumps)
        if (jolts[x + 1] - jolts[x] < 4) ways[x + 1] += ways[x];
        if (x < jolts.size() - 2 && jolts[x + 2] - jolts[x] < 4) ways[x + 2] += ways[x];
        if (x < jolts.size() - 3 && jolts[x + 3] - jolts[x] < 4) ways[x + 3] += ways[x];
    }

    // Total is number of ways to get to last item.
    cout << "Soln2 = " << ways.back() << endl;
}
