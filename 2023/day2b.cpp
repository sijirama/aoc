#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
#define show(x) cout << x << endl
#define showLine(x) cout << x

string removeCharacter(string line, char remove);
int solution(string line);
vector<string> customSplit(string str, char separator);
int gameId(string line);

int main() {
    std::fstream File;
    vector<string> question;
    File.open("input/day2.txt", ios::in);
    string line;
    long long answer = 0;
    // string answer = 0;

    while (getline(File, line)) {
        // bool rreturn;
        answer += solution(line);
        // if (rreturn) {
        //     answer += gameId(line);
        // }
        //  show(solution(line));
    }
    show(answer);
}

int solution(string line) {
    // show(line);
    int ans = 0;
    int red = 12, green = 13, blue = 14;
    int cred = 0, cgreen = 0, cblue = 0;

    auto it = find(line.begin(), line.end(), ':');
    int index = distance(line.begin(), it);
    line = line.substr(index + 2, line.length() - 1);
    // Game: has been removed from the list
    line = removeCharacter(line, ',');
    line = removeCharacter(line, ';');
    vector<string> question = customSplit(line, ' ');

    std::map<string, int> colors;
    colors["red"] = 12;
    colors["green"] = 13;
    colors["blue"] = 14;

    for (int i = 1; i < question.size(); i = i + 2) {
        // show(question[i]);
        string color = question[i];
        int figure = stoi(question[i - 1]);
        if (color == "red") {
            if (figure > cred) {
                cred = figure;
                continue;
            }
        } else if (color == "green") {
            if (figure > cgreen) {
                cgreen = figure;
                continue;
            }
        } else if (color == "blue") {
            if (figure > cblue) {
                cblue = figure;
                continue;
            }
        }
    }
    ans = cred * cgreen * cblue;
    // show(ans);
    return ans;
}
string removeCharacter(string line, char remove) {
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == remove) {
            line.erase(i, 1);
            i--;
        }
    }
    return line;
}

vector<string> customSplit(string str, char separator) {
    vector<string> strings = {};
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

int gameId(string line) {
    auto it = find(line.begin(), line.end(), ':');
    int index = distance(line.begin(), it);
    string game = line.substr(0, index);
    string number = game.substr(5, game.length());
    size_t finalNumber = stoll(number);
    return finalNumber;
}
