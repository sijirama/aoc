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
    int lines = 0;
    while (getline(myFile, line)) {
        games.push_back(line);
        ++lines;
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

    int opponent = 0, me = 2;
    for (int i = 0; i < games.size(); ++i) {
        string game = games[i];
        int opp = opponentMap[game[opponent]];
        int mygame = myMap[game[me]];
        int score = 0;

        if (mygame > opp) {
            score += mygame + 6;
        } else if (mygame == opp) {
            score += mygame + 3;
        } else if (mygame < opp) {
            score += mygame + 0;
        } else {
            continue;
        }

        if (i > 100 && i < 150 && i % 2 == 0) {
            cout << "My Pick is: " << mygame << " and the opp pick is: " << opp
                 << " so the final answer is: " << score << endl;
        }

        FINAL_SCORE += score;
    }

    std::cout << lines << '\n';
    cout << FINAL_SCORE;
}

// int main(int argc, char *argv[]) {
//     std::string input = "input/day2.txt";
//     if (argc > 1) {
//         input = argv[1];
//     }
//
//     std::string line;
//     std::fstream file(input);
//
//     int score = 0;
//     int lines = 0;
//     while (std::getline(file, line)) {
//         // Account for CRLF if required
//         // line.erase(std::remove_if(std::begin(line), std::end(line),[](auto
//         // c) { return !isprint(c); }), std::end(line));
//         score += line[2] - 'X' + 1;
//         int delta = (line[2] - line[0] - 23 + 3) % 3;
//         if (delta == 1) {
//             score += 6;
//         } else if (delta == 0) {
//             score += 3;
//         }
//         ++lines;
//     }
//     std::cout << score << '\n';
//     std::cout << lines << '\n';
//     return 0;
// }
