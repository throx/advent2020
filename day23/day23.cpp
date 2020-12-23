#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

#include "../shared/shared.h"

using namespace std;

//const string INPUT = "389125467"s;
const string INPUT = "952316487"s;

// Runs game, returns position of "1"
list<int>::const_iterator game(list<int>& nums, int turns)
{
    int sz = nums.size();
    vector<list<int>::const_iterator> backref;
    backref.resize(sz + 1);
    for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
        backref[*it] = it;
    }

    for (int t = 0; t < turns; ++t) {
        int cl = nums.front(); nums.pop_front();
        nums.push_back(cl);
        auto ni = nums.end();
        --ni;
        backref[cl] = ni;

        vector<int> pickup;

        pickup.push_back(nums.front()); nums.pop_front();
        pickup.push_back(nums.front()); nums.pop_front();
        pickup.push_back(nums.front()); nums.pop_front();

        cl = cl - 1;
        if (cl < 1) cl = sz;
        while (find(pickup.begin(), pickup.end(), cl) != pickup.end()) {
            cl = cl - 1;
            if (cl < 1) cl = sz;
        }

        auto it = backref[cl];
        for (int i = 0; i < 3; ++i) {
            ++it;
            if (it == nums.end()) it = nums.begin();
            it = nums.insert(it, pickup[i]);
            backref[pickup[i]] = it;
        }
    }

    return backref[1];
}

int main()
{
    list<int> nums;
    for (auto& c : INPUT) {
        nums.push_back(c - '0');
    }

    const list<int> baseline = nums;

    game(nums, 100);

    while (nums.front() != 1) {
        nums.push_front(nums.back()); nums.pop_back();
    }
    nums.pop_front();

    std::cout << "Part 1: ";
    for (auto x : nums) std::cout << x;
    std::cout << endl;

    nums = baseline;
    for (int i = 10; i <= 1000000; ++i) nums.push_back(i);

    auto it = game(nums, 10000000);
    int n1 = *(++it);
    int n2 = *(++it);

    std::cout << "Part 2 = " << n1 << " * " << n2 << " = " << 1i64 * n1 * n2 << endl;
}
