// day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
int main()
{
    vector<__int64> nums;

    while (!cin.eof()) {
        __int64 num;
        cin >> num;
        nums.push_back(num);
    }

    int preamble;
    if (nums.size() > 100) {
        preamble = 25;
    }
    else {
        preamble = 5;
    }

    __int64 soln1 = 0;
    for (int pos = preamble; pos < nums.size(); ++pos) {

        bool found = false;
        // Does this number have a sum in previous 25?
        for (int n1 = 0; !found && n1 < preamble - 1; ++n1) {
            for (int n2 = n1 + 1; !found && n2 < preamble; ++n2) {
                if (nums[pos - n1 - 1] + nums[pos - n2 - 1] == nums[pos]) {
                    found = true;
                    cout << nums[pos] << " = " << nums[pos - n1 - 1] << " + " << nums[pos - n2 - 1] << endl;
                }
            }
        }

        if (!found) {
            soln1 = nums[pos];
            break;
        }

    }

    if (soln1 == 0) return 1;
    cout << "Soln 1: " << soln1 << endl;

    __int64 soln2 = 0;

    for (int pos = 0; pos < nums.size(); ++pos) {
        __int64 sum = 0;
        int x;
        for (x = pos; x < nums.size() && sum < soln1; ++x) {
            sum += nums[x];
        }

        if (sum == soln1) {
            auto minmax = minmax_element(&nums[pos], &nums[x]);
            soln2 = *minmax.first + *minmax.second;
            break;
        }
    }

    cout << "Soln 2: " << soln2 << endl;
}
