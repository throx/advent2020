// day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../shared/shared.h"
#include <set>

using namespace std;

int main()
{
    CPU cpu;

    while (!cin.eof()) {
        string s;
        getline(cin, s);
        cpu.AddInstruction(s);
    }

    CPU checkpt(cpu);

    set<__int64> locs;

    while (true) {
        locs.insert(cpu.GetIP());
        if (cpu.Step()) break;
        if (locs.find(cpu.GetIP()) != locs.end()) break;
    }

    cout << "Part 1: ACC = " << cpu.GetAcc() << endl;

    for (__int64 x = 0; x < checkpt.GetIntSize(); ++x) {
        cpu = checkpt;

        if (cpu.GetOp(x) == "nop"s) {
            cpu.SetOp(x, "jmp"s);
        }
        else if (cpu.GetOp(x) == "jmp"s) {
            cpu.SetOp(x, "nop"s);
        }
        else {
            continue;
        }

        bool term = false;
        locs.clear();
        while (true) {
            locs.insert(cpu.GetIP());
            if (cpu.Step()) {
                term = true;
                break;
            }
            if (locs.find(cpu.GetIP()) != locs.end()) break;
        }

        if (term) {
            cout << "Part 2: ACC = " << cpu.GetAcc() << endl;
            break;
        }
    }
    


}
