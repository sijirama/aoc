#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
#define show(x) cout << x << endl

string solution(string line);
int main() {
    std::fstream File;
    vector<string> question;
    File.open("input/day1.txt", ios::in);

    string line;
    int answer = 0;

    while (getline(File, line)) {
        answer += stoi(solution(line));
        // show(solution(line));
    }

    File.close();
    show(answer);
    return answer;
}

bool isCharacterDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

string solution(string line) {
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
