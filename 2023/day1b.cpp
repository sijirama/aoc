#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
// #include <vcruntime.h>
#include <vector>

using namespace std;
#define show(x) cout << x << endl
#define showIn(x) cout << x
string solution(string line);
int getNumber(string number);

int main() {
    std::fstream File;
    vector<string> question;
    File.open("input/day1.txt", ios::in);

    string line;
    int answer = 0;

    while (getline(File, line)) {
        answer += stoi(solution(line));
    }

    File.close();
    show(answer);
    return answer;
}

int getNumber(string number) {
    vector<string> numbers = {"one", "two",   "three", "four", "five",
                              "six", "seven", "eight", "nine"};
    auto iter = find(numbers.begin(), numbers.end(), number);
    int index = distance(numbers.begin(), iter);
    return index + 1;
}

bool isCharacterDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

bool vectorHas(string target, vector<string> values) {
    auto iter = find(values.begin(), values.end(), target);
    if (iter != values.end()) {
        return true;
    }
    return false;
}

string realSolution(string line) {
    vector<string> numbersToReplace = {"one", "two",   "three", "four", "five",
                                       "six", "seven", "eight", "nine"};
    vector<string> replacements = {"on1e", "tw2o",  "th3ee", "fo4r", "fi5e",
                                   "s6x",  "se7en", "ei8ht", "ni9e"};

    for (size_t i = 0; i < numbersToReplace.size(); ++i) {
        size_t pos = line.find(numbersToReplace[i]);

        while (pos != std::string::npos) {
            line.replace(pos, numbersToReplace[i].length(), replacements[i]);
            pos =
                line.find(numbersToReplace[i], pos + replacements[i].length());
        }
    }

    return line;
}

string solution(string line) {
    string realString = realSolution(line);
    line = realString;
    string left, right;

    for (int i = 0; i < line.length(); i++) {
        if (isCharacterDigit(line[i])) {
            left = line[i];
            break;
        }
    }

    for (int i = line.length(); i > -1; i--) {
        if (isCharacterDigit(line[i])) {
            right = line[i];
            break;
        }
    }
    return left + right;
}
