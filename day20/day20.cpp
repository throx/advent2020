#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

const int SZ = 10;

string reverse(const string& in) {
    string out(in.length(), ' ');
    for (int i = 0; i < in.length(); ++i) {
        out[i] = in[in.length() - i - 1];
    }
    return out;
}

void RotateCCW(vector<string>& data) {
    cout << endl;
    int sz = data.size();
    vector<string> newdata(sz, string(sz, 0));
    for (int y = 0; y < sz; ++y) {
        for (int x = 0; x < sz; ++x) {
            newdata[y][x] = data[x][sz - y - 1];
        }
    }
    data.swap(newdata);
}

void Flip(vector<string>& data) {
    int sz = data.size();
    vector<string> newdata(sz, string(sz, 0));
    for (int y = 0; y < sz; ++y) {
        newdata[y] = data[sz - y - 1];
    }
    data.swap(newdata);
}

struct Tile {
    Tile(int num, const vector<string>& data) : num(num), m_data(data) {}

    vector<string> Edges() {
        vector<string> result;
        result.push_back(m_data[0]);
        result.push_back(m_data[SZ - 1]);

        string l, r;
        l.resize(SZ);
        r.resize(SZ);
        for (int i = 0; i < SZ; ++i) {
            l[i] = m_data[i][0];
            r[i] = m_data[i][SZ - 1];
        }
        result.push_back(l);
        result.push_back(r);
        return result;
    }

    string GetBottom() {
        return m_data[SZ - 1];
    }

    string GetRight() {
        string r(SZ, ' ');
        for (int i = 0; i < SZ; ++i) {
            r[i] = m_data[i][SZ - 1];
        }
        return r;
    }

    void MakeTop(string top) {
        for (int i = 0; i < 4; ++i) {
            if (m_data[0] == top) return;
            RotateCCW();
        }
        Flip();
        for (int i = 0; i < 4; ++i) {
            if (m_data[0] == top) return;
            RotateCCW();
        }
        throw "Bad";
    }

    void RotateCCW() {
        ::RotateCCW(m_data);
    }

    void Flip() {
        ::Flip(m_data);
    }

    int num;
    vector<string> m_data;
};

int main()
{
    vector<Tile> tiles;

    while (!cin.eof()) {
        string s;
        getline(cin, s);
        int num = stoi(s.substr(5));
        vector<string> t;
        for (int i = 0; i < SZ; ++i) {
            getline(cin, s);
            t.push_back(s);
        }

        tiles.push_back(Tile(num, t));
        getline(cin, s);
    }

    map<string, set<int>> edges;
    for (int i = 0; i < tiles.size(); ++i) {
        auto e = tiles[i].Edges();
        for (auto& edge : e) {
            string r = reverse(edge);
            edges[min(r, edge)].insert(i);
        }
    }

    map<int, int> candidates;
    for (auto& e : edges) {
        if (e.second.size() == 1) {
            int can = *e.second.begin();
            ++candidates[can];
        }
    }

    __int64 p = 1;
    int a_can = 0;
    for (auto& c : candidates) {
        if (c.second == 2) {
            a_can = c.first;
            p *= tiles[c.first].num;
        }
    }

    cout << "Product = " << p << endl;

    // Now I have to stitch the tiles together...
    // ... crap

    int mapsize = sqrt(tiles.size());
    vector<vector<int>> tilemap(mapsize, vector<int>(mapsize, 0));

    tilemap[0][0] = a_can;

    // Rotate TL tile to line up matches
    while (true) {
        tiles[a_can].RotateCCW();

        string edge = tiles[a_can].GetRight();
        string edge_min = min(edge, reverse(edge));
        if (edges[edge_min].size() != 2) continue;

        edge = tiles[a_can].GetBottom();
        edge_min = min(edge, reverse(edge));
        if (edges[edge_min].size() != 2) continue;

        break;
    }

    // Fill in the top row
    for (int x = 1; x < mapsize; ++x) {
        int num = tilemap[0][x - 1];
        string edge = tiles[num].GetRight();
        string edge_min = min(edge, reverse(edge));
        auto& matches = edges[edge_min];
        int next = 0;
        for (auto& m : matches) {
            if (m != num) {
                next = m;
                break;
            }
        }
        tilemap[0][x] = next;
        tiles[next].MakeTop(reverse(edge));
        tiles[next].RotateCCW();
    }

    // Fill down
    for (int y = 1; y < mapsize; ++y) {
        for (int x = 0; x < mapsize; ++x) {
            int num = tilemap[y - 1][x];
            string edge = tiles[num].GetBottom();
            string edge_min = min(edge, reverse(edge));
            auto& matches = edges[edge_min];
            int next = 0;
            for (auto& m : matches) {
                if (m != num) {
                    next = m;
                    break;
                }
            }
            tilemap[y][x] = next;
            tiles[next].MakeTop(edge);
        }
    }

    // Dump tiles
    for (auto& r : tilemap) {
        for (auto& i : r) {
            cout << tiles[i].num << ' ';
        }
        cout << endl;
    }

    for (int y = 0; y < mapsize; ++y) {
        for (int y1 = 0; y1 < SZ; ++y1) {
            for (int x = 0; x < mapsize; ++x) {
            auto& tile = tiles[tilemap[y][x]];
                for (int x1 = 0; x1 < SZ; ++x1) {
                    cout << tile.m_data[y1][x1];
                }
                cout << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }


    // Generate map
    int msz = mapsize * (SZ - 2);
    vector<string> seamap(msz, string(msz, ' '));
    for (int y = 0; y < mapsize; ++y) {
        for (int x = 0; x < mapsize; ++x) {
            auto& tile = tiles[tilemap[y][x]];
            for (int y1 = 0; y1 < (SZ - 2); ++y1) {
                for (int x1 = 0; x1 < (SZ - 2); ++x1) {
                    seamap[y * (SZ - 2) + y1][x * (SZ - 2) + x1] = tile.m_data[y1+1][x1+1];
                }
            }
        }
    }

    for (auto& s : seamap) cout << s << endl;
    cout << endl;

    const vector<string> monster({
        "                  # "s,
        "#    ##    ##    ###"s,
        " #  #  #  #  #  #   "s,
        });

    const int mx = monster[0].length();
    const int my = monster.size();

    for (int flip = 0; flip < 2; ++flip) {
        for (int rot = 0; rot < 4; ++rot) {
            for (int y = 0; y <= msz - my; ++y) {
                for (int x = 0; x <= msz - mx; ++x) {
                    bool found = true;

                    for (int y1 = 0; y1 < my && found; ++y1) {
                        for (int x1 = 0; x1 < mx && found; ++x1) {
                            if (monster[y1][x1] == '#' && seamap[y + y1][x + x1] == '.') {
                                found = false;
                            }
                        }
                    }

                    if (found) {
                        // block out monster
                        for (int y1 = 0; y1 < my && found; ++y1) {
                            for (int x1 = 0; x1 < mx && found; ++x1) {
                                if (monster[y1][x1] == '#') {
                                    seamap[y + y1][x + x1] = 'O';
                                }
                            }
                        }
                    }
                }
            }
            ::RotateCCW(seamap);
        }
        ::Flip(seamap);
    }

    for (auto& s : seamap) cout << s << endl;
    cout << endl;

    int sum = 0;
    for (auto& s : seamap) {
        for (auto& c : s) {
            if (c == '#') ++sum;
        }
    }

    cout << "Roughness = " << sum << endl;
}
