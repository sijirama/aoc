#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define show(x) cout << x << endl

int getTotal(vector<int> vect) {
    int ans = 0;
    for (int i : vect) {
        ans += i;
    }
    return ans;
}

int main() {
    fstream File;
    vector<vector<int>> question;
    File.open("input/day1.txt", ios::in);

    string line;
    vector<int> lineVect;

    while (getline(File, line)) {
        if (line == "") {
            question.push_back(lineVect);
            lineVect.clear();
            continue;
        }
        lineVect.push_back(stoi(line));
    }
    File.close();

    vector<int> elfs;
    for (int i = 0; i < question.size(); ++i) {
        elfs.emplace_back(getTotal(question[i]));
    }

    int index = 0;
    int value = elfs[0];
    for (int i = 1; i < elfs.size(); ++i) {
        if (elfs[i] > value) {
            index = i;
            value = elfs[i];
        }
    }

    show(value); // part 1

    sort(elfs.begin(), elfs.end());
    int finalAns =
        elfs[elfs.size() - 1] + elfs[elfs.size() - 2] + elfs[elfs.size() - 3];
    show(finalAns);
}
