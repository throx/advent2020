#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

// Because they are all size 10!
const int SZ = 10;

// Reverse a string
string reverse(const string& in) {
    string out(in.length(), ' ');
    for (int i = 0; i < in.length(); ++i) {
        out[i] = in[in.length() - i - 1];
    }
    return out;
}

// Rotate a square counterclockwise
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

// Flip a square top to bottom
void Flip(vector<string>& data) {
    int sz = data.size();
    vector<string> newdata(sz, string(sz, 0));
    for (int y = 0; y < sz; ++y) {
        newdata[y] = data[sz - y - 1];
    }
    data.swap(newdata);
}

// Structure representing a Tile of info
// Contains a tile number, and some data
struct Tile {
    Tile(int num, const vector<string>& data) : num(num), m_data(data) {}

    // Return the 4 edges as strings
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

    // Get the bottom edge
    string GetBottom() {
        return m_data[SZ - 1];
    }

    // Get the right edge
    string GetRight() {
        string r(SZ, ' ');
        for (int i = 0; i < SZ; ++i) {
            r[i] = m_data[i][SZ - 1];
        }
        return r;
    }

    // Rotate/Flip until the top matches the string
    // specified.  If it can't be done, BOOM!
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

    // Rotate tile Counterclockwise
    void RotateCCW() {
        ::RotateCCW(m_data);
    }

    // Flip a tile top to bottom
    void Flip() {
        ::Flip(m_data);
    }

    int num;
    vector<string> m_data;
};

// THE MAIN FUNCTION!!!
int main()
{
    vector<Tile> tiles;

    // Read in all the tiles
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

    // Create a map of each edge to the tiles that contain it.
    // Reversed edges are dealt with by using the minimum of an
    // edge and its reversed representation.
    map<string, set<int>> edges;
    for (int i = 0; i < tiles.size(); ++i) {
        auto e = tiles[i].Edges();
        for (auto& edge : e) {
            string r = reverse(edge);
            edges[min(r, edge)].insert(i);
        }
    }

    // File the tiles with edges seen only once.
    map<int, int> candidates;
    for (auto& e : edges) {
        if (e.second.size() == 1) {
            int can = *e.second.begin();
            ++candidates[can];
        }
    }

    // The corner candidates are the tiles which have
    // two of their edges seen only once.
    __int64 p = 1;
    int a_can = 0;
    for (auto& c : candidates) {
        if (c.second == 2) {
            a_can = c.first;
            p *= tiles[c.first].num;
        }
    }

    // Part 1 done
    cout << "Product = " << p << endl;

    // Now I have to stitch the tiles together...
    // ... crap

    // Create a 2D array (using vector) for the tiles, as we find them
    int mapsize = sqrt(tiles.size());
    vector<vector<int>> tilemap(mapsize, vector<int>(mapsize, 0));

    // Start with one of the corner candidates, from above.
    tilemap[0][0] = a_can;

    // Rotate TL tile to line up matches on the right and bottom by
    // rotating until they have the edges with 2 tiles.
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

    // Fill in the top row by matching each right edge in turn
    for (int x = 1; x < mapsize; ++x) {
        int num = tilemap[0][x - 1];
        string edge = tiles[num].GetRight();
        string edge_min = min(edge, reverse(edge));
        auto& matches = edges[edge_min];

        // Have to find the match that isn't the one already placed
        int next = 0;
        for (auto& m : matches) {
            if (m != num) {
                next = m;
                break;
            }
        }
        tilemap[0][x] = next;

        // Make the matched edge the top (reverse, because tiles match that way)
        tiles[next].MakeTop(reverse(edge));

        // Rotate it CCW, so the top is now on the left.
        tiles[next].RotateCCW();
    }

    // Fill down all columns, using same logic as above
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

    // Dump tiles ids, to show our work
    for (auto& r : tilemap) {
        for (auto& i : r) {
            cout << tiles[i].num << ' ';
        }
        cout << endl;
    }

    // Dump the contents of the tiles
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

    // Dump the actual map now, because I like dumping things
    for (auto& s : seamap) cout << s << endl;
    cout << endl;

    // A SEA MONSTER.  OMG!
    const vector<string> monster({
        "                  # "s,
        "#    ##    ##    ###"s,
        " #  #  #  #  #  #   "s,
        });

    const int mx = monster[0].length();
    const int my = monster.size();

    // Two flips
    for (int flip = 0; flip < 2; ++flip) {

        // Four rotations to check every permutation of a map.
        for (int rot = 0; rot < 4; ++rot) {

            // Loop through current permutation
            for (int y = 0; y <= msz - my; ++y) {
                for (int x = 0; x <= msz - mx; ++x) {

                    // Look for monster pattern
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

    // Show where we found the monsters
    for (auto& s : seamap) cout << s << endl;
    cout << endl;

    // Count the bits that aren't monsters
    int sum = 0;
    for (auto& s : seamap) {
        for (auto& c : s) {
            if (c == '#') ++sum;
        }
    }

    cout << "Roughness = " << sum << endl;
}
