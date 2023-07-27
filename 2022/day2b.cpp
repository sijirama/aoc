#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    int FINAL_SCORE = 0;
    fstream myFile;
    vector<string> games;
    myFile.open("input/day2.txt", ios::in);

    string line;
    while (getline(myFile, line)) {
        games.push_back(line);
        line.clear();
    }

    // map of the games and the values
    std::map<char, int> opponentMap;
    opponentMap['A'] = 1;
    opponentMap['B'] = 2;
    opponentMap['C'] = 3;

    std::map<char, int> myMap;
    myMap['X'] = 1;
    myMap['Y'] = 2;
    myMap['Z'] = 3;

    // Rock = 1
    // Paper = 2
    // Scissors = 3
    // Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock
    // 1 > 3, 3 > 2, 2 > 1 // that means if the diff between my game andthe opps
    // game is -2 or 1, then i won

    int opponent = 0, me = 2;
    for (int i = 0; i < games.size(); ++i) {
        string game = games[i];
        int opp = opponentMap[game[opponent]];
        int mygame = myMap[game[me]];
        int score = 0;

        if (mygame == 2) { // its a draw
            mygame = opp;
        } else if (mygame == 1) { // i have to lose
            if (opp == 1) {
                mygame = 3;
            } else if (opp == 2) {
                mygame = 1;
            } else if (opp == 3) {
                mygame = 2;
            }
        } else if (mygame == 3) { // i have to win
            if (opp == 1)
                mygame = 2;
            if (opp == 2)
                mygame = 3;
            if (opp == 3)
                mygame = 1;
        }

        if ((mygame - opp) == -2 || (mygame - opp) == 1) {
            score += mygame + 6;
        } else if (mygame == opp) {
            score += mygame + 3;
        } else {
            score += mygame + 0;
        }

        FINAL_SCORE += score;
    }

    cout << FINAL_SCORE;
}
