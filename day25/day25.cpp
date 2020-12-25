#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Thanks Bruce.
__int64 powermod(__int64 base, __int64 exp, __int64 mod)
{
    if (exp == 1) return 0;

    __int64 res = 1;
    base = base % mod;
    while (exp != 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return res;
}

int main()
{
    //__int64 n1 = 5764801;
    //__int64 n2 = 17807724;
    __int64 n1 = 18499292;
    __int64 n2 = 8790390;
    __int64 m = 20201227;
    __int64 b = 7;
   
    // Solving b^x mod m = n1, n2
    //   OH HAI Diffie Hellman!

    __int64 acc = 1;
    __int64 x1 = 0;
    __int64 x2 = 0;
    __int64 x = 0;
    while (x1 == 0 || x2 == 0) {
        if (acc == n1) {
            x1 = x;
        }
        if (acc == n2) {
            x2 = x;
        }
        ++x;
        acc *= b;
        if (acc > m) acc = acc % m;
    }

    cout << "x1 = " << x1 << ", x2 = " << x2 << endl;

    __int64 sol = powermod(7, x1 * x2, m);

    cout << "Soln 1 = " << sol << endl;
}
