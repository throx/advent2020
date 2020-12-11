#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

int NumOcc(const vector<string>& seats, int x, int y)
{
    int maxx = seats[0].length();
    int maxy = seats.size();
    int numocc = 0;

    for (int x1 = max(0, x - 1); x1 < min(maxx, x + 2); ++x1) {
        for (int y1 = max(0, y - 1); y1 < min(maxy, y + 2); ++y1) {
            if (x != x1 || y != y1) {
                if (seats[y1][x1] == '#') {
                    ++numocc;
                }
            }
        }
    }

    return numocc;
}

int NumOccSeen(const vector<string>& seats, int x, int y)
{
    int maxx = seats[0].length();
    int maxy = seats.size();
    int numocc = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx != 0 || dy != 0) {

                int x1 = x + dx;
                int y1 = y + dy;

                while (x1 >= 0 && x1 < maxx && y1 >= 0 && y1 < maxy) {
                    if (seats[y1][x1] == '#') {
                        ++numocc;
                        break;
                    }
                    else if (seats[y1][x1] == 'L') {
                        break;
                    }

                    x1 += dx;
                    y1 += dy;
                }

            }
        }
    }

    return numocc;
}

void DoRound(vector<string>& seats, int maxocc = 4, int occfn(const vector<string>&, int, int) = NumOcc)
{
    int maxx = seats[0].length();
    int maxy = seats.size();

    vector<string> newseats;
    for (int y = 0; y < maxy; ++y) {
        string s;
        for (int x = 0; x < maxx; ++x) {

            if (seats[y][x] != '.') {
                int n = occfn(seats, x, y);
                if (n == 0) {
                    s.push_back('#');
                }
                else if (n >= maxocc) {
                    s.push_back('L');
                }
                else {
                    s.push_back(seats[y][x]);
                }
            }
            else {
                s.push_back('.');
            }
        }
        newseats.push_back(s);
    }

    seats = newseats;
}

void Dump(const vector<string>& seats)
{
    for (auto v : seats) {
        cout << v << endl;
    }
    cout << endl;
}

int Occupancy(const vector<string>& seats)
{
    int occ = 0;
    for (auto s : seats) {
        for (auto c : s) {
            if (c == '#') ++occ;
        }
    }

    return occ;
}

int main()
{
    vector<string> seats;
    string s;
    while (getline(cin, s)) {
        seats.push_back(s);
    }

    auto base = seats;

    vector<string> prev;
    int rounds = 0;
    while (prev != seats) {
        prev = seats;
        DoRound(seats);
        ++rounds;
        //Dump(seats);
    }

    cout << "Rounds to stable = " << rounds - 1 << endl;
    cout << "Occupancy = " << Occupancy(seats) << endl << endl;

    seats = base;
    rounds = 0;
    while (prev != seats) {
        prev = seats;
        DoRound(seats, 5, NumOccSeen);
        ++rounds;
        //Dump(seats);
    }

    cout << "Rounds to stable = " << rounds - 1 << endl;
    cout << "Occupancy = " << Occupancy(seats) << endl;
}
