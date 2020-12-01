#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> nums;
    
    while (!cin.eof()) {
        int x;
        cin >> x;
        nums.push_back(x);
    }
    
    for(auto x : nums) {
        for (auto y : nums) {
            if (x + y == 2020) {
                cout << x << " * " << y << " = " << x * y << endl;
                goto nextloop;
            }
        }
    }
    cout << "No two-way sum to 2020!" << endl;
    return 1;

    nextloop:
    
    for(auto x : nums) {
        for (auto y : nums) {
            for (auto z : nums) {
                if (x + y + z == 2020) {
                    cout << x << " * " << y << " * " << z << " = " << x * y * z << endl;
                    return 0;
                }
            }
        }
    }
    
    cout << "No three-way sum to 2020!" << endl;
    return 1;
}