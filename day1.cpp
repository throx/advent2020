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
    
    /*
    for(auto x : nums) {
        for (auto y : nums) {
            if (x + y == 2020) {
                cout << x << " * " << y << " = " << x * y << endl;
                return 0;
            }
        }
    }
    */
    
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
    
    return 1;
}