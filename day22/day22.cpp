#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <set>

#include "../shared/shared.h"

using namespace std;

typedef list<int> IntList;

int playrecursivehand(vector<IntList>& hands);

int playrecursivehand(vector<IntList>& hands, set<vector<IntList>>& history)
{
    while (hands[0].size() > 0 && hands[1].size() > 0) {

        //cout << "-- Round -- " << endl;
        //cout << "Player 1's deck: "; Dump(hands[0]); cout << endl;
        //cout << "Player 2's deck: "; Dump(hands[1]); cout << endl;

        // If hands are in the history, player 1 wins
        if (history.find(hands) != history.end()) {
            //cout << "Player 1 wins the round by history" << endl << endl;
            return 0;
        }

        // Add hands to history
        history.insert(hands);

        // Take top card
        int c0 = hands[0].front();
        hands[0].pop_front();
        int c1 = hands[1].front();
        hands[1].pop_front();

        //cout << "Player 1 plays: " << c0 << endl;
        //cout << "Player 2 plays: " << c1 << endl;

        int winner;

        if (c0 <= hands[0].size() && c1 <= hands[1].size()) {
            //cout << "Going recursive!" << endl << endl;

            vector<IntList> handcopy = hands;
            handcopy[0].resize(c0);
            handcopy[1].resize(c1);
            winner = playrecursivehand(handcopy);   // Recursive game has new history?
        }
        else {
            winner = (c0 > c1) ? 0 : 1;

            //cout << "Player " << winner + 1 << " wins the round directly" << endl << endl;
        }

        if (winner == 0) {
            hands[winner].push_back(c0);
            hands[winner].push_back(c1);
        }
        else {
            hands[winner].push_back(c1);
            hands[winner].push_back(c0);
        }
    }

    //cout << "Player " << ((hands[0].size() > 0) ? 1 : 2) << " wins the game!" << endl << endl;

    if (hands[0].size() > 0)
        return 0;

    return 1;
}

int playrecursivehand(vector<IntList>& hands)
{
    set<vector<IntList>> history;
    return playrecursivehand(hands, history);
}

int main()
{
    vector<IntList> hands(2, IntList());

    string s;
    getline(cin, s);    // Player 1
    while (!cin.eof()) {
        getline(cin, s);
        if (s.empty()) break;
        hands[0].push_back(stoi(s));
    }
    getline(cin, s);    // Player 2
    while (!cin.eof()) {
        getline(cin, s);
        if (s.empty()) break;
        hands[1].push_back(stoi(s));
    }

    const vector<IntList> baseline = hands;

    while (!hands[0].empty() && !hands[1].empty()) {
        int c0 = hands[0].front();
        hands[0].pop_front();
        int c1 = hands[1].front();
        hands[1].pop_front();
        if (c0 > c1) {
            hands[0].push_back(c0);
            hands[0].push_back(c1);
        }
        else {
            hands[1].push_back(c1);
            hands[1].push_back(c0);
        }
    }

    int winner = 0;
    if (hands[0].empty()) winner = 1;

    cout << "Part 1 Winner = Player " << winner + 1 << ": ";
    Dump(hands[winner]);
    cout << endl;

    int p = hands[winner].size();
    int part1 = 0;
    for (auto x : hands[winner]) {
        part1 += (p * x);
        --p;
    }
    cout << "Part 1 = " << part1 << endl;

    hands = baseline;
    winner = playrecursivehand(hands);

    cout << "Part 2 Winner = Player " << winner + 1 << ": ";
    Dump(hands[winner]);
    cout << endl;

    p = hands[winner].size();
    int part2 = 0;
    for (auto x : hands[winner]) {
        part2 += (p * x);
        --p;
    }
    cout << "Part 2 = " << part2 << endl;

}
