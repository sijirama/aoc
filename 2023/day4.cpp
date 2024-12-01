#include <algorithm>
#include <cctype>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
#define show(x) cout << x << endl
#define showLine(x) cout << x
int solution(string line);

int main() {
    std::fstream File;
    vector<string> question;
    File.open("input/day4.txt", ios::in);
    string line;
    int answer = 0;
    // string answer = 0;

    while (getline(File, line)) {
        answer += solution(line);
    }
    cout << "The Final answer is: " << answer << endl;
}

string purgeOffGame(string line) {
    auto it = find(line.begin(), line.end(), ':');
    int index = distance(line.begin(), it);
    line = line.substr(index + 1, line.length());
    return line;
}

string getWinningGame(string line) {
    auto it = find(line.begin(), line.end(), '|');
    int index = distance(line.begin(), it);
    line = line.substr(0, index);
    return line;
}

string getPlayingGame(string line) {
    auto it = find(line.begin(), line.end(), '|');
    int index = distance(line.begin(), it);
    line = line.substr(index + 1, line.length() - 1);
    return line;
}

std::vector<std::string> splitStringBySpace(const std::string &line) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;

    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int solution(string line) {
    line = purgeOffGame(line);
    string winningString = getWinningGame(line);
    string playingString = getPlayingGame(line);

    vector<string> winningCharacters = splitStringBySpace(winningString);
    vector<string> playingCharacters = splitStringBySpace(playingString);

    vector<int> winningNumbers;
    vector<int> playingNumbers;

    for (auto i : winningCharacters) {
        winningNumbers.push_back(stoi(i));
    }

    for (auto i : playingCharacters) {
        playingNumbers.push_back(stoi(i));
    }

    int count = 0;
    int determinant = 0;
    for (int i = 0; i < winningNumbers.size(); i++) {
        for (int j = 0; j < playingNumbers.size(); j++) {
            if (winningNumbers[i] == playingNumbers[j]) {
                ++count;
            }
        }
    }

    if (count == 0) {
        return 0;
    }

    if (count >= 1) {
        determinant = 1;
        count = count - 1;
    }
    while (count > 0) {
        determinant = 2 * determinant;
        count = count - 1;
    }

    return determinant;
}
