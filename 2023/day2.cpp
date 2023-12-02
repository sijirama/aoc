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
}

string solution(string line) {}
